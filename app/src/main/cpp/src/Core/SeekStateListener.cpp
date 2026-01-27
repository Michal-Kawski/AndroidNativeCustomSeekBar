//
// Created by Michal.Kawski on 27.01.2026.
//

#include "Core/SeekStateListener.h"

#include "View/SeekLoadingView.h"

namespace Core {

    void SeekStateListener::OnSeekStateChanged(SeekState state)
    {
        if (!m_pSeekLoadingView) return;

        if (state == SeekState::STARTED) {
            m_pSeekLoadingView->Start();
        } else {
            m_pSeekLoadingView->Finish();
        }
    }

    void SeekStateListener::SetSeekLoadingView(std::shared_ptr<View::SeekLoadingView> pSeekLoadingView)
    {
        m_pSeekLoadingView = pSeekLoadingView;
    }

} // Core