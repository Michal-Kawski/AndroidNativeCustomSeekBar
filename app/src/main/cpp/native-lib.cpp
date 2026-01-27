#include "App/Context.h"
#include "Drawing/SkiaDrawer.h"
#include "View/SeekBarViewBuilder.h"
#include "Utils/JNIUtils.h"

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
                                                                    jfloat yPosition, jobject segments) {
    View::SeekBarViewBuilder builder;
    builder.AtPosition(0.9f); // draw the bar at 90% of the screen
    const auto cppSegments = Utils::KotlinSegmentListToCppSegmentList(env, segments);
    for (const auto &segment : cppSegments) {
        builder.AddSegment(segment);
    }

    auto seekBar = builder.Build();

    seekBar->Draw();
    return reinterpret_cast<jlong>(seekBar.release());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeDestroyProgressBar(JNIEnv *env, jobject thiz,
                                                                     jlong nativeSeekBar) {
    auto seekBar = reinterpret_cast<View::SeekBarView*>(nativeSeekBar);
    if (seekBar) {
        delete seekBar;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSeekTouch(JNIEnv *env, jobject thiz, jlong nativeSeekBar,
                                                              jfloat x, jfloat y, jint action) {
    auto seekBar = reinterpret_cast<View::SeekBarView*>(nativeSeekBar);
    if (seekBar) {
        seekBar->OnTouchEvent(x, y, action);
    }
}