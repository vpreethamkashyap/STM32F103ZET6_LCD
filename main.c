//STM32F103ZET6 Buttons Test
#include "stm32f10x.h"
#include "leds.h"
#include "buttons.h"
#include "usart.h"
#include "lcd.h"
#include "stm32f10x_it.h"
#include "main.h"
#include <math.h>
extern u8 Image_Table[];

int main(void)
{
  //char i;
  uint32_t status=0;
	//init leds
  LEDsInit();
  //init buttons t ogenerate interrupts
  ButtonsInitEXTI();
  //initialize USART
  USART1Init();
  /* Initialize the LCD */
  LCD_Init();
  LEDToggle(3);
  //SysTick_Config(15000000);
  LCD_SetDisplayWindow(00, 00, 239, 319);
  LCD_Clear(Black);
  LCD_DisplayStringLine(Line2, "   Click any button  ", Black,Green);
  printf("\r\n USART1 Test \r\n");
while(1	)
	{
			status = ButtonGetStatus();
		switch (status){
		case 1:
			LCDBMPDemo();
			break;
		case 2:
			LCDTextDemo();
			break;
		case 3:
			LCDShapeDemo();
			break;
		case 4:
			LCDSineDemo();
			break;
		default:
			break;
		}
	}
}
void LCDBMPDemo(void)
{
	LCD_Clear(Blue);
	LCD_WriteBMP_Dim(30, 30, 210, 210, Image_Table);

}
void LCDTextDemo(void)
{
	LCD_Clear(Black);
	LCD_DisplayStringLine(Line0, "   Hello   ",White, Black);
	LCD_DisplayStringLine(Line1, "   This is LCD DEMO  ", Black,Blue);
	LCD_DisplayStringLine(Line2, "   Click any button  ", Black,Green);
	LCD_DisplayStringLine(Line3, "   to continue...  ", Black,Red);
}
void LCDShapeDemo(void)
{
	LCD_Clear(White);
	LCD_SetTextColor(Black);
	LCD_DrawCircle(60, 60, 50);
	LCD_SetTextColor(Green);
	LCD_DrawCircle(100, 160, 53);
	LCD_DrawRect(10, 300, 50, 50);
	uint16_t i=0;
	for(;i<320;i++)
	{
		LCD_SetTextColor(i+Red);
		LCD_DrawLine(200, i, 30, Vertical);
	}
}
void LCDSineDemo(void)
{
	LCD_Clear(White);
	//LCDDrawLine(10, 10, 120, 200, Magenta);
	//LCDDrawLine(10, 2, 220, 100, Black);

	uint16_t xmax=239;
	uint16_t ymax=319;

	uint16_t x, y;
	uint8_t prx=0;
	uint8_t pry=0;
	LCD_SetTextColor(Green);
	LCD_DrawLine(0, ymax>>1, xmax, Vertical);
	LCD_DrawLine(xmax>>1, 0, ymax, Horizontal);
	LCD_SetTextColor(Blue);
	for (x=0;x<xmax;x++)
	{
	y=(uint16_t)((ymax>>2)*sin(x*M_PI/40)+(ymax>>1));
	if (x==0)
		LCD_SetPoint(x, y, Black);
	else
		{
		LCDDrawLine(prx, pry, x, y, Black);
		}
	prx=x;
	pry=y;
	}
}

