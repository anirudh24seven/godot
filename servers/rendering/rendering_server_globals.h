
/*  rendering_server_globals.h                                           */

#ifndef RENDERING_SERVER_GLOBALS_H
#define RENDERING_SERVER_GLOBALS_H

#include "rasterizer.h"

class RenderingServerCanvas;
class RenderingServerViewport;
class RenderingServerScene;

class RenderingServerGlobals {
public:
	static RasterizerStorage *storage;
	static RasterizerCanvas *canvas_render;
	static RasterizerScene *scene_render;
	static Rasterizer *rasterizer;

	static RenderingServerCanvas *canvas;
	static RenderingServerViewport *viewport;
	static RenderingServerScene *scene;
};

#define RSG RenderingServerGlobals

#endif // RENDERING_SERVER_GLOBALS_H
