#include <msp430.h> 
#include "config.h"
#include "termistor.h"
#include "push_button.h"
#include "led_rgb.h"

/*
 * MVC para MSP430
 * Criado em: 15/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 *
 */

// --------- Variáveis do sistema ---------
unsigned int volatile conv_ADC_DIGITAL = 0;
unsigned int var_convertida = 0;
char string[] = { "AB\r\n" };

int main(void)
{
	//Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

    config_CLOCK(1,2);
    config_PORT();
    config_TA0(1,'A',1,8192);
	config_TA1_PWM('A',1,327,0);
	config_ADC('S',1,7,64);
	config_UART('S',52,0,UCBRF_1);

	config_push_botton(1);
	//config_led_RGB();
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMERA0_ISR(void)
{
	//converter_ADC10(5);
	//temp_vlookup();

	//converte_decimal_char();
	//send_uart(string);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	push_button();
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	if(UCA0RXBUF=='B') 									//Apenas envio de informa‹o
	{
		led_RGB(LED_BLUE,1);
		led_RGB(LED_GREEN,0);
		led_RGB(LED_RED,0);
	}
	else if(UCA0RXBUF=='R') 									//Apenas envio de informa‹o
	{
		led_RGB(LED_BLUE,0);
		led_RGB(LED_GREEN,0);
		led_RGB(LED_RED,1);
	}
	else if(UCA0RXBUF=='G') 									//Apenas envio de informa‹o
	{
		led_RGB(LED_BLUE,0);
		led_RGB(LED_GREEN,1);
		led_RGB(LED_RED,0);
	}
}
