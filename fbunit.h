typedef struct {
  unsigned char Mask[60][60];   // y, x
} FB_FontMask;


extern FB_FontMask huge *FB_Font[76]; // from 0 (48) to (122) z, huge cause it will be
                                  // larger than a segment
extern unsigned int FB_XSize;
extern unsigned int FB_YSize;

int FB_ReserveMem (void);
void FB_FreeMem (void);
int FB_LoadFont (char *filename);
void FB_PutChar (int chr, int x, int y);
void FB_PutStr (char *str, int x, int y);
