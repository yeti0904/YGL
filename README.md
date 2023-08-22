# YGL
Yeti's Graphics Library

## Build
```
make
```

This will create a static library called libygl.a

## Usage
Using YGL requires you to pick a backend

Available backends
- SDL (uses SDL2, macro: `YGL_USE_SDL`)
- SDL1 (uses SDL 1.2, macro: `YGL_USE_SDL1`)

In the YGL makefile and example makefile, you can select them by adding `backend=(backend here)` to the parameters to `make` (the examples only support SDL2 though)

In your YGL project, choose the backend by defining the backend macro in your code or compile arguments, and then linking the backend you have chosen
