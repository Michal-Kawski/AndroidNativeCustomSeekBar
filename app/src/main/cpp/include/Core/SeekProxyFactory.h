//
// Created by Kawa on 28.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKPROXYFACTORY_H
#define CUSTOMSEEKBAR_SEEKPROXYFACTORY_H

#include "ISeekProxyFactory.h"
#include "SeekProxy.h"

#include <memory>

namespace Core
{
    class SeekProxyFactory : public ISeekProxyFactory
    {
        std::unique_ptr<ISeekProxy> Create(IMediaController& mediaController, int64_t durationMs) override {
            return std::make_unique<SeekProxy>(mediaController, durationMs);
        }
    };
} // Core

#endif //CUSTOMSEEKBAR_SEEKPROXYFACTORY_H
