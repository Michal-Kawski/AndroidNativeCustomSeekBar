//
// Created by Michal.Kawski on 23.01.2026.
//

#include "App/Context.h"

#include "Drawing/SkiaDrawer.h"

namespace App {

    Context::~Context()
    {
        m_pSeekBarDrawer.reset();
    }

    Context& Context::GetInstance()
    {
        static Context instance;
        return instance;
    }

    void Context::Reset() {
        m_pSeekBarDrawer.reset();
    }

    Drawing::SkiaDrawer* Context::GetSkiaDrawer()
    {
        if (!m_pSeekBarDrawer) {
            m_pSeekBarDrawer = std::make_unique<Drawing::SkiaDrawer>();
        }

        return m_pSeekBarDrawer.get();
    }

} // App