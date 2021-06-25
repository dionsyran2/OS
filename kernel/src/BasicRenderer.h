#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "SimpleFonts.h"

class BasicRenderer
{


public:
BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* PSF1_Font);
Point CursorPosition;
Framebuffer* targetFramebuffer;
PSF1_FONT* PSF1_Font;
unsigned int colour;
void Print(const char* str);
void putChar( char chr, unsigned int xOff, unsigned int yOff);
};
