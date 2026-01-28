//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_ICOMPONENTFACTORY_H
#define CUSTOMSEEKBAR_ICOMPONENTFACTORY_H

#include "Core/ISeekProxyFactory.h"
#include "Drawing/SkiaDrawerFactory.h"

#include <memory>

namespace App
{

    class IComponentFactory
    {
    public:
        virtual ~IComponentFactory() = default;
        virtual std::unique_ptr<Core::ISeekProxyFactory> GetSeekProxyFactory() = 0;
        virtual std::unique_ptr<Drawing::ISkiaDrawerFactory> GetSkiaDrawerFactory() = 0;
    };

} // App

#endif //CUSTOMSEEKBAR_ICOMPONENTFACTORY_H
