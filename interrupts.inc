.ORG 0x0000	
JMP RESET			// External Pin, Power-on Reset, Brown-out Reset and Watchdog System
.ORG 0x0002 
RETI ;RJMP I_INT0			// External Interrupt Request 0
.ORG 0x0004 
RETI ;RJMP I_INT1			// External Interrupt Request 0
.ORG 0x0006 
RETI ;RJMP I_PCINT0			// Pin Change Interrupt Request 0
.ORG 0x0008 
RETI ;RJMP I_PCINT1			// Pin Change Interrupt Request 1
.ORG 0x000A 
RETI ;RJMP I_PCINT2			// Pin Change Interrupt Request 2
.ORG 0x000C 
RETI ;RJMP I_WDT			// Time-out Interrupt
.ORG 0x000E 
RETI ;	RJMP I_TIMER2_COMPA	// Timer/Counter2 Compare Match A
.ORG 0x0010 
RETI ;RJMP I_TIMER2_COMPB	// Timer/Coutner2 Compare Match B
.ORG 0x0012  
RETI ;	RJMP I_TIMER2_OVF		// Timer/Counter2 Overflow
.ORG 0x0014 
RETI ;RJMP I_TIMER1_CAPT	// Timer/Counter1 Capture Event
.ORG 0x0016 
RETI ;RJMP I_TIMER1_COMPA	// Timer/Counter1 Compare Match A
.ORG 0x0018 
RETI ;RJMP I_TIMER1_COMPB	// Timer/Coutner1 Compare Match B
.ORG 0x001A 
RETI ;RJMP I_TIMER1_OVF		// Timer/Counter1 Overflow
.ORG 0x001C ;RETI ;
	RJMP I_TIMER0_COMPA	// Timer/Counter0 Compare Match A
.ORG 0x001E 
RETI ;RJMP I_TIMER0_COMPB	// Timer/Coutner0 Compare Match B
.ORG 0x0020 
RETI ;RJMP I_TIMER0_OVF		// Timer/Counter0 Overflow
.ORG 0x0022 
RETI ;RJMP I_SPI_STC		//SPI Serial Transfer Complete
.ORG 0x0024 
RETI ;RJMP I_USART_RX		// USART Rx Complete
.ORG 0x0026 
RETI ;RJMP I_USART_UDRE		// USART Data Register Empty
.ORG 0x0028 
RETI ;RJMP I_USART_TX		// USART Tx Complete
.ORG 0x002A 
RETI ;RJMP I_ADC			// ADC Conversion Complete
.ORG 0x002C 
RETI ;RJMP I_EE				// READY EEPROM Ready
.ORG 0x002E 
RETI ;RJMP I_ANALOG			// COMP Analog Comparator

; Interrupts ==============================================
// RETI 
// I_INT0:
// RETI 
// I_INT1:
// RETI 
// I_PCINT0:
// RETI 
// I_PCINT1:
// RETI 
// I_PCINT2:
// RETI 
// I_WDT:
// RETI 
// I_TIMER2_COMPA:
// RETI 
// I_TIMER2_COMPB:
// RETI 
// I_TIMER2_OVF:
// RETI
// I_TIMER1_CAPT:
// RETI 
// I_TIMER1_COMPA:
// RETI 
// I_TIMER1_COMPB:
// RETI 
// I_TIMER1_OVF:
// RETI 
I_TIMER0_COMPA:

	CPI		ZH, high(soundend*2) ; проверка на окончание аудио файла 
	BRNE	NOTRESET
	CPI		ZL, low(soundend*2)
	BREQ	TURNOFF
NOTRESET:	
	LPM		R19, Z+
	UOUT	OCR2B,	R19
RETI 
// I_TIMER0_COMPB:
// RETI 
// I_TIMER0_OVF:
// RETI
// I_SPI_STC:
// RETI 
// I_USART_RX:
// RETI 
// I_USART_UDRE:
// RETI 
// I_USART_TX:	
// RETI 
// I_ADC:	
// RETI
// I_EE:	
// RETI 
// I_ANALOG:

TURNOFF:
	SBIS	PIND,	1
	RJMP	RESET

	OUTI	TCCR0A, 0
	OUTI	TCCR0B, 0
	OUTI	TIMSK0, 0
	OUTI	OCR0A,	0
	OUTI	OCR0B,	0
; инициализация тамера 2 - шим
	OUTI	TCCR2A, 0
	OUTI	TCCR2B, 0
	OUTI	TIMSK2, 0
	OUTI	OCR2A,	0
	OUTI	OCR2B,	0
; инициализация портов вывод 
	/*OUTI	DDRD,	0*/
	OUTI	PORTD,	0

	SBI		PIND,	1
	SBI		PIND,	1
	NOP
	SBI		PIND,	1
	SBI		PIND,	1

	OUTI	SMCR, (0<<SM2)|(1<<SM1)|(0<<SM0)|(1<<SE)
	SLEEP

	RJMP TURNOFF
; End Interrupts ==========================================
RESET:  
