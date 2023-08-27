# YGL
Yeti's Graphics Library

Make sure to clone recursively

## Build
```
make
```

This will create a static library called libygl.a

See info about parameters you can pass below (this is very important)

## Usage
Using YGL requires you to pick a backend

Available backends
- SDL (uses SDL2, macro: `YGL_USE_SDL`)
- SDL1 (uses SDL 1.2, macro: `YGL_USE_SDL1`)

In the YGL makefile and example makefile, you can select them by adding `backend=(backend here)` to the parameters to `make` (the examples only support SDL2 though)

In your YGL project, link your chosen backend

YGL can be used with no backend, programs will be mostly the same except you can't create/use windows

## Custom backends
YGL allows you to create custom backends

Using a custom library in YGL works like this:
- Compile YGL, passing `backend=custom` to the makefile
- In your code, create a header file containing the backend info
- In the header, create a `YGL_BackendWindow` structure, this contains info about the window
- Add a `null` member to the `YGL_BackendWindow` structure of type `bool`
- Add members containing window structures from your backend
- Include YGL after the structure definition, and include your header file in all source files using YGL
- Create a source file to contain backend functions
- Create functions that do these things:
	* initialise your backend (no parameters)
	* free your backend (no parameters)
	* create a window (`char* name, int w, int h`) returning `YGL_BackendWindow`
	* free a window (`YGL_BackendWindow* window`)
	* draw the window from a canvas (`YGL_Canvas* canvas, YGL_BackendWindow* window`)
- create an instance of [YGL_Backend](https://github.com/yeti0904/YGL/blob/main/source/backend.h#L21-L30)
- set the function pointers in it to the functions you made
- set the null member to false
- pass it to `YGL_SetBackend`
- YGL is now using your backend
