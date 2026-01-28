//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_MOCKSEEKPROXY_H
#define CUSTOMSEEKBAR_MOCKSEEKPROXY_H

#include <Core/ISeekProxy.h>
#include <gmock/gmock.h>

namespace Core
{
    class MockSeekProxy : public ISeekProxy
    {
    public:
        MOCK_METHOD(void, SeekToNormalized, (float normalized), (override));
        MOCK_METHOD(void, SeekToTimeMs, (int64_t timeMs), (override));
        MOCK_METHOD(float, TimeToNormalized, (int64_t timeMs), (const, override));
        MOCK_METHOD(int64_t, NormalizedToTime, (float normalized), (const override))
        MOCK_METHOD(void, OnDoubleTap, (int64_t seekDeltaMs), (override));
    };
} // Core

#endif //CUSTOMSEEKBAR_MOCKSEEKPROXY_H
