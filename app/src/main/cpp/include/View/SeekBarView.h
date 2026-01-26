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
        void Draw() const;

        void OnTouchEvent(const float progress) const;
        void OnDoubleTap(const TapDirection tapDirection) const;

    private:
        friend class SeekBarViewBuilder;
        float m_yPosition = 0.0f;
        float m_progress = 0.0f;
        std::list<Graphics::Segment> m_segments;
    };

} // View

#endif //CUSTOMSEEKBAR_SEEKBARVIEW_H
