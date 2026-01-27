//
// Created by Michal.Kawski on 27.01.2026.
//

#include "Core/SeekProxy.h"

namespace Core {

    SeekProxy::SeekProxy(int64_t durationMs) : m_durationMs(durationMs)
    {

    }

    void SeekProxy::SetCurrentTimeMs(int64_t timeMs)
    {
        m_currentTimeMs = timeMs;
    }

    void SeekProxy::SetDurationMs(int64_t durationMs)
    {
        m_durationMs = durationMs;
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

    float SeekProxy::CurrentNormalized() const
    {
        return TimeToNormalized(m_currentTimeMs);
    }

    void SeekProxy::SetSegments(std::vector<Segment> segments)
    {
        m_segments = std::move(segments);
    }

    const std::vector<SeekProxy::Segment>& SeekProxy::GetSegments() const
    {
        return m_segments;
    }

    void SeekProxy::SeekToTimeMs(int64_t timeMs) {
        m_currentTimeMs = std::clamp<int64_t>(timeMs, 0LL, m_durationMs);

        // forward to player
        //MediaController::instance().seekTo(m_currentTimeMs);
    }
} // Core