#pragma once

#include <libsystem/unicode/Codepoint.h>

int font_height();

int font_width();

void font_draw(Codepoint cp, int x, int y);
