#include <dos.h>
#pragma hdrstop
#include "menu.h"
#include "mcgaunit.h"
#include "fbunit.h"
#include "kbhandle.h"

//
// we assume that the font is already loaded and the palette
// already set by now
//

void InitMenu (t_menu menu)
{
  unsigned char i;

  for (i = 0; i < menu.total; i++)
    FB_PutStr (menu.options[i].text, menu.options[i].x, menu.options[i].y);
}

void DrawPointer (int x, int y, int color)
{
  PlotPixel (x-1, y, color, VGA);
  PlotPixel (x, y, color+1, VGA);
  PlotPixel (x-1, y+1, color, VGA);
  PlotPixel (x, y+1, color+1, VGA);
}

unsigned char LightBar (t_menu menu)
{
  unsigned char update = 1, pos = 0;

  while ((!KeyTable[K_ENTER]) && (!KeyTable[K_ESC])) {
    if (update) {
      DrawPointer (menu.options[pos].x-4, menu.options[pos].y, 45);
      RefreshKeyTable ();
      update = 0;
    }
    if (KeyTable[K_UP]) {
      DrawPointer (menu.options[pos].x-4, menu.options[pos].y, 0);
      pos--;
      if (pos == 255) pos = menu.total-1;
      update = 1;
    }
    if (KeyTable[K_DOWN]) {
      DrawPointer (menu.options[pos].x-4, menu.options[pos].y, 0);
      pos++;
      if (pos > menu.total-1) pos = 0;
      update = 1;
    }
  }
  if (KeyTable[K_ESC]) pos = 254;
  RefreshKeyTable ();
  pos++;
  return (pos);
}
