//
// Created by Michal.Kawski on 23.01.2026.
//

#ifndef CUSTOMSEEKBAR_SKIADRAWER_H
#define CUSTOMSEEKBAR_SKIADRAWER_H

#include "Core/Color.h"
#include "Core/MetronomeService.h"

#include <core/SkRefCnt.h>

#include <cstdint>
#include <memory>
#include <vector>

class ANativeWindow;
class GrDirectContext;
class SkSurface;

namespace Drawing {

    class Renderable;

    class SkiaDrawer final {
    public:
        ~SkiaDrawer();

        void OnSurfaceCreated(ANativeWindow* pWindow);

        void Draw(float diffMs);
        void AddRenderable(Renderable* renderable);
        void RemoveRenderable(Renderable* renderable);

        void DrawRectangle(float x, float y, float endX, float height, Core::Color color) const;
        void DrawCircle(float x, float y, float radius, Core::Color color) const;
        void DrawLoading(float x, float y, float radius, float rotation, Core::Color color) const;

        [[nodiscard]] int GetWindowWidth() const;
        [[nodiscard]] int GetWindowHeight() const;

    private:
        bool InitSkia();

        void ClearBackground(Core::Color backgroundColor = Core::Color::BLACK) const;
        void Flush() const;

        static ANativeWindow *s_pWindow; // the Kotlin side is the owner
        static sk_sp<GrDirectContext> s_pContext;
        static sk_sp<SkSurface> s_pSurface;

        std::vector<Renderable*> m_renderables;
        std::unique_ptr<Core::MetronomeService> m_pRenderService;

        bool m_isSkiaInitialized = false;
        int m_width = 0;
        int m_height = 0;
    };

} // Drawing

#endif //CUSTOMSEEKBAR_SKIADRAWER_H
