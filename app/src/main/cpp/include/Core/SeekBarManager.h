//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKBARMANAGER_H
#define CUSTOMSEEKBAR_SEEKBARMANAGER_H

#include "SeekProxy.h"
#include "IMediaController.h"
#include "SeekStateListener.h"

#include <memory>
#include <vector>

namespace View {
    class SeekBarView;
} // View

namespace Core {

    class SeekBarManager final : public IMediaController {
    public:
        SeekBarManager(float yPositionPercent, int64_t durationMs, std::vector<Segment> segments);
        ~SeekBarManager();

        SeekBarManager(const SeekBarManager&) = delete;
        SeekBarManager(SeekBarManager&&) noexcept = default;
        SeekBarManager& operator=(const SeekBarManager&) = delete;
        SeekBarManager& operator=(SeekBarManager&&) = default;

        void SetSeekStateListener(std::unique_ptr<ISeekStateListener> pSeekStateListener);

        void OnTouchEvent(float x, float y, int action);
        void OnDoubleTap(int64_t seekDeltaMs);

        void SeekTo(int64_t currentTimeMs) override;

        void SeekStart() const;
        void SeekFinish() const;
    private:
        std::unique_ptr<ISeekProxy> m_pSeekProxy;
        std::unique_ptr<ISeekStateListener> m_pSeekStateListener;
        std::unique_ptr<View::SeekBarView> m_pSeekBarView;

        bool m_isDragging = false;
    };

} // Core

#endif //CUSTOMSEEKBAR_SEEKBARMANAGER_H
