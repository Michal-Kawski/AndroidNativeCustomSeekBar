//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_ISEEKSTATELISTENER_H
#define CUSTOMSEEKBAR_ISEEKSTATELISTENER_H

namespace Core
{
    enum class SeekState {
        STARTED,
        FINISHED
    };

    class ISeekStateListener {
    public:
        virtual ~ISeekStateListener() = default;

        virtual void OnSeekStateChanged(SeekState state) = 0;
    };
} // Core

#endif //CUSTOMSEEKBAR_ISEEKSTATELISTENER_H
