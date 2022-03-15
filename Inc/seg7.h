/*
 * seg7.h
 *
 *  Created on: Mar 10, 2022
 *      Author: ponia
 */

#ifndef INC_SEG7_H_
#define INC_SEG7_H_

#include <stdint.h>
#include "gpio.h"
#include "main.h"

void seg7_show_digit(uint32_t value);

void seg7_show(uint32_t value);

void seg7_update(void);

uint32_t seg7_TimeToInt(void);

void SetTime(uint8_t hour, uint8_t min);










#endif /* INC_SEG7_H_ */
