//
// Created by Kawa on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEGMENT_H
#define CUSTOMSEEKBAR_SEGMENT_H

#include "Color.h"

#include <cstdint>

namespace Core
{
    struct Segment {
        int64_t startMs;
        int64_t endMs;
        Color color;
    };
} // Core

#endif //CUSTOMSEEKBAR_SEGMENT_H
