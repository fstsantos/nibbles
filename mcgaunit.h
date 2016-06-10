#define VGA 0x0a000
#define MCGA 0x13
#define TEXT 0x3

typedef struct
{
  unsigned char R;
  unsigned char G;
  unsigned char B;
} rgb;

typedef int pal[255][3];

void SetVideoMode (int type);
void PlotPixel (int x, int y, unsigned char Color, int Where);
void Cls (unsigned char Color, int Where);
void SetPal (unsigned char Color, unsigned char R, unsigned char G, unsigned char B);
rgb GetPal (unsigned char Color);
void SavePal (pal *palette);
void RestorePal (pal *palette);
void InitFade (void);
void FadeIn (int del);
void FadeOut (int del);
void Flash (unsigned char r, unsigned char g, unsigned char b, int del);
void PixelFade (unsigned char Color, int del, int Where);
void WaitRetrace (void);
void Text (int x, int y, int Color, char *string, int Where);
