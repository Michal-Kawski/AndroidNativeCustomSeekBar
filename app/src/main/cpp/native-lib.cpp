#include "App/Context.h"
#include "Drawing/SkiaDrawer.h"

#include <jni.h>
#include <android/native_window_jni.h>


extern "C"
JNIEXPORT void JNICALL
Java_com_example_customseekbar_MainActivity_nativeOnSurfaceCreated(JNIEnv *env, jobject thiz,
                                                                   jobject surface) {

    App::Context::GetInstance().GetSkiaDrawer().OnSurfaceCreated(ANativeWindow_fromSurface(env, surface));
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
    // TODO: implement nativeOnSurfaceDestroyed()
}