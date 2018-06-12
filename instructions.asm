%define	C	1
%define	Z	1 << 1
%define	V	1 << 6
%define	N	1 << 7

%macro	FLAGS_UPD	2
	setc	al
	setz	r9b
	seto	r10b
	sets	r11b
	and	byte %1, ~(%2)
	shl	r9b, 1
	shl	r10b, 6
	shl	r11b, 7
	or	al, r9b
	or	al, r10b
	or	al, r11b
	and	al, %2
	or	%1, al
%endmacro

section	.text

global	OP_ADC
OP_ADC:
	clc
	test	byte [r8], C
	jz	.sk
	stc
.sk:	adc	[rcx], dl
	FLAGS_UPD	[r8], (C | Z | V | N)
	ret

global	OP_AND
OP_AND:
	and	[rcx], dl
	FLAGS_UPD	[r8], (Z | N)
	ret

global	OP_ASL
OP_ASL:
	sal	byte [rcx], 1
	FLAGS_UPD	[rdx], (C | Z | N)
	ret

global	OP_BIT
OP_BIT:
	test	dl, [rcx]
	FLAGS_UPD	[r8], (Z | N)
	and	byte [r8], ~V
	test	dl, 1 << 6
	jz	.sk
	or	byte [r8], V
.sk:	ret

global	OP_CMP
OP_CMP:
	cmp	[rcx], dl
	FLAGS_UPD	[r8], (C | Z | N)
	; TODO: CF when op1 = op2 ?
	ret

global	OP_DEC
OP_DEC:
	dec	byte [rcx]
	FLAGS_UPD	[rdx], (Z | N)
	ret

global	OP_EOR
OP_EOR:
	xor	[rcx], dl
	FLAGS_UPD	[r8], (Z | N)
	ret

global	OP_INC
OP_INC:
	inc	byte [rcx]
	FLAGS_UPD	[rdx], (Z | N)
	ret

global	OP_LD
OP_LD:
	mov	[rcx], dl
	or	byte [rcx], 0
	FLAGS_UPD	[r8], (Z | N)
	ret

global	OP_LSR
OP_LSR:
	shr	byte [rcx], 1
	FLAGS_UPD	[rdx], (C | Z | N)
	ret

global	OP_ORA
OP_ORA:
	or	[rcx], dl
	FLAGS_UPD	[r8], (Z | N)
	ret

global	OP_ROL
OP_ROL:
	clc
	test	byte [rdx], C
	jz	.sk
	stc
.sk:	rol	byte [rcx], 1
	FLAGS_UPD	[rdx], (C | Z | N)
	ret

global	OP_ROR
OP_ROR:
	clc
	test	byte [rdx], C
	jz	.sk
	stc
.sk:	ror	byte [rcx], 1
	FLAGS_UPD	[rdx], (C | Z | N)
	ret

global	OP_SBC
OP_SBC:
	clc
	test	byte [r8], C
	jz	.sk
	stc
.sk:	sbb	[rcx], dl
	FLAGS_UPD	[r8], (C | Z | V | N)
	ret
