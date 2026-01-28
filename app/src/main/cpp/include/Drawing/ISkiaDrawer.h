//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_ISKIADRAWER_H
#define CUSTOMSEEKBAR_ISKIADRAWER_H

#include "Renderable.h"
#include "Core/Color.h"

class ANativeWindow;

namespace Drawing
{
    class ISkiaDrawer
    {
    public:
        virtual ~ISkiaDrawer() = default;

        virtual void OnSurfaceCreated(ANativeWindow* pWindow) = 0;

        virtual void Draw(float diffMs) = 0;
        virtual void AddRenderable(Renderable* renderable) = 0;
        virtual void RemoveRenderable(Renderable* renderable) = 0;

        virtual void DrawRectangle(float x, float y, float endX, float height, Core::Color color) const = 0;
        virtual void DrawCircle(float x, float y, float radius, Core::Color color) const = 0;
        virtual void DrawLoading(float x, float y, float radius, float rotation, Core::Color color) const = 0;

        virtual int GetWindowWidth() const = 0;
        virtual int GetWindowHeight() const = 0;
    };
} // Drawing

#endif //CUSTOMSEEKBAR_ISKIADRAWER_H
