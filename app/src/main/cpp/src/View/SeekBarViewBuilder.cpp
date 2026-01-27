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

    SeekBarViewBuilder &SeekBarViewBuilder::AtPosition(const float yPositionPercentage)
    {
        m_pSeeKBarView->m_yPositionPercentage = yPositionPercentage;
        return *this;
    }

    SeekBarViewBuilder &SeekBarViewBuilder::AddSegments(std::vector<Core::Segment> segments)
    {
        m_pSeeKBarView->AddProgressBarSegments(std::move(segments));
        return *this;
    }

} // View
