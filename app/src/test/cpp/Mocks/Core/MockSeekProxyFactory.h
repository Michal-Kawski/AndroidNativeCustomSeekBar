//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_MOCKSEEKPROXYFACTORY_H
#define CUSTOMSEEKBAR_MOCKSEEKPROXYFACTORY_H

#include "MockSeekProxy.h"

#include <Core/ISeekProxyFactory.h>

namespace Core
{
    class MockSeekProxyFactory : public ISeekProxyFactory
    {
    public:
        std::unique_ptr<ISeekProxy> Create(IMediaController& mediaController, int64_t durationMs) override
        {
            return std::make_unique<>();
        }
    };
} // Core

#endif //CUSTOMSEEKBAR_MOCKSEEKPROXYFACTORY_H
