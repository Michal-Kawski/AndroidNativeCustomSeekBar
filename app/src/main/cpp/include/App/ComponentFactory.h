//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_COMPONENTFACTORY_H
#define CUSTOMSEEKBAR_COMPONENTFACTORY_H

#include "IComponentFactory.h"

#include "Core/SeekProxyFactory.h"
#include "Drawing/SkiaDrawerFactory.h"

namespace App
{
    class ComponentFactory : public IComponentFactory {
    public:
        std::unique_ptr<Core::ISeekProxyFactory> GetSeekProxyFactory()
        {
            return std::make_unique<Core::SeekProxyFactory>();
        }

        std::unique_ptr<Drawing::ISkiaDrawerFactory> GetSkiaDrawerFactory()
        {
            return std::make_unique<Drawing::SkiaDrawerFactory>();
        }
    };

} // App

#endif //CUSTOMSEEKBAR_COMPONENTFACTORY_H
