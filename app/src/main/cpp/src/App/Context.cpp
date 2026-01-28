//
// Created by Michal.Kawski on 23.01.2026.
//

#include "App/Context.h"

#include "Drawing/SkiaDrawer.h"
#include "Core/SeekProxyFactory.h"

#include <android/log.h>

namespace App {

    Context& Context::GetInstance()
    {
        static Context instance;
        return instance;
    }

    void Context::SetComponentFactory(std::unique_ptr<IComponentFactory> pComponentFactory)
    {
        m_pComponentFactory = std::move(pComponentFactory);
    }

    IComponentFactory* Context::GetComponentFactory()
    {
        return m_pComponentFactory.get();
    }

    Drawing::ISkiaDrawer* Context::GetSkiaDrawer()
    {
        if (!m_pComponentFactory) {
            __android_log_print(ANDROID_LOG_DEBUG, "Context", "Can not get SkiaDrawer, invalid ComponentFactory");
            return nullptr;
        }

        auto pSkiaDrawerFactory = m_pComponentFactory->GetSkiaDrawerFactory();
        if (!pSkiaDrawerFactory) {
            __android_log_print(ANDROID_LOG_DEBUG, "Context", "Can not get SkiaDrawer, invalid SkiaDrawerFactory");
            return nullptr;
        }

        return &pSkiaDrawerFactory->GetInstance();
    }

} // App