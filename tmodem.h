#define COM1 0x03F8
#define COM2 0x02F8
#define COM3 0x03E8
#define COM4 0x02E8


extern int COM;

void LoadNewISR (void);
void RestoreISR (void);
void LowerDTR (void);
void InitModem (int BaudRate, unsigned char Bits, char Parity, unsigned char TStop);
void SendToModem (char *Line);
void HangupModem (void);
