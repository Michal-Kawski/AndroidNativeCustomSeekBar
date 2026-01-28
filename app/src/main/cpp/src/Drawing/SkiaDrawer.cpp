//
// Created by Michal.Kawski on 23.01.2026.
//

#include "Drawing/SkiaDrawer.h"
#include "Drawing/Renderable.h"

#include "Core/MetronomeService.h"

#include <android/native_window_jni.h>
#include <android/log.h>

#include <core/SkCanvas.h>
#include <core/SkColorSpace.h>
#include <core/SkSurface.h>
#include <core/SkRefCnt.h>

#include <gpu/ganesh/GrBackendSurface.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <gpu/ganesh/gl/GrGLInterface.h>
#include <gpu/ganesh/gl/GrGLDirectContext.h>
#include <gpu/ganesh/gl/egl/GrGLMakeEGLInterface.h>
#include <gpu/ganesh/gl/GrGLBackendSurface.h>
#include <gpu/ganesh/GrDirectContext.h>

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <unordered_map>


namespace Drawing {

    ANativeWindow* SkiaDrawer::s_pWindow = nullptr;
    sk_sp<GrDirectContext> SkiaDrawer::s_pContext = nullptr;
    sk_sp<SkSurface> SkiaDrawer::s_pSurface = nullptr;

    EGLContext eglContext = nullptr;
    EGLDisplay eglDisplay = nullptr;
    EGLSurface eglSurface = nullptr;

    SkColor CoreColorToSkiaColor(const Core::Color color) {
        static std::unordered_map<Core::Color, SkColor> s_skiaColorMap = {
                {Core::Color::RED,   SK_ColorRED},
                {Core::Color::BLACK, SK_ColorBLACK},
                {Core::Color::BLUE,  SK_ColorBLUE},
                {Core::Color::WHITE, SK_ColorWHITE}
        };

        const auto colorIt = s_skiaColorMap.find(color);
        if (colorIt != s_skiaColorMap.cend()) {
            return colorIt->second;
        }

        __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Unknown color");
        return SK_ColorBLACK;
    }

    SkiaDrawer &SkiaDrawer::GetInstance()
    {
        static SkiaDrawer skiaDrawer;
        return skiaDrawer;
    }

    SkiaDrawer::~SkiaDrawer()
    {
        if (m_pRenderService) {
            m_pRenderService->Stop();
            m_pRenderService.reset();
        }
    }

    bool SkiaDrawer::InitSkia() {
        if (m_isSkiaInitialized) {
            return true;
        }

        eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (eglDisplay == EGL_NO_DISPLAY) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not get display");
            return false;
        }

        if (!eglInitialize(eglDisplay, nullptr, nullptr)) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not initialize display");
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
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not configure display");
            return false;
        }

        eglSurface = eglCreateWindowSurface(
                eglDisplay,
                config,
                s_pWindow,
                nullptr
        );

        if (eglSurface == EGL_NO_SURFACE) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not create EGL window surface");
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
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not create EGL context");
            return false;
        }

        if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not bind EGL context for rendering");
            return false;
        }

        const auto glInterface = GrGLMakeEGLInterface();
        if (!glInterface) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not create EGL interface");
            return false;
        }

        s_pContext = GrDirectContexts::MakeGL(glInterface);
        if (!s_pContext) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not create skia context");
            return false;
        }

        m_width  = ANativeWindow_getWidth(s_pWindow);
        m_height = ANativeWindow_getHeight(s_pWindow);

        GrGLFramebufferInfo fbInfo;
        fbInfo.fFBOID = 0;           // default framebuffer
        fbInfo.fFormat = GL_RGBA8;

        GrBackendRenderTarget backendRT = GrBackendRenderTargets::MakeGL(
                m_width,
                m_height,
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
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not create skia surface");
            return false;
        }

        m_isSkiaInitialized = true;
        __android_log_print(ANDROID_LOG_INFO, "SkiaDrawer", "Initialized skia");
        return true;
    }

    void SkiaDrawer::OnSurfaceCreated(ANativeWindow* pWindow)
    {
        s_pWindow = pWindow;

        m_pRenderService = std::make_unique<Core::MetronomeService>(40);
        m_pRenderService->AddCallback([this](float diffMs){
            SkiaDrawer::InitSkia();

            Draw(diffMs);
        });

        m_pRenderService->Start();
    }

    void SkiaDrawer::Draw(float diffMs)
    {
        ClearBackground();

        for (auto pRenderable : m_renderables) {
            pRenderable->Draw(diffMs);
        }

        Flush();
    }

    void SkiaDrawer::AddRenderable(Drawing::Renderable *renderable)
    {
        if (std::find(m_renderables.begin(), m_renderables.end(), renderable) != m_renderables.end()) return;

        m_renderables.push_back(renderable);
    }

    void SkiaDrawer::RemoveRenderable(Drawing::Renderable *renderable)
    {
        m_renderables.erase(std::remove(m_renderables.begin(), m_renderables.end(), renderable), m_renderables.end());
    }

    void SkiaDrawer::ClearBackground(Core::Color backgroundColor) const
    {
        if (!s_pSurface || !s_pContext) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not clean the background, skia is not initialized");
            return;
        }

        SkCanvas* canvas = s_pSurface->getCanvas();
        canvas->clear(CoreColorToSkiaColor(backgroundColor));
    }

    void SkiaDrawer::Flush() const
    {
        s_pContext->flush();
        eglSwapBuffers(eglDisplay, eglSurface);
    }

    void SkiaDrawer::DrawRectangle(const float x, const float y, const float width, const float height, const Core::Color color) const
    {
        if (!s_pSurface || !s_pContext) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not draw rectangle, skia is not initialized");
            return;
        }

        SkPaint paint;
        paint.setColor(CoreColorToSkiaColor(color));

        SkCanvas* canvas = s_pSurface->getCanvas();
        canvas->save();
        canvas->drawRect(SkRect::MakeXYWH(x, y, width, height), paint);
        canvas->restore();
    }

    void SkiaDrawer::DrawCircle(const float x, const float y, const float radius, const Core::Color color) const
    {
        if (!s_pSurface || !s_pContext) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not draw circle, skia is not initialized");
            return;
        }

        SkPaint paint;
        paint.setColor(CoreColorToSkiaColor(color));

        SkCanvas* canvas = s_pSurface->getCanvas();
        canvas->save();
        canvas->drawCircle(SkPoint(x, y), radius, paint);
        canvas->restore();
    }

    void SkiaDrawer::DrawLoading(float x, float y, float radius, float rotation, Core::Color color) const
    {
        if (!s_pSurface || !s_pContext) {
            __android_log_print(ANDROID_LOG_DEBUG, "SkiaDrawer", "Could not draw loading animation, skia is not initialized");
            return;
        }

        SkPoint center(x, y);
        
        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::kStroke_Style);
        paint.setStrokeWidth(6);
        paint.setColor(CoreColorToSkiaColor(color));

        SkRect rect = SkRect::MakeLTRB(
                center.x() - radius,
                center.y() - radius,
                center.x() + radius,
                center.y() + radius
        );

        SkCanvas* canvas = s_pSurface->getCanvas();
        canvas->save();
        canvas->rotate(rotation, center.x(), center.y());
        canvas->drawArc(rect, 0, 270, false, paint);
        canvas->restore();
    }

    int SkiaDrawer::GetWindowWidth() const
    {
        return m_width;
    }

    int SkiaDrawer::GetWindowHeight() const {
        return m_height;
    }

} // Drawing