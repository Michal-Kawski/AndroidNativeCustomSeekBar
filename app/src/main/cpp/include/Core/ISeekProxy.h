//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_ISEEKPROXY_H
#define CUSTOMSEEKBAR_ISEEKPROXY_H

#include <cstdint>

namespace Core
{
    class ISeekProxy
    {
    public:
        virtual ~ISeekProxy() = default;

        virtual void SeekToNormalized(float normalized) = 0;
        virtual void SeekToTimeMs(int64_t timeMs) = 0;
        virtual float TimeToNormalized(int64_t timeMs) const = 0;
        virtual int64_t NormalizedToTime(float normalized) const = 0;

        virtual void OnDoubleTap(int64_t seekDeltaMs) = 0;
    };
}

#endif //CUSTOMSEEKBAR_ISEEKPROXY_H
