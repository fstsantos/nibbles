#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <string.h>
#include <graphics.h>
#include <alloc.h>
#pragma hdrstop
#include "mcgaunit.h"
#include "kbhandle.h"
#include "menu.h"
#include "tmodem.h"
#include "pcxunit.h"
#include "fbunit.h"


#define byte unsigned char
#define Cima 1
#define Baixo 2
#define Esquerda 3
#define Direita 4

const int XMin = 0;
const int XMax = 316;
const int YMin = 2;
const int YMax = 182;

const byte Levels = 1;          // game with levels
const byte CellPhone = 2;       // cell phone nibbles style
const byte Survive = 3;         // no blocks, the nibbles and the score grow at every move

typedef struct
{
  int x;
  int y;
  byte Direction;
} xy;

typedef struct
{
  byte Direction;
  int Size;
  byte Color;
  int Velocity;
  int Score;
  byte Lives;
  byte Dead;
  byte Level;
  xy *Body;
} T_Nibbles;

typedef struct
{
  byte Number;
  byte Color;
  int x;
  int y;
} T_Blocks;


T_Nibbles    Player1;                     
T_Blocks     Blocks;
int          TotalBlocks = 10;
t_menu       menu1, menu1_1;
T_PCX       *PCX_Menu;
pal         *NormalPalette;
byte         GameType = 3;
byte         NearWall = 0;         // if the nibbles is going to hit itself or a wall
                                   // slow down a little, so its not that hard
                                   // just like in the cell phone


// prototypes
void         Quit (char *error);
void         DrawBlock (int x, int y, byte Color, int Where);
void         UpdateScreen (T_Nibbles Player);
void         DrawScreenLimits (byte Color);
void         CalcBlockPosition (T_Nibbles Player);
T_Nibbles    SetupNewGame (void);
T_Nibbles    PlayerDied (T_Nibbles Player);
T_Nibbles    AddPlayer (T_Nibbles Player);
T_Nibbles    NextLevel (T_Nibbles Player);
T_Nibbles    CheckLimits (T_Nibbles Player);
T_Nibbles    UpdatePlayer (T_Nibbles Player);
void         Menu1 (void);
void         Menu1_1 (void);
void         GameLoop (void);
void         Init (void);


void Quit (char *error)
{
  FadeIn (10);
  SetVideoMode (TEXT);
  if (strcmp(error, "NOERROR"))
    printf ("%s\n", error);
  FB_FreeMem ();
  free (PCX_Menu);
  free (NormalPalette);
  free (menu1.options);
  free (menu1_1.options);
  RestoreInt09();
  asm mov ah,0x4c
  asm int 0x21
}

void DrawBlock (int x, int y, byte Color, int Where)
{
  asm mov bx,4
loopline:
  asm mov es,Where
  asm mov ax,y
  asm shl ax,8
  asm mov di,ax
  asm shr di,2
  asm add di,ax
  asm add di,x
  asm mov al,Color
  asm mov cx,4
looppixel:
  asm mov [es:di],al
  asm inc di
  asm loopnz looppixel
  asm inc y
  asm dec bx
  asm cmp bx,0
  asm jne loopline
}

void UpdateScreen (T_Nibbles Player)
{
  int i;
  char *str = "                                                                         ";

  for (i = 1; i <= Player.Size; i++)
    DrawBlock (Player.Body[i].x, Player.Body[i].y, Player.Color, VGA);
  if (GameType != Survive) DrawBlock (Blocks.x, Blocks.y, Blocks.Color, VGA);
  WaitRetrace ();
  asm mov es,VGA
  asm mov ax,190
  asm shl ax,8
  asm mov di,ax
  asm shr di,2
  asm add di,ax
  asm xor ax,ax
  asm mov cx,1600
looppixel:
  asm mov [es:di],ax
  asm inc di
  asm inc di
  asm loopnz looppixel
  if (GameType == Levels) sprintf (str, "score]%i]]]]]lives]%i]]]]]blocks]%i]]]]]level]%i", Player.Score, Player.Lives, Blocks.Number, Player.Level);
  if (GameType == CellPhone) sprintf (str, "score]%i", Player.Score);
  if (GameType == Survive) sprintf (str, "score]%i", Player.Score);
  FB_PutStr (str, 5, 190);
}

