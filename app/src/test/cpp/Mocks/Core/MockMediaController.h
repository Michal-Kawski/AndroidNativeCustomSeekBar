//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_MOCKMEDIACONTROLLER_H
#define CUSTOMSEEKBAR_MOCKMEDIACONTROLLER_H

#include <Core/IMediaController.h>

#include <gmock/gmock.h>

class MockMediaController : public Core::IMediaController
{
public:
    MOCK_METHOD(void, SeekTo, (int64_t currentTimeMs), (override));
};

#endif //CUSTOMSEEKBAR_MOCKMEDIACONTROLLER_H
