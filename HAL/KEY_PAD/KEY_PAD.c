#include "KEY_PAD_CFG.h"
#include "KEY_PAD.h"
#include "DIO.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void KEY_PAD_INIT(void)
{
	PIN_MODE(KEY_PAD_R0,OUTPUT);
	PIN_MODE(KEY_PAD_R1,OUTPUT);
	PIN_MODE(KEY_PAD_R2,OUTPUT);
	PIN_MODE(KEY_PAD_R3,OUTPUT);
	
	PIN_MODE(KEY_PAD_C0,INPUT);
	PIN_MODE(KEY_PAD_C1,INPUT);
	PIN_MODE(KEY_PAD_C2,INPUT);
	PIN_MODE(KEY_PAD_C3,INPUT);
	
	PIN_WRITE(KEY_PAD_C0,HIGH);
	PIN_WRITE(KEY_PAD_C1,HIGH);
	PIN_WRITE(KEY_PAD_C2,HIGH);
	PIN_WRITE(KEY_PAD_C3,HIGH);
}

u8 KEY_PAD_READ(void)
{
	u8 r = 0;
	u8 c = 0;
	for (r = KEY_PAD_R0; r <= KEY_PAD_R3; r++)
	{
		PIN_WRITE(r,LOW);
		for (c = KEY_PAD_C0; c <= KEY_PAD_C3; c++)
		{
			if (PIN_READ(c) == PRESSED)
			{
				_delay_ms(120);
				if (PIN_READ(c) == PRESSED)
				{
					while (PIN_READ(c) == PRESSED);
					if (r == KEY_PAD_R3 && c == KEY_PAD_C1)
					    return '0';
					else if (r == KEY_PAD_R2 && c == KEY_PAD_C0)
						return '1';
					else if (r == KEY_PAD_R2 && c == KEY_PAD_C1)
						return '2';
					else if (r == KEY_PAD_R2 && c == KEY_PAD_C2)
						return '3';
					else if (r == KEY_PAD_R1 && c == KEY_PAD_C0)
						return '4';
					else if (r == KEY_PAD_R1 && c == KEY_PAD_C1)
						return '5';
					else if (r == KEY_PAD_R1 && c == KEY_PAD_C2)
						return '6';
					else if (r == KEY_PAD_R0 && c == KEY_PAD_C0)
						return '7';
					else if (r == KEY_PAD_R0 && c == KEY_PAD_C1)
						return '8';
					else if (r == KEY_PAD_R0 && c == KEY_PAD_C2)
						return '9';
					else if (r == KEY_PAD_R0 && c == KEY_PAD_C3)
						return '+';
					else if (r == KEY_PAD_R1 && c == KEY_PAD_C3)
						return '-';
					else if (r == KEY_PAD_R2 && c == KEY_PAD_C3)
						return '*';
					else if (r == KEY_PAD_R3 && c == KEY_PAD_C3)
						return '/';
					else if (r == KEY_PAD_R3 && c == KEY_PAD_C2)
						return '=';
					else
						return '#';
				}
			}
		}
		PIN_WRITE(r,HIGH);
	}
	return '#';
}
