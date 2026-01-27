//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKLOADINGVIEW_H
#define CUSTOMSEEKBAR_SEEKLOADINGVIEW_H

namespace View
{
    class ISeekLoadingView {
    public:
        virtual void Start() = 0;
        virtual void Finish() = 0;
    };

    class SeekLoadingView : public ISeekLoadingView {
    public:
        void Start() override;
        void Finish() override;
    };
}


#endif //CUSTOMSEEKBAR_SEEKLOADINGVIEW_H
