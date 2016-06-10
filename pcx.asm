	.386p
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "pcx.c"
	?debug	T "pcx.c"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
$$BNAMES	ends
$$BROWSE	segment byte public use32 'DEBSYM'
$$BROWSE	ends
$$BROWFILE	segment byte public use32 'DEBSYM'
$$BROWFILE	ends
DGROUP	group	_BSS,_DATA
_TEXT	segment dword public use32 'CODE'
_Quit	proc	near
?live1@0:
	?debug L 33
	push      ebp
	mov       ebp,esp
	push      ebx
	mov       ebx,dword ptr [ebp+8]
	?debug L 35
?live1@16: ; EBX = error
@1:
	push      offset s@
	push      ebx
	call      _strcmp
	add       esp,8
	test      eax,eax
	je        short @2
	?debug L 36
	push      ebx
	push      offset s@+8
	call      _printf
	add       esp,8
	?debug L 37
?live1@48: ; 
@2:
 	mov	 ah,04cH
	?debug L 38
 	int	 021H
	?debug L 39
@3:
	pop       ebx
	pop       ebp
	ret 
_Quit	endp
_TEXT	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	db	1
	db	0
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	db	2
	db	0
	db	0
	db	0
	dw	52
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch1
	dd	?patch2
	dd	?patch3
	df	_Quit
	dw	0
	dw	4096
	dw	0
	dw	1
	dw	0
	dd	?patch4
	db	5
	db	95
	db	81
	db	117
	db	105
	db	116
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	2
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	33
	db	1
	db	35
	db	1
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	4
	dw	0
	dw	?patch5
	dw	529
	dw	?patch6
	dd	?live1@16-_Quit
	dd	?live1@48-?live1@16
	dw	20
?patch6	equ	1
?patch5	equ	14
?patch1	equ	@3-_Quit+3
?patch2	equ	0
?patch3	equ	@3-_Quit
	dw	2
	dw	6
	dw	8
	dw	531
	dw	1
	dw	65532
	dw	65535
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_LoadPal	proc	near
?live1@96:
	?debug L 41
	push      ebp
	mov       ebp,esp
	add       esp,-772
	?debug L 47
@4:
	push      2
	push      -768
	push      dword ptr [_filee]
	call      _fseek
	add       esp,12
	?debug L 48
	push      dword ptr [_filee]
	push      1
	push      768
	lea       eax,dword ptr [ebp-772]
	push      eax
	call      _fread
	add       esp,16
	?debug L 49
 	mov	 dx,03c8H
	?debug L 50
 	xor	 ax,ax
	?debug L 51
 	out	 dx,al
	?debug L 52
 	mov	 dx,03c9H
	?debug L 53
	mov       cx,1
	?debug L 54
?live1@224: ; ECX = i
@5:
	movzx     edx,cx
	mov       al,byte ptr [ebp+edx-772]
	mov       byte ptr [ebp-1],al
	?debug L 55
?live1@240: ; 
 	mov	 al,byte ptr [ebp-1]
	?debug L 56
 	out	 dx,al
@7:
	inc       ecx
	cmp       cx,768
	jbe       short @5
	?debug L 58
@6:
@8:
	mov       esp,ebp
	pop       ebp
	ret 
_LoadPal	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	55
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch7
	dd	?patch8
	dd	?patch9
	df	_LoadPal
	dw	0
	dw	4098
	dw	0
	dw	3
	dw	0
	dd	?patch10
	db	8
	db	95
	db	76
	db	111
	db	97
	db	100
	db	80
	db	97
	db	108
	dw	18
	dw	512
	dw	65535
	dw	65535
	dw	32
	dw	0
	dw	4
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	45
	db	1
	db	54
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	18
	dw	0
	dw	16
	dw	2
	dw	33
	dw	0
	dw	10
	dw	5
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	44
	db	1
	db	53
	db	1
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	31
	dw	0
	dw	?patch11
	dw	529
	dw	?patch12
	dd	?live1@224-_LoadPal
	dd	?live1@240-?live1@224
	dw	10
?patch12	equ	1
?patch11	equ	14
	dw	18
	dw	512
	dw	64764
	dw	65535
	dw	4100
	dw	0
	dw	6
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	43
	db	1
	db	48
	db	6
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	45
	dw	0
