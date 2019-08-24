/*
 * Criado em: 19/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 *
 */

#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

// --------- Variáveis gerais --------- //
#define SW				BIT3	//Switch -> P1.3(S2)
#define t_debounce		32000	//time_debounce = 16000/MCLK = 16K/16MHz = 1ms

// --------- Funcões da biblioteca ------------- //
void push_button(void);
void config_push_botton(unsigned int borda);

#endif /* PUSH_BUTTON_H_ */
