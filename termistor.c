#include <msp430.h>
#include <string.h>
#include "config.h"
#include "push_button.h"
#include "led_rgb.h"
#include "termistor.h"

/* ---- Conversão com ADC ----
 * Criação: 23/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 */

void temp_vlookup(void)
{
	/* ---- VLOOKUP para temperatura do termistor ----
	 *
	 * @param 									void
	 * @return									void
	 *
	 * A tabela engloba os valores de 0C até 70C e joga o valor em 'var_convertida'
	 *
	 */

	if(conv_ADC_DIGITAL<=231)
	{
		var_convertida = 21;
		set_dutty_cycle_TA1(0);
	}
	else if(conv_ADC_DIGITAL<=236)
	{
		var_convertida = 22;
		set_dutty_cycle_TA1(14);
	}
	else if(conv_ADC_DIGITAL<=251)
	{
		var_convertida = 23;
		set_dutty_cycle_TA1(34);
	}
	else if(conv_ADC_DIGITAL<=256)
	{
		var_convertida = 24;
		set_dutty_cycle_TA1(44);
	}
	else if(conv_ADC_DIGITAL<=266)
	{
		var_convertida = 25;
		set_dutty_cycle_TA1(63);
	}
	else if(conv_ADC_DIGITAL<=276)
	{
		var_convertida = 26;
		set_dutty_cycle_TA1(82);
	}
	else if(conv_ADC_DIGITAL<=286)
	{
		var_convertida = 27;
		set_dutty_cycle_TA1(100);
	}
	else if(conv_ADC_DIGITAL<=296)
	{
		var_convertida = 28;
		set_dutty_cycle_TA1(118);
	}
	else if(conv_ADC_DIGITAL<=306)
	{
		var_convertida = 29;
		set_dutty_cycle_TA1(136);
	}
	else if(conv_ADC_DIGITAL<=316)
	{
		var_convertida = 30;
		set_dutty_cycle_TA1(154);
	}
	else if(conv_ADC_DIGITAL<=326)
	{
		var_convertida = 31;
		set_dutty_cycle_TA1(171);
	}
	else if(conv_ADC_DIGITAL<=336)
	{
		var_convertida = 32;
		set_dutty_cycle_TA1(188);
	}
	else if(conv_ADC_DIGITAL<=346)
	{
		var_convertida = 33;
		set_dutty_cycle_TA1(205);
	}
	else if(conv_ADC_DIGITAL<=356)
	{
		var_convertida = 34;
		set_dutty_cycle_TA1(221);
	}
	else if(conv_ADC_DIGITAL<=371)
	{
		var_convertida = 35;
		set_dutty_cycle_TA1(246);
	}
	else if(conv_ADC_DIGITAL<=381)
	{
		var_convertida = 36;
		set_dutty_cycle_TA1(262);
	}
	else if(conv_ADC_DIGITAL<=391)
	{
		var_convertida = 37;
		set_dutty_cycle_TA1(278);
	}
	else if(conv_ADC_DIGITAL<=406)
	{
		var_convertida = 38;
		set_dutty_cycle_TA1(301);
	}
	else if(conv_ADC_DIGITAL<=416)
	{
		var_convertida = 39;
		set_dutty_cycle_TA1(317);
	}
	else if(conv_ADC_DIGITAL<=426)
	{
		var_convertida = 40;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=441)
	{
		var_convertida = 41;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=451)
	{
		var_convertida = 42;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=466)
	{
		var_convertida = 43;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=481)
	{
		var_convertida = 44;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=491)
	{
		var_convertida = 45;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=506)
	{
		var_convertida = 46;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=516)
	{
		var_convertida = 47;
		set_dutty_cycle_TA1(327);
	}
	else if(conv_ADC_DIGITAL<=530)
	{
		var_convertida = 48;
		set_dutty_cycle_TA1(327);
	}
	else
	{
		var_convertida = 0;
		set_dutty_cycle_TA1(327);
	}
}
