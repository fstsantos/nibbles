typedef char *string;
typedef struct {
  string text;
  unsigned int x, y;
} t_menuoption;

typedef struct {
  unsigned char total;
  t_menuoption *options;
} t_menu;


void InitMenu (t_menu menu);
unsigned char LightBar (t_menu menu);
