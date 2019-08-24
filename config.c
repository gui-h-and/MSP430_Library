#include <msp430.h>
#include <string.h>
#include "config.h"

/* ---- Configura��es essenciais do sistema ----
 * Cria��o: 15/11/2017
 * @author Guilherme Henrique E. Andrade <guilherme1475963@hotmail.com>
 */

int config_CLOCK(unsigned int ACLK_div, unsigned int SMCLK_div)
{
	/* ---- Configurar o M�dulo de Clock do sistema ----
	 *
	 * @param int ACLK_div:  divisor para o ACLK	1,2,4,8
	 * @param int SMCLK_div: divisor para o SMCLK	1,2,4,8
	 * @return int 									1->configura��o conclu�da
	 *
	 * Configura��o Pr�-estabelecida:
	 * - DCOCLK -> 16MHz
	 * - LFXT1CLK -> 32768Hz
	 * - ACLK  -> LFXT1CLK
	 * - SMCLK -> DCOCLK
	 * - MCLK = DCOCLK/1 = 16MHz
	 * - Interrup��es habilitadas
	 *
	 * O BCM (Basic Clock Module) inclui at� 4 fontes de clock:
	 * 1) LFXT1CLK: Baixa/Alta freq - Fontes externas de clock 32768Hz, ou de 400KHz at� 16MHz
	 * 2) XT2CLK: Alta freq - Oscilador opcional para fontes externas de 400KHz at� 16MHz
	 * 3) DCOCLK: Oscilador interno 16MHz
	 * 4) VLOCLK: Oscilador interno para baixo consumo 12KHz
	 *
	 * 3 sinais de clock est�o dispon�veis no BCM
	 * 1) ACLK:  (LFXT1CLK, VLOCLK) para perif�ricos
	 * 2) MCLK:  (LFXT1CLK, VLOCLK, XT2CLK) para CPU e Sistema
	 * 3) SMCLK: (LFXT1CLK, VLOCLK, XT2CLK, DCOCLK) para perif�ricos
	 *
	 */

	//P�ra o WDT para realizar as configura��es sem o risco de resetar o uC antes da conclus�o
	WDTCTL = WDTPW + WDTHOLD;

	//Convers�o do par�metro ACLK_div
	if(ACLK_div == 1)
	{
		ACLK_div = DIVA_0;
	}
	else if(ACLK_div == 2)
	{
		ACLK_div = DIVA_1;
	}
	else if(ACLK_div == 4)
	{
		ACLK_div = DIVA_2;
	}
	else if(ACLK_div == 8)
	{
		ACLK_div = DIVA_3;
	}

	//Convers�o do par�metro SMCLK_div
	if(SMCLK_div == 1)
	{
		SMCLK_div = DIVS_0;
	}
	else if(SMCLK_div == 2)
	{
		SMCLK_div = DIVS_1;
	}
	else if(SMCLK_div == 4)
	{
		SMCLK_div = DIVS_2;
	}
	else if(SMCLK_div == 8)
	{
		SMCLK_div = DIVS_3;
	}

	//DCO recebe 16MHz
	DCOCTL = CALDCO_16MHZ;

	//Desliga XT2CLK | Divisor do ACLK | RSEL = 15 para o DCO 16MHz
	BCSCTL1 = XT2OFF + ACLK_div + (RSEL0 + RSEL1 + RSEL2 + RSEL3);
	//MCLK = DCOCLK | divisor do MCLK = 1 | SMLCK = DCOCLK | Divisor do SMCLK
	BCSCTL2 = SMCLK_div;
	BCSCTL3 = XCAP_3;

	//Prossegue quando LFXT1 estiver est�vel
	//Habilita gerac�o de interrup��o
	while(BCSCTL3 & LFXT1OF);
	__enable_interrupt();

	return 1;
}

void config_PORT(void)
{
	/* ---- Configurar Portas de I/O ----
	 *
	 * @param	void
	 * @return	void
	 *
	 * Configura��o Pr�-estabelecida:
	 * - Todas as portas P1 e P2 s�o sa�da
	 * - Sa�da baixa em todas as portas P1 e P2
	 *
	 */

	P1DIR = 0xFF;
	P1OUT = 0x00;
	P2DIR = 0xFF;
	P2OUT = 0x00;
}

