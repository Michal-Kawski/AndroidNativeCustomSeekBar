//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKPROXY_H
#define CUSTOMSEEKBAR_SEEKPROXY_H

#include "Segment.h"

#include <cstdint>
#include <vector>

namespace Core {

    class SeekProxy {
    public:
        explicit SeekProxy(int64_t durationMs);

        void SetCurrentTimeMs(int64_t timeMs);
        void SetDurationMs(int64_t durationMs);

        void SeekToNormalized(float normalized);   // from UI
        void SeekToTimeMs(int64_t timeMs);          // from player

        float CurrentNormalized() const;
        float TimeToNormalized(int64_t timeMs) const;
        int64_t NormalizedToTime(float normalized) const;

        void SetSegments(std::vector<Segment> segments);
        const std::vector<Segment>& GetSegments() const;

    private:
        int64_t m_durationMs = 0;
        int64_t m_currentTimeMs = 0;
        std::vector<Segment> m_segments;
    };

} // Core

#endif //CUSTOMSEEKBAR_SEEKPROXY_H
