//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEGMENT_H
#define CUSTOMSEEKBAR_SEGMENT_H

#include "Color.h"

#include <cstdint>

namespace Core
{
    struct Segment {
        float startX = 0.0f;
        float endX = 0.0f;
        Color color = Color::BLUE;
    };
} // Core

#endif //CUSTOMSEEKBAR_SEGMENT_H
