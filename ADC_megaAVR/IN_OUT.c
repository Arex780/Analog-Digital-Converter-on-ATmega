#include "IN_OUT.h"
void init_pins (void) {
	/*ustawienie odpowiednich pin�w mikrokontrolera jako
	wyj�� dla portu, do kt�rego pod��czono diody LED*/
	DIRLED |= (_BV(LED0)|_BV(LED1)|_BV(LED2)|_BV(LED3));
	/*ustawienie odpowiednich pin�w mikrokontrolera jako 
	wej�� dla portu, do kt�rego pod��czono przyciski KEY*/
	DIRKEY &= (~_BV(KEY0)&~_BV(KEY1)&~_BV(KEY2)&~_BV(KEY3));
	/*ustawienie odpowiednich pin�w mikrokontrolera jako 
	wej�� dla portu, do kt�rego pod��czono prze��czniki SW*/
	DIRSWITCH &= (~_BV(SW0)&~_BV(SW1)&~_BV(SW2)&~_BV(SW3));
	/*ustawienie wyj�� dla portu, do kt�rego pod��czono linie danych LCD*/
	LCD_DIR_DATA = 0xFF;
	/*ustawienie odpowiednich pin�w mikrokontrolera jako 
	wyj�� dla portu, do kt�rego pod��czono sygna�y steruj�ce LCD*/
	LCD_DIR_CONTROL |= (_BV(LCD_RS)|_BV(LCD_EN)|_BV(LCD_R_W));
}
