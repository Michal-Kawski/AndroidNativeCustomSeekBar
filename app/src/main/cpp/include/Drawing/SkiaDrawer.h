//
// Created by Michal.Kawski on 23.01.2026.
//

#ifndef CUSTOMSEEKBAR_SKIADRAWER_H
#define CUSTOMSEEKBAR_SKIADRAWER_H

#include "Graphics/Graphics.h"

#include <core/SkRefCnt.h>

#include <cstdint>
#include <memory>

class ANativeWindow;
class GrDirectContext;
class SkSurface;

namespace Drawing {

    class SkiaDrawer final {
    public:
        void OnSurfaceCreated(ANativeWindow* pWindow);

        void ClearBackground(Graphics::Color backgroundColor = Graphics::Color::BLACK) const;
        void Flush() const;
        void DrawRectangle(const float x, const float y, const float endX, const float height, const Graphics::Color color) const;
        void DrawCircle(const float x, const float y, const float radius, const Graphics::Color color) const;

        int GetWindowWidth() const;
        int GetWindowHeight() const;

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
