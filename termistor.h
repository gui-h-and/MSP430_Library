/*
 * Criado em: 23/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 *
 */

#ifndef TERMISTOR_H_
#define TERMISTOR_H_

// --------- Vari�veis gerais do projeto --------- //
extern unsigned int volatile conv_ADC_DIGITAL;
extern unsigned int var_convertida;

// --------- Func�es da biblioteca ------------- //
void temp_vlookup(void);

#endif /* TERMISTOR_H_ */
