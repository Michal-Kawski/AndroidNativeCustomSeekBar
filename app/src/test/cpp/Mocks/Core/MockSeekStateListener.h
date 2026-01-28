//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKSTATELISTENER_H
#define CUSTOMSEEKBAR_SEEKSTATELISTENER_H

#include <Core/ISeekStateListener.h>
#include <Core/SeekBarManager.h>

#include <gmock/gmock.h>

class MockSeekStateListener : public Core::ISeekStateListener
{
public:
    MOCK_METHOD(void, OnSeekStateChanged, (Core::SeekState seekState), (override));
};

#endif //CUSTOMSEEKBAR_SEEKSTATELISTENER_H
