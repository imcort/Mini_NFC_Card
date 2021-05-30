#include "disp_menu.h"

#include "u8g2.h"
#include "u8x8.h"

#include "string.h"

u8log_t u8log;
extern u8g2_t u8g2;

#define U8LOG_WIDTH 12
#define U8LOG_HEIGHT 7
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];

void disp_menu_begin(void)
{

		u8log_Init(&u8log, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
		u8log_WriteString(&u8log, "imCort\nRFID HACK!\nAAAAAAAAAAAA");
//		u8log_WriteString(&u8log, "RFID HACK gerthrthbytdhdytjtydnjtyuyndjtyjdny");
//		u8log_WriteString(&u8log, "\n");

}

void disp_menu_draw(uint16_t slot, uint8_t * uid)
{
	char strtemp[100];

  u8g2_FirstPage(&u8g2);
  do {
			u8g2_SetFontPosTop(&u8g2);
			u8g2_SetFont(&u8g2, u8g2_font_6x13_tf);
			
			u8g2_SetDrawColor(&u8g2, 1);
			u8g2_DrawRBox(&u8g2, 0, 0, 62, 12, 1);
			u8g2_SetDrawColor(&u8g2, 0);
			u8g2_DrawStr(&u8g2, 10, 0, "Console");
			
			u8g2_SetDrawColor(&u8g2, 1);
			u8g2_DrawRBox(&u8g2, 65, 0, 62, 12, 1);
			u8g2_SetDrawColor(&u8g2, 0);
			u8g2_DrawStr(&u8g2, 80, 0, "Cards");
		
			u8g2_SetFont(&u8g2, u8g2_font_bubble_tn);
			u8g2_SetDrawColor(&u8g2, 1);
			sprintf(strtemp,"%d",slot);
			u8g2_DrawStr(&u8g2, 80, 13, strtemp);
					
			u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
			u8g2_SetDrawColor(&u8g2, 1);
			u8g2_DrawStr(&u8g2, 72, 33, "Ultralight");
		
			u8g2_SetFont(&u8g2, u8g2_font_t0_11b_tf);
			u8g2_SetDrawColor(&u8g2, 1);
			sprintf(strtemp,"%.2x%.2x %.2x%.2x",uid[0],uid[1],uid[2],uid[3]);
			u8g2_DrawStr(&u8g2, 70, 43, strtemp);
			sprintf(strtemp,"%.2x%.2x %.2x",uid[4],uid[5],uid[6]);
			u8g2_DrawStr(&u8g2, 70, 54, strtemp); 
		
			u8g2_SetDrawColor(&u8g2, 1);
			u8g2_DrawVLine(&u8g2, 63, 13, 52);
			u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);		// set the font for the terminal window
			u8g2_DrawLog(&u8g2, 2, 13, &u8log);		// draw the terminal window on the display
  } while (u8g2_NextPage(&u8g2));

}


