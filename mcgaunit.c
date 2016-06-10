#include <dos.h>
#include <stdlib.h>
#include <time.h>
#include "mcgaunit.h"
#pragma hdrstop


#define byte unsigned char


pal palette, fadepal;

void SetVideoMode (int type)
{
  asm mov ax,type
  asm int 0x10
}

void PlotPixel (int x, int y, unsigned char Color, int Where)
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

void Cls (unsigned char Color, int Where)
{
  asm mov es,Where
  asm xor di,di
  asm mov ah,Color
  asm mov al,ah
  asm mov cx,32000
  asm rep stosw
}

void SetPal (unsigned char Color, unsigned char R, unsigned char G, unsigned char B)
{
  asm mov dx,0x3c8
  asm mov al,Color
  asm out dx,al
  asm mov dx,0x3c9
  asm mov al,R
  asm out dx,al
  asm mov al,G
  asm out dx,al
  asm mov al,B
  asm out dx,al
}

rgb GetPal (unsigned char Color)
{
  rgb i;
  unsigned char r, g, b;

  asm mov dx,0x3c7
  asm mov al,Color
  asm out dx,al
  asm mov dx,0x3c9
  asm in al,dx
  asm mov r,al
  asm in al,dx
  asm mov g,al
  asm in al,dx
  asm mov b,al
  i.R = r;
  i.G = g;
  i.B = b;
  return i;
}

void SavePal (pal *palette)
{
  rgb color;
  unsigned int i;

  for (i = 0; i <= 255; i++) {
    color = GetPal (i);
    *palette[i][1] = color.R;
    *palette[i][2] = color.G;
    *palette[i][3] = color.B;
  }
}

void RestorePal (pal *palette)
{
  unsigned int i;

  for (i = 0; i <= 255; i++)
    SetPal (i, *palette[i][1], *palette[i][2], *palette[i][3]);
}

void InitFade (void)
{
  int i;
  rgb x;

  for (i = 0; i <= 255; i++) {
    x = GetPal (i);
    palette[i][1] = x.R;
    palette[i][2] = x.G;
    palette[i][3] = x.B;
    fadepal[i][1] = x.R;
    fadepal[i][2] = x.G;
    fadepal[i][3] = x.B;
  }
}

void FadeIn (int del)
{
  int i, i2;

  for (i = 0; i < 64; i++) {
    for (i2 = 0; i2 <= 255; i2++) {
      if (fadepal[i2][1] > 0) fadepal[i2][1]--;
      if (fadepal[i2][2] > 0) fadepal[i2][2]--;
      if (fadepal[i2][3] > 0) fadepal[i2][3]--;
      SetPal (i2, fadepal[i2][1], fadepal[i2][2], fadepal[i2][3]);
    }
  delay (del);
  }
}

void FadeOut (int del)
{
  int i, i2;

  for (i = 0; i < 64; i++) {
    for (i2 = 0; i2 <= 255; i2++) {
      if (fadepal[i2][1] < palette[i2][1]) fadepal[i2][1]++;
      if (fadepal[i2][2] < palette[i2][2]) fadepal[i2][2]++;
      if (fadepal[i2][3] < palette[i2][3]) fadepal[i2][3]++;
      SetPal (i2, fadepal[i2][1], fadepal[i2][2], fadepal[i2][3]);
    }
    delay (del);
  }
}

void Flash (unsigned char r, unsigned char g, unsigned char b, int del)
{
  int i, i2;

  for (i = 0; i <= 255; i++) {
    fadepal[i][1] = r;
    fadepal[i][2] = g;
    fadepal[i][3] = b;
  }
  for (i = 0; i < 64; i++) {
    for (i2 = 0; i2 <= 255; i2++) {
      if (fadepal[i2][1] > palette[i2][1]) fadepal[i2][1]--;
      else if (fadepal[i2][1] < palette[i2][1]) fadepal[i2][1]++;
      if (fadepal[i2][2] > palette[i2][2]) fadepal[i2][2]--;
      else if (fadepal[i2][2] < palette[i2][2]) fadepal[i2][2]++;
      if (fadepal[i2][3] > palette[i2][3]) fadepal[i2][3]--;
      else if (fadepal[i2][3] < palette[i2][3]) fadepal[i2][3]++;
      SetPal (i2, fadepal[i2][1], fadepal[i2][2], fadepal[i2][3]);
    }
    delay (del);
  }
}

void PixelFade (unsigned char Color, int del, int Where)
{
  long int i;
  int i2;

  randomize();
  for (i = 0; i <= 64000; i++) {
    PlotPixel (random(320), random(200), Color, Where);
    for (i2 = 0; i2 <= del; i2++) asm nop;
  }
  Cls (Color, Where);
}

void WaitRetrace (void)
{
  asm mov dx,0x3da
horz:
  asm in al,dx
  asm test al,8
  asm jz horz
vert:
  asm in al,dx
  asm test al,8
  asm jnz vert
}

void Text (int x, int y, int Color, char *string, int Where)
{
  int i, mx, my;
  unsigned char b, chpos;

  for (i = 0; i <= sizeof(string); i++) {
    chpos = 0xfa68+string[i]*8;
    for (my = 0; my < 8; my++)
      for (mx = 0; mx < 8; mx++) {
        asm push ds
        asm mov ax,0xf000
        asm mov ds,ax
        asm mov si,chpos
        asm add si,my
        asm pop ax
        asm mov es,ax
        asm push ax
        asm mov di,offset b
        asm movsb
        asm shl b,mx
        asm and b,128
        asm pop ds
        asm cmp b,0
        asm jmp draw
        return;
      draw:
        asm mov es,Where
//        asm mov ax,y
//        asm add ax,my
//        asm mul ax,320
//        asm mov bx,i
//        asm mul bx,8
//        asm add ax,bx
//        asm add ax,x
//        asm add ax,mx
        b = (y+my)*320+(i*8)+x+mx;
        asm mov di,b
        asm mov al,Color
        asm stosb
      }
  }
}
