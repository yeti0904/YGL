# YGL
Yeti's Graphics Library

## Build
```
make
```

This will create a static library called libygl.a

## Usage
Add this to the top of your code
```
#include <SDL2/SDL.h>
#define YGL_USE_SDL
#include <YGL.h>
```
And compile linking libygl.a and with these flags:
```
-lSDL2 -lm
```
