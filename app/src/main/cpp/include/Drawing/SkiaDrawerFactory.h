//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_SKIADRAWERFACTORY_H
#define CUSTOMSEEKBAR_SKIADRAWERFACTORY_H

#include "ISkiaDrawerFactory.h"

#include "SkiaDrawer.h"

namespace Drawing
{
    class SkiaDrawerFactory : public ISkiaDrawerFactory
    {
    public:
        ISkiaDrawer& GetInstance() override
        {
            return SkiaDrawer::GetInstance();
        }
    };
} // Drawing

#endif //CUSTOMSEEKBAR_SKIADRAWERFACTORY_H
