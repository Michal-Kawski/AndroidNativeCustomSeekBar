//
// Created by Michal.Kawski on 23.01.2026.
//

#include "../../include/Drawing/SeekBarDrawer.h"

#include <android/native_window_jni.h>

#include <core/SkCanvas.h>
#include <core/SkSurface.h>
#include <core/SkColorSpace.h>

#include <gpu/ganesh/GrBackendSurface.h>
#include <gpu/ganesh/GrDirectContext.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <gpu/ganesh/gl/GrGLInterface.h>
#include <gpu/ganesh/gl/GrGLDirectContext.h>
#include <gpu/ganesh/gl/egl/GrGLMakeEGLInterface.h>
#include <gpu/ganesh/gl/GrGLBackendSurface.h>

#include <EGL/egl.h>
#include <GLES3/gl3.h>

namespace Drawing {

    ANativeWindow* SeekBarDrawer::s_pWindow = nullptr;
    sk_sp<GrDirectContext> SeekBarDrawer::s_pContext = nullptr;
    sk_sp<SkSurface> SeekBarDrawer::s_pSurface = nullptr;

    EGLContext eglContext = nullptr;
    EGLDisplay eglDisplay = nullptr;
    EGLSurface eglSurface = nullptr;

    bool SeekBarDrawer::InitSkia() {
        eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (eglDisplay == EGL_NO_DISPLAY) {
            return false;
        }

        if (!eglInitialize(eglDisplay, nullptr, nullptr)) {
            return false;
        }

        const EGLint configAttribs[] = {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
                EGL_RED_SIZE,        8,
                EGL_GREEN_SIZE,      8,
                EGL_BLUE_SIZE,       8,
                EGL_ALPHA_SIZE,      8,
                EGL_DEPTH_SIZE,      0,
                EGL_STENCIL_SIZE,    8,
                EGL_NONE
        };

        EGLConfig config;
        EGLint numConfigs = 0;

        eglChooseConfig(eglDisplay, configAttribs, &config, 1, &numConfigs);
        if (numConfigs == 0) {
            return false;
        }

        eglSurface = eglCreateWindowSurface(
                eglDisplay,
                config,
                s_pWindow,
                nullptr
        );

        if (eglSurface == EGL_NO_SURFACE) {
            return false;
        }

        const EGLint contextAttribs[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2,
                EGL_NONE
        };

        eglContext = eglCreateContext(
                eglDisplay,
                config,
                EGL_NO_CONTEXT,
                contextAttribs
        );

        if (eglContext == EGL_NO_CONTEXT) {
            return false;
        }

        if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
            return false;
        }

        auto glInterface = GrGLMakeEGLInterface();
        if (!glInterface) {
            return false;
        }

        s_pContext = GrDirectContexts::MakeGL(glInterface);
        if (!s_pContext) {
            return false;
        }

        return true;
    }

    void SeekBarDrawer::OnSurfaceCreated(ANativeWindow* pWindow)
    {
        s_pWindow = pWindow;

        if (InitSkia()) {
            DrawSeekBar();
        }
    }

    void SeekBarDrawer::DrawSeekBar()
    {
        if (!s_pWindow || !s_pContext) {
            return;
        }

        int width  = ANativeWindow_getWidth(s_pWindow);
        int height = ANativeWindow_getHeight(s_pWindow);

        GrGLFramebufferInfo fbInfo;
        fbInfo.fFBOID = 0;           // default framebuffer
        fbInfo.fFormat = GL_RGBA8;

        GrBackendRenderTarget backendRT = GrBackendRenderTargets::MakeGL(
                width,
                height,
                0,    // sample count
                8,    // stencil bits
                fbInfo
        );

        s_pSurface = SkSurfaces::WrapBackendRenderTarget(
                s_pContext.get(),
                backendRT,
                kBottomLeft_GrSurfaceOrigin,
                kRGBA_8888_SkColorType,
                nullptr,
                nullptr
        );

        if (!s_pSurface) {
            return;
        }

        SkCanvas* canvas = s_pSurface->getCanvas();
        canvas->clear(SK_ColorBLACK);

        const float xMargin = width * 0.05f;
        const float yMargin = height * 0.07f;

        SkPaint paint;
        paint.setColor(SK_ColorRED);
        canvas->drawRect(SkRect::MakeXYWH(xMargin / 2.0f,
                                          height - yMargin,
                                          width - xMargin,
                                          height * 0.007f), paint);

        s_pContext->flush();
        eglSwapBuffers(eglDisplay, eglSurface);
    }

} // Drawing