int config_TA0(unsigned int habilita_interrup, char timerA0_font, unsigned int timerA0_div,unsigned int contagem)
{
	/* ---- Configurar o TIMER A0 ----
	 *
	 * @param  int  habilita_interrup: Interrup��es do Timer	0->desabilitadas, 1->habilitadas
	 * @param  char timerA0_font: Fonte do clock				A->ACLK, S->SMCLK
	 * @param int   timerA0_div: Divisor para o clock	 		1,2,4,8
	 * @param  int  contagem: At� quanto o timer deve contar	1 at� 65535
	 * @return int												1->configura��o conclu�da, 0->erro
	 *
	 * Configura��o Pr�-estabelecida:
	 * - Modo UP: conta at� 'contagem' -> Quando acaba a contagem, gera interrup��o
	 *
	 * O TIMER A0 tem 4 op��es de fontes de clock:
	 * Internas: ACLK, SMCLK
	 * Externas: TACLK
	 *
	 */

	unsigned int clock_font = 0;

	//Convers�o do par�metro timerA0_div
	if(timerA0_div == 1)
	{
		timerA0_div = ID_0;
	}
	else if(timerA0_div == 2)
	{
		timerA0_div = ID_1;
	}
	else if(timerA0_div == 4)
	{
		timerA0_div = ID_2;
	}
	else if(timerA0_div == 8)
	{
		timerA0_div = ID_3;
	}

	//Convers�o do par�metro timerA0_font
	if(timerA0_font=='A')
	{
		//Fonte ACLK
		clock_font = TASSEL_1;
	}
	else if(timerA0_font=='S')
	{
		//Fonte SMCLK
		clock_font = TASSEL_2;
	}
	else return 0; //Erro na identifica��o dos par�metros

	if(habilita_interrup==0)
	{
		//Interrup��es do Timer desabilitadas
		CLR(TACCTL0,CCIE);
	}
	else if(habilita_interrup==1)
	{
		//Interrup��es do Timer habilitadas
		SET(TACCTL0,CCIE);
	}
	else CLR(TACCTL0,CCIE); //Interrup��es do Timer desabilitadas

	//Cada contagem equivale, em seg, a TACCR0/clock
	//Eg: se TACCR0 = 4096 e ACLK = 32768Hz -> 4096/32768Hz = 0,125s -> gera interrup��o a cada 0,125s
	TACCR0 = contagem;
	//Clock clock_font | Clock = clock_font/timerA0_div | Modo UP (At� TA1CCR0) | Limpa contador
	TA0CTL = clock_font + timerA0_div + MC_1 + TACLR;

	return 1;
}

int config_TA1_PWM(char timerA1_font, unsigned int timerA1_div, unsigned int contagem, unsigned int dutty)
{
	/* ---- Configurar o TIMER A1 ----
	 *
	 * @param  char timerA0_font: Fonte do clock				A->ACLK, S->SMCLK
	 * @param  int  timerA0_div: Divisor para o clock	 		1,2,4,8
	 * @param  int  contagem: At� quanto o timer deve contar	1 at� 65535
	 * @param  int  dutty: raz�o c�clica do PWM					1 at� 65535
	 * @return int												1->configura��o conclu�da, 0->erro
	 *
	 * Configura��o Pr�-estabelecida:
	 * - Modo UP: conta at� 'contagem'
	 * - Sem Interrup��o
	 * - Sa�da em P2.2
	 *
	 * O TIMER A0 tem 4 op��es de fontes de clock:
	 * Internas: ACLK, SMCLK
	 * Externas: TACLK
	 *
	 */

	unsigned int clock_font = 0;

	//Convers�o do par�metro timerA0_div
	if(timerA1_div == 1)
	{
		timerA1_div = ID_0;
	}
	else if(timerA1_div == 2)
	{
		timerA1_div = ID_1;
	}
	else if(timerA1_div == 4)
	{
		timerA1_div = ID_2;
	}
	else if(timerA1_div == 8)
	{
		timerA1_div = ID_3;
	}

	//Convers�o do par�metro timerA0_font
	if(timerA1_font=='A')
	{
		//Fonte ACLK
		clock_font = TASSEL_1;
	}
	else if(timerA1_font=='S')
	{
		//Fonte SMCLK
		clock_font = TASSEL_2;
	}
	else return 0; //Erro na identifica��o dos par�metros

    P1DIR |= BIT6;							// P1.6/TA0.1 is used for PWM, thus also an output
    P2DIR |= BIT2;							// P2.2/TA1.1 is used for PWM, thus also an output
	SET(P1SEL,BIT6);
	SET(P2SEL,BIT2);

	//Clock clock_font | Clock = clock_font/timerA0_div | Modo UP (At� TA1CCR0) | Limpa contador
	TA1CTL = clock_font + timerA1_div + MC_1 + TACLR;

	//PWM reset/set
	TA1CCTL1 = OUTMOD_7;

	//Eg: SMCLK de 2MHz e Per�odo desejado de 16ms ->
	//Per�odo do PWM = TA1CCR0/clock_font -> TA1CCR0 = 16ms*2MHz = 32000 contagens
	//Dutty cycle desejado de 50% -> dutty = TA1CCR1/TA1CCR0 -> TA1CCR1 = dutty*TA1CCR0 = 0,5*32000 = 16000 contagens
	TA1CCR0 = contagem;
	TA1CCR1 = dutty; //Dutty cycle

	return 1;
}

