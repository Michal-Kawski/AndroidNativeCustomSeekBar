#include "App/Context.h"
#include "Drawing/SkiaDrawer.h"
#include "Utils/JNIUtils.h"
#include "Core/SeekBarManager.h"

#include <android/native_window_jni.h>
#include <jni.h>

#include <memory>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSurfaceCreated(JNIEnv *env, jobject thiz,
                                                                   jobject surface) {
    App::Context::GetInstance().GetSkiaDrawer()->OnSurfaceCreated(ANativeWindow_fromSurface(env, surface));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                   jint width, jint height) {
    // TODO: implement nativeOnSurfaceChanged()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSurfaceDestroyed(JNIEnv *env, jobject thiz) {
    App::Context::GetInstance().Reset();
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_customseekbar_MainActivity_nativeCreateProgressBar(JNIEnv *env, jobject thiz,
                                                                    jfloat yPosition, jlong durationMs, jobject segments) {
    auto pSeekBarManager = std::make_unique<Core::SeekBarManager>(yPosition, durationMs, Utils::KotlinSegmentListToCppSegmentList(env, segments));
    return reinterpret_cast<jlong>(pSeekBarManager.release());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeDestroyProgressBar(JNIEnv *env, jobject thiz,
                                                                     jlong nativeSeekBarManager) {
    auto seekBarManager = reinterpret_cast<Core::SeekBarManager*>(nativeSeekBarManager);
    if (seekBarManager) {
        delete seekBarManager;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSeekTouch(JNIEnv *env, jobject thiz, jlong nativeSeekBarManager,
                                                              jfloat x, jfloat y, jint action) {
    auto seekBarManager = reinterpret_cast<Core::SeekBarManager*>(nativeSeekBarManager);
    if (seekBarManager) {
        seekBarManager->OnTouchEvent(x, y, action);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnDoubleTap(JNIEnv *env, jobject thiz,
                                                              jlong nativeSeekBarManager,
                                                              jlong seekDeltaMs) {
    auto seekBarManager = reinterpret_cast<Core::SeekBarManager*>(nativeSeekBarManager);
    if (seekBarManager) {
        seekBarManager->OnDoubleTap(seekDeltaMs);
    }
}