?patch7	equ	@8-_LoadPal+4
?patch8	equ	0
?patch9	equ	@8-_LoadPal
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_LoadPCX	proc	near
?live1@288:
	?debug L 60
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 64
@9:
	push      offset s@+12
	push      dword ptr [ebp+8]
	call      _fopen
	add       esp,8
	mov       dword ptr [_filee],eax
	?debug L 65
	cmp       dword ptr [_filee],0
	jne       short @10
	push      offset s@+15
	call      _Quit
	pop       ecx
	?debug L 66
@10:
	push      dword ptr [_filee]
	push      1
	push      128
	push      offset _Header
	call      _fread
	add       esp,16
	?debug L 67
	cmp       byte ptr [_Header],10
	jne       short @12
	cmp       byte ptr [_Header+1],5
	jne       short @12
	cmp       byte ptr [_Header+3],8
	jne       short @12
	cmp       byte ptr [_Header+65],1
	je        short @11
	?debug L 68
@12:
	push      offset s@+33
	call      _Quit
	pop       ecx
	?debug L 69
@11:
	push      2
	push      -769
	push      dword ptr [_filee]
	call      _fseek
	add       esp,12
	?debug L 70
	push      dword ptr [_filee]
	push      1
	push      1
	lea       eax,dword ptr [ebp-1]
	push      eax
	call      _fread
	add       esp,16
	?debug L 71
	cmp       byte ptr [ebp-1],12
	je        short @13
	push      offset s@+57
	call      _Quit
	pop       ecx
	?debug L 72
@13:
	push      19
	call      _SetVideoMode
	pop       ecx
	?debug L 73
	call      _LoadPal
	?debug L 74
@14:
	pop       ecx
	pop       ebp
	ret 
_LoadPCX	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	55
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch13
	dd	?patch14
	dd	?patch15
	df	_LoadPCX
	dw	0
	dw	4101
	dw	0
	dw	7
	dw	0
	dd	?patch16
	db	8
	db	95
	db	76
	db	111
	db	97
	db	100
	db	80
	db	67
	db	88
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	8
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	60
	db	1
	db	64
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	59
	dw	0
	dw	18
	dw	512
	dw	65535
	dw	65535
	dw	32
	dw	0
	dw	9
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	62
	db	1
	db	70
	db	1
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	72
	dw	0
?patch13	equ	@14-_LoadPCX+3
?patch14	equ	0
?patch15	equ	@14-_LoadPCX
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_main	proc	near
?live1@480:
	?debug L 76
	push      ebp
	mov       ebp,esp
	?debug L 78
@15:
	cmp       dword ptr [ebp+8],1
	jle       short @17
	?debug L 79
	mov       eax,dword ptr [ebp+12]
	push      dword ptr [eax+4]
	call      _LoadPCX
	pop       ecx
	?debug L 80
	push      3
	call      _SetVideoMode
	pop       ecx
	?debug L 81
	push      dword ptr [_filee]
	call      _fclose
	pop       ecx
	?debug L 82
@18:
@17:
	pop       ebp
	ret 
_main	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	52
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch17
	dd	?patch18
	dd	?patch19
	df	_main
	dw	0
	dw	4103
	dw	0
	dw	10
	dw	0
	dd	?patch20
	db	5
	db	95
	db	109
	db	97
	db	105
	db	110
	dw	18
	dw	512
	dw	8
	dw	0
	dw	116
	dw	0
	dw	11
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	76
	db	1
	db	78
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	86
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	4104
	dw	0
	dw	12
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	76
	db	1
	db	79
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	99
	dw	0
?patch17	equ	@18-_main+2
?patch18	equ	0
?patch19	equ	@18-_main
	dw	2
	dw	6
$$BSYMS	ends
_BSS	segment dword public use32 'BSS'
_Header	label	byte
	db	128	dup(?)
	align	4
_filee	label	dword
	db	4	dup(?)
_BSS	ends
_DATA	segment dword public use32 'DATA'
s@	label	byte
	;	s@+0:
	db	"NOERROR",0
	;	s@+8:
	db	"%s",10,0
	;	s@+12:
	db	"rb",0
	;	s@+15:
	db	"cannot open file!",0
	;	s@+33:
	db	"PCX type not supported!",0
	;	s@+57:
	db	"Invalid palette!",0
	align	4
