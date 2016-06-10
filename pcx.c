#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <io.h>
#include <conio.h>
#pragma hdrstop
#include "mcgaunit.h"

#define byte unsigned char
#define word unsigned short

typedef struct {
  byte Manufacturer;
  byte Version;
  byte Encoding;
  byte BitsPerPixel;
  word XMin, YMin;
  word XMax, YMax;
  word HRes;
  word VRes;
  byte Palette[48];
  byte Reserved;
  byte ColorPlanes;
  word BytesPerLine;
  word PaletteType;
  byte Filler[58];
} T_PCXHeader;

T_PCXHeader Header;
FILE *filee;


void Quit (char *error)
{
  if (strcmp(error, "NOERROR"))
    printf ("%s\n", error);
  asm mov ah,0x4c
  asm int 0x21
}

void PPixel (word ofs, unsigned char Color, int Where)
{
  asm mov es,Where
  asm mov di,ofs
  asm mov al,Color
  asm stosb
}

void Unpack (void)
{
  byte k, loop;
  word j, i, Max, v;
  word Ofs = 0;

  Max = Header.YMax+Header.YMin+1;
  fseek (filee, 128, SEEK_SET);
  for (i = 0; i <= Max; i++) {
    j = 0;
    while (j < Header.BytesPerLine) {
      fread (&v, 1, 1, filee);
      if ((v & 192) == 192) {
        loop = v & 63;
        j += loop;
        fread (&v, 1, 1, filee);
        for (k = 1; k <= loop; k++) {
          PPixel (Ofs, v, VGA);
          Ofs++;
        }
      } else {
        PPixel (Ofs, v, VGA);
        Ofs++;
        j++;
      }
    }
  }
}

void LoadPal (void)
{
  byte Pal[767];
  word i;
  byte i2;

  fseek (filee, -768, SEEK_END);
  fread (&Pal, 1, 768, filee);
  asm mov dx,0x3c8
  asm xor al,al
  asm out dx,al
  asm mov dx,0x3c9
  for (i = 0; i <= 767; i++) {
    i2 = Pal[i];
    asm mov al,i2
    asm shr al,2
    asm out dx,al
  }
}

void LoadPCX (char *filename)
{
  byte b;

  filee = fopen (filename, "rb");
  if (filee == NULL) Quit ("cannot open file!");
  fread (&Header, sizeof(T_PCXHeader), 1, filee);
  if (Header.Manufacturer != 10 || Header.Version != 5 ||
      Header.BitsPerPixel != 8 || Header.ColorPlanes != 1) Quit ("PCX type not supported!");
  fseek (filee, -769, SEEK_END);
  fread (&b, sizeof(byte), 1, filee);
  if (b != 12) Quit ("Invalid palette!");
  SetVideoMode (MCGA);
  LoadPal ();
  Unpack ();
}

void main (int argc, char *argv[])
{
  if (argc <= 1) return;
  LoadPCX (argv[1]);
  getch ();
  SetVideoMode (TEXT);
  fclose (filee);
}