void DrawScreenLimits (byte Color)
{
  int i;

  for (i = XMin; i <= XMax; i++)
    DrawBlock (i, YMin, Color, VGA);
  for (i = YMin; i <= YMax; i++)
    DrawBlock (XMin, i, Color, VGA);
  for (i = XMin; i <= XMax; i++)
    DrawBlock (i, YMax, Color, VGA);
  for (i = YMin; i <= YMax; i++)
    DrawBlock (XMax, i, Color, VGA);
}

void CalcBlockPosition (T_Nibbles Player)
{
  byte found = 0;
  int i;

  while (!found) {
    Blocks.x = random(XMax-2)+2;
    Blocks.x = Blocks.x - (Blocks.x % 4);
    if (Blocks.x <= XMin) Blocks.x += 4;
    if (Blocks.x >= XMax) Blocks.x -= 4;
    Blocks.y = random(YMax-2)+2;
    Blocks.y = Blocks.y - (Blocks.y % 4);
    Blocks.y += 2;
    if (Blocks.y <= YMin) Blocks.y += 4;
    if (Blocks.y >= YMax) Blocks.y -= 4;
    for (i = 1; i <= Player.Size; i++)
      if ((Blocks.x == Player.Body[i].x) && (Blocks.y == Player.Body[i].y))
         found = 0;
      else return;
  }
}

T_Nibbles SetupNewGame (void)
{
  byte i, i2;
  T_Nibbles x;

  Cls (0, VGA);
  x.Direction = Direita;
  x.Size = 6;
  x.Color = 9;
  x.Velocity = 35;
  x.Score = 0;
  x.Lives = 3;
  x.Dead = 0;
  x.Level = 1;
  x.Body = (xy *) malloc (1000*sizeof(xy));
  i2 = 20;
  for (i = 1; i <= x.Size; i++) {
    x.Body[i].x = i2;
    x.Body[i].y = 170;
    x.Body[i].Direction = Direita;
    i2 += 4;
  }
  if (GameType != Survive) CalcBlockPosition (x);
  Blocks.Number = 10;
  Blocks.Color = 95;
  DrawScreenLimits (3);
  return x;
}

T_Nibbles PlayerDied (T_Nibbles Player)
{
  byte i, i2;
  T_Nibbles x;

  x = Player;
  x.Lives--;
//  if (x.Lives == 0)
  if (GameType != Levels) x.Lives = 0;
  Cls (0, VGA);
  x.Direction = Direita;
  x.Size = 6;
  x.Color = 9;
  x.Dead = 0;
  i2 = 20;
  for (i = 1; i <= x.Size; i++) {
    x.Body[i].x = i2;
    x.Body[i].y = 170;
    x.Body[i].Direction = Direita;
    i2 += 4;
  }
  if (GameType != Survive) CalcBlockPosition (x);
  DrawScreenLimits (3);
  return x;
}

T_Nibbles AddPlayer (T_Nibbles Player)
{
  int i;
  xy *BodySave;
  T_Nibbles x;

  x = Player;
  BodySave = (xy *) malloc (1000*sizeof(xy));
  for (i = 1; i <= Player.Size; i++)
    BodySave[i] = Player.Body[i];
  for (i = 2; i <= Player.Size+1; i++)
    x.Body[i] = BodySave[i-1];
  switch (Player.Body[2].Direction) {
        case Cima : x.Body[1].x = Player.Body[2].x;
                    x.Body[1].y = Player.Body[2].y+4;
                    break;
       case Baixo : x.Body[1].x = Player.Body[2].x;
                    x.Body[1].y = Player.Body[2].y-4;
                    break;
    case Esquerda : x.Body[1].x = Player.Body[2].x+4;
                    x.Body[1].y = Player.Body[2].y;
                    break;
     case Direita : x.Body[1].x = Player.Body[2].x-4;
                    x.Body[1].y = Player.Body[2].y;
                    break;
  }
  x.Size++;
  free (BodySave);
  return x;
}

T_Nibbles NextLevel (T_Nibbles Player)
{
  T_Nibbles x;

  x = Player;
  Cls (0, VGA);
  x.Size = 6;
  x.Level++;
  Blocks.x = 126;
  Blocks.y = 8;
  Blocks.Number = TotalBlocks+5;
  TotalBlocks += 5;
  DrawScreenLimits (3);
  return x;
}

