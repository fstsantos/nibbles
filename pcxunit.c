#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <io.h>
#include <conio.h>
#pragma hdrstop
#include "pcxunit.h"


FILE *filee;


void Unpack (T_PCX *PCX)
{
  byte k, loop;
  word j, i, Max, v;
  word Ofs = 0;

  Max = PCX->Header.YMax+PCX->Header.YMin+1;
  fseek (filee, 128, SEEK_SET);
  for (i = 0; i <= Max; i++) {
    j = 0;
    while (j < PCX->Header.BytesPerLine) {
      fread (&v, 1, 1, filee);
      if ((v & 192) == 192) {
        loop = v & 63;
        j += loop;
        fread (&v, 1, 1, filee);
        for (k = 1; k <= loop; k++) {
          PCX->Image[Ofs] = v;
          Ofs++;
        }
      } else {
        PCX->Image[Ofs] = v;
        Ofs++;
        j++;
      }
    }
  }
}

void LoadPal (T_PCX *PCX)
{
  fseek (filee, -768, SEEK_END);
  fread (&PCX->Pal, 1, 768, filee);
}

int LoadPCX (char *filename, T_PCX *PCX)
{
  byte b;

  filee = fopen (filename, "rb");
  if (filee == NULL) return 0;
  fread (&PCX->Header, sizeof(T_PCXHeader), 1, filee);
  if (PCX->Header.Manufacturer != 10 || PCX->Header.Version != 5 ||
      PCX->Header.BitsPerPixel != 8 || PCX->Header.ColorPlanes != 1) return 0;
  fseek (filee, -769, SEEK_END);
  fread (&b, sizeof(byte), 1, filee);
  if (b != 12) return 0;
  LoadPal (PCX);
  Unpack (PCX);
  return 1;
}

void LoadPCXPal (T_PCX *PCX)
{
  byte i2;
  word i;

  asm mov dx,0x3c8
  asm xor al,al
  asm out dx,al
  asm mov dx,0x3c9
  for (i = 0; i <= 767; i++) {
    i2 = PCX->Pal[i];
    asm mov al,i2
    asm shr al,2
    asm out dx,al
  }
}

void ShowPCX (T_PCX *PCX, word Where)
{
  word i, ofs;

  for (ofs = 0; ofs <= 63999; ofs++) {
    i = PCX->Image[ofs];
    asm mov es,Where
    asm mov di,ofs
    asm mov al,i
    asm stosb
  }
}
