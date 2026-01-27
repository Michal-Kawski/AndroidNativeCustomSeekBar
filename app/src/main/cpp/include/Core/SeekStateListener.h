//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKSTATELISTENER_H
#define CUSTOMSEEKBAR_SEEKSTATELISTENER_H

#include <memory>

namespace View
{
    class SeekLoadingView;
}

namespace Core {

    enum class SeekState {
        STARTED,
        FINISHED
    };

    class ISeekStateListener {
    public:
        virtual ~ISeekStateListener() = default;
        virtual void OnSeekStateChanged(SeekState state) = 0;
    };

    class SeekStateListener : public ISeekStateListener {
    public:
        ~SeekStateListener();

        void OnSeekStateChanged(SeekState state) override;

        void SetSeekLoadingView(std::shared_ptr<View::SeekLoadingView> pSeekLoadingView);

    private:
        std::shared_ptr<View::SeekLoadingView> m_pSeekLoadingView;
    };

} // Core

#endif //CUSTOMSEEKBAR_SEEKSTATELISTENER_H
