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

        void OnTouchEvent(const float x, const float y);
        void OnDoubleTap(const TapDirection tapDirection) const;

    private:
        bool HitTest(const float x, const float y) const;
        void SetSeekBarBoundaries(const int windowWidth, const int windowHeight);

        friend class SeekBarViewBuilder;
        float m_yPosition = 0.0f;
        float m_progress = 0.0f;

        int m_windowWidth = 0;
        int m_windowHeight = 0;

        float m_barHeightPercent = 0.02;
        float m_barLeft = 0.0f;
        float m_barRight = 0.0f;
        float m_barTop = 0.0f;
        float m_barBottom = 0.0f;

        std::list<Graphics::Segment> m_segments;
    };

} // View

#endif //CUSTOMSEEKBAR_SEEKBARVIEW_H
