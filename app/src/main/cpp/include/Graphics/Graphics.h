//
// Created by Michal.Kawski on 26.01.2026.
//

#ifndef CUSTOMSEEKBAR_GRAPHICS_H
#define CUSTOMSEEKBAR_GRAPHICS_H

namespace Graphics {

    enum class Color {
        RED,
        BLACK,
        WHITE,
        BLUE
    };

    struct Segment {
        float startX = 0.0f;
        float endX = 0.0f;
        Color color;
    };

} // View

#endif //CUSTOMSEEKBAR_GRAPHICS_H
