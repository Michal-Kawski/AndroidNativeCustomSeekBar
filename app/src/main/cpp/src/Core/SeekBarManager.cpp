//
// Created by Michal.Kawski on 27.01.2026.
//

#include "Core/SeekBarManager.h"

#include "App/Context.h"

#include "View/SeekBarViewBuilder.h"
#include "View/SeekBarView.h"

#include <android/log.h>

namespace Core {

    static constexpr int AMOTION_EVENT_ACTION_DOWN = 0;
    static constexpr int AMOTION_EVENT_ACTION_UP = 1;
    static constexpr int AMOTION_EVENT_ACTION_MOVE = 2;
    static constexpr int AMOTION_EVENT_ACTION_CANCEL = 3;


    SeekBarManager::SeekBarManager(float yPositionPercent, int64_t durationMs, std::vector<Segment> segments) :
            m_pSeekProxy(App::Context::GetInstance().GetComponentFactory()->GetSeekProxyFactory()->Create(*this, durationMs))
    {
        View::SeekBarViewBuilder seekBarViewBuilder;
        seekBarViewBuilder.AddSegments(std::move(segments));
        seekBarViewBuilder.AtPosition(yPositionPercent);

        m_pSeekBarView = seekBarViewBuilder.Build();
        m_pSeekBarView->DrawSeekBar();
    }

    SeekBarManager::~SeekBarManager() {
        m_pSeekBarView.reset();
    }

    void SeekBarManager::SetSeekStateListener(std::unique_ptr<ISeekStateListener> pSeekStateListener)
    {
        m_pSeekStateListener = std::move(pSeekStateListener);
    }

    void SeekBarManager::OnTouchEvent(const float x, const float y, const int action)
    {
        if (!m_pSeekBarView || !m_pSeekProxy) return;

        switch (action) {
            case AMOTION_EVENT_ACTION_DOWN: {
                    if (m_pSeekBarView->HitTest(x, y)) {
                        SeekStart();
                        m_isDragging = true;
                        m_pSeekProxy->SeekToNormalized(m_pSeekBarView->GetXCoordProgress(x));
                    }
                    break;
                }

                case AMOTION_EVENT_ACTION_MOVE: {
                    if (m_isDragging) {
                        SeekStart();
                        m_pSeekProxy->SeekToNormalized(m_pSeekBarView->GetXCoordProgress(x));
                    }
                    break;
                }

                case AMOTION_EVENT_ACTION_UP:
                case AMOTION_EVENT_ACTION_CANCEL: {
                    SeekFinish();
                    if (m_isDragging) {
                        m_isDragging = false;
                        m_pSeekProxy->SeekToNormalized(m_pSeekBarView->GetXCoordProgress(x));
                    }
                    break;
                    default:
                        __android_log_print(ANDROID_LOG_DEBUG, "SeekBarManager", "Action not recognized");
                }
            }
    }

    void SeekBarManager::OnDoubleTap(int64_t seekDeltaMs)
    {
        m_pSeekProxy->OnDoubleTap(seekDeltaMs);
    }

    void SeekBarManager::SeekTo(const int64_t currentTimeMs)
    {
        m_pSeekBarView->UpdateProgressToX(m_pSeekProxy->TimeToNormalized(currentTimeMs));
    }

    void SeekBarManager::SeekStart() const
    {
        if (m_pSeekStateListener) {
            m_pSeekStateListener->OnSeekStateChanged(SeekState::STARTED);
        }
    }

    void SeekBarManager::SeekFinish() const
    {
        if (m_pSeekStateListener) {
            m_pSeekStateListener->OnSeekStateChanged(SeekState::FINISHED);
        }
    }

} // Core