void set_dutty_cycle_TA1(unsigned int dutty)
{
	/* ---- Setar a raz�o c�clica do PWM do TA1 ----
	 *
	 * @param  int dutty: dutty/contagem determina a % de dutty cycle		0 at� 'contagem'
	 * @return void
	 *
	 */

	TA1CCR1 = dutty;
}

void config_ADC(char ADC_font, int ADC_div, int porta, int periodo_amost)
{
	/* ---- Configurar o ADC10 ----
	 *
	 * @param  char ADC_font: Fonte do clock							A->ACLK, S->SMCLK, M->MCLK, C->ADC10
	 * @param int   ADC_div: Divisor para o clock	 					1,2,4,8
	 * @param  int  porta: Porta para o sinal anal�gico					6->A6, 7->A7
	 * @param  int  periodo_amost: quanto tempo para cada amostragem	4,8,16,64 x Clock
	 * @return void
	 *
	 * Configura��o Pr�-estabelecida:
	 * - Refer�ncia de 2,5V (2,5V = 1023 digital)
	 * - Interrup��es desabilitadas
	 *
	 * O ADC10 realiza convers�es de 10-bit (0~1023)
	 * 4 op��es de fontes de clock: SMCLK, MCLK, ACLK, e oscilador interno ADC10OSC(5MHz)
	 *
	 */

	int clock_font = 0;

	//Convers�o do par�metro timerA0_font
	if(ADC_font=='A')
	{
		//Fonte ACLK
		clock_font = ADC10SSEL_1;
	}
	else if(ADC_font=='S')
	{
		//Fonte SMCLK
		clock_font = ADC10SSEL_3;
	}
	else if(ADC_font=='M')
	{
		//Fonte ADC
		clock_font = ADC10SSEL_2;
	}
	else if(ADC_font=='C')
	{
		//Fonte ADC10
		clock_font = ADC10SSEL_0;
	}

	//Convers�o do par�metro ADC_div
	if(ADC_div==1)
	{
		ADC_div = ADC10DIV_0;
	}
	else if(ADC_div==2)
	{
		ADC_div = ADC10DIV_1;
	}
	else if(ADC_div==4)
	{
		ADC_div = ADC10DIV_3;
	}
	else if(ADC_div==8)
	{
		ADC_div = ADC10DIV_7;
	}

	//Convers�o do par�metro periodo_amost
	if(periodo_amost==4)
	{
		periodo_amost = ADC10SHT_0;
	}
	else if(periodo_amost==8)
	{
		periodo_amost = ADC10SHT_1;
	}
	else if(periodo_amost==16)
	{
		periodo_amost = ADC10SHT_2;
	}
	else if(periodo_amost==64)
	{
		periodo_amost = ADC10SHT_3;
	}

	//Convers�o do par�metro porta
	if(porta==7)
	{
		porta = INCH_7;
		ADC10AE0 = BIT7;
	}
	else if(porta==6)
	{
		porta = INCH_6;
		ADC10AE0 = BIT6;
	}

	//Gerador ref ON | 2.5V ref | ADC10 ON | 64xADC_clock
	ADC10CTL0 = SREF_1 + REFON + REF2_5V + ADC10ON + periodo_amost;

	//Canal de input = porta | ADC clock = clock_font/ADC_div | ADC clock = ADC_font
    ADC10CTL1 = porta + ADC_div + clock_font;
}

void converter_ADC10(unsigned int canal)
{
	/* ---- Realizar convers�o do canal escolhido ----
	 *
	 * @param  int canal: seleciona o canal para converter			5->A5, 6->A6, 7->A7
	 * @return void
	 *
	 * Configura��o Pr�-estabelecida:
	 * Joga valor da convers�o em 'var_convertida'
	 *
	 */

	//Convers�o do par�metro 'canal'
	if(canal==5)
	{
		//Troca canal para Temperatura A5
		SET_ADC_A5;
	}
	else if(canal==6)
	{
		//Troca canal para Temperatura A6
		SET_ADC_A6;
	}
	else if(canal==7)
	{
		//Troca canal para Temperatura A7
		SET_ADC_A7;
	}

	//Habilita e inicia convers�o
	ADC10CTL0 |= ENC + ADC10SC;
	//Espera a convers�o
	while(ADC10CTL1 & BUSY);
	//Guarda valor em conv_corrente
	conv_ADC_DIGITAL = ADC10MEM;
	//Desabilita convers�o
	ADC10CTL0&=~ENC;
	//Consulta VLOOKUP Table
}

