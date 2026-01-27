//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_RENDERABLE_H
#define CUSTOMSEEKBAR_RENDERABLE_H

namespace Drawing {

    class Renderable
    {
    public:
        virtual ~Renderable() = default;
        virtual void Draw(float diffMs) = 0;
    };

} // Drawing

#endif //CUSTOMSEEKBAR_RENDERABLE_H
