//
// Created by Michal.Kawski on 26.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKBARVIEW_H
#define CUSTOMSEEKBAR_SEEKBARVIEW_H

#include "Graphics/Graphics.h"

#include <list>

namespace View {

    class SeekBarView {
    public:
        enum class TapDirection {
            LEFT,
            RIGHT
        };

        explicit SeekBarView(float yPosition);

        void AddProgressBarSegment(const Graphics::Segment &segment);
        void Draw();

        void OnTouchEvent(const float x, const float y, int action);
        void OnDoubleTap(const TapDirection tapDirection) const;

    private:
        bool HitTest(const float x, const float y) const;
        void UpdateProgressFromX(const float x);
        void SetSeekBarBoundaries();

        friend class SeekBarViewBuilder;
        float m_progress = 0.0f;
        bool  m_isDragging = false;

        int m_windowWidth = 0;
        int m_windowHeight = 0;

        float m_yPositionPercentage = 0.0f;
        float m_barHeightPercent = 0.015;
        float m_barLeft = 0.0f;
        float m_barRight = 0.0f;
        float m_barTop = 0.0f;
        float m_barBottom = 0.0f;

        std::list<Graphics::Segment> m_segments;
    };

} // View

#endif //CUSTOMSEEKBAR_SEEKBARVIEW_H
