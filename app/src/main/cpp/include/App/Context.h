//
// Created by Michal.Kawski on 23.01.2026.
//

#ifndef CUSTOMSEEKBAR_CONTEXT_H
#define CUSTOMSEEKBAR_CONTEXT_H

#include "IComponentFactory.h"

#include <memory>

namespace Drawing {
    class ISkiaDrawer;
} // Drawing

namespace Core {
    class ISeekProxyFactory;
} // Core

namespace App {

    class Context final {
    public:
        // Delete copy/move
        Context(const Context &) = delete;
        Context(Context &&) = delete;
        Context& operator=(const Context&) = delete;
        Context& operator=(Context&&) = delete;

        static Context& GetInstance();

        void SetComponentFactory(std::unique_ptr<IComponentFactory> pComponentFactory);
        IComponentFactory* GetComponentFactory();

        Drawing::ISkiaDrawer* GetSkiaDrawer();
    private:
        Context() = default;
        ~Context() = default;

        std::unique_ptr<IComponentFactory> m_pComponentFactory;
    };

} // App

#endif //CUSTOMSEEKBAR_CONTEXT_H
