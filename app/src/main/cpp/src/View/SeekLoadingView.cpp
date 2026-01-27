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
        Drawing::SkiaDrawer* skiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!skiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekLoadingView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        m_loadingAnimation.active = true;

        skiaDrawer->AddRenderable(this);
    }

    void SeekLoadingView::Finish()
    {
        Drawing::SkiaDrawer* skiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!skiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekLoadingView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        skiaDrawer->RemoveRenderable(this);

        m_loadingAnimation.active = false;
        m_loadingAnimation.rotation = 0.0f;
    }

    void SeekLoadingView::Draw(float diffMs)
    {
        Drawing::SkiaDrawer* skiaDrawer = App::Context::GetInstance().GetSkiaDrawer();
        if (!skiaDrawer) {
            __android_log_print(ANDROID_LOG_DEBUG, "SeekLoadingView", "Can not draw seek bar, invalid skiaDrawer");
            return;
        }

        UpdateAnimation(diffMs);

        auto xCenter = static_cast<float>(skiaDrawer->GetWindowWidth()) / 2.0f;
        auto yCenter = static_cast<float>(skiaDrawer->GetWindowHeight()) / 2.0f;
        float radius = static_cast<float>(skiaDrawer->GetWindowWidth()) * 0.1;
        skiaDrawer->DrawLoading(xCenter, yCenter, radius, m_loadingAnimation.rotation, Core::Color::WHITE);
    }

    void SeekLoadingView::UpdateAnimation(float deltaMs) {
        if (!m_loadingAnimation.active) return;

        __android_log_print(ANDROID_LOG_INFO, "SeekLoadingView", "UpdateAnimation, loading animation is active");

        m_loadingAnimation.rotation += deltaMs * 0.4f;
        if (m_loadingAnimation.rotation > 360.f) {
            m_loadingAnimation.rotation -= 360.f;
        }
    }
}