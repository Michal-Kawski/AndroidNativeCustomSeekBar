//
// Created by Michal.Kawski on 23.01.2026.
//

#ifndef CUSTOMSEEKBAR_CONTEXT_H
#define CUSTOMSEEKBAR_CONTEXT_H

#include <memory>

namespace Drawing {
    class SkiaDrawer;
} // Drawing

namespace App {

    class Context final {
    public:
        // Delete copy/move
        Context(const Context &) = delete;
        Context(Context &&) = delete;
        Context& operator=(const Context&) = delete;
        Context& operator=(Context&&) = delete;

        static Context& GetInstance();

        void Reset();

        Drawing::SkiaDrawer* GetSkiaDrawer(); // intention: we can hold the object through an app lifetime on cpp side when the instance is not coupled with an activity

    private:
        Context() = default;
        ~Context();

        std::unique_ptr<Drawing::SkiaDrawer> m_pSeekBarDrawer;
    };

} // App

#endif //CUSTOMSEEKBAR_CONTEXT_H
