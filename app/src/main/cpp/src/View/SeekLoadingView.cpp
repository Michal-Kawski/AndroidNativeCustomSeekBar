//
// Created by Michal.Kawski on 27.01.2026.
//

#include "View/SeekLoadingView.h"

#include "App/Context.h"
#include "Drawing/SkiaDrawer.h"

#include <android/log.h>

namespace View
{

    void SeekLoadingView::Start()
    {
        auto pSkiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!pSkiaDrawer)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekLoadingView", "Can not get SkiaDrawer");
            return;
        }

        m_loadingAnimation.active = true;

        pSkiaDrawer->AddRenderable(this);
    }

    void SeekLoadingView::Finish()
    {
        auto pSkiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!pSkiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekLoadingView", "Can not finish load animation, invalid SkiaDrawer");
            return;
        }
        pSkiaDrawer->RemoveRenderable(this);

        m_loadingAnimation.active = false;
        m_loadingAnimation.rotation = 0.0f;
    }

    void SeekLoadingView::Draw(float diffMs)
    {
        auto pSkiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!pSkiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekLoadingView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        UpdateAnimation(diffMs);

        auto xCenter = static_cast<float>(pSkiaDrawer->GetWindowWidth()) / 2.0f;
        auto yCenter = static_cast<float>(pSkiaDrawer->GetWindowHeight()) / 2.0f;
        float radius = static_cast<float>(pSkiaDrawer->GetWindowWidth()) * 0.1;
        pSkiaDrawer->DrawLoading(xCenter, yCenter, radius, m_loadingAnimation.rotation, Core::Color::WHITE);
    }

    void SeekLoadingView::UpdateAnimation(float deltaMs) {
        if (!m_loadingAnimation.active) return;

        m_loadingAnimation.rotation += deltaMs * 0.4f;
        if (m_loadingAnimation.rotation > 360.f) {
            m_loadingAnimation.rotation -= 360.f;
        }
    }
}