//
// Created by Michal.Kawski on 26.01.2026.
//

#include "Utils/JNIUtils.h"

#include <android/log.h>

namespace Utils {

    Graphics::Color KotlinColorToCppColor(JNIEnv *env, jobject color)
    {
        jclass colorClass = env->GetObjectClass(color);
        jmethodID ordinalMethodID = env->GetMethodID(colorClass, "ordinal", "()I");

        jint ordinal = env->CallIntMethod(color, ordinalMethodID);

        switch (ordinal) {
            case 0: return Graphics::Color::WHITE;
            case 1: return Graphics::Color::BLACK;
            case 2: return Graphics::Color::BLUE;
            case 3: return Graphics::Color::RED;
            default:
                __android_log_print(ANDROID_LOG_DEBUG, "JNIUtils", "Unknown color");
                return Graphics::Color::WHITE; // Default case
        }
    }

    std::list<Graphics::Segment> KotlinSegmentListToCppSegmentList(JNIEnv *env, jobject segments)
    {
        std::list<Graphics::Segment> cppSegments;

        jclass segmentListClass = env->GetObjectClass(segments);
        jmethodID sizeMethodID = env->GetMethodID(segmentListClass, "size", "()I");
        jint listSize = env->CallIntMethod(segments, sizeMethodID);

        //jmethodID getMethodID = env->GetMethodID(segmentListClass, "get", "(I)Lcom/example/customseekbar/SeekBarFactory/Segment;");
        jmethodID getMethodID = env->GetMethodID(segmentListClass, "get", "(I)Ljava/lang/Object;");

        for (jint i = 0; i < listSize; ++i) {
            jobject segmentObj = env->CallObjectMethod(segments, getMethodID, i);

            jclass segmentClass = env->GetObjectClass(segmentObj);

            // Get the startTime and endTime
            jfieldID startTimeFieldID = env->GetFieldID(segmentClass, "startTime", "F");
            jfieldID endTimeFieldID = env->GetFieldID(segmentClass, "endTime", "F");

            jfloat startTime = env->GetFloatField(segmentObj, startTimeFieldID);
            jfloat endTime = env->GetFloatField(segmentObj, endTimeFieldID);

            // Get the color
            jclass colorEnumClass = env->FindClass("com/example/customseekbar/SeekBarFactory/Color");

            jfieldID colorFieldID = env->GetFieldID(segmentClass, "color", "Lcom/example/customseekbar/SeekBarFactory/Color;");

            jobject colorObj = env->GetObjectField(segmentObj, colorFieldID);

            // Map the Kotlin Color to C++ Color
            Graphics::Color color = KotlinColorToCppColor(env, colorObj);

            // Create a new C++ Segment and add it to the vector
            Graphics::Segment cppSegment = { startTime, endTime, color };
            cppSegments.push_back(cppSegment);
        }

        return cppSegments;
    }

} // Utils
