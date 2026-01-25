//
// Created by Michal.Kawski on 23.01.2026.
//

#ifndef CUSTOMSEEKBAR_CONTEXT_H
#define CUSTOMSEEKBAR_CONTEXT_H

#include <memory>

namespace Drawing {
    class SeekBarDrawer;
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

        Drawing::SeekBarDrawer& GetSeekBarDrawer();

    private:
        Context();
        ~Context();

        std::unique_ptr<Drawing::SeekBarDrawer> m_pSeekBarDrawer;
    };

} // App

#endif //CUSTOMSEEKBAR_CONTEXT_H
