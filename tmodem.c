#include <dos.h>
#include <conio.h>
#include "tmodem.h"
#pragma hdrstop


#define THR 0x00
#define RDR 0x00
#define BRDL 0x00
#define BRDH 0x01
#define IER 0x01
#define IIR 0x02
#define LCR 0x03
#define MCR 0x04
#define LSR 0x05
#define MSR 0x06

int COM;
unsigned char IRQ;
char Buffer[4096];
int Head, Tail, Size;


void interrupt ( *OldISRHandler) ();

void interrupt ISRHandler ()
{
  unsigned char i;

  asm sti;
  i = inp(COM+IIR);
  if ((i & 0x06) == 0x04) {
    if (Head != Tail) {
      Buffer[Tail] = inp(COM+RDR);
      Tail++;
      if (Tail > 4096)
        Tail = 0;
    } else i = inp(COM+RDR);
  } else if ((i & 0x06) == 0x06)
           i = inp(COM+RDR);
  i = inp(COM+MSR);
  asm cli;
}

void LoadNewISR (void)
{
  if (COM == COM1) IRQ = 0x0C;
  if (COM == COM2) IRQ = 0x0B;
  if (COM == COM3) IRQ = 0x0C;
  if (COM == COM4) IRQ = 0x0B;
  OldISRHandler = getvect (IRQ);
  setvect (IRQ, ISRHandler);
}

void RestoreISR (void)
{
  setvect (IRQ, OldISRHandler);
}

void LowerDTR (void)
{
  outp(COM+MSR, (inp(COM+MCR) & ! 0x01));
}

void InitModem (int BaudRate, unsigned char Bits, char Parity, unsigned char TStop)
{
  unsigned char Stop, Par, bh, bl;
  int Baud;

  if (TStop == 1) Stop = 0x00;
  else Stop = 0x04;
//  if (Parity == "S") Par = 0x38;
//  if (Parity == "O") Par = 0x08;
//  if (Parity == "M") Par = 0x28;
//  if (Parity == "E") Par = 0x18;
//  if (Parity == "N") Par = 0x00;
  Par = Parity;
  Par = 0x00;
  switch (BaudRate) {
    case 19200 : Baud = 0x06;
                 break;
    case 38400 : Baud = 0x03;
                 break;
    case 57600 : Baud = 0x02;
                 break;
  }
  Baud = 0x03;
  outp(COM+LCR, 0x80);
  asm mov ax,Baud
  asm mov bh,ah
  asm mov bl,al
  outp(COM+BRDH, bh);
  outp(COM+BRDL, bl);
  outp(COM+LCR, (0x00 | Par | (Bits - 5) | Stop));
  outp(COM+MCR, 0x0B);
}

void SendToModem (char *Line)
{
  unsigned char i, i2, i3;

  i3 = 2000;
  for (i = 1; i <= sizeof(Line); i++) {
    i2 = 0;
    while ( ((inp(COM+LSR & 0x20)) == 0) || (i2 > i3) ) {
      i2++;
    }
    if (i2 < i3)
      outp(COM+THR, Line[i]); 
  }
}

void HangupModem (void)
{
  LowerDTR ();
  delay (500);
  SendToModem ("+++");
  delay (1000);
  SendToModem ("ATH0"+13);
}
