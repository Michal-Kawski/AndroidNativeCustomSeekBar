package com.example.customseekbar

import android.annotation.SuppressLint
import android.os.Bundle
import android.view.GestureDetector
import android.view.MotionEvent
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView
import androidx.appcompat.app.AppCompatActivity
import kotlin.time.Duration.Companion.minutes
import com.example.customseekbar.SeekBarFactory.SeekBarFactory
import com.example.customseekbar.SeekBarFactory.Segment


private lateinit var gestureDetector: GestureDetector

class MainActivity : AppCompatActivity() {

    // Native seek bar tightly coupled life time to the activity
    private var nativeSeekBarManager: Long = 0 // Native object reference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        initSeekBar()

        gestureDetector = GestureDetector(
            this,
            DoubleTapSeekListener(this) { seekDeltaMs ->
                nativeOnDoubleTap(nativeSeekBarManager, seekDeltaMs)
            }
        )
    }

    @SuppressLint("ClickableViewAccessibility")
    fun initSeekBar() {
        val surfaceView = SurfaceView(this)
        setContentView(surfaceView)

        surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                nativeOnSurfaceCreated(holder.surface)

                val fiveMinutesMs: Long = 5.minutes.inWholeMilliseconds
                val yPositionPercent: Float = 0.9f; //create progress bar at 90% of screen height
                nativeSeekBarManager = nativeCreateProgressBar(yPositionPercent, fiveMinutesMs, SeekBarFactory().createSeekBarSegments())
            }

            override fun surfaceChanged(
                holder: SurfaceHolder,
                format: Int,
                width: Int,
                height: Int
            ) {
                nativeOnSurfaceChanged(width, height)
            }

            override fun surfaceDestroyed(holder: SurfaceHolder) {
                nativeOnSurfaceDestroyed()

                nativeDestroyProgressBar(nativeSeekBarManager)
            }
        })

        surfaceView.setOnTouchListener { _, event ->
            gestureDetector.onTouchEvent(event)

            when (event.actionMasked) {
                MotionEvent.ACTION_DOWN,
                MotionEvent.ACTION_MOVE,
                MotionEvent.ACTION_UP,
                MotionEvent.ACTION_CANCEL -> {
                    nativeOnSeekTouch(
                        nativeSeekBarManager,
                        event.x,
                        event.y,
                        event.actionMasked
                    )
                    true
                }
                else -> false
            }
        }
    }

    /**
     * A native method that is implemented by the 'customseekbar' native library,
     * which is packaged with this application.
     */
    external fun nativeOnSurfaceCreated(surface: Surface)
    external fun nativeOnSurfaceChanged(width: Int, height: Int)
    external fun nativeOnSurfaceDestroyed()
    external fun nativeCreateProgressBar(yPosition: Float, durationMs: Long, segments: ArrayList<Segment>): Long
    external fun nativeDestroyProgressBar(nativeSeekBarManager: Long)
    external fun nativeOnSeekTouch(nativeSeekBarManager: Long, x: Float, y: Float, actionMasked: Int)
    external fun nativeOnDoubleTap(nativeSekBarManager: Long, seekDeltaMs: Long)

    companion object {
        // Used to load the 'customseekbar' library on application startup.
        init {
            System.loadLibrary("customseekbar")
        }
    }
}