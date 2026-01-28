//
// Created by Michal.Kawski on 26.01.2026.
//

#include "View/SeekBarView.h"

#include "App/Context.h"
#include "Drawing/SkiaDrawer.h"
#include "Drawing/Renderable.h"

#include <android/log.h>

namespace View {

    SeekBarView::SeekBarView(float yPositionPercentage) : m_yPositionPercentage(yPositionPercentage)
    {
    }

    SeekBarView::~SeekBarView()
    {

    }

    void SeekBarView::AddProgressBarSegments(std::vector<Core::Segment> segments)
    {
        m_segments = std::move(segments);
        std::sort(m_segments.begin(), m_segments.end(), [](const Core::Segment& left, const Core::Segment &right) {
            return left.endX <= right.endX;
        });
    }

    void SeekBarView::DrawSeekBar()
    {
        auto pSkiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!pSkiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekBarView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        pSkiaDrawer->AddRenderable(this);
    }

    void SeekBarView::Draw(float diffMs)
    {
        auto pSkiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!pSkiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekBarView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        m_windowWidth = pSkiaDrawer->GetWindowWidth();
        m_windowHeight = pSkiaDrawer->GetWindowHeight();
        SetSeekBarBoundaries();

        const float margin = 0.01;
        for (const auto &segment : m_segments) {
            const float width = static_cast<float>(m_windowWidth) * (segment.endX - segment.startX - margin);
            const float height = static_cast<float>(m_windowHeight) * m_barHeightPercent;
            const float x = (segment.startX + margin) * static_cast<float>(m_windowWidth);
            const float y = m_yPositionPercentage * static_cast<float>(m_windowHeight) - height/2.0f;

            pSkiaDrawer->DrawRectangle(x, y, width, height, segment.color);
        }

        const float progressBarX = (m_barRight - m_barLeft) * m_progress;
        const float progressBarYCenter = m_yPositionPercentage * static_cast<float>(m_windowHeight);
        const float radius = 0.02f * static_cast<float>(m_windowHeight);
        pSkiaDrawer->DrawCircle(progressBarX, progressBarYCenter, radius, Core::Color::RED);
    }

    void SeekBarView::SetSeekBarBoundaries()
    {
        Core::Segment firstSegment = m_segments.front();
        Core::Segment lastSegment = m_segments.back();

        float barWidth = static_cast<float>(m_windowWidth) * (lastSegment.endX - firstSegment.startX);
        float barHeight = static_cast<float>(m_windowHeight) * m_barHeightPercent;

        m_barLeft = firstSegment.startX * barWidth;
        m_barRight = lastSegment.endX * barWidth;
        m_barTop = (m_yPositionPercentage * static_cast<float>(m_windowHeight)) - (barHeight / 2.0f);
        m_barBottom = (m_yPositionPercentage * static_cast<float>(m_windowHeight)) + (barHeight / 2.0f);
    }

    void SeekBarView::UpdateProgressFromX(float x) {
        float width = m_barRight - m_barLeft;
        if (width <= 0) return;

        float localX = x - m_barLeft;
        float progress = localX / width;

        m_progress = std::clamp(progress, 0.0f, 1.0f);

        DrawSeekBar();
    }

    void SeekBarView::UpdateProgressToX(const float x)
    {
        m_progress = std::clamp(x, 0.0f, 1.0f);
        DrawSeekBar();
    }

    float SeekBarView::GetXCoordProgress(float x) const
    {
        float width = m_barRight - m_barLeft;
        if (width <= 0) return 0.0;

        float localX = x - m_barLeft;
        float progress = localX / width;

        return std::clamp(progress, 0.0f, 1.0f);
    }

    bool SeekBarView::HitTest(const float x, const float y) const {
        return x >= m_barLeft &&
               x <= m_barRight &&
               y >= m_barTop &&
               y <= m_barBottom;
    }

} // View