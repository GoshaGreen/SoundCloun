.include "macro.inc"	
;88 RAM ========================================================
.DSEG ; Сегмент 

;88 END RAM / FLASH ============================================
.CSEG ; Сегмент
; Include ======================================================
	.include "interrupts.inc"
	.include "coreinit.inc"	
; END Include / Internal Hardware Init  ========================
; инициализация тамера 0 - обновление шим 
	OUTI	TCCR0A, (0<<COM0A1)|(0<<COM0A0)|(0<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(0<<WGM00); 
	OUTI	TCCR0B, (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00); div8
	OUTI	TIMSK0, (1<<2)|(1<<1)|(1<<0)	; OCIEB = 2, OCIEA = 1, TOIE = 0
	OUTI	OCR0A,	165
	OUTI	OCR0B,	0
; инициализация тамера 2 - шим
	OUTI	TCCR2A, (1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00)
	OUTI	TCCR2B, (0<<FOC2A)|(0<<FOC2B)|(0<<WGM22)|(0<<CS22)|(0<<CS21)|(1<<CS20)  ; div1
	OUTI	TIMSK2, (0<<2)|(0<<1)|(0<<0)	; OCIEB = 2, OCIEA = 1, TOIE = 0
	OUTI	OCR2A,	127 
	OUTI	OCR2B,	63
; инициализация портов вывод 
	OUTI	DDRD,	0b00001100
	OUTI	PORTD,	0b00000010
; калибровка осциллятора
	OUTI	OSCCAL,	0x7F
; END Internal Hardware Init / External Hardware Init  =========

; END External Hardware Init / Main ============================
	LDI 	ZL,	low(sound*2) 	; заносим младший байт адреса, в регистровую пару Z
	LDI  	ZH,	high(sound*2)
	SBI		PORTD, 2
main:		; тупняк
	SEI
	NOP
	NOP
	NOP
	RJMP main
; END Main / Procedure =========================================

; END Procedure ================================================
//sound:
.include "sound.inc"
//soundend:
;88 END FLASH / EEPROM =========================================
.ESEG				; Сегмент EEPROM

;88 End EEPROM =================================================