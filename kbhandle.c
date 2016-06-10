#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "kbhandle.h"
#pragma hdrstop

#define INT 0x09

// refresh variables
unsigned char KeyTable[127];
unsigned char Pressed;

unsigned char LastKey;

void interrupt ( *OldKBHandler) ();

void interrupt KBHandler ()
{
  unsigned char i, ScanCode, KeyCode;

  ScanCode = inp(0x60);
  if (ScanCode != LastKey) Pressed = 1;
  else Pressed = 0;
  LastKey = ScanCode;
  KeyCode = ScanCode & 0x7F;
  if (!(ScanCode & 0x80)) KeyTable[KeyCode] = 1;
  else KeyTable[KeyCode] = 0;
  i = inp(0x61);
  outp(0x61, i | 0x80);
  outp(0x61, i);
  outp(0x20, 0x20);
}

void RefreshKeyTable (void)
{
  unsigned char i;

  for (i = 0; i <= 127; i++)
    KeyTable[i] = 0;
}

void LoadNewInt09 (void)
{
  RefreshKeyTable ();
  OldKBHandler = getvect (INT);
  setvect (INT, KBHandler);
}

void RestoreInt09 (void)
{
  setvect (INT, OldKBHandler);
}
