/*
 * ILI9488.c
 *
 *  Created on: May 4, 2022
 *      Author: Haru
 */


#include "ILI9488.h"

void ILI9488_wait(){
	uint8_t w = 1;
	while(w--)
		asm("nop");
}

void ILI9488_CMD(uint8_t cmd){
	DC_GPIO_Port->BSRR = DC_Pin << 16;
	ILI9488_DATPORT->BSRR = 0xff << 16;
	ILI9488_DATPORT->BSRR = cmd;
	WR_GPIO_Port->BSRR = WR_Pin << 16;
	ILI9488_wait();
	WR_GPIO_Port->BSRR = WR_Pin;
	DC_GPIO_Port->BSRR = DC_Pin;
	ILI9488_wait();
}


void ILI9488_DAT(uint8_t dat){
	DC_GPIO_Port->BSRR = DC_Pin;
	ILI9488_DATPORT->BSRR = 0xff << 16;
	ILI9488_DATPORT->BSRR = dat;
	WR_GPIO_Port->BSRR = WR_Pin << 16;
	ILI9488_wait();
	WR_GPIO_Port->BSRR = WR_Pin;
	ILI9488_wait();
}

void ILI9488_init(){
	RST_GPIO_Port->BSRR = RST_Pin << 16;
	ILI9488_wait();
	RST_GPIO_Port->BSRR = RST_Pin;
	ILI9488_wait();

	CS_GPIO_Port->BSRR = CS_Pin << 16;

	ILI9488_CMD(0x01);
	HAL_Delay(50);
	ILI9488_CMD(0x11);
	HAL_Delay(50);

	ILI9488_CMD(0xe0);
	ILI9488_DAT(0x00);
	ILI9488_DAT(0x0e);
	ILI9488_DAT(0x15);
	ILI9488_DAT(0x06);
	ILI9488_DAT(0x13);
	ILI9488_DAT(0x09);
	ILI9488_DAT(0x3a);
	ILI9488_DAT(0xac);
	ILI9488_DAT(0x4f);
	ILI9488_DAT(0x05);
	ILI9488_DAT(0x0d);
	ILI9488_DAT(0x0b);
	ILI9488_CMD(0x33);
	ILI9488_DAT(0x3b);
	ILI9488_DAT(0x0f);

	ILI9488_CMD(0xe1);
	ILI9488_DAT(0x00);
	ILI9488_DAT(0x0e);
	ILI9488_DAT(0x16);
	ILI9488_DAT(0x05);
	ILI9488_DAT(0x13);
	ILI9488_DAT(0x08);
	ILI9488_DAT(0x3b);
	ILI9488_DAT(0x9a);
	ILI9488_DAT(0x50);
	ILI9488_DAT(0x0a);
	ILI9488_DAT(0x13);
	ILI9488_DAT(0x0f);
	ILI9488_DAT(0x31);
	ILI9488_DAT(0x36);
	ILI9488_DAT(0x0f);

	ILI9488_CMD(0xc0);
	ILI9488_DAT(0x10);
	ILI9488_DAT(0x10);

	ILI9488_CMD(0xc1);
	ILI9488_DAT(0x44);

	ILI9488_CMD(0xc5);
	ILI9488_DAT(0x00);
	ILI9488_DAT(0x10);
	ILI9488_DAT(0x80);

	ILI9488_CMD(0x36);
	ILI9488_DAT(0b1001000);

	ILI9488_CMD(0x3a);
	ILI9488_DAT(0x05);

	ILI9488_CMD(0xb0);
	ILI9488_DAT(0x00);

	ILI9488_CMD(0xb1);
	ILI9488_DAT(0xb0);
	ILI9488_DAT(0x11);

	ILI9488_CMD(0xb4);
	ILI9488_DAT(0x02);

	ILI9488_CMD(0xb6);
	ILI9488_DAT(0x02);
	ILI9488_DAT(0x22);

	ILI9488_CMD(0xb7);
	ILI9488_DAT(0xc6);

	ILI9488_CMD(0xbe);
	ILI9488_DAT(0x00);
	ILI9488_DAT(0x04);

	ILI9488_CMD(0xe9);
	ILI9488_DAT(0x00);

	ILI9488_CMD(0xf7);
	ILI9488_DAT(0xa9);
	ILI9488_DAT(0x51);
	ILI9488_DAT(0x2c);
	ILI9488_DAT(0x82);

	ILI9488_CMD(0x11);

	HAL_Delay(120);

	ILI9488_CMD(0x29);

	CS_GPIO_Port->BSRR = CS_Pin;
}

void ILI9488_setArea(uint16_t xs,uint16_t xe,uint16_t ys,uint16_t ye){
	CS_GPIO_Port->BSRR = CS_Pin << 16;
	ILI9488_CMD(0x2a);
	ILI9488_DAT(ys >> 8);
	ILI9488_DAT(ys & 0x00ff);
	ILI9488_DAT(ye >> 8);
	ILI9488_DAT(ye & 0x00ff);
	ILI9488_CMD(0x2b);
	ILI9488_DAT(xs >> 8);
	ILI9488_DAT(xs & 0x00ff);
	ILI9488_DAT(xe >> 8);
	ILI9488_DAT(xe & 0x00ff);
	CS_GPIO_Port->BSRR = CS_Pin;
}

void ILI9488_drawRect(uint16_t xs,uint16_t ys,uint16_t xlen,uint16_t ylen,uint16_t color){
	ILI9488_setArea(xs, xs+xlen, ys, ys+ylen);
	CS_GPIO_Port->BSRR = CS_Pin << 16;
	ILI9488_CMD(0x2c);
	uint32_t count = xlen*ylen;
	while(count--){
		ILI9488_DAT(color >> 8);
		ILI9488_DAT(color & 0x00ff);
	}
	CS_GPIO_Port->BSRR = CS_Pin;
}
