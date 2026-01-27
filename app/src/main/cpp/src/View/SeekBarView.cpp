//
// Created by Michal.Kawski on 26.01.2026.
//

#include "View/SeekBarView.h"

#include "App/Context.h"
#include "Drawing/SkiaDrawer.h"

#include <android/log.h>

namespace View {

    static constexpr int AMOTION_EVENT_ACTION_DOWN = 0;
    static constexpr int AMOTION_EVENT_ACTION_UP = 1;
    static constexpr int AMOTION_EVENT_ACTION_MOVE = 2;
    static constexpr int AMOTION_EVENT_ACTION_CANCEL = 3;

    SeekBarView::SeekBarView(float yPositionPercentage) : m_yPositionPercentage(yPositionPercentage)
    {

    }

    void SeekBarView::AddProgressBarSegments(std::vector<Graphics::Segment> segments)
    {
        m_segments = std::move(segments);
        std::sort(m_segments.begin(), m_segments.end(), [](const Graphics::Segment& left, const Graphics::Segment &right) {
            return left.endX <= right.endX;
        });
    }

    void SeekBarView::Draw()
    {
        Drawing::SkiaDrawer* skiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!skiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekBarView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        m_windowWidth = skiaDrawer->GetWindowWidth();
        m_windowHeight = skiaDrawer->GetWindowHeight();
        SetSeekBarBoundaries();

        skiaDrawer->ClearBackground();

        const float margin = 0.01;
        for (const auto &segment : m_segments) {
            const float width = static_cast<float>(m_windowWidth) * (segment.endX - segment.startX - margin);
            const float height = static_cast<float>(m_windowHeight) * m_barHeightPercent;
            const float x = (segment.startX + margin) * static_cast<float>(m_windowWidth);
            const float y = m_yPositionPercentage * static_cast<float>(m_windowHeight) - height/2.0f;

            skiaDrawer->DrawRectangle(x, y, width, height, segment.color);
        }

        const float progressBarX = (m_barRight - m_barLeft) * m_progress;
        const float progressBarYCenter = m_yPositionPercentage * static_cast<float>(m_windowHeight);
        const float radius = 0.02f * static_cast<float>(m_windowHeight);
        skiaDrawer->DrawCircle(progressBarX, progressBarYCenter, radius, Graphics::Color::RED);

        skiaDrawer->Flush();
    }

    void SeekBarView::SetSeekBarBoundaries()
    {
        Graphics::Segment firstSegment = m_segments.front();
        Graphics::Segment lastSegment = m_segments.back();

        float barWidth = static_cast<float>(m_windowWidth) * (lastSegment.endX - firstSegment.startX);
        float barHeight = static_cast<float>(m_windowHeight) * m_barHeightPercent;

        m_barLeft = firstSegment.startX * barWidth;
        m_barRight = lastSegment.endX * barWidth;
        m_barTop = (m_yPositionPercentage * static_cast<float>(m_windowHeight)) - (barHeight / 2.0f);
        m_barBottom = (m_yPositionPercentage * static_cast<float>(m_windowHeight)) + (barHeight / 2.0f);
    }

    void SeekBarView::OnTouchEvent(const float x, const float y, const int action)
    {
        switch (action) {
            case AMOTION_EVENT_ACTION_DOWN: {
                if (HitTest(x, y)) {
                    m_isDragging = true;
                    UpdateProgressFromX(x);
                }
                break;
            }

            case AMOTION_EVENT_ACTION_MOVE: {
                if (m_isDragging) {
                    UpdateProgressFromX(x);
                }
                break;
            }

            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_CANCEL: {
                if (m_isDragging) {
                    m_isDragging = false;
                    UpdateProgressFromX(x);
                }
                break;
            }
        }
    }

    void SeekBarView::UpdateProgressFromX(float x) {
        float width = m_barRight - m_barLeft;
        if (width <= 0) return;

        float localX = x - m_barLeft;
        float progress = localX / width;

        m_progress = std::clamp(progress, 0.0f, 1.0f);

        Draw();
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