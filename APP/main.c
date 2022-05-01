#include "STD_TYPES.h"
#include "LCD.h"
#include "KEY_PAD.h"
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	LCD_INIT();
	KEY_PAD_INIT();
	
	u8 n1 = 0, n2 = 0, result = 0, op = 0;
	
	enum { N1, OP, N2, EQUAL } state;
	state = N1;
	
    while (1)
    {
		switch (state)
		{
			case N1:
			n1 = KEY_PAD_READ();
			if (n1 >= 48 && n1 <= 57)
			{
				LCD_WRITE_CHR(n1);
				n1 -= 48;
				state = OP;
			}
			break;
			case OP:
			op = KEY_PAD_READ();
			if (op == '+' || op == '-' || op == '*' || op == '/')
			{
				LCD_WRITE_CHR(op);
				state = N2;
			}
			break;
			case N2:
			n2 = KEY_PAD_READ();
			if (n2 >= 48 && n2 <= 57)
			{
				LCD_WRITE_CHR(n2);
				n2 -= 48;
				state = EQUAL;
			}
			break;
			case EQUAL:
			if (KEY_PAD_READ() == '=')
			{
				LCD_WRITE_CHR('=');
				switch (op)
				{
					case '+':
					result = n1 + n2;
					break;
					case '-':
					result = n1 - n2;
					break;
					case '*':
					result = n1 * n2;
					break;
					case '/':
					result = n1 / n2;
					break;
					default:
					result = 0;
					break;
				}
				LCD_WRITE_NUM(result);
				_delay_ms(2000);
				LCD_CLR();
				state = N1;
			}
			break;
			default:
			break;
		}
    }
}
