
/*  default_theme.h                                                      */

#ifndef DEFAULT_THEME_H
#define DEFAULT_THEME_H

#include "scene/resources/theme.h"

void fill_default_theme(Ref<Theme> &theme, const Ref<Font> &default_font, const Ref<Font> &large_font, Ref<Texture2D> &default_icon, Ref<StyleBox> &default_style, float p_scale);
void make_default_theme(bool p_hidpi, Ref<Font> p_font);
void clear_default_theme();

#endif
