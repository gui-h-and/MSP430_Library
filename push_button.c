#include <msp430.h>
#include "config.h"
#include "push_button.h"
#include "led_rgb.h"
#include "termistor.h"

/* ---- Biblioteca de Push Botton ----
 * Cria��o: 19/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 */

void config_push_botton(unsigned int borda)
{
	/* ---- Configurar o as portas para o Button ----
	 *
	 * @param  	int  borda: borda do sinal						0->descida, 1->subida
	 * @return 	void
	 *
	 * Configura��o Pr�-estabelecida:
	 * - Pino SW Pull-Up
	 * - Habilita interrup��o no pino SW
	 *
	 */

	//Seta pino SW como Entrada
	P1DIR &= ~SW;
	//Habilita resistor para o pino SW
    P1REN |= SW;
    //Pino SW como Pull-Up
    P1OUT |= SW;

    if(borda==1)
    {
        //Interrup��o na borda de subida
        CLR(P1IES,SW);
    }
    else if(borda==0)
    {
        //Interrup��o na borda de descida
        TST(P1IES,SW);
    }

    else CLR(P1IES,SW);	//Por default, interrup��o na borda de Subida

    //Limpa flag de interrup��o
    CLR(P1IFG,SW);
    //Habilita interrup��o no pino SW
    SET(P1IE,SW);
}

void push_button(void)
{
	/* ---- Fun��o que executa as a��es quando o bot�o � pressionado ----
	 *
	 * @param  	void
	 * @return 	void
	 *
	 * Configura��o Pr�-estabelecida:
	 * - Delay de t_debounce (ver push_button.h) para ter certeza que n�o � um ru�do do button
	 *
	 */

	//Ignora aperto do bot�o para tempo menor que 1 ms
	__delay_cycles(t_debounce);
	if(P1IN&SW)
	{
	    /* Aqui vai o c�digo de a��o quando o bot�o � pressionado
	     */

		send_uart(string);

		TOG(P2DIR,BIT2);
		TOG(P1OUT,BIT0);

	    //Limpa flag de interrup��o
	    CLR(P1IFG,SW);
	}
}
