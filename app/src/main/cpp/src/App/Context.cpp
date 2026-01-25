//
// Created by Michal.Kawski on 23.01.2026.
//

#include "../../include/App/Context.h"

#include "Drawing/SeekBarDrawer.h"

namespace App {

    Context::Context()
    {
        m_pSeekBarDrawer = std::make_unique<Drawing::SeekBarDrawer>();
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

    Drawing::SeekBarDrawer& Context::GetSeekBarDrawer()
    {
        return *m_pSeekBarDrawer;
    }

} // App