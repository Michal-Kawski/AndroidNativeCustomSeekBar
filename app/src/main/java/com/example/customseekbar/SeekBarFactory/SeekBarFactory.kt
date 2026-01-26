package com.example.customseekbar.SeekBarFactory

import java.util.ArrayList

class SeekBarFactory {

    /*
    The intention of the class is just to provide some input data for demonstration and testing purposes.
    * */
    private class SegmentMock {
        fun getSegments6Sections(): ArrayList<Segment> {
            return arrayListOf(
                Segment(0.0f, 0.12f, Color.RED),
                Segment(0.12f, 0.28f, Color.RED),
                Segment(0.28f, 0.4f, Color.RED),
                Segment(0.4f, 0.55f, Color.RED),
                Segment(0.55f, 0.78f, Color.RED),
                Segment(0.78f, 1.0f, Color.RED)
            )
        }

        fun getSegments6SectionsMultipleColors(): ArrayList<Segment> {
            return arrayListOf(
                Segment(0.0f, 0.12f, Color.RED),
                Segment(0.12f, 0.28f, Color.BLUE),
                Segment(0.28f, 0.4f, Color.WHITE),
                Segment(0.4f, 0.55f, Color.BLUE),
                Segment(0.55f, 0.78f, Color.RED),
                Segment(0.78f, 1.0f, Color.BLUE)
            )
        }

        fun getSegments5Sections(): ArrayList<Segment> {
            return arrayListOf(
                Segment(0.0f, 0.15f, Color.WHITE),
                Segment(0.15f, 0.32f, Color.RED),
                Segment(0.32f, 0.45f, Color.BLUE),
                Segment(0.45f, 0.65f, Color.RED),
                Segment(0.65f, 0.1f, Color.WHITE)
            )
        }
    }

    fun createSeekBarSegments(): ArrayList<Segment> {
        return SegmentMock().getSegments6Sections()
    }
}
