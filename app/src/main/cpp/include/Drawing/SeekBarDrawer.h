//
// Created by Michal.Kawski on 23.01.2026.
//

#ifndef CUSTOMSEEKBAR_SEEKBARDRAWER_H
#define CUSTOMSEEKBAR_SEEKBARDRAWER_H

#include <core/SkRefCnt.h>

#include <cstdint>
#include <memory>

class ANativeWindow;
class GrDirectContext;
class SkSurface;

namespace Drawing {

    class SeekBarDrawer final {
    public:
        void OnSurfaceCreated(ANativeWindow* pWindow);

    private:
        void DrawSeekBar();
        bool InitSkia();

        static ANativeWindow *s_pWindow; // the Kotlin side is the owner
        static sk_sp<GrDirectContext> s_pContext;
        static sk_sp<SkSurface> s_pSurface;
    };

} // Drawing

#endif //CUSTOMSEEKBAR_SEEKBARDRAWER_H
