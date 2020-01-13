#include "IN_OUT.h"
void init_pins (void) {
	/*ustawienie odpowiednich pinów mikrokontrolera jako
	wyjœæ dla portu, do którego pod³¹czono diody LED*/
	DIRLED |= (_BV(LED0)|_BV(LED1)|_BV(LED2)|_BV(LED3));
	/*ustawienie odpowiednich pinów mikrokontrolera jako 
	wejœæ dla portu, do którego pod³¹czono przyciski KEY*/
	DIRKEY &= (~_BV(KEY0)&~_BV(KEY1)&~_BV(KEY2)&~_BV(KEY3));
	/*ustawienie odpowiednich pinów mikrokontrolera jako 
	wejœæ dla portu, do którego pod³¹czono prze³¹czniki SW*/
	DIRSWITCH &= (~_BV(SW0)&~_BV(SW1)&~_BV(SW2)&~_BV(SW3));
	/*ustawienie wyjœæ dla portu, do którego pod³¹czono linie danych LCD*/
	LCD_DIR_DATA = 0xFF;
	/*ustawienie odpowiednich pinów mikrokontrolera jako 
	wyjœæ dla portu, do którego pod³¹czono sygna³y steruj¹ce LCD*/
	LCD_DIR_CONTROL |= (_BV(LCD_RS)|_BV(LCD_EN)|_BV(LCD_R_W));
}
