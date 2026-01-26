//
// Created by Michal.Kawski on 26.01.2026.
//

#include "View/SeekBarViewBuilder.h"

namespace View {

    SeekBarViewBuilder::SeekBarViewBuilder() : m_pSeeKBarView(std::make_unique<SeekBarView>(0.90f))
    {

    }

    std::unique_ptr<SeekBarView> SeekBarViewBuilder::Build()
    {
        return std::move(m_pSeeKBarView);
    }

    SeekBarViewBuilder &SeekBarViewBuilder::AtPosition(const float yPosition)
    {
        m_pSeeKBarView->m_yPosition = yPosition;
        return *this;
    }

    SeekBarViewBuilder &SeekBarViewBuilder::AddSegment(const Graphics::Segment &segment)
    {
        m_pSeeKBarView->AddProgressBarSegment(segment);
        return *this;
    }

} // View
