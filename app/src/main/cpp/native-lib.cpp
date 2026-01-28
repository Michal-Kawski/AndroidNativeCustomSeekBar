#include "App/Context.h"
#include "App/ComponentFactory.h"
#include "Drawing/SkiaDrawer.h"
#include "Utils/JNIUtils.h"
#include "Core/SeekBarManager.h"
#include "Core/SeekStateListener.h"
#include "View/SeekLoadingView.h"

#include <android/native_window_jni.h>
#include <android/log.h>
#include <jni.h>

#include <memory>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeInit(JNIEnv *env, jobject thiz) {
    auto &context = App::Context::GetInstance();
    context.SetComponentFactory(std::make_unique<App::ComponentFactory>());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSurfaceCreated(JNIEnv *env, jobject thiz,
                                                                   jobject surface) {
    auto pSkiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
    if (!pSkiaDrawer) {
        __android_log_print(ANDROID_LOG_DEBUG, "SeekLoadingView", "Can not initialize SkiaDrawer");
        return;
    }

    pSkiaDrawer->OnSurfaceCreated(ANativeWindow_fromSurface(env, surface));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                   jlong nativeSeekBarManager, jint width, jint height) {
    // Not implemented yet, as this is not treated as a topic of the task
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSurfaceDestroyed(JNIEnv *env, jobject thiz) {
    // Nothing to do atm. as Skia is static now
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_customseekbar_MainActivity_nativeCreateProgressBar(JNIEnv *env, jobject thiz,
                                                                    jfloat yPosition, jlong durationMs, jobject segments) {
    auto pSeekBarManager = std::make_unique<Core::SeekBarManager>(yPosition, durationMs, Utils::KotlinSegmentListToCppSegmentList(env, segments));
    auto pSeekStateListener = std::make_unique<Core::SeekStateListener>();
    pSeekStateListener->SetSeekLoadingView(std::make_unique<View::SeekLoadingView>());
    pSeekBarManager->SetSeekStateListener(std::move(pSeekStateListener));
    return reinterpret_cast<jlong>(pSeekBarManager.release());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeDestroyProgressBar(JNIEnv *env, jobject thiz,
                                                                     jlong nativeSeekBarManager) {
    auto pSeekBarManager = reinterpret_cast<Core::SeekBarManager*>(nativeSeekBarManager);
    if (pSeekBarManager) {
        pSeekBarManager->SeekFinish();
        delete pSeekBarManager;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSeekTouch(JNIEnv *env, jobject thiz, jlong nativeSeekBarManager,
                                                              jfloat x, jfloat y, jint action) {
    auto pSeekBarManager = reinterpret_cast<Core::SeekBarManager*>(nativeSeekBarManager);
    if (pSeekBarManager) {
        pSeekBarManager->OnTouchEvent(x, y, action);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnDoubleTap(JNIEnv *env, jobject thiz,
                                                              jlong nativeSeekBarManager,
                                                              jlong seekDeltaMs) {
    auto pSeekBarManager = reinterpret_cast<Core::SeekBarManager*>(nativeSeekBarManager);
    if (pSeekBarManager) {
        pSeekBarManager->OnDoubleTap(seekDeltaMs);
    }
}
