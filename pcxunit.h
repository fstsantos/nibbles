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

typedef struct {
  T_PCXHeader Header;
  byte Pal[768];
  byte Image[63999];
} T_PCX;


int LoadPCX (char *filename, T_PCX *PCX);
void LoadPCXPal (T_PCX *PCX);
void ShowPCX (T_PCX *PCX, word Where);