void config_UART(char UART_font, unsigned int UCA_0, unsigned int UCA_1, unsigned int UCBRF)
{
	/* ---- Configurar a UART ----
	 *
	 * @param  char UART_font: Fonte do clock							A->ACLK, S->SMCLK, M->MCLK, U->UCLK
	 * @param  int  UCA_0: 7 bits menos significativos					0 at� 127
	 * @param  int  UCA_1: 7 bits mais significativos					0 at� 127
	 * @param  int  UCBRF: User Guide pg.425 Tabela 15-5				UCBRF_0 at� UCBRF_15
	 * @return void
	 *
	 * Configura��o Pr�-estabelecida:
	 * - P1.1 = RXD - P1.2 = TXD
	 * - Interrup��o habilitada
	 * - Paridade desabilitada
	 * - Gera��o de Baud Rate para clocks de alta frequ�ncia (USCO16 = 1)
	 *
	 * A Interface Universal de Comunica��o Serial (USCI) suporta verios modos de comunica��o:
	 * O m�dulo USCI_Ax suporta:
	 * UART mode
	 * SPI mode
	 * O m�dulo USCI_Bx suporta:
	 * I2C mode
	 * SPI mode
	 *
	 * No modo ass�ncrono, o m�dulo USCI_Ax conecta o MSP430 em um sistema externo via 2 pinos externos:
	 * UCAxRXD e UCAxTXD
	 */

	unsigned int clock_font = 0;

	//Convers�o do par�metro USCIA0_font
	if(UART_font=='A')
	{
		//Fonte ACLK
		clock_font = UCSSEL_1;
	}
	else if(UART_font=='S')
	{
		//Fonte SMCLK
		clock_font = UCSSEL_2;
	}
	else if(UART_font=='U')
	{
		//Fonte UCLK
		clock_font = UCSSEL_0;
	}

	//P1.1 = RXD - P1.2 = TXD
	P1SEL |= BIT1+BIT2;
	P1SEL2 |= BIT1+BIT2;

	//Desabilita USC para configura��o/ Seleciona fonte de clock
	UCA0CTL1 = UCSWRST;
	UCA0CTL1 = clock_font;

	//Baud Rate (M�ximo caso queira utilizar o USB do Lauchpad para transmiss�o serial)
	//N = f_Clock/Baud_rate
	//Eg: SMCLK de 8MHz, baudrate de 9600 e UCOS16 = 1 -> 8MHz/9600 = 52
	//52 = 00101100000000 -> UCA0BR0 = 0010110 e UCA0BR1 = 0000000 -> UCA0BR0 = 52 e UCA0BR1 = 0
	UCA0BR0 = UCA_0;
    UCA0BR1 = UCA_1;

    //Tablela do Manual do Usu�rio pg.425 Tabela 15-5
    UCA0MCTL = UCOS16 + UCBRF;

    //Habilita USC novamente
    UCA0CTL1 &= ~UCSWRST;

    //Habilita interrup��o RX
    UC0IE |= UCA0RXIE;
}

void send_uart(char *data)
{
	/* ---- Enviar mensagem pela UART ----
	 *
	 * @param int ACLK_div:  vetor de char			char string[] = { "TEXTO" };
	 * @return int 									void
	 *
	 */

	unsigned int i;
	unsigned int size = strlen(data);
	for(i=0;i<size;i++)
	{
		//Aguarda buffer TX estar preparado para nova transmiss�o
		while (!(IFG2&UCA0TXIFG));
		//Put a char into the TX Buffer, which will send the char out
		UCA0TXBUF = data[i];
	}

	_delay_cycles(32000000);
}

void converte_decimal_char(void)
{
	int x = var_convertida, digit, n = 1;
	//char x_str[2];

	while(n>=0)
	{
		//Base decimal
		digit = x%10;
		x = x/10;
		if (digit < 10)
		{
			string[n] = digit + '0';
		}
		else
		{
			string[n] = digit + 'A' - 10;  /* handle base > 9 */
		}

		n = n-1;
	}
}
