//
// Created by Michal.Kawski on 26.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKBARVIEW_H
#define CUSTOMSEEKBAR_SEEKBARVIEW_H

#include "Core/Segment.h"
#include "Drawing/Renderable.h"

#include <vector>

namespace View {

class SeekBarView : public Drawing::Renderable {
    public:
        explicit SeekBarView(float yPositionPercentage);
        ~SeekBarView();

        void AddProgressBarSegments(std::vector<Core::Segment> segments);

        void DrawSeekBar();

        void UpdateProgressFromX(float x);
        void UpdateProgressToX(float x);

        [[nodiscard]] float GetXCoordProgress(float x) const;
        [[nodiscard]] bool HitTest(float x, float y) const;

        void Draw(float diffMs) override;

    private:
        void SetSeekBarBoundaries();

        friend class SeekBarViewBuilder;
        float m_progress = 0.0f;

        int m_windowWidth = 0;
        int m_windowHeight = 0;
        float m_yPositionPercentage = 0.0f;
        float m_barHeightPercent = 0.015;

        float m_barLeft = 0.0f;
        float m_barRight = 0.0f;
        float m_barTop = 0.0f;
        float m_barBottom = 0.0f;

        std::vector<Core::Segment> m_segments;
    };

} // View

#endif //CUSTOMSEEKBAR_SEEKBARVIEW_H
