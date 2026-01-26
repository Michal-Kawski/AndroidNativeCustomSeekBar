//
// Created by Michal.Kawski on 26.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKBARVIEWBUILDER_H
#define CUSTOMSEEKBAR_SEEKBARVIEWBUILDER_H

#include "SeekBarView.h"

#include <memory>

namespace View {

    class SeekBarViewBuilder final {
    public:
        SeekBarViewBuilder();

        std::unique_ptr<SeekBarView> Build();
        SeekBarViewBuilder &AtPosition(const float yPosition);
        SeekBarViewBuilder &AddSegment(const Graphics::Segment &segment);

    private:
        std::unique_ptr<SeekBarView> m_pSeeKBarView;
    };

} // namespace View

#endif //CUSTOMSEEKBAR_SEEKBARVIEWBUILDER_H
