//
// Created by Michal.Kawski on 23.01.2026.
//

#include "../../include/App/Context.h"

#include "Drawing/SkiaDrawer.h"

namespace App {

    Context::Context()
    {
        m_pSeekBarDrawer = std::make_unique<Drawing::SkiaDrawer>();
    }

    Context::~Context()
    {
        m_pSeekBarDrawer.reset();
    }

    Context& Context::GetInstance()
    {
        static Context instance;
        return instance;
    }

    Drawing::SkiaDrawer& Context::GetSkiaDrawer()
    {
        return *m_pSeekBarDrawer;
    }

} // App