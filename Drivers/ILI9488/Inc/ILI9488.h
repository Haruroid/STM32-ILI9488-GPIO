/*
 * ILI9488.h
 *
 *  Created on: May 4, 2022
 *      Author: Haru
 */

#ifndef ILI9488_INC_ILI9488_H_
#define ILI9488_INC_ILI9488_H_

#define ILI9488_DATPORT GPIOD
#define RGB565(r,g,b) ((uint16_t)((uint16_t)(r >> 3) << 11 | (uint16_t)(g >> 2) << 5 | b >> 3))

#include "stm32f3xx_hal.h"
#include "main.h"

void ILI9488_init(void);
void ILI9488_setArea(uint16_t xs,uint16_t xe,uint16_t ys,uint16_t ye);
void ILI9488_drawRect(uint16_t xs,uint16_t ys,uint16_t xlen,uint16_t ylen,uint16_t color);

#endif /* ILI9488_INC_ILI9488_H_ */
