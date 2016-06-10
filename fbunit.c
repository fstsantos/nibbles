#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include "fbunit.h"
#pragma hdrstop


FB_FontMask huge *FB_Font[76];
unsigned int FB_XSize;
unsigned int FB_YSize;


void FB_PlotPixel (int x, int y, unsigned char Color, int Where)
{
  asm mov es,Where
  asm mov ax,y
  asm shl ax,8
  asm mov di,ax
  asm shr di,2
  asm add di,ax
  asm add di,x
  asm mov al,Color
  asm stosb
}

int FB_ReserveMem (void)
{
  int i, i2, i3;

  for (i = 0; i <= 76; i++)
    FB_Font[i] = (FB_FontMask huge *) farmalloc (3600);
  if (FB_Font == NULL) return 0;
  for (i = 0; i <= 75; i++)
    for (i2 = 0; i2 <= 60; i2++)
      for (i3 = 0; i3 <= 60; i3++)
        FB_Font[i]->Mask[i2][i3] = 0;
  return 1;
}

void FB_FreeMem (void)
{
  farfree (FB_Font);
}

int FB_LoadFont (char *filename)
{
  int x, y, size;
  FILE *in;

  in = fopen (filename, "rb");
  if (in == NULL) return 0;
  FB_XSize = fgetc (in);
  FB_YSize = fgetc (in);
  for (size = 0; size <= 75; size++)
    for (y = 0; y <= FB_YSize; y++)
      for (x = 0; x <= FB_XSize; x++)
        FB_Font[size]->Mask[y][x] = fgetc (in);
  fclose (in);
  return 1;
}

void FB_PutChar (int chr, int x, int y)
{
  int i, i2;

  for (i = y; i <= y+FB_YSize-1; i++)
    for (i2 = x; i2 <= x+FB_XSize-1; i2++)
      FB_PlotPixel (i2, i, FB_Font[chr-48]->Mask[i-y][i2-x], 0x0a000);
}

void FB_PutStr (char *str, int x, int y)
{
  int pos, i, i2;
  char chr;

  for (pos = 0; pos < strlen(str); pos++) {
    chr = str[pos];
    for (i = y; i <= y+FB_YSize-1; i++)
      for (i2 = x; i2 <= x+FB_XSize-1; i2++)
        FB_PlotPixel (i2, i, FB_Font[chr-48]->Mask[i-y][i2-x], 0x0a000);
    x += FB_XSize;
  }
}