_DATA	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
	extrn	_fclose:near
	extrn	_fopen:near
	extrn	_fread:near
	extrn	_fseek:near
	extrn	_printf:near
	extrn	_strcmp:near
	extrn	_SetVideoMode:near
	public	_Header
	public	_filee
	public	_Quit
	public	_LoadPal
	public	_LoadPCX
	public	_main
	extrn	__setargv__:near
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	22
	dw	514
	df	_Header
	dw	0
	dw	4125
	dw	0
	dw	40
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	29
	db	1
	db	66
	db	1
	db	1
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	112
	dw	0
	dw	22
	dw	514
	df	_filee
	dw	0
	dw	4107
	dw	0
	dw	41
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	30
	db	1
	db	47
	db	1
	db	16
	db	1
	db	1
	db	3
	db	1
	db	11
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	127
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	42
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	2
	dw	40
	db	2
	db	254
	dw	327
	db	3
	db	7
	db	1
	db	1
	db	1
	db	1
	db	1
	db	3
	db	9
	db	1
	db	97
	db	7
	db	8
	db	255
	db	5
	dw	301
	db	8
	db	23
	db	255
	db	7
	dw	57
	db	4
	db	2
	db	2
	db	1
	db	4
	db	2
	db	2
	db	2
	db	2
	db	1
	db	13
	db	2
	db	7
	db	1
	db	22
	db	10
	db	2
	db	2
	db	1
	db	8
	db	2
	db	2
	db	2
	db	1
	db	99
	db	1
	db	2
	db	1
	db	255
	db	9
	dw	65
	db	2
	db	2
	db	2
	db	2
	db	1
	db	10
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	147
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	43
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	2
	dw	63
	db	2
	db	254
	dw	339
	db	2
	db	13
	db	2
	db	255
	db	7
	dw	57
	db	1
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	223
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	44
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	49
	db	5
	db	254
	dw	295
	db	12
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	246
	dw	0
	dw	16
	dw	4
	dw	4108
	dw	0
	dw	0
	dw	45
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	254
	db	5
	db	254
	dw	269
	db	13
	db	9
	db	1
	db	1
	db	1
	db	1
	db	1
	db	1
	db	1
	db	1
	db	1
	db	2
	db	1
	db	1
	db	1
	db	1
	db	1
	db	1
	db	2
	db	4
	db	6
	db	8
	db	2
	db	1
	db	11
	db	2
	db	1
	db	2
	db	10
	db	3
	db	1
	db	1
	db	1
	db	3
	db	4
	db	2
	db	1
	db	5
	db	1
	db	255
	db	1
	dw	30
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	262
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	46
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	8
	dw	41
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	320
	dw	0
	dw	16
	dw	4
	dw	4125
	dw	0
	dw	0
	dw	47
	dw	0
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	27
	db	1
	db	29
	db	37
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	330
	dw	0
	dw	?patch21
	dw	1
	db	2
	db	0
	db	8
	db	24
	db	6
	db	66
	db	67
	db	52
	db	46
	db	48
	db	48
?patch21	equ	13
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	245
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	246
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	247
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	248
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	249
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	250
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	251
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	252
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	5
	dw	253
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	13
	db	1
	db	67
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	14
	db	1
	db	67
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	15
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	16
	db	1
	db	68
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	17
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	17
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	18
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	18
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	19
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	20
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	21
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	22
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	23
	db	1
	db	68
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	24
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	25
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	26
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	76
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
?patch20	equ	606
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	60
	db	1
	db	79
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
?patch16	equ	616
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	41
	db	1
	db	73
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
?patch10	equ	629
$$BSYMS	ends
$$BROWSE	segment byte public use32 'DEBSYM'
	dw	0
	dw	0
	dw	0
	db	1
	dw	33
	db	1
	db	65
	db	3
	db	3
	db	0
	db	0
$$BROWSE	ends
$$BSYMS	segment byte public use32 'DEBSYM'
?patch4	equ	642
$$BSYMS	ends
$$BROWFILE	segment byte public use32 'DEBSYM'
	dw	48
	dw	0
	dw	49
	dw	0
	dw	50
	dw	0
	dw	51
	dw	0
	dw	52
	dw	0
	dw	53
	dw	0
	dw	54
	dw	0
	dw	55
	dw	0
	dw	56
	dw	0
	dw	57
	dw	0
	dw	58
	dw	0
