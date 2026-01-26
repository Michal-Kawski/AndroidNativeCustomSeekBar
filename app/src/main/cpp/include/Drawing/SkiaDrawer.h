//
// Created by Michal.Kawski on 23.01.2026.
//

#ifndef CUSTOMSEEKBAR_SKIADRAWER_H
#define CUSTOMSEEKBAR_SKIADRAWER_H

#include <core/SkRefCnt.h>

#include <cstdint>
#include <memory>

class ANativeWindow;
class GrDirectContext;
class SkSurface;

namespace Drawing {

    class SkiaDrawer final {
    public:
        enum class Color {
            RED,
            BLACK,
            WHITE,
            BLUE
        };

        void OnSurfaceCreated(ANativeWindow* pWindow);

        void ClearBackground(Color backgroundColor = Color::BLACK) const;
        void DrawRectangle(float x, float y, float width, float height, Color color = Color::RED) const;

    private:
        bool InitSkia();

        static ANativeWindow *s_pWindow; // the Kotlin side is the owner
        static sk_sp<GrDirectContext> s_pContext;
        static sk_sp<SkSurface> s_pSurface;

        bool m_isSkiaInitialized = false;
        int m_width = 0;
        int m_height = 0;
    };

} // Drawing

#endif //CUSTOMSEEKBAR_SKIADRAWER_H
