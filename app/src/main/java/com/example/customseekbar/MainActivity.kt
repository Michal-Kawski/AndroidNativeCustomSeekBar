package com.example.customseekbar

import android.annotation.SuppressLint
import android.os.Bundle
import android.view.MotionEvent
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView
import androidx.appcompat.app.AppCompatActivity
import com.example.customseekbar.SeekBarFactory.SeekBarFactory
import com.example.customseekbar.SeekBarFactory.Segment


class MainActivity : AppCompatActivity() {

    // Native seek bar tightly coupled life time to the activity
    private var nativeSeekBar: Long = 0 // Native object reference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        initSeekBar()
    }

    @SuppressLint("ClickableViewAccessibility")
    fun initSeekBar() {
        val surfaceView = SurfaceView(this)
        setContentView(surfaceView)

        surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                nativeOnSurfaceCreated(holder.surface)

                nativeSeekBar = nativeCreateProgressBar(0.9f, SeekBarFactory().createSeekBarSegments())
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

                nativeDestroyProgressBar(nativeSeekBar)
            }
        })

        surfaceView.setOnTouchListener { _, event ->
            when (event.actionMasked) {
                MotionEvent.ACTION_DOWN,
                MotionEvent.ACTION_MOVE,
                MotionEvent.ACTION_UP,
                MotionEvent.ACTION_CANCEL -> {
                    nativeOnSeekTouch(
                        nativeSeekBar,
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
    external fun nativeCreateProgressBar(yPosition: Float, segments: ArrayList<Segment>): Long
    external fun nativeDestroyProgressBar(nativeSeekBar: Long)
    external fun nativeOnSeekTouch(nativeSeekBar: Long, x: Float, y: Float, actionMasked: Int)

    companion object {
        // Used to load the 'customseekbar' library on application startup.
        init {
            System.loadLibrary("customseekbar")
        }
    }
}