//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_IMEDIACONTROLLER_H
#define CUSTOMSEEKBAR_IMEDIACONTROLLER_H

#include <cstdint>

namespace Core
{
    class IMediaController
    {
    public:
        virtual void SeekTo(int64_t currentTimeMs) = 0;
    };
} // Core

#endif //CUSTOMSEEKBAR_IMEDIACONTROLLER_H