T_Nibbles CheckLimits (T_Nibbles Player)
{
  int i;
  T_Nibbles x;

  x = Player;
  for (i = 1; i < Player.Size; i++)
    if ((Player.Body[i].x == Player.Body[Player.Size].x) &&
       (Player.Body[i].y == Player.Body[Player.Size].y)) x.Dead = 1;
  if ((Player.Body[Player.Size].x == XMin) || (Player.Body[Player.Size].x == XMax) ||
     (Player.Body[Player.Size].y == YMin) || (Player.Body[Player.Size].y == YMax))
     x.Dead = 1;

  // check if nibbles is going to hit a wall or itself in the next move
  switch (Player.Direction) {
        case Cima : if (Player.Body[Player.Size].y-4 == YMin) NearWall = 1;
                    for (i = 1; i < Player.Size; i++)
                      if ((Player.Body[i].x == Player.Body[Player.Size].x) &&
                         (Player.Body[i].y == Player.Body[Player.Size].y-4)) NearWall = 1;
                    break;
       case Baixo : if (Player.Body[Player.Size].y+4 == YMax) NearWall = 1;
                    for (i = 1; i < Player.Size; i++)
                      if ((Player.Body[i].x == Player.Body[Player.Size].x) &&
                         (Player.Body[i].y == Player.Body[Player.Size].y+4)) NearWall = 1;
                    break;
    case Esquerda : if (Player.Body[Player.Size].x-4 == XMin) NearWall = 1;
                    for (i = 1; i < Player.Size; i++)
                      if ((Player.Body[i].x == Player.Body[Player.Size].x-4) &&
                         (Player.Body[i].y == Player.Body[Player.Size].y)) NearWall = 1;
                    break;
     case Direita : if (Player.Body[Player.Size].x+4 == XMax) NearWall = 1;
                    for (i = 1; i < Player.Size; i++)
                      if ((Player.Body[i].x == Player.Body[Player.Size].x+4) &&
                         (Player.Body[i].y == Player.Body[Player.Size].y)) NearWall = 1;
                    break;
  }
  if (GameType != Survive)
    if ((Player.Body[Player.Size].x == Blocks.x) && (Player.Body[Player.Size].y == Blocks.y)) {
      x.Score += 100;
      if (GameType == Levels) {
        Blocks.Number--;
        if (Blocks.Number == 0)
          x = NextLevel (x);
      }
      x = AddPlayer (x);
      x = AddPlayer (x);
      x = AddPlayer (x);
      CalcBlockPosition (Player);
    }
  return x;
}

T_Nibbles UpdatePlayer (T_Nibbles Player)
{
  int i;
  xy *BodySave;
  T_Nibbles x;

  x = Player;
  BodySave = (xy *) malloc (1000*sizeof(xy));
  DrawBlock (Player.Body[1].x, Player.Body[1].y, 0, VGA);
  for (i = 1; i <= Player.Size; i++)
    BodySave[i] = Player.Body[i];
  for (i = Player.Size; i >= 2; i--)
    x.Body[i-1] = BodySave[i];
  x.Body[Player.Size].Direction = Player.Direction;
  switch (Player.Direction) {
        case Cima : x.Body[Player.Size].y -= 4;
                    break;
       case Baixo : x.Body[Player.Size].y += 4;
                    break;
    case Esquerda : x.Body[Player.Size].x -= 4;
                    break;
     case Direita : x.Body[Player.Size].x += 4;
                    break;
  }
  free (BodySave);
  return x;
}

void ClearBox (int x1, int x2, int y1, int y2, byte color)
{
  int ix, iy;

  for (iy = y1; iy <= y2; iy++)
    for (ix = x1; ix <= x2; ix++)
      PlotPixel (ix, iy, color, VGA);
}

void Menu1 (void)
{
  byte option;

  LoadPCXPal (PCX_Menu);
  InitFade ();
  FadeIn (0);
  ShowPCX (PCX_Menu, VGA);
  FadeOut (10);
  while (2 != 3) {
    ClearBox (90, 300, 100, 150, 0);
    InitMenu (menu1);
    option = LightBar (menu1);
    switch (option) {
        case 1 : Menu1_1 ();
                 break;
      case 255 :
        case 4 : Quit ("NOERROR");
                 break;
    }
  }
}

