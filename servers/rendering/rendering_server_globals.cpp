
/*  rendering_server_globals.cpp                                         */



#include "rendering_server_globals.h"

RasterizerStorage *RenderingServerGlobals::storage = nullptr;
RasterizerCanvas *RenderingServerGlobals::canvas_render = nullptr;
RasterizerScene *RenderingServerGlobals::scene_render = nullptr;
Rasterizer *RenderingServerGlobals::rasterizer = nullptr;

RenderingServerCanvas *RenderingServerGlobals::canvas = nullptr;
RenderingServerViewport *RenderingServerGlobals::viewport = nullptr;
RenderingServerScene *RenderingServerGlobals::scene = nullptr;
