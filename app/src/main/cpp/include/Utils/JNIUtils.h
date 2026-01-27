//
// Created by Michal.Kawski on 26.01.2026.
//

#ifndef CUSTOMSEEKBAR_JNIUTILS_H
#define CUSTOMSEEKBAR_JNIUTILS_H

#include "Graphics/Graphics.h"

#include <jni.h>

#include <vector>

namespace Utils {

    Graphics::Color KotlinColorToCppColor(JNIEnv *env, jobject color);
    std::vector<Graphics::Segment> KotlinSegmentListToCppSegmentList(JNIEnv *env, jobject segments);

} // Utils


#endif //CUSTOMSEEKBAR_JNIUTILS_H