void Menu1_1 (void)
{
  byte option;

  ClearBox (90, 300, 100, 150, 0);
  InitMenu (menu1_1);
  option = LightBar (menu1_1);
  switch (option) {
      case 1 : GameType = Levels;
               break;
      case 2 : GameType = CellPhone;
               break;
      case 3 : GameType = Survive;
               break;
    case 255 : GameType = 0;
               break;
  }
  if (GameType != 0) {
    Cls (0, VGA);
    RestorePal (NormalPalette);
    InitFade ();
    Player1 = SetupNewGame();
    UpdateScreen (Player1);
    GameLoop ();
    free (Player1.Body);
  }
}

void GameLoop (void)
{
  int i;

  while (!KeyTable[K_ESC]) {
    if (GameType == Survive) {
      Player1.Score++;
      Player1 = AddPlayer (Player1);
    }
    Player1 = UpdatePlayer (Player1);
    Player1 = CheckLimits (Player1);
    if (Player1.Dead)
      Player1 = PlayerDied (Player1);
    if (Player1.Lives <= 0) break;
    UpdateScreen (Player1);
    if (NearWall) Player1.Velocity += 40;
    for (i = 1; i <= Player1.Velocity; i++) {
      if (KeyTable[K_UP])
        if (Player1.Direction != Baixo)
          Player1.Direction = Cima;
      if (KeyTable[K_DOWN])
        if (Player1.Direction != Cima)
          Player1.Direction = Baixo;
      if (KeyTable[K_LEFT])
        if (Player1.Direction != Direita)
          Player1.Direction = Esquerda;
      if (KeyTable[K_RIGHT])
        if (Player1.Direction != Esquerda)
          Player1.Direction = Direita;
      delay (1);
    }
    if (NearWall) {
      Player1.Velocity -= 40;
      NearWall = 0;
    }
  }
  LoadPCXPal (PCX_Menu);
  InitFade ();
  FadeIn (0);
  ShowPCX (PCX_Menu, VGA);
  FadeOut (10);
}

void Init (void)
{
  byte i;

  // init menu values
  menu1.total = 4;
  menu1.options = (t_menuoption *) malloc (sizeof(t_menuoption)*menu1.total);
  for (i = 0; i < menu1.total; i++)
    menu1.options[i].text = (char *) malloc (255);
  menu1.options[0].text = "new]game";
  menu1.options[0].x = 90;
  menu1.options[0].y = 100;
  menu1.options[1].text = "high]score";
  menu1.options[1].x = 90;
  menu1.options[1].y = 112;
  menu1.options[2].text = "options";
  menu1.options[2].x = 90;
  menu1.options[2].y = 124;
  menu1.options[3].text = "quit";
  menu1.options[3].x = 90;
  menu1.options[3].y = 136;

  menu1_1.total = 3;
  menu1_1.options = (t_menuoption *) malloc (sizeof(t_menuoption)*menu1_1.total);
  for (i = 0; i < menu1_1.total; i++)
    menu1_1.options[i].text = (char *) malloc (255);
  menu1_1.options[0].text = "levels";
  menu1_1.options[0].x = 90;
  menu1_1.options[0].y = 100;
  menu1_1.options[1].text = "cell]phone";
  menu1_1.options[1].x = 90;
  menu1_1.options[1].y = 112;
  menu1_1.options[2].text = "survive";
  menu1_1.options[2].x = 90;
  menu1_1.options[2].y = 124;

  if (!(FB_ReserveMem ())) Quit ("Init: FB_ReserveMem: not enough mem!");
  if (!(FB_LoadFont ("fb.fnt"))) Quit ("Init: FB_LoadFont: fb.fnt not found!");
  PCX_Menu = (T_PCX *) malloc (sizeof(T_PCX));
  NormalPalette = (pal *) malloc (sizeof(pal));
  randomize();
  LoadNewInt09();
  if (!LoadPCX ("nib.pcx", PCX_Menu)) Quit ("Init: cannot load nib.pcx!");
  SetVideoMode (MCGA);
  SavePal (NormalPalette);
}


void main (void)
{
  Init ();
  Menu1 ();
  Quit ("main: Menu1() exited, should not happen!");
/*  COM = COM2;
  LoadNewISR ();
  InitModem (38400, 8, 0, 1);
  SendToModem ("ATDT"+13);
  delay (1000);
  HangupModem ();
  RestoreISR (); */
}
