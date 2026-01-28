//
// Created by Michal.Kawski on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_ISEEKPROXYFACTORY_H
#define CUSTOMSEEKBAR_ISEEKPROXYFACTORY_H

#include "ISeekProxy.h"
#include "IMediaController.h"

#include <memory>

namespace Core
{
    class ISeekProxyFactory {
    public:
        virtual ~ISeekProxyFactory() = default;
        virtual std::unique_ptr<ISeekProxy> Create(IMediaController& mediaController, int64_t durationMs) = 0;
    };
} // Core

#endif //CUSTOMSEEKBAR_ISEEKPROXYFACTORY_H
