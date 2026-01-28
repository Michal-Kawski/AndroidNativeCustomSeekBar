//
// Created by Michal.Kawski on 27.01.2026.
//

#include "Core/SeekProxy.h"

#include "Core/IMediaController.h"

#include "View/SeekBarView.h"

#include <algorithm>

namespace Core {

    SeekProxy::SeekProxy(IMediaController& mediaController, int64_t durationMs) :
        m_mediaController(mediaController),
        m_durationMs(durationMs)
    {

    }

    float SeekProxy::TimeToNormalized(int64_t timeMs) const {
        if (m_durationMs <= 0) return 0.0f;
        return static_cast<float>(timeMs) / static_cast<float>(m_durationMs);
    }

    int64_t SeekProxy::NormalizedToTime(float normalized) const {
        normalized = std::clamp(normalized, 0.0f, 1.0f);
        return static_cast<int64_t>(normalized * static_cast<float>(m_durationMs));
    }

    void SeekProxy::SeekToNormalized(float normalized) {
        const int64_t targetMs = NormalizedToTime(normalized);
        SeekToTimeMs(targetMs);
    }

    void SeekProxy::SeekToTimeMs(int64_t timeMs) {
        m_currentTimeMs = std::clamp<int64_t>(timeMs, 0LL, m_durationMs);

        // forward to player
        m_mediaController.SeekTo(m_currentTimeMs);
    }

    void SeekProxy::OnDoubleTap(int64_t seekDeltaMs)
    {
        m_currentTimeMs = std::clamp<int64_t>(m_currentTimeMs + seekDeltaMs, 0LL, m_durationMs);
        m_mediaController.SeekTo(m_currentTimeMs);
    }

} // Core