//
// Created by Michal.Kawski on 26.01.2026.
//

#include "View/SeekBarView.h"

#include "App/Context.h"
#include "Drawing/SkiaDrawer.h"

#include <android/log.h>

namespace View {

    SeekBarView::SeekBarView(float yPosition) : m_yPosition(yPosition)
    {

    }

    void SeekBarView::AddProgressBarSegment(const Graphics::Segment &segment)
    {
        m_segments.emplace_back(segment);
    }

    void SeekBarView::Draw()
    {
        Drawing::SkiaDrawer* skiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!skiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekBarView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        skiaDrawer->ClearBackground();

        const float margin = 0.01;
        for (const auto &segment : m_segments) {
            skiaDrawer->DrawRectangle(segment.startX + margin, m_yPosition, segment.endX - margin, m_barHeightPercent, segment.color);
        }

        skiaDrawer->Flush();

        SetSeekBarBoundaries(skiaDrawer->GetWindowWidth(), skiaDrawer->GetWindowHeight());
    }

    void SeekBarView::SetSeekBarBoundaries(const int windowWidth, const int windowHeight)
    {
        Graphics::Segment firstSegment = m_segments.front();
        Graphics::Segment lastSegment = m_segments.back();

        m_windowWidth = windowWidth;
        m_windowHeight = windowHeight;

        float barWidth = static_cast<float>(windowWidth) * (lastSegment.endX - firstSegment.startX);
        float barHeight = static_cast<float>(windowHeight) * m_barHeightPercent;

        m_barLeft = firstSegment.startX * barWidth;
        m_barRight = lastSegment.endX * barWidth;
        m_barTop = (m_yPosition * static_cast<float>(m_windowHeight)) - (barHeight / 2.0f);
        m_barBottom = (m_yPosition * static_cast<float>(m_windowHeight)) + (barHeight / 2.0f);
    }

    void SeekBarView::OnTouchEvent(const float x, const float y)
    {
        if (!HitTest(x, y)) return;

        auto localX = x - m_barLeft;
        auto width = (m_barRight - m_barLeft);

        m_progress = std::clamp(localX / width, 0.0f, 1.0f);
    }

    void SeekBarView::OnDoubleTap(const TapDirection tapDirection) const
    {

    }

    bool SeekBarView::HitTest(const float x, const float y) const {
        return x >= m_barLeft &&
               x <= m_barRight &&
               y >= m_barTop &&
               y <= m_barBottom;
    }

} // View