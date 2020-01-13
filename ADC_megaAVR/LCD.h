/* instrukcje wy�wietlacza LCD */
#define LCD_MODE     		0x06		// I/D=1 - inkrementacja, S=0 - brak przesuni�cia zawarto�ci DDRAM
#define LCD_CLEAR    		0x01		// czy�ci wy�wietlacz i ustawia kursor na pocz�tku (adres=0)
#define LCD_ON		 		0x0c		// D=1 - w��czenie wy�wietlacza, C=0 - wy��czenie kursora, B=0 - wy��czenie migania kursora
#define LCD_OFF		 		0x08		// D=0 - wy��czenie wy�wietlacza, C=0 - wy��czenie kursora, B=0 - wy��czenie migania kursora
#define LCD_8bit_data 		0x38		// DL=1 - 8 linii danych, N=1 - dwu liniowy, F=0 - matryca 5x7 punkt�w

// ustawienie sygna��w sterujacych dla rozpocz�cia zapisu instrukcji
#define LCD_WR_INST	LCD_CONTROL&=(~_BV(LCD_RS)&~_BV(LCD_R_W))
// ustawienie sygna��w sterujacych dla rozpocz�cia zapisu danej
#define LCD_WR_DATA	LCD_CONTROL|=_BV(LCD_RS); LCD_CONTROL&=~_BV(LCD_R_W)
// ustawienie sygna��w sterujacych dla rozpocz�cia odczytu flagi zaj�to�ci
#define LCD_RD_FLAG	LCD_CONTROL|=_BV(LCD_R_W); LCD_CONTROL&=~_BV(LCD_RS)
// ustawienie sygna��w sterujacych dla rozpocz�cia odczytu danej
#define LCD_RD_DATA	LCD_CONTROL|=(_BV(LCD_RS)|_BV(LCD_R_W))	
// ustawienie sygna�u sterujacego EN
#define LCD_EN_SET		LCD_CONTROL|=_BV(LCD_EN)	
// wyzerowanie sygna�u sterujacego EN
#define LCD_EN_CLEAR	LCD_CONTROL&=~_BV(LCD_EN)

void init_TIMER2 (void);
void check_busy_flag (void);
void send_LCDdata (unsigned char LCDdata);
void send_LCDdata_pol(char LCDdata);
void send_LCDinstr (unsigned char LCDinstr);
void send_LCDinstr_without_check_flag (unsigned char LCDinstr);
void send_gcram	(unsigned char v0,unsigned char v1,unsigned char v2,unsigned char v3,
	 			unsigned char v4,unsigned char v5,unsigned char v6,unsigned char v7);
void define_char(void);
void init_LCD (void);
unsigned char address_DDRAM (unsigned char x, unsigned char y);
void write_string_xy(unsigned char x, unsigned char y, PGM_P text);	//z pamieci programu
void int_to_digits(unsigned int liczba, unsigned char liczba_cyfr, signed char *pcyfry);
void window_1(void);
void window_2(void);

// #define DEFCHARS {'�','�','�','�','�','�','�','�'}


