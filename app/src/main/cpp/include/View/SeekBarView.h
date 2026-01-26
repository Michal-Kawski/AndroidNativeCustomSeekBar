//
// Created by Michal.Kawski on 26.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKBARVIEW_H
#define CUSTOMSEEKBAR_SEEKBARVIEW_H

#include "Color.h"

#include <vector>

namespace View {

    class SeekBarView {
    public:
        enum class TapDirection {
            LEFT,
            RIGHT
        };

        SeekBarView(float yPosition);

        void AddProgressBarSegment(const float startTime, const float endTime, const Color color);
        void Draw() const;

        void OnTouchEvent(const float progress) const;
        void OnDoubleTap(const TapDirection tapDirection) const;

    private:
        struct Segment {
            float startTime = 0.0f;
            float endTime = 0.0f;
            Color color;
        };

        float m_yPosition = 0.0f;
        float m_progress = 0.0f;
        float m_maxProgress = 0.0f;
        std::vector<Segment> m_segments;
    };

} // View

#endif //CUSTOMSEEKBAR_SEEKBARVIEW_H
