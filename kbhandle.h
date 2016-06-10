#define K_ESC 1
#define K_ENTER 28
#define K_CTRL 29
#define K_UP 72
#define K_DOWN 80
#define K_LEFT 75
#define K_RIGHT 77
#define K_PGUP 73
#define K_PGDN 81
#define K_HOME 71
#define K_SHIFT 42
#define K_SPACE 57
#define K_F1 59
#define K_F2 60
#define K_F3 61
#define K_F4 62
#define K_F5 63
#define K_W 17
#define K_S 31
#define K_A 30
#define K_D 32
#define K_1 2
#define K_2 3
#define K_3 4
#define K_4 5
#define K_5 6

extern unsigned char KeyTable[127];
extern unsigned char Pressed;

void RefreshKeyTable (void);
void LoadNewInt09 (void);
void RestoreInt09 (void);
