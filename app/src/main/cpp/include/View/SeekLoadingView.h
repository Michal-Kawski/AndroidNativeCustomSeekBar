//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKLOADINGVIEW_H
#define CUSTOMSEEKBAR_SEEKLOADINGVIEW_H

#include "Drawing/Renderable.h"


namespace View
{
    class ISeekLoadingView {
    public:
        virtual ~ISeekLoadingView() = default;
        virtual void Start() = 0;
        virtual void Finish() = 0;
    };

class SeekLoadingView : public ISeekLoadingView, Drawing::Renderable {
    public:
        void Start() override;
        void Finish() override;

        void Draw(float diffMs) override;

        void UpdateAnimation(float deltaMs);

    private:
        struct LoadingAnimation {
            bool active = false;
            float rotation = 0.f;
        };

        LoadingAnimation m_loadingAnimation;
    };
}

#endif //CUSTOMSEEKBAR_SEEKLOADINGVIEW_H
