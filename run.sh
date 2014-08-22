#!/bin/sh
export SDL_VIDEODRIVER=omapdss
export LD_LIBRARY_PATH=./
export SDL_OMAP_FORCE_DOUBLEBUF=1
export SDL_OMAP_VSYNC=0
./shootet.pandora
