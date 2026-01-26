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

    void SeekBarView::Draw() const
    {
        Drawing::SkiaDrawer* skiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!skiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekBarView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        skiaDrawer->ClearBackground();

        const float margin = 0.01;
        for (const auto &segment : m_segments) {
            skiaDrawer->DrawRectangle(segment.startX + margin, m_yPosition, segment.endX - margin, 0.02f, segment.color);
        }

        skiaDrawer->Flush();
    }

    void SeekBarView::OnTouchEvent(const float progress) const
    {

    }

    void SeekBarView::OnDoubleTap(const TapDirection tapDirection) const
    {

    }

} // View