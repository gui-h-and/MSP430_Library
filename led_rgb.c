#include <msp430.h>
#include <string.h>
#include "config.h"
#include "push_button.h"
#include "led_rgb.h"

/* ---- Configurações essenciais do sistema ----
 * Criação: 19/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 */

void config_led_RGB(void)
{
	/* ---- Configurar o as portas para o led ----
	 *
	 * @param  int
	 * @return int
	 *
	 * Configuração Pré-estabelecida:
	 * - Portas LED_BLUE, LED_GREEN, LED_RED são saída
	 * - Saída baixa em todas as portas P1 e P2
	 *
	 */

	SET(P1DIR,(LED_BLUE + LED_GREEN + LED_RED));
	SET(P1OUT,0x00);
	SET(P2DIR,0xFF);
	SET(P2OUT,0x00);
}

void led_RGB(char cor, unsigned int status)
{
	switch(status)
	{
		case 0:
		switch(cor)
		{
			case 'B':
				CLR(P1OUT,(LED_BLUE));
				break;
			case 'G':
				CLR(P1OUT,(LED_GREEN));
				break;
			case 'R':
				CLR(P1OUT,(LED_RED));
				break;
			default:
				CLR(P1OUT,(LED_BLUE+LED_GREEN+LED_RED));
				break;
		}
		break;

		case 1:
		switch(cor)
		{
			case 'B':
				SET(P1OUT,(LED_BLUE));
				break;
			case 'G':
				SET(P1OUT,(LED_GREEN));
				break;
			case 'R':
				SET(P1OUT,(LED_RED));
				break;
			default:
				SET(P1OUT,(LED_BLUE+LED_GREEN+LED_RED));
				break;
		 }
		break;
	}
}
