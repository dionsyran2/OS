#include <stddef.h>
#include <stdint.h>
#include "BasicRenderer.h"
#include "cstr.h"
#include "Framebuffer.h"
#include "SimpleFonts.h"
#include "efiMemory.h"

struct BootInfo
{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	void* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;

};


extern "C" void _start(BootInfo* bootInfo, PSF1_FONT* psf1_font){
    Framebuffer* framebuffer = bootInfo->framebuffer;
    PSF1_FONT* Psf1_font = bootInfo->psf1_font;




    BasicRenderer newRenderer = BasicRenderer(framebuffer, Psf1_font);
    newRenderer.colour = 0x0ff00ffff;
    newRenderer.Print(to_string((uint64_t)1234976));
    newRenderer.CursorPosition = {0, 16}; 
    newRenderer.Print(to_string((int64_t)-1234976));
    newRenderer.colour = 0x00ff00ff;


    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    for (int i = 0; i < mMapEntries; i++){
        newRenderer.colour = 0x00ff00ff;
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));
        newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
        newRenderer.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
        newRenderer.colour = 0x0000ffff;
        newRenderer.Print(" ");
        newRenderer.Print(to_string(desc->numPages * 4096 / 1024));
        newRenderer.Print(" ");
        newRenderer.colour = 0xff0f0fff;
        newRenderer.Print("KB");
    }

    return ;
}