$$BROWFILE	ends
$$BTYPES	segment byte public use32 'DEBTYP'
	db        2,0,0,0,14,0,8,0,3,0,0,0,0,0,1,0
	db        1,16,0,0,8,0,1,2,1,0,16,4,0,0,14,0
	db        8,0,3,0,0,0,0,0,0,0,3,16,0,0,4,0
	db        1,2,0,0,18,0,3,0,32,0,0,0,17,0,0,0
	db        0,0,0,0,0,3,0,3,14,0,8,0,3,0,0,0
	db        0,0,1,0,6,16,0,0,8,0,1,2,1,0,16,4
	db        0,0,14,0,8,0,3,0,0,0,0,0,2,0,9,16
	db        0,0,8,0,2,0,10,0,16,4,0,0,12,0,1,2
	db        2,0,116,0,0,0,8,16,0,0,14,0,8,0,116,0
	db        0,0,0,0,1,0,14,16,0,0,8,0,2,0,10,0
	db        12,16,0,0,28,0,5,0,9,0,13,16,0,0,0,0
	db        0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0
	db        24,0,180,0,4,2,6,4,32,4,0,0,0,0,14,0
	db        0,0,88,1,0,0,0,0,242,241,6,4,32,4,0,0
	db        0,0,15,0,0,0,98,1,0,0,4,0,242,241,6,4
	db        116,0,0,0,0,0,16,0,0,0,108,1,0,0,8,0
	db        242,241,6,4,116,0,0,0,0,0,17,0,0,0,118,1
	db        0,0,12,0,242,241,6,4,33,0,0,0,0,0,18,0
	db        0,0,128,1,0,0,16,0,242,241,6,4,33,0,0,0
	db        0,0,19,0,0,0,138,1,0,0,18,0,242,241,6,4
	db        17,0,0,0,0,0,20,0,0,0,148,1,0,0,20,0
	db        242,241,6,4,16,0,0,0,0,0,21,0,0,0,158,1
	db        0,0,22,0,242,241,6,4,32,0,0,0,0,0,22,0
	db        0,0,168,1,0,0,23,0,8,0,1,2,1,0,11,16
	db        0,0,14,0,8,0,11,16,0,0,0,0,2,0,18,16
	db        0,0,8,0,2,0,10,0,17,16,0,0,8,0,1,0
	db        1,0,16,0,0,0,12,0,1,2,2,0,16,16,0,0
	db        16,16,0,0,14,0,8,0,117,0,0,0,0,0,4,0
	db        20,16,0,0,20,0,1,2,4,0,3,4,0,0,117,0
	db        0,0,117,0,0,0,11,16,0,0,14,0,8,0,116,0
	db        0,0,0,0,3,0,22,16,0,0,16,0,1,2,3,0
	db        11,16,0,0,18,0,0,0,116,0,0,0,14,0,8,0
	db        116,0,0,0,64,0,2,0,24,16,0,0,12,0,1,2
	db        2,0,16,16,0,0,0,0,0,0,14,0,8,0,116,0
	db        0,0,0,0,2,0,26,16,0,0,12,0,1,2,2,0
	db        16,16,0,0,16,16,0,0,14,0,8,0,3,0,0,0
	db        0,0,1,0,28,16,0,0,8,0,1,2,1,0,116,0
	db        0,0,28,0,5,0,16,0,32,16,0,0,0,0,0,0
	db        0,0,0,0,0,0,0,0,0,0,23,0,0,0,128,0
	db        18,0,3,0,32,0,0,0,17,0,0,0,0,0,0,0
	db        48,0,48,0,18,0,3,0,32,0,0,0,17,0,0,0
	db        0,0,0,0,58,0,58,0,64,1,4,2,6,4,32,0
	db        0,0,0,0,24,0,0,0,178,1,0,0,0,0,242,241
	db        6,4,32,0,0,0,0,0,25,0,0,0,191,1,0,0
	db        1,0,242,241,6,4,32,0,0,0,0,0,26,0,0,0
	db        204,1,0,0,2,0,242,241,6,4,32,0,0,0,0,0
	db        27,0,0,0,214,1,0,0,3,0,242,241,6,4,33,0
	db        0,0,0,0,28,0,0,0,227,1,0,0,4,0,242,241
	db        6,4,33,0,0,0,0,0,29,0,0,0,237,1,0,0
	db        6,0,242,241,6,4,33,0,0,0,0,0,30,0,0,0
	db        247,1,0,0,8,0,242,241,6,4,33,0,0,0,0,0
	db        31,0,0,0,1,2,0,0,10,0,242,241,6,4,33,0
	db        0,0,0,0,32,0,0,0,11,2,0,0,12,0,242,241
	db        6,4,33,0,0,0,0,0,33,0,0,0,21,2,0,0
	db        14,0,242,241,6,4,30,16,0,0,0,0,34,0,0,0
	db        31,2,0,0,16,0,242,241,6,4,32,0,0,0,0,0
	db        35,0,0,0,41,2,0,0,64,0,242,241,6,4,32,0
	db        0,0,0,0,36,0,0,0,51,2,0,0,65,0,242,241
	db        6,4,33,0,0,0,0,0,37,0,0,0,64,2,0,0
	db        66,0,242,241,6,4,33,0,0,0,0,0,38,0,0,0
	db        74,2,0,0,68,0,242,241,6,4,31,16,0,0,0,0
	db        39,0,0,0,84,2,0,0,70,0,14,0,8,0,116,0
	db        0,0,2,0,0,0,34,16,0,0,4,0,1,2,0,0
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
	db	4,'Quit'
	db	5,'error'
	db	7,'LoadPal'
	db	2,'i2'
	db	1,'i'
	db	3,'Pal'
	db	7,'LoadPCX'
	db	8,'filename'
	db	1,'b'
	db	4,'main'
	db	4,'argc'
	db	4,'argv'
	db	4,'FILE'
	db	4,'curp'
	db	6,'buffer'
	db	5,'level'
	db	5,'bsize'
	db	6,'istemp'
	db	5,'flags'
	db	5,'token'
	db	2,'fd'
	db	4,'hold'
	db	11,'T_PCXHeader'
	db	12,'Manufacturer'
	db	7,'Version'
	db	8,'Encoding'
	db	12,'BitsPerPixel'
	db	4,'XMin'
	db	4,'YMin'
	db	4,'XMax'
	db	4,'YMax'
	db	4,'HRes'
	db	4,'VRes'
	db	7,'Palette'
	db	8,'Reserved'
	db	11,'ColorPlanes'
	db	12,'BytesPerLine'
	db	11,'PaletteType'
	db	6,'Filler'
	db	6,'Header'
	db	5,'filee'
	db	6,'size_t'
	db	7,'wchar_t'
	db	6,'fpos_t'
	db	4,'FILE'
	db	9,'ptrdiff_t'
	db	11,'T_PCXHeader'
	db	5,'pcx.c'
	db	23,'D:\BC5\INCLUDE\STDLIB.H'
	db	22,'D:\BC5\INCLUDE\_defs.h'
	db	22,'D:\BC5\INCLUDE\_null.h'
	db	22,'D:\BC5\INCLUDE\STDIO.H'
	db	23,'D:\BC5\INCLUDE\_nfile.h'
	db	23,'D:\BC5\INCLUDE\STRING.H'
	db	23,'D:\BC5\INCLUDE\stddef.h'
	db	20,'D:\BC5\INCLUDE\MEM.H'
	db	19,'D:\BC5\INCLUDE\IO.H'
	db	10,'mcgaunit.h'
$$BNAMES	ends
	?debug	D "mcgaunit.h" 8231 15264
	?debug	D "D:\BC5\INCLUDE\IO.H" 8277 10240
	?debug	D "D:\BC5\INCLUDE\MEM.H" 8277 10240
	?debug	D "D:\BC5\INCLUDE\stddef.h" 8277 10240
	?debug	D "D:\BC5\INCLUDE\STRING.H" 8277 10240
	?debug	D "D:\BC5\INCLUDE\_nfile.h" 8277 10240
	?debug	D "D:\BC5\INCLUDE\STDIO.H" 8277 10240
	?debug	D "D:\BC5\INCLUDE\_null.h" 8277 10240
	?debug	D "D:\BC5\INCLUDE\_defs.h" 8277 10240
	?debug	D "D:\BC5\INCLUDE\STDLIB.H" 8277 10240
	?debug	D "pcx.c" 8226 358
	end
