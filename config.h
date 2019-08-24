/*
 * Criado em: 15/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// --------- Funções gerais do sistema --------- //
// Eg: TOG(P1OUT,BIT0);	XOR (Liga/Desliga) a porta P1.0
#define TST(x,y) (x & (y))
#define SET(x,y) (x |= (y))
#define CLR(x,y) (x &= ~(y))
#define TOG(x,y) (x ^= (y))

// --------- Canais de conversão --------- //
#define SET_ADC_A5 ADC10CTL1 = INCH_5 + ADC10SSEL_3; ADC10AE0 = BIT5
#define SET_ADC_A6 ADC10CTL1 = INCH_6 + ADC10SSEL_3; ADC10AE0 = BIT6
#define SET_ADC_A7 ADC10CTL1 = INCH_7 + ADC10SSEL_3; ADC10AE0 = BIT7

// --------- Variáveis gerais --------- //
extern unsigned int volatile conv_ADC_DIGITAL;
extern unsigned int var_convertida;
extern char string[];

// --------- Funcões da biblioteca ------------- //
int config_CLOCK(unsigned int ACLK_div, unsigned int SMCLK_div);
void config_PORT(void);
int config_TA0(unsigned int habilita_interrup, char timerA0_font, unsigned int timerA0_div,unsigned int contagem);
void config_ADC(char ADC_font, int ADC_div, int porta, int periodo_amost);
void config_UART(char UART_font, unsigned int UCA_0, unsigned int UCA_1, unsigned int UCBRF);
int config_TA1_PWM(char timerA1_font, unsigned int timerA1_div, unsigned int contagem, unsigned int dutty);
void send_uart(char *data);
void set_dutty_cycle_TA1(unsigned int dutty);
void converter_ADC10(unsigned int canal);
void converte_decimal_char(void);

#endif /* CONFIG_H_ */
