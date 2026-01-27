//
// Created by Michal.Kawski on 26.01.2026.
//

#ifndef CUSTOMSEEKBAR_JNIUTILS_H
#define CUSTOMSEEKBAR_JNIUTILS_H

#include "Core/Segment.h"

#include <jni.h>

#include <vector>

namespace Utils {

    [[nodiscard]] Core::Color KotlinColorToCppColor(JNIEnv *env, jobject color);
    [[nodiscard]] std::vector<Core::Segment> KotlinSegmentListToCppSegmentList(JNIEnv *env, jobject segments);

} // Utils


#endif //CUSTOMSEEKBAR_JNIUTILS_H
