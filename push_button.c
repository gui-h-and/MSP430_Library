#include <msp430.h>
#include "config.h"
#include "push_button.h"
#include "led_rgb.h"
#include "termistor.h"

/* ---- Biblioteca de Push Botton ----
 * Criação: 19/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 */

void config_push_botton(unsigned int borda)
{
	/* ---- Configurar o as portas para o Button ----
	 *
	 * @param  	int  borda: borda do sinal						0->descida, 1->subida
	 * @return 	void
	 *
	 * Configuração Pré-estabelecida:
	 * - Pino SW Pull-Up
	 * - Habilita interrupção no pino SW
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
        //Interrupção na borda de subida
        CLR(P1IES,SW);
    }
    else if(borda==0)
    {
        //Interrupção na borda de descida
        TST(P1IES,SW);
    }

    else CLR(P1IES,SW);	//Por default, interrupção na borda de Subida

    //Limpa flag de interrupção
    CLR(P1IFG,SW);
    //Habilita interrupção no pino SW
    SET(P1IE,SW);
}

void push_button(void)
{
	/* ---- Função que executa as ações quando o botão é pressionado ----
	 *
	 * @param  	void
	 * @return 	void
	 *
	 * Configuração Pré-estabelecida:
	 * - Delay de t_debounce (ver push_button.h) para ter certeza que não é um ruído do button
	 *
	 */

	//Ignora aperto do botão para tempo menor que 1 ms
	__delay_cycles(t_debounce);
	if(P1IN&SW)
	{
	    /* Aqui vai o código de ação quando o botão é pressionado
	     */

		send_uart(string);

		TOG(P2DIR,BIT2);
		TOG(P1OUT,BIT0);

	    //Limpa flag de interrupção
	    CLR(P1IFG,SW);
	}
}
