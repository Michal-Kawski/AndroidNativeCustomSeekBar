//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKPROXY_H
#define CUSTOMSEEKBAR_SEEKPROXY_H

#include "Segment.h"

#include <cstdint>
#include <vector>

namespace Core {

    class IMediaController;

    class ISeekProxy {
    public:
        virtual ~ISeekProxy() = default;

        virtual void SeekToNormalized(float normalized) = 0;
        virtual void SeekToTimeMs(int64_t timeMs) = 0;
        virtual float TimeToNormalized(int64_t timeMs) const = 0;

        virtual void OnDoubleTap(int64_t seekDeltaMs) = 0;
    };

    class SeekProxy : public ISeekProxy{
    public:
        explicit SeekProxy(IMediaController& mediaController, int64_t durationMs);
        ~SeekProxy() = default;

        void SeekToNormalized(float normalized) override;
        void SeekToTimeMs(int64_t timeMs) override;

        [[nodiscard]] float CurrentNormalized() const;
        [[nodiscard]] float TimeToNormalized(int64_t timeMs) const override;
        [[nodiscard]] int64_t NormalizedToTime(float normalized) const;

        void OnDoubleTap(int64_t seekDeltaMs) override;

    private:
        IMediaController& m_mediaController;

        int64_t m_durationMs = 0;
        int64_t m_currentTimeMs = 0;
    };

} // Core

#endif //CUSTOMSEEKBAR_SEEKPROXY_H
