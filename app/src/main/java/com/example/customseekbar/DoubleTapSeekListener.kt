package com.example.customseekbar

import android.content.Context
import android.content.res.Resources
import android.view.GestureDetector
import android.view.MotionEvent
import kotlin.time.Duration.Companion.seconds


class DoubleTapSeekListener(
    context: Context,
    private val onSeek: (Long) -> Unit
) : GestureDetector.SimpleOnGestureListener() {

    private val screenWidth =
        Resources.getSystem().displayMetrics.widthPixels

    override fun onDoubleTap(e: MotionEvent): Boolean {
        val isLeftHalf = e.x < screenWidth / 2

        val seekDeltaMs: Long = if (isLeftHalf) {
            -10.seconds.inWholeMilliseconds // backward
        } else {
            +10.seconds.inWholeMilliseconds // forward
        }

        onSeek(seekDeltaMs)
        return true
    }
}
