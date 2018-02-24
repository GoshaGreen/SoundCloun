;вывести число
;OUTI регистр значение
.macro OUTI
	PUSH R16          	
    LDI R16,@1
	.if @0 < 0x40
		OUT @0,R16       
   	.else
		STS @0,R16
   	.endif
	POP R16
.endm

;универсальный вывод 
;UOUT регистр значение
.macro    UOUT      
	.if	@0 < 0x40
		OUT	@0,@1         
	.else
      	STS	@0,@1
   	.endif
.endm
	
;поместить регистр SREG в стэк
;PUSHF
.MACRO PUSHF
	PUSH	R16
	IN	R16,SREG
	PUSH	R16
.ENDM
 
;достать регистр SREG из стека
;POPF
.MACRO POPF
	POP	R16
	OUT	SREG,R16
	POP	R16
.ENDM

;установить бит с использованием стека
;SETBM регистр бит
.MACRO	SETBM 
	.if @0 < 0x20
		SBI	@0,@1
	.else
		.if @0<0x40
			PUSH	R17
			IN	R17,@0
			ORI	R17,1<<@1
			OUT	@0,R17
			POP	R17
		.else
			PUSH	R17
			LDS	R17,@0
			ORI	R17,1<<@1
			STS	@0,R17
			POP	R17
		.endif
	.endif
.ENDM
 
;установить бит с использованием регистра
;SETB регистр бит регистр_буфер
.MACRO	SETB
	.if @0 < 0x20			; Low IO
		SBI	@0,@1
	.else
		.if @0<0x40		; High IO
			IN	@2,@0
			ORI	@2,1<<@1
			OUT	@0,@2
		.else			; Memory
			LDS	@2,@0
			ORI	@2,1<<@1
			STS	@0,@2
		.endif
	.endif
.ENDM

;очистить бит с использованием регистра
;CLRB регистр бит регистр_буфер
.MACRO	CLRB 
	.if @0 < 0x20			; Low IO
		CBI	@0,@1
	.else
		.if @0<0x40		; High IO
			IN	@2,@0
			ANDI @2,~(1<<@1)
			OUT	@0,@2
		.else			; Memory
			LDS	@2,@0
			ANDI @2,~(1<<@1)
			STS	@0,@2
		.endif
	.endif
.ENDM
 
;очисттить бит с использованием стека
;CLRBM регистр бит
.MACRO	CLRBM 
	.if @0 < 0x20
		CBI	@0,@1
	.else
		.if @0<0x40
			PUSH R17
			IN R17,@0
			ANDI R17,~(1<<@1)
			OUT	@0,R17
			POP	R17
		.else
			PUSH	R17
			LDS	R17,@0
			ANDI	R17,~(1<<@1)
			STS	@0,R17
			POP	R17
		.endif
	.endif
.ENDM

;инвертирование бита с использованием двух регистров
;INVB регистр бит регистр_буфер_1 регистр_буфер_2
.MACRO	INVB
	.if	@0 < 0x40
		IN	@2,@0
		LDI	@3,1<<@1
		EOR	@3,@2
		OUT	@0,@3
	.else
		LDS	@2,@0
		LDI	@3,1<<@1
		EOR	@2,@3
		STS	@0,@2
	.endif
.ENDM
 
;инвертирование бита с использованием стека
;INVBM регистр бит
.MACRO	INVBM
	.if	@0 < 0x40
		PUSH R16
		PUSH R17
		IN	R16,@0
		LDI	R17,1<<@1
		EOR	R17,R16
		OUT	@0,R17
		POP	R17
		POP	R16
	.else
		PUSH R16
		PUSH R17
		LDS	R16,@0
		LDI	R17,1<<@1
		EOR	R17,R16
		STS	@0,R17
		POP	R17
		POP	R16
	.endif
.ENDM
