# Qart

Quadtree generated images.

This program is a visualization of an "image compression" algorithm based on the use of Quadtrees. The image is split in four sub-squares. Then each square is assigned an averaged color based on the colors from the parent square, and calculates its error (difference between the averaged color and the real ones, divided by the width of the square). Every frame, the square with the highest error is split into its four sub-squares, refining the image. This process is repeated N times until all the squares have an error of 0.

## Release versions

Precompiled versions for Windows and Linux
* [Qart 1.0.0 Linux](https://github.com/Dibad/Qart/releases/download/v1.0.0/Qart-1.0.0-linux.tar.gz)
* [Qart 1.0.0 Windows](https://github.com/Dibad/Qart/releases/download/v1.0.0/Qart-1.0.0-windows.zip)

## Build

* ### On Linux

Take note that SDL2 and SDL2_image dependencies must be installed first by running the following commands:
```
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-dev
```
Clone the repo and make.
```
$ git clone https://github.com/Dibad/Qart
$ cd Qart
$ make
```


## Examples
View of the iterative process with every quadtree outlined (Stopped after 4029 iterations, with 12088 squares created).
![Cat](https://i.imgur.com/5mDiqZB.gif)<p>
And a view of the same process but without outlines.
![Cat2](https://i.imgur.com/MIi4Gxr.gif)

## Acknowledgments

This project idea was shared by [Michael Fogleman](https://github.com/fogleman), so please check his fantastic implementation in Python. [Link to his repository](https://github.com/fogleman/Quads)
