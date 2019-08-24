/*
 * led_rgb.h
 *
 *  Created on: 19/11/2017
 *      Author: Guilherme Henrique
 */

#ifndef LED_RGB_H_
#define LED_RGB_H_

// --------- Variáveis gerais do projeto --------- //
#define LED_BLUE		BIT7
#define LED_GREEN		BIT5
#define LED_RED			BIT4

// --------- Funcões da biblioteca ------------- //
void config_led_RGB(void);
void led_RGB(char cor, unsigned int status);

#endif /* LED_RGB_H_ */
