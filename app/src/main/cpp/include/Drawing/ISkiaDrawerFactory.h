//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_ISKIADRAWERFACTORY_H
#define CUSTOMSEEKBAR_ISKIADRAWERFACTORY_H

#include "ISkiaDrawer.h"

#include <memory>

namespace Drawing
{
    class ISkiaDrawerFactory
    {
    public:
        virtual ~ISkiaDrawerFactory() = default;
        virtual ISkiaDrawer& GetInstance() = 0;
    };
} // Drawing

#endif //CUSTOMSEEKBAR_ISKIADRAWERFACTORY_H
