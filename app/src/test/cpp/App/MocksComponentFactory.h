//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_MOCKSCOMPONENTFACTORY_H
#define CUSTOMSEEKBAR_MOCKSCOMPONENTFACTORY_H

#include <App/IComponentFactory.h>


class MocksComponentFactory : public App::IComponentFactory
{
public:
    std::unique_ptr<Core::ISeekProxyFactory> GetSeekProxyFactory() override;
    std::unique_ptr<Drawing::ISkiaDrawerFactory> GetSkiaDrawerFactory() override;
};

#endif //CUSTOMSEEKBAR_MOCKSCOMPONENTFACTORY_H
