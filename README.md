ImageResize
===========

Image resizing tool using OpenCV

Following 5 interpolation methods are supported:

* INTER_NEAREST - a nearest-neighbor interpolation
* INTER_LINEAR - a bilinear interpolation (used by default)
* INTER_AREA - resampling using pixel area relation. It may be a preferred method for image decimation, as it gives moire’-free results. But when the image is zoomed, it is similar to the INTER_NEAREST method.
* INTER_CUBIC - a bicubic interpolation over 4x4 pixel neighborhood
* INTER_LANCZOS4 - a Lanczos interpolation over 8x8 pixel neighborhood
