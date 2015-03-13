opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 10920"

opt pagewidth 120

	opt lm

	processor	16F819
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
	FNCALL	_main,_init
	FNCALL	_main,_OPTION_SELECT
	FNCALL	_main,_PING
	FNCALL	_main,_interrupts
	FNCALL	_main,_ADC_READ
	FNCALL	_main,_OUTPUT
	FNCALL	_PING,_delay2
	FNCALL	_PING,_delay1
	FNCALL	_OPTION_SELECT,_delay
	FNROOT	_main
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_ADCHIGH
	global	_ADCLOW
	global	_AND
	global	_DATA
	global	_END
	global	_IN
	global	_OR
	global	_SPEED
	global	_T
	global	_Y
	global	_Z
	global	_adc1
	global	_count2
	global	_lasercount
	global	_laseroff
	global	_adc
	global	_c
	global	_i
psect	nvBANK0,class=BANK0,space=1
global __pnvBANK0
__pnvBANK0:
_i:
       ds      2

	global	_ADCON0
_ADCON0	set	31
	global	_ADRESH
_ADRESH	set	30
	global	_PORTA
_PORTA	set	5
	global	_PORTB
_PORTB	set	6
	global	_ADON
_ADON	set	248
	global	_CARRY
_CARRY	set	24
	global	_GIE
_GIE	set	95
	global	_GO_DONE
_GO_DONE	set	250
	global	_INTE
_INTE	set	92
	global	_INTF
_INTF	set	89
	global	_PEIE
_PEIE	set	94
	global	_RA1
_RA1	set	41
	global	_RA6
_RA6	set	46
	global	_RA7
_RA7	set	47
	global	_RB0
_RB0	set	48
	global	_RB1
_RB1	set	49
	global	_RB2
_RB2	set	50
	global	_RB3
_RB3	set	51
	global	_RB4
_RB4	set	52
	global	_RBIE
_RBIE	set	91
	global	_SSPEN
_SSPEN	set	165
	global	_ADCON1
_ADCON1	set	159
	global	_OSCCON
_OSCCON	set	143
	global	_INTEDG
_INTEDG	set	1038
	global	_TRISA0
_TRISA0	set	1064
	global	_TRISA1
_TRISA1	set	1065
	global	_TRISA2
_TRISA2	set	1066
	global	_TRISA6
_TRISA6	set	1070
	global	_TRISA7
_TRISA7	set	1071
	global	_TRISB0
_TRISB0	set	1072
	global	_TRISB1
_TRISB1	set	1073
	global	_TRISB2
_TRISB2	set	1074
	global	_TRISB3
_TRISB3	set	1075
	global	_TRISB4
_TRISB4	set	1076
	global	_TRISB5
_TRISB5	set	1077
	global	_EEADR
_EEADR	set	269
	global	_EEDATA
_EEDATA	set	268
	global	_EECON1
_EECON1	set	396
	global	_EECON2
_EECON2	set	397
	global	_RD
_RD	set	3168
	global	_WR
_WR	set	3169
	global	_WREN
_WREN	set	3170
	file	"TRIG.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_adc:
       ds      2

_c:
       ds      2

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_ADCHIGH:
       ds      2

_ADCLOW:
       ds      2

_AND:
       ds      2

_DATA:
       ds      2

_END:
       ds      2

_IN:
       ds      2

_OR:
       ds      2

_SPEED:
       ds      2

_T:
       ds      2

_Y:
       ds      2

_Z:
       ds      2

_adc1:
       ds      2

_count2:
       ds      2

_lasercount:
       ds      2

_laseroff:
       ds      2

psect clrtext,class=CODE,delta=2
global clear_ram
;	Called with FSR containing the base address, and
;	W with the last address+1
clear_ram:
	clrwdt			;clear the watchdog before getting into this loop
clrloop:
	clrf	indf		;clear RAM location pointed to by FSR
	incf	fsr,f		;increment pointer
	xorwf	fsr,w		;XOR with final address
	btfsc	status,2	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
	xorwf	fsr,w		;XOR again to restore value
	goto	clrloop		;do the next byte

; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	movlw	low(__pbssCOMMON)
	movwf	fsr
	movlw	low((__pbssCOMMON)+04h)
	fcall	clear_ram
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	bcf	status, 7	;select IRP bank0
	movlw	low(__pbssBANK0)
	movwf	fsr
	movlw	low((__pbssBANK0)+01Eh)
	fcall	clear_ram
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_init
?_init:	; 0 bytes @ 0x0
	global	?_interrupts
?_interrupts:	; 0 bytes @ 0x0
	global	?_delay
?_delay:	; 0 bytes @ 0x0
	global	?_delay2
?_delay2:	; 0 bytes @ 0x0
	global	?_OPTION_SELECT
?_OPTION_SELECT:	; 0 bytes @ 0x0
	global	?_delay1
?_delay1:	; 0 bytes @ 0x0
	global	?_ADC_READ
?_ADC_READ:	; 0 bytes @ 0x0
	global	?_OUTPUT
?_OUTPUT:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	?_ISR
?_ISR:	; 0 bytes @ 0x0
	global	??_ISR
??_ISR:	; 0 bytes @ 0x0
	global	?_PING
?_PING:	; 2 bytes @ 0x0
	ds	4
	global	??_init
??_init:	; 0 bytes @ 0x4
	global	??_interrupts
??_interrupts:	; 0 bytes @ 0x4
	global	??_delay
??_delay:	; 0 bytes @ 0x4
	global	??_delay2
??_delay2:	; 0 bytes @ 0x4
	global	??_OPTION_SELECT
??_OPTION_SELECT:	; 0 bytes @ 0x4
	global	??_delay1
??_delay1:	; 0 bytes @ 0x4
	global	??_ADC_READ
??_ADC_READ:	; 0 bytes @ 0x4
	global	PING@a
PING@a:	; 2 bytes @ 0x4
	ds	2
	global	??_main
??_main:	; 0 bytes @ 0x6
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	??_PING
??_PING:	; 0 bytes @ 0x0
	global	??_OUTPUT
??_OUTPUT:	; 0 bytes @ 0x0
	ds	3
;;Data sizes: Strings 0, constant 0, data 0, bss 34, persistent 2 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      6      10
;; BANK0           80      3      35
;; BANK1           80      0       0
;; BANK2           80      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_PING
;;   _main->_ADC_READ
;;
;; Critical Paths under _ISR in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_PING
;;   _main->_OUTPUT
;;
;; Critical Paths under _ISR in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _ISR in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.
;;
;; Critical Paths under _ISR in BANK2
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 0     0      0     111
;;                               _init
;;                      _OPTION_SELECT
;;                               _PING
;;                         _interrupts
;;                           _ADC_READ
;;                             _OUTPUT
;; ---------------------------------------------------------------------------------
;; (1) _OUTPUT                                               3     3      0       0
;;                                              0 BANK0      3     3      0
;; ---------------------------------------------------------------------------------
;; (1) _PING                                                 5     5      0     111
;;                                              4 COMMON     2     2      0
;;                                              0 BANK0      3     3      0
;;                             _delay2
;;                             _delay1
;; ---------------------------------------------------------------------------------
;; (1) _ADC_READ                                             2     2      0       0
;;                                              4 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (1) _OPTION_SELECT                                        0     0      0       0
;;                              _delay
;; ---------------------------------------------------------------------------------
;; (2) _delay1                                               0     0      0       0
;; ---------------------------------------------------------------------------------
;; (2) _delay2                                               0     0      0       0
;; ---------------------------------------------------------------------------------
;; (2) _delay                                                0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _interrupts                                           0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _init                                                 0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (3) _ISR                                                  4     4      0       0
;;                                              0 COMMON     4     4      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 3
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _init
;;   _OPTION_SELECT
;;     _delay
;;   _PING
;;     _delay2
;;     _delay1
;;   _interrupts
;;   _ADC_READ
;;   _OUTPUT
;;
;; _ISR (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      6       A       1       71.4%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       2       2        0.0%
;;BANK0               50      3      23       3       43.8%
;;BITBANK1            50      0       0       4        0.0%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;BANK1               50      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BITBANK2            50      0       0       6        0.0%
;;BANK2               50      0       0       7        0.0%
;;ABS                  0      0      2D       8        0.0%
;;BITBANK0            50      0       0       9        0.0%
;;DATA                 0      0      2F      10        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 6 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\Main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_init
;;		_OPTION_SELECT
;;		_PING
;;		_interrupts
;;		_ADC_READ
;;		_OUTPUT
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\Main.c"
	line	6
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 5
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	7
	
l3425:	
;Main.c: 7: init();
	fcall	_init
	line	8
;Main.c: 8: OPTION_SELECT();
	fcall	_OPTION_SELECT
	line	9
	
l3427:	
;Main.c: 9: END =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_END)
	clrf	(_END+1)
	line	10
	
l3429:	
;Main.c: 10: c =0;
	clrf	(_c)
	clrf	(_c+1)
	line	11
	
l3431:	
;Main.c: 11: RA1 =0;
	bcf	(41/8),(41)&7
	line	12
;Main.c: 12: PING();
	fcall	_PING
	line	13
	
l3433:	
;Main.c: 13: Y =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_Y)
	clrf	(_Y+1)
	line	14
	
l3435:	
;Main.c: 14: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	15
	
l3437:	
;Main.c: 15: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	16
	
l3439:	
;Main.c: 16: TRISB1 =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1073/8)^080h,(1073)&7
	line	17
	
l3441:	
;Main.c: 17: RB1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(49/8),(49)&7
	line	18
	
l3443:	
;Main.c: 18: RA1 =0;
	bcf	(41/8),(41)&7
	line	19
	
l3445:	
;Main.c: 19: c =0;
	clrf	(_c)
	clrf	(_c+1)
	line	20
	
l3447:	
;Main.c: 20: RB4 =1;
	bsf	(52/8),(52)&7
	line	21
	
l3449:	
;Main.c: 21: interrupts();
	fcall	_interrupts
	line	22
;Main.c: 22: if(END ==1)
	movlw	01h
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	xorwf	(_END),w
	iorwf	(_END+1),w
	skipz
	goto	u3961
	goto	u3960
u3961:
	goto	l3453
u3960:
	line	24
	
l3451:	
;Main.c: 23: {
;Main.c: 24: INTE =0;
	bcf	(92/8),(92)&7
	line	25
;Main.c: 25: INTF =0;
	bcf	(89/8),(89)&7
	goto	l3453
	line	26
	
l561:	
	line	27
	
l3453:	
;Main.c: 26: }
;Main.c: 27: count2 =0;
	clrf	(_count2)
	clrf	(_count2+1)
	goto	l3487
	line	29
;Main.c: 29: while(1)
	
l562:	
	line	34
;Main.c: 30: {
;Main.c: 34: while(Z ==1)
	goto	l3487
	
l564:	
	goto	l3455
	line	36
;Main.c: 35: {
;Main.c: 36: while(1)
	
l565:	
	line	38
	
l3455:	
;Main.c: 37: {
;Main.c: 38: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	39
;Main.c: 39: while(c <25000)
	goto	l3465
	
l567:	
	line	41
	
l3457:	
;Main.c: 40: {
;Main.c: 41: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	42
;Main.c: 42: if(c ==1500)
	movlw	high(05DCh)
	xorwf	(_c+1),w
	skipz
	goto	u3975
	movlw	low(05DCh)
	xorwf	(_c),w
u3975:

	skipz
	goto	u3971
	goto	u3970
u3971:
	goto	l3465
u3970:
	line	44
	
l3459:	
;Main.c: 43: {
;Main.c: 44: IN =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_IN)
	clrf	(_IN+1)
	line	45
;Main.c: 45: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	46
	
l3461:	
;Main.c: 46: RB1 =1;
	bsf	(49/8),(49)&7
	line	47
	
l3463:	
;Main.c: 47: RA1 =0;
	bcf	(41/8),(41)&7
	goto	l3465
	line	48
	
l568:	
	goto	l3465
	line	49
	
l566:	
	line	39
	
l3465:	
	movlw	high(061A8h)
	subwf	(_c+1),w
	movlw	low(061A8h)
	skipnz
	subwf	(_c),w
	skipc
	goto	u3981
	goto	u3980
u3981:
	goto	l3457
u3980:
	goto	l3467
	
l569:	
	line	50
	
l3467:	
;Main.c: 48: }
;Main.c: 49: }
;Main.c: 50: ADC_READ();
	fcall	_ADC_READ
	line	51
	
l3469:	
;Main.c: 51: if(adc <112)
	movlw	high(070h)
	subwf	(_adc+1),w
	movlw	low(070h)
	skipnz
	subwf	(_adc),w
	skipnc
	goto	u3991
	goto	u3990
u3991:
	goto	l3477
u3990:
	line	55
	
l3471:	
;Main.c: 52: {
;Main.c: 55: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	56
	
l3473:	
;Main.c: 56: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	57
	
l3475:	
;Main.c: 57: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	l3477
	line	61
	
l570:	
	line	62
	
l3477:	
;Main.c: 61: }
;Main.c: 62: if(adc >153)
	movlw	high(09Ah)
	subwf	(_adc+1),w
	movlw	low(09Ah)
	skipnz
	subwf	(_adc),w
	skipc
	goto	u4001
	goto	u4000
u4001:
	goto	l3485
u4000:
	line	66
	
l3479:	
;Main.c: 63: {
;Main.c: 66: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	67
	
l3481:	
;Main.c: 67: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	68
	
l3483:	
;Main.c: 68: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	l3485
	line	72
	
l571:	
	line	73
	
l3485:	
;Main.c: 72: }
;Main.c: 73: OUTPUT();
	fcall	_OUTPUT
	goto	l3455
	line	74
	
l572:	
	line	36
	goto	l3455
	
l573:	
	goto	l3487
	line	75
	
l563:	
	line	34
	
l3487:	
	movlw	01h
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	xorwf	(_Z),w
	iorwf	(_Z+1),w
	skipnz
	goto	u4011
	goto	u4010
u4011:
	goto	l3455
u4010:
	goto	l3533
	
l574:	
	line	79
;Main.c: 74: }
;Main.c: 75: }
;Main.c: 79: while(Z ==2)
	goto	l3533
	
l576:	
	line	81
;Main.c: 80: {
;Main.c: 81: while(RB2 ==0)
	goto	l3509
	
l578:	
	line	83
	
l3489:	
;Main.c: 82: {
;Main.c: 83: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	84
;Main.c: 84: if(c ==12500)
	movlw	high(030D4h)
	xorwf	(_c+1),w
	skipz
	goto	u4025
	movlw	low(030D4h)
	xorwf	(_c),w
u4025:

	skipz
	goto	u4021
	goto	u4020
u4021:
	goto	l3497
u4020:
	line	86
	
l3491:	
;Main.c: 85: {
;Main.c: 86: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	87
;Main.c: 87: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	88
	
l3493:	
;Main.c: 88: RB1 =1;
	bsf	(49/8),(49)&7
	line	89
	
l3495:	
;Main.c: 89: RA1 =0;
	bcf	(41/8),(41)&7
	goto	l3497
	line	90
	
l579:	
	line	91
	
l3497:	
;Main.c: 90: }
;Main.c: 91: ADC_READ();
	fcall	_ADC_READ
	line	92
	
l3499:	
;Main.c: 92: if(adc >194)
	movlw	high(0C3h)
	subwf	(_adc+1),w
	movlw	low(0C3h)
	skipnz
	subwf	(_adc),w
	skipc
	goto	u4031
	goto	u4030
u4031:
	goto	l3507
u4030:
	line	94
	
l3501:	
;Main.c: 93: {
;Main.c: 94: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	95
	
l3503:	
;Main.c: 95: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	96
	
l3505:	
;Main.c: 96: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	l3507
	line	97
	
l580:	
	line	98
	
l3507:	
;Main.c: 97: }
;Main.c: 98: OUTPUT();
	fcall	_OUTPUT
	goto	l3509
	line	99
	
l577:	
	line	81
	
l3509:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(50/8),(50)&7
	goto	u4041
	goto	u4040
u4041:
	goto	l3489
u4040:
	goto	l3531
	
l581:	
	line	101
;Main.c: 99: }
;Main.c: 101: while(RB2 ==1)
	goto	l3531
	
l583:	
	line	103
	
l3511:	
;Main.c: 102: {
;Main.c: 103: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	104
;Main.c: 104: if(c >=12500)
	movlw	high(030D4h)
	subwf	(_c+1),w
	movlw	low(030D4h)
	skipnz
	subwf	(_c),w
	skipc
	goto	u4051
	goto	u4050
u4051:
	goto	l3519
u4050:
	line	106
	
l3513:	
;Main.c: 105: {
;Main.c: 106: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	107
;Main.c: 107: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	108
	
l3515:	
;Main.c: 108: RB1 =1;
	bsf	(49/8),(49)&7
	line	109
	
l3517:	
;Main.c: 109: RA1 =0;
	bcf	(41/8),(41)&7
	goto	l3519
	line	110
	
l584:	
	line	111
	
l3519:	
;Main.c: 110: }
;Main.c: 111: ADC_READ();
	fcall	_ADC_READ
	line	112
	
l3521:	
;Main.c: 112: if(adc <145)
	movlw	high(091h)
	subwf	(_adc+1),w
	movlw	low(091h)
	skipnz
	subwf	(_adc),w
	skipnc
	goto	u4061
	goto	u4060
u4061:
	goto	l3529
u4060:
	line	114
	
l3523:	
;Main.c: 113: {
;Main.c: 114: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	115
	
l3525:	
;Main.c: 115: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	116
	
l3527:	
;Main.c: 116: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	l3529
	line	117
	
l585:	
	line	118
	
l3529:	
;Main.c: 117: }
;Main.c: 118: OUTPUT();
	fcall	_OUTPUT
	goto	l3531
	line	119
	
l582:	
	line	101
	
l3531:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfsc	(50/8),(50)&7
	goto	u4071
	goto	u4070
u4071:
	goto	l3511
u4070:
	goto	l3533
	
l586:	
	goto	l3533
	line	120
	
l575:	
	line	79
	
l3533:	
	movlw	02h
	xorwf	(_Z),w
	iorwf	(_Z+1),w
	skipnz
	goto	u4081
	goto	u4080
u4081:
	goto	l3509
u4080:
	goto	l3579
	
l587:	
	line	124
;Main.c: 119: }
;Main.c: 120: }
;Main.c: 124: while(Z ==3)
	goto	l3579
	
l589:	
	line	126
;Main.c: 125: {
;Main.c: 126: while(RB2 ==0)
	goto	l3555
	
l591:	
	line	128
	
l3535:	
;Main.c: 127: {
;Main.c: 128: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	129
;Main.c: 129: if(c >=12500)
	movlw	high(030D4h)
	subwf	(_c+1),w
	movlw	low(030D4h)
	skipnz
	subwf	(_c),w
	skipc
	goto	u4091
	goto	u4090
u4091:
	goto	l3543
u4090:
	line	131
	
l3537:	
;Main.c: 130: {
;Main.c: 131: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	132
;Main.c: 132: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	133
	
l3539:	
;Main.c: 133: RB1 =1;
	bsf	(49/8),(49)&7
	line	134
	
l3541:	
;Main.c: 134: RA1 =0;
	bcf	(41/8),(41)&7
	goto	l3543
	line	135
	
l592:	
	line	136
	
l3543:	
;Main.c: 135: }
;Main.c: 136: ADC_READ();
	fcall	_ADC_READ
	line	137
	
l3545:	
;Main.c: 137: if(adc >209)
	movlw	high(0D2h)
	subwf	(_adc+1),w
	movlw	low(0D2h)
	skipnz
	subwf	(_adc),w
	skipc
	goto	u4101
	goto	u4100
u4101:
	goto	l3553
u4100:
	line	139
	
l3547:	
;Main.c: 138: {
;Main.c: 139: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	140
	
l3549:	
;Main.c: 140: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	141
	
l3551:	
;Main.c: 141: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	l3553
	line	142
	
l593:	
	line	143
	
l3553:	
;Main.c: 142: }
;Main.c: 143: OUTPUT();
	fcall	_OUTPUT
	goto	l3555
	line	144
	
l590:	
	line	126
	
l3555:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(50/8),(50)&7
	goto	u4111
	goto	u4110
u4111:
	goto	l3535
u4110:
	goto	l3577
	
l594:	
	line	145
;Main.c: 144: }
;Main.c: 145: while(RB2 ==1)
	goto	l3577
	
l596:	
	line	147
	
l3557:	
;Main.c: 146: {
;Main.c: 147: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	148
;Main.c: 148: if(c >=12500)
	movlw	high(030D4h)
	subwf	(_c+1),w
	movlw	low(030D4h)
	skipnz
	subwf	(_c),w
	skipc
	goto	u4121
	goto	u4120
u4121:
	goto	l3565
u4120:
	line	150
	
l3559:	
;Main.c: 149: {
;Main.c: 150: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	151
;Main.c: 151: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	152
	
l3561:	
;Main.c: 152: RB1 =1;
	bsf	(49/8),(49)&7
	line	153
	
l3563:	
;Main.c: 153: RA1 =0;
	bcf	(41/8),(41)&7
	goto	l3565
	line	154
	
l597:	
	line	155
	
l3565:	
;Main.c: 154: }
;Main.c: 155: ADC_READ();
	fcall	_ADC_READ
	line	156
	
l3567:	
;Main.c: 156: if(adc <160)
	movlw	high(0A0h)
	subwf	(_adc+1),w
	movlw	low(0A0h)
	skipnz
	subwf	(_adc),w
	skipnc
	goto	u4131
	goto	u4130
u4131:
	goto	l3575
u4130:
	line	158
	
l3569:	
;Main.c: 157: {
;Main.c: 158: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	159
	
l3571:	
;Main.c: 159: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	160
	
l3573:	
;Main.c: 160: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	l3575
	line	161
	
l598:	
	line	162
	
l3575:	
;Main.c: 161: }
;Main.c: 162: OUTPUT();
	fcall	_OUTPUT
	goto	l3577
	line	163
	
l595:	
	line	145
	
l3577:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfsc	(50/8),(50)&7
	goto	u4141
	goto	u4140
u4141:
	goto	l3557
u4140:
	goto	l3579
	
l599:	
	goto	l3579
	line	164
	
l588:	
	line	124
	
l3579:	
	movlw	03h
	xorwf	(_Z),w
	iorwf	(_Z+1),w
	skipnz
	goto	u4151
	goto	u4150
u4151:
	goto	l3555
u4150:
	goto	l3643
	
l600:	
	line	168
;Main.c: 163: }
;Main.c: 164: }
;Main.c: 168: while(Z ==4)
	goto	l3643
	
l602:	
	line	170
;Main.c: 169: {
;Main.c: 170: RBIE =0;
	bcf	(91/8),(91)&7
	line	171
;Main.c: 171: RB3 =1;
	bsf	(51/8),(51)&7
	line	172
	
l3581:	
;Main.c: 172: c =0;
	clrf	(_c)
	clrf	(_c+1)
	line	173
;Main.c: 173: laseroff =0;
	clrf	(_laseroff)
	clrf	(_laseroff+1)
	line	174
;Main.c: 174: while(RB2 ==0)
	goto	l3611
	
l604:	
	line	176
	
l3583:	
;Main.c: 175: {
;Main.c: 176: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	177
;Main.c: 177: if(c >=2)
	movlw	high(02h)
	subwf	(_c+1),w
	movlw	low(02h)
	skipnz
	subwf	(_c),w
	skipc
	goto	u4161
	goto	u4160
u4161:
	goto	l3591
u4160:
	line	179
	
l3585:	
;Main.c: 178: {
;Main.c: 179: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	180
;Main.c: 180: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	181
	
l3587:	
;Main.c: 181: RA1 =0;
	bcf	(41/8),(41)&7
	line	182
	
l3589:	
;Main.c: 182: RB1 =1;
	bsf	(49/8),(49)&7
	goto	l3591
	line	183
	
l605:	
	line	184
	
l3591:	
;Main.c: 183: }
;Main.c: 184: ADC_READ();
	fcall	_ADC_READ
	line	185
	
l3593:	
;Main.c: 185: if(adc <203)
	movlw	high(0CBh)
	subwf	(_adc+1),w
	movlw	low(0CBh)
	skipnz
	subwf	(_adc),w
	skipnc
	goto	u4171
	goto	u4170
u4171:
	goto	l3607
u4170:
	line	187
	
l3595:	
;Main.c: 186: {
;Main.c: 187: if(laseroff ==0)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	((_laseroff+1)),w
	iorwf	((_laseroff)),w
	skipz
	goto	u4181
	goto	u4180
u4181:
	goto	l3605
u4180:
	line	189
	
l3597:	
;Main.c: 188: {
;Main.c: 189: RA1 =1;
	bsf	(41/8),(41)&7
	line	190
	
l3599:	
;Main.c: 190: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	191
	
l3601:	
;Main.c: 191: RB3 =0;
	bcf	(51/8),(51)&7
	line	192
	
l3603:	
;Main.c: 192: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	l3605
	line	193
	
l607:	
	line	194
	
l3605:	
;Main.c: 193: }
;Main.c: 194: c =0;
	clrf	(_c)
	clrf	(_c+1)
	line	195
;Main.c: 195: }
	goto	l3609
	line	196
	
l606:	
	line	198
	
l3607:	
;Main.c: 196: else
;Main.c: 197: {
;Main.c: 198: laseroff =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_laseroff)
	clrf	(_laseroff+1)
	goto	l3609
	line	199
	
l608:	
	line	200
	
l3609:	
;Main.c: 199: }
;Main.c: 200: OUTPUT();
	fcall	_OUTPUT
	goto	l3611
	line	202
	
l603:	
	line	174
	
l3611:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(50/8),(50)&7
	goto	u4191
	goto	u4190
u4191:
	goto	l3583
u4190:
	goto	l3613
	
l609:	
	line	203
	
l3613:	
;Main.c: 202: }
;Main.c: 203: laseroff =0;
	clrf	(_laseroff)
	clrf	(_laseroff+1)
	line	204
;Main.c: 204: while(RB2 ==1)
	goto	l3641
	
l611:	
	line	206
	
l3615:	
;Main.c: 205: {
;Main.c: 206: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	207
;Main.c: 207: if(c >=2)
	movlw	high(02h)
	subwf	(_c+1),w
	movlw	low(02h)
	skipnz
	subwf	(_c),w
	skipc
	goto	u4201
	goto	u4200
u4201:
	goto	l3623
u4200:
	line	209
	
l3617:	
;Main.c: 208: {
;Main.c: 209: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	210
;Main.c: 210: T =0;
	clrf	(_T)
	clrf	(_T+1)
	line	211
	
l3619:	
;Main.c: 211: RB1 =1;
	bsf	(49/8),(49)&7
	line	212
	
l3621:	
;Main.c: 212: RA1 =0;
	bcf	(41/8),(41)&7
	goto	l3623
	line	213
	
l612:	
	line	214
	
l3623:	
;Main.c: 213: }
;Main.c: 214: ADC_READ();
	fcall	_ADC_READ
	line	215
	
l3625:	
;Main.c: 215: if(adc>203)
	movlw	high(0CCh)
	subwf	(_adc+1),w
	movlw	low(0CCh)
	skipnz
	subwf	(_adc),w
	skipc
	goto	u4211
	goto	u4210
u4211:
	goto	l3637
u4210:
	line	217
	
l3627:	
;Main.c: 216: {
;Main.c: 217: if(laseroff ==0)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	((_laseroff+1)),w
	iorwf	((_laseroff)),w
	skipz
	goto	u4221
	goto	u4220
u4221:
	goto	l3635
u4220:
	line	219
	
l3629:	
;Main.c: 218: {
;Main.c: 219: RA1 =1;
	bsf	(41/8),(41)&7
	line	220
	
l3631:	
;Main.c: 220: T =2;
	movlw	low(02h)
	movwf	(_T)
	movlw	high(02h)
	movwf	((_T))+1
	line	221
	
l3633:	
;Main.c: 221: RB3 =0;
	bcf	(51/8),(51)&7
	goto	l3635
	line	222
	
l614:	
	line	223
	
l3635:	
;Main.c: 222: }
;Main.c: 223: c =0;
	clrf	(_c)
	clrf	(_c+1)
	line	224
;Main.c: 224: }
	goto	l3639
	line	225
	
l613:	
	line	227
	
l3637:	
;Main.c: 225: else
;Main.c: 226: {
;Main.c: 227: laseroff =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_laseroff)
	clrf	(_laseroff+1)
	goto	l3639
	line	228
	
l615:	
	line	229
	
l3639:	
;Main.c: 228: }
;Main.c: 229: OUTPUT();
	fcall	_OUTPUT
	goto	l3641
	line	230
	
l610:	
	line	204
	
l3641:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfsc	(50/8),(50)&7
	goto	u4231
	goto	u4230
u4231:
	goto	l3615
u4230:
	goto	l3643
	
l616:	
	goto	l3643
	line	231
	
l601:	
	line	168
	
l3643:	
	movlw	04h
	xorwf	(_Z),w
	iorwf	(_Z+1),w
	skipnz
	goto	u4241
	goto	u4240
u4241:
	goto	l602
u4240:
	goto	l3487
	
l617:	
	goto	l3487
	line	232
	
l618:	
	line	29
	goto	l3487
	
l619:	
	line	233
	
l620:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_OUTPUT
psect	text416,local,class=CODE,delta=2
global __ptext416
__ptext416:

;; *************** function _OUTPUT *****************
;; Defined at:
;;		line 208 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       3       0       0
;;      Totals:         0       3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text416
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	208
	global	__size_of_OUTPUT
	__size_of_OUTPUT	equ	__end_of_OUTPUT-_OUTPUT
	
_OUTPUT:	
	opt	stack 6
; Regs used in _OUTPUT: [wreg+status,2+status,0]
	line	209
	
l3379:	
;main.h: 209: if(OR ==1)
	movlw	01h
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	xorwf	(_OR),w
	iorwf	(_OR+1),w
	skipz
	goto	u3801
	goto	u3800
u3801:
	goto	l3391
u3800:
	line	211
	
l3381:	
;main.h: 210: {
;main.h: 211: if(T ==2)
	movlw	02h
	xorwf	(_T),w
	iorwf	(_T+1),w
	skipz
	goto	u3811
	goto	u3810
u3811:
	goto	l3385
u3810:
	line	213
	
l3383:	
;main.h: 212: {
;main.h: 213: RB1 =0;
	bcf	(49/8),(49)&7
	line	214
;main.h: 214: RA1 =1;
	bsf	(41/8),(41)&7
	goto	l3385
	line	215
	
l546:	
	line	216
	
l3385:	
;main.h: 215: }
;main.h: 216: if((IN ==1) && (END !=1))
	movlw	01h
	xorwf	(_IN),w
	iorwf	(_IN+1),w
	skipz
	goto	u3821
	goto	u3820
u3821:
	goto	l3391
u3820:
	
l3387:	
	movlw	01h
	xorwf	(_END),w
	iorwf	(_END+1),w
	skipnz
	goto	u3831
	goto	u3830
u3831:
	goto	l3391
u3830:
	line	218
	
l3389:	
;main.h: 217: {
;main.h: 218: RB1 =0;
	bcf	(49/8),(49)&7
	line	219
;main.h: 219: RA1 =1;
	bsf	(41/8),(41)&7
	goto	l3391
	line	220
	
l547:	
	goto	l3391
	line	221
	
l545:	
	line	222
	
l3391:	
;main.h: 220: }
;main.h: 221: }
;main.h: 222: if(AND ==1)
	movlw	01h
	xorwf	(_AND),w
	iorwf	(_AND+1),w
	skipz
	goto	u3841
	goto	u3840
u3841:
	goto	l3413
u3840:
	line	224
	
l3393:	
;main.h: 223: {
;main.h: 224: if((T ==2) && ((IN ==1)|| ( RB0 ==0)) && (END !=1))
	movlw	02h
	xorwf	(_T),w
	iorwf	(_T+1),w
	skipz
	goto	u3851
	goto	u3850
u3851:
	goto	l3403
u3850:
	
l3395:	
	movlw	01h
	xorwf	(_IN),w
	iorwf	(_IN+1),w
	skipnz
	goto	u3861
	goto	u3860
u3861:
	goto	l3399
u3860:
	
l3397:	
	btfsc	(48/8),(48)&7
	goto	u3871
	goto	u3870
u3871:
	goto	l3403
u3870:
	goto	l3399
	
l551:	
	
l3399:	
	movlw	01h
	xorwf	(_END),w
	iorwf	(_END+1),w
	skipnz
	goto	u3881
	goto	u3880
u3881:
	goto	l3403
u3880:
	line	226
	
l3401:	
;main.h: 225: {
;main.h: 226: TRISB1 =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1073/8)^080h,(1073)&7
	line	227
;main.h: 227: RB1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(49/8),(49)&7
	line	228
;main.h: 228: RA1 =1;
	bsf	(41/8),(41)&7
	goto	l3403
	line	229
	
l549:	
	line	230
	
l3403:	
;main.h: 229: }
;main.h: 230: if((END ==1) && (T ==2))
	movlw	01h
	xorwf	(_END),w
	iorwf	(_END+1),w
	skipz
	goto	u3891
	goto	u3890
u3891:
	goto	l552
u3890:
	
l3405:	
	movlw	02h
	xorwf	(_T),w
	iorwf	(_T+1),w
	skipz
	goto	u3901
	goto	u3900
u3901:
	goto	l552
u3900:
	line	232
	
l3407:	
;main.h: 231: {
;main.h: 232: TRISB1 =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1073/8)^080h,(1073)&7
	line	233
;main.h: 233: RB1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(49/8),(49)&7
	line	234
;main.h: 234: RA1 =1;
	bsf	(41/8),(41)&7
	line	235
	
l552:	
	line	236
;main.h: 235: }
;main.h: 236: if(RB0 ==1)
	btfss	(48/8),(48)&7
	goto	u3911
	goto	u3910
u3911:
	goto	l3413
u3910:
	line	238
	
l3409:	
;main.h: 237: {
;main.h: 238: IN =0;
	clrf	(_IN)
	clrf	(_IN+1)
	line	239
	
l3411:	
;main.h: 239: RB1 =1;
	bsf	(49/8),(49)&7
	goto	l3413
	line	240
	
l553:	
	goto	l3413
	line	241
	
l548:	
	line	242
	
l3413:	
;main.h: 240: }
;main.h: 241: }
;main.h: 242: if(Z ==4)
	movlw	04h
	xorwf	(_Z),w
	iorwf	(_Z+1),w
	skipz
	goto	u3921
	goto	u3920
u3921:
	goto	l558
u3920:
	line	244
	
l3415:	
;main.h: 243: {
;main.h: 244: if(T ==2)
	movlw	02h
	xorwf	(_T),w
	iorwf	(_T+1),w
	skipz
	goto	u3931
	goto	u3930
u3931:
	goto	l558
u3930:
	line	246
	
l3417:	
;main.h: 245: {
;main.h: 246: if(laseroff ==0)
	movf	((_laseroff+1)),w
	iorwf	((_laseroff)),w
	skipz
	goto	u3941
	goto	u3940
u3941:
	goto	l558
u3940:
	line	248
	
l3419:	
;main.h: 247: {
;main.h: 248: if(RB3 ==0)
	btfsc	(51/8),(51)&7
	goto	u3951
	goto	u3950
u3951:
	goto	l558
u3950:
	line	250
	
l3421:	
;main.h: 249: {
;main.h: 250: _delay((unsigned long)((200)*(8000000/4000.0)));
	opt asmopt_off
movlw  3
movwf	((??_OUTPUT+0)+0+2),f
movlw	8
movwf	((??_OUTPUT+0)+0+1),f
	movlw	120
movwf	((??_OUTPUT+0)+0),f
u4257:
	decfsz	((??_OUTPUT+0)+0),f
	goto	u4257
	decfsz	((??_OUTPUT+0)+0+1),f
	goto	u4257
	decfsz	((??_OUTPUT+0)+0+2),f
	goto	u4257
opt asmopt_on

	line	251
	
l3423:	
;main.h: 251: RB3 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(51/8),(51)&7
	line	252
;main.h: 252: laseroff =1;
	movlw	low(01h)
	movwf	(_laseroff)
	movlw	high(01h)
	movwf	((_laseroff))+1
	goto	l558
	line	253
	
l557:	
	goto	l558
	line	254
	
l556:	
	goto	l558
	line	255
	
l555:	
	goto	l558
	line	256
	
l554:	
	line	257
	
l558:	
	return
	opt stack 0
GLOBAL	__end_of_OUTPUT
	__end_of_OUTPUT:
;; =============== function _OUTPUT ends ============

	signat	_OUTPUT,88
	global	_PING
psect	text417,local,class=CODE,delta=2
global __ptext417
__ptext417:

;; *************** function _PING *****************
;; Defined at:
;;		line 99 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  a               2    4[COMMON] unsigned int 
;; Return value:  Size  Location     Type
;;                  2  521[COMMON] int 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         2       0       0       0
;;      Temps:          0       3       0       0
;;      Totals:         2       3       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_delay2
;;		_delay1
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text417
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	99
	global	__size_of_PING
	__size_of_PING	equ	__end_of_PING-_PING
	
_PING:	
	opt	stack 5
; Regs used in _PING: [wreg+status,2+status,0+pclath+cstack]
	line	100
	
l3269:	
;main.h: 100: unsigned int a = 0;
	clrf	(PING@a)
	clrf	(PING@a+1)
	line	101
;main.h: 101: Y =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_Y)
	clrf	(_Y+1)
	line	102
;main.h: 102: c =0;
	clrf	(_c)
	clrf	(_c+1)
	line	103
	
l3271:	
;main.h: 103: RA1 =0;
	bcf	(41/8),(41)&7
	line	104
	
l3273:	
;main.h: 104: TRISB1 =1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1073/8)^080h,(1073)&7
	line	105
;main.h: 105: while(Y ==0)
	goto	l3277
	
l523:	
	line	107
;main.h: 106: {
;main.h: 107: if(RB1 ==0)
	btfsc	(49/8),(49)&7
	goto	u3681
	goto	u3680
u3681:
	goto	l3277
u3680:
	line	109
	
l3275:	
;main.h: 108: {
;main.h: 109: Y =1;
	movlw	low(01h)
	movwf	(_Y)
	movlw	high(01h)
	movwf	((_Y))+1
	line	110
;main.h: 110: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	111
;main.h: 111: while(RB1 ==0);
	goto	l525
	
l526:	
	
l525:	
	btfss	(49/8),(49)&7
	goto	u3691
	goto	u3690
u3691:
	goto	l525
u3690:
	goto	l3277
	
l527:	
	goto	l3277
	line	112
	
l524:	
	goto	l3277
	line	113
	
l522:	
	line	105
	
l3277:	
	bcf	status, 5	;RP0=0, select bank0
	movf	(_Y+1),w
	iorwf	(_Y),w
	skipnz
	goto	u3701
	goto	u3700
u3701:
	goto	l523
u3700:
	goto	l529
	
l528:	
	line	115
;main.h: 112: }
;main.h: 113: }
;main.h: 115: while(a <5120)
	goto	l529
	
l530:	
	line	117
;main.h: 116: {
;main.h: 117: if(RB1 ==0)
	btfsc	(49/8),(49)&7
	goto	u3711
	goto	u3710
u3711:
	goto	l531
u3710:
	line	119
	
l3279:	
;main.h: 118: {
;main.h: 119: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	120
;main.h: 120: a =5500;
	movlw	low(0157Ch)
	movwf	(PING@a)
	movlw	high(0157Ch)
	movwf	((PING@a))+1
	line	121
	
l531:	
	line	122
;main.h: 121: }
;main.h: 122: a++;
	movlw	low(01h)
	addwf	(PING@a),f
	skipnc
	incf	(PING@a+1),f
	movlw	high(01h)
	addwf	(PING@a+1),f
	line	123
	
l529:	
	line	115
	movlw	high(01400h)
	subwf	(PING@a+1),w
	movlw	low(01400h)
	skipnz
	subwf	(PING@a),w
	skipc
	goto	u3721
	goto	u3720
u3721:
	goto	l530
u3720:
	goto	l3281
	
l532:	
	line	124
	
l3281:	
;main.h: 123: }
;main.h: 124: if(c ==1)
	movlw	01h
	xorwf	(_c),w
	iorwf	(_c+1),w
	skipz
	goto	u3731
	goto	u3730
u3731:
	goto	l3287
u3730:
	line	126
	
l3283:	
;main.h: 125: {
;main.h: 126: AND =0;
	clrf	(_AND)
	clrf	(_AND+1)
	line	127
	
l3285:	
;main.h: 127: OR =1;
	movlw	low(01h)
	movwf	(_OR)
	movlw	high(01h)
	movwf	((_OR))+1
	goto	l3287
	line	128
	
l533:	
	line	129
	
l3287:	
;main.h: 128: }
;main.h: 129: if(c ==2)
	movlw	02h
	xorwf	(_c),w
	iorwf	(_c+1),w
	skipz
	goto	u3741
	goto	u3740
u3741:
	goto	l3293
u3740:
	line	131
	
l3289:	
;main.h: 130: {
;main.h: 131: AND =1;
	movlw	low(01h)
	movwf	(_AND)
	movlw	high(01h)
	movwf	((_AND))+1
	line	132
	
l3291:	
;main.h: 132: OR =0;
	clrf	(_OR)
	clrf	(_OR+1)
	goto	l3293
	line	133
	
l534:	
	line	134
	
l3293:	
;main.h: 133: }
;main.h: 134: if(AND ==1)
	movlw	01h
	xorwf	(_AND),w
	iorwf	(_AND+1),w
	skipz
	goto	u3751
	goto	u3750
u3751:
	goto	l3319
u3750:
	line	137
	
l3295:	
;main.h: 135: {
;main.h: 137: TRISB0 =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1072/8)^080h,(1072)&7
	line	138
;main.h: 138: RB0 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(48/8),(48)&7
	line	139
	
l3297:	
;main.h: 139: delay2();
	fcall	_delay2
	line	140
	
l3299:	
;main.h: 140: RB0 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(48/8),(48)&7
	line	141
;main.h: 141: delay2();
	fcall	_delay2
	line	142
	
l3301:	
;main.h: 142: RB0 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(48/8),(48)&7
	line	143
;main.h: 143: delay2();
	fcall	_delay2
	line	144
	
l3303:	
;main.h: 144: RB0 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(48/8),(48)&7
	line	145
	
l3305:	
;main.h: 145: TRISB0 =1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1072/8)^080h,(1072)&7
	line	146
	
l3307:	
;main.h: 146: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	147
;main.h: 147: delay1();
	fcall	_delay1
	line	148
	
l3309:	
;main.h: 148: RA1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	line	149
;main.h: 149: delay1();
	fcall	_delay1
	line	150
	
l3311:	
;main.h: 150: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	151
;main.h: 151: delay1();
	fcall	_delay1
	line	152
	
l3313:	
;main.h: 152: RA1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	line	153
;main.h: 153: delay1();
	fcall	_delay1
	line	154
	
l3315:	
;main.h: 154: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	155
;main.h: 155: delay1();
	fcall	_delay1
	line	156
	
l3317:	
;main.h: 156: RA1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	goto	l3319
	line	158
	
l535:	
	line	159
	
l3319:	
;main.h: 158: }
;main.h: 159: if(OR ==1)
	movlw	01h
	xorwf	(_OR),w
	iorwf	(_OR+1),w
	skipz
	goto	u3761
	goto	u3760
u3761:
	goto	l3335
u3760:
	line	161
	
l3321:	
;main.h: 160: {
;main.h: 161: delay1();
	fcall	_delay1
	line	162
	
l3323:	
;main.h: 162: TRISB0 =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1072/8)^080h,(1072)&7
	line	163
	
l3325:	
;main.h: 163: RB0 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(48/8),(48)&7
	line	164
;main.h: 164: delay2();
	fcall	_delay2
	line	165
	
l3327:	
;main.h: 165: RB0 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(48/8),(48)&7
	line	166
	
l3329:	
;main.h: 166: TRISB0 =1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1072/8)^080h,(1072)&7
	line	167
	
l3331:	
;main.h: 167: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	168
;main.h: 168: delay1();
	fcall	_delay1
	line	169
;main.h: 169: delay1();
	fcall	_delay1
	line	170
	
l3333:	
;main.h: 170: RA1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	goto	l3335
	line	171
	
l536:	
	line	172
	
l3335:	
;main.h: 171: }
;main.h: 172: TRISB1 =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1073/8)^080h,(1073)&7
	line	173
	
l3337:	
;main.h: 173: RB1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(49/8),(49)&7
	line	174
	
l3339:	
;main.h: 174: a =0;
	clrf	(PING@a)
	clrf	(PING@a+1)
	line	175
	
l3341:	
;main.h: 175: delay1();
	fcall	_delay1
	line	176
	
l3343:	
;main.h: 176: delay1();
	fcall	_delay1
	line	177
	
l3345:	
;main.h: 177: TRISB0 =1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1072/8)^080h,(1072)&7
	line	178
	
l3347:	
;main.h: 178: END =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_END)
	clrf	(_END+1)
	line	179
;main.h: 179: while(a<15000)
	goto	l537
	
l538:	
	line	181
;main.h: 180: {
;main.h: 181: if(RB0 ==0)
	btfsc	(48/8),(48)&7
	goto	u3771
	goto	u3770
u3771:
	goto	l539
u3770:
	line	183
	
l3349:	
;main.h: 182: {
;main.h: 183: c++;
	movlw	low(01h)
	addwf	(_c),f
	skipnc
	incf	(_c+1),f
	movlw	high(01h)
	addwf	(_c+1),f
	line	184
;main.h: 184: a =20000;
	movlw	low(04E20h)
	movwf	(PING@a)
	movlw	high(04E20h)
	movwf	((PING@a))+1
	line	185
	
l539:	
	line	186
;main.h: 185: }
;main.h: 186: a++;
	movlw	low(01h)
	addwf	(PING@a),f
	skipnc
	incf	(PING@a+1),f
	movlw	high(01h)
	addwf	(PING@a+1),f
	line	187
	
l537:	
	line	179
	movlw	high(03A98h)
	subwf	(PING@a+1),w
	movlw	low(03A98h)
	skipnz
	subwf	(PING@a),w
	skipc
	goto	u3781
	goto	u3780
u3781:
	goto	l538
u3780:
	goto	l3351
	
l540:	
	line	188
	
l3351:	
;main.h: 187: }
;main.h: 188: if(a <16000)
	movlw	high(03E80h)
	subwf	(PING@a+1),w
	movlw	low(03E80h)
	skipnz
	subwf	(PING@a),w
	skipnc
	goto	u3791
	goto	u3790
u3791:
	goto	l542
u3790:
	line	190
	
l3353:	
;main.h: 189: {
;main.h: 190: _delay((unsigned long)((250)*(8000000/4000.0)));
	opt asmopt_off
movlw  3
movwf	((??_PING+0)+0+2),f
movlw	138
movwf	((??_PING+0)+0+1),f
	movlw	86
movwf	((??_PING+0)+0),f
u4267:
	decfsz	((??_PING+0)+0),f
	goto	u4267
	decfsz	((??_PING+0)+0+1),f
	goto	u4267
	decfsz	((??_PING+0)+0+2),f
	goto	u4267
	nop2
opt asmopt_on

	line	191
	
l3355:	
;main.h: 191: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	192
	
l3357:	
;main.h: 192: delay1();
	fcall	_delay1
	line	193
	
l3359:	
;main.h: 193: RA1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	line	194
	
l3361:	
;main.h: 194: delay1();
	fcall	_delay1
	line	195
	
l3363:	
;main.h: 195: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	196
	
l3365:	
;main.h: 196: delay1();
	fcall	_delay1
	line	197
	
l3367:	
;main.h: 197: RA1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	line	198
	
l3369:	
;main.h: 198: delay1();
	fcall	_delay1
	line	199
	
l3371:	
;main.h: 199: RA1 =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	200
	
l3373:	
;main.h: 200: delay1();
	fcall	_delay1
	line	201
	
l3375:	
;main.h: 201: RA1 =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	line	202
	
l3377:	
;main.h: 202: END =1;
	movlw	low(01h)
	movwf	(_END)
	movlw	high(01h)
	movwf	((_END))+1
	goto	l542
	line	204
	
l541:	
	line	205
	
l542:	
	return
	opt stack 0
GLOBAL	__end_of_PING
	__end_of_PING:
;; =============== function _PING ends ============

	signat	_PING,90
	global	_ADC_READ
psect	text418,local,class=CODE,delta=2
global __ptext418
__ptext418:

;; *************** function _ADC_READ *****************
;; Defined at:
;;		line 86 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          2       0       0       0
;;      Totals:         2       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text418
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	86
	global	__size_of_ADC_READ
	__size_of_ADC_READ	equ	__end_of_ADC_READ-_ADC_READ
	
_ADC_READ:	
	opt	stack 6
; Regs used in _ADC_READ: [wreg+status,2]
	line	87
	
l2881:	
;main.h: 87: ADCON1 =0b00000000;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	clrf	(159)^080h	;volatile
	line	88
	
l2883:	
;main.h: 88: ADCON0 =0b00000001;
	movlw	(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(31)	;volatile
	line	89
	
l2885:	
;main.h: 89: ADON =1;
	bsf	(248/8),(248)&7
	line	90
	
l2887:	
;main.h: 90: _delay((unsigned long)((5)*(8000000/4000000.0)));
	opt asmopt_off
movlw	3
movwf	(??_ADC_READ+0)+0,f
u4277:
decfsz	(??_ADC_READ+0)+0,f
	goto	u4277
opt asmopt_on

	line	91
	
l2889:	
;main.h: 91: GO_DONE =1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(250/8),(250)&7
	line	92
;main.h: 92: while(GO_DONE);
	goto	l516
	
l517:	
	
l516:	
	btfsc	(250/8),(250)&7
	goto	u3101
	goto	u3100
u3101:
	goto	l516
u3100:
	
l518:	
	line	93
;main.h: 93: ADON =0;
	bcf	(248/8),(248)&7
	line	94
	
l2891:	
;main.h: 94: _delay((unsigned long)((5)*(8000000/4000000.0)));
	opt asmopt_off
movlw	3
movwf	(??_ADC_READ+0)+0,f
u4287:
decfsz	(??_ADC_READ+0)+0,f
	goto	u4287
opt asmopt_on

	line	95
;main.h: 95: adc =ADRESH;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(30),w	;volatile
	movwf	(??_ADC_READ+0)+0
	clrf	(??_ADC_READ+0)+0+1
	movf	0+(??_ADC_READ+0)+0,w
	movwf	(_adc)
	movf	1+(??_ADC_READ+0)+0,w
	movwf	(_adc+1)
	line	96
	
l519:	
	return
	opt stack 0
GLOBAL	__end_of_ADC_READ
	__end_of_ADC_READ:
;; =============== function _ADC_READ ends ============

	signat	_ADC_READ,88
	global	_OPTION_SELECT
psect	text419,local,class=CODE,delta=2
global __ptext419
__ptext419:

;; *************** function _OPTION_SELECT *****************
;; Defined at:
;;		line 54 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_delay
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text419
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	54
	global	__size_of_OPTION_SELECT
	__size_of_OPTION_SELECT	equ	__end_of_OPTION_SELECT-_OPTION_SELECT
	
_OPTION_SELECT:	
	opt	stack 5
; Regs used in _OPTION_SELECT: [wreg+status,2+status,0+pclath+cstack]
	line	55
	
l2865:	
;main.h: 55: delay();
	fcall	_delay
	line	56
	
l2867:	
;main.h: 56: if(RA6 ==0)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfsc	(46/8),(46)&7
	goto	u3061
	goto	u3060
u3061:
	goto	l501
u3060:
	line	58
	
l2869:	
;main.h: 57: {
;main.h: 58: if(RA7 ==0)
	btfsc	(47/8),(47)&7
	goto	u3071
	goto	u3070
u3071:
	goto	l2873
u3070:
	line	60
	
l2871:	
;main.h: 59: {
;main.h: 60: Z =1;
	movlw	low(01h)
	movwf	(_Z)
	movlw	high(01h)
	movwf	((_Z))+1
	line	61
;main.h: 61: }
	goto	l508
	line	62
	
l502:	
	line	64
	
l2873:	
;main.h: 62: else
;main.h: 63: {
;main.h: 64: Z =2;
	movlw	low(02h)
	movwf	(_Z)
	movlw	high(02h)
	movwf	((_Z))+1
	goto	l508
	line	65
	
l503:	
	line	66
;main.h: 65: }
;main.h: 66: }
	goto	l508
	line	67
	
l501:	
;main.h: 67: else if(RA6 ==1)
	btfss	(46/8),(46)&7
	goto	u3081
	goto	u3080
u3081:
	goto	l508
u3080:
	line	69
	
l2875:	
;main.h: 68: {
;main.h: 69: if(RA7 ==0)
	btfsc	(47/8),(47)&7
	goto	u3091
	goto	u3090
u3091:
	goto	l2879
u3090:
	line	71
	
l2877:	
;main.h: 70: {
;main.h: 71: Z =3;
	movlw	low(03h)
	movwf	(_Z)
	movlw	high(03h)
	movwf	((_Z))+1
	line	72
;main.h: 72: }
	goto	l508
	line	73
	
l506:	
	line	75
	
l2879:	
;main.h: 73: else
;main.h: 74: {
;main.h: 75: Z =4;
	movlw	low(04h)
	movwf	(_Z)
	movlw	high(04h)
	movwf	((_Z))+1
	goto	l508
	line	76
	
l507:	
	goto	l508
	line	77
	
l505:	
	goto	l508
	line	78
	
l504:	
	
l508:	
	return
	opt stack 0
GLOBAL	__end_of_OPTION_SELECT
	__end_of_OPTION_SELECT:
;; =============== function _OPTION_SELECT ends ============

	signat	_OPTION_SELECT,88
	global	_delay1
psect	text420,local,class=CODE,delta=2
global __ptext420
__ptext420:

;; *************** function _delay1 *****************
;; Defined at:
;;		line 81 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_PING
;; This function uses a non-reentrant model
;;
psect	text420
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	81
	global	__size_of_delay1
	__size_of_delay1	equ	__end_of_delay1-_delay1
	
_delay1:	
	opt	stack 5
; Regs used in _delay1: [wreg]
	line	82
	
l2835:	
;main.h: 82: for(i=1;i<20000;i++);
	movlw	low(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(_i)
	movlw	high(01h)
	movwf	((_i))+1
	movlw	high(04E20h)
	subwf	(_i+1),w
	movlw	low(04E20h)
	skipnz
	subwf	(_i),w
	skipc
	goto	u2991
	goto	u2990
u2991:
	goto	l2839
u2990:
	goto	l513
	
l2837:	
	goto	l513
	
l511:	
	
l2839:	
	movlw	low(01h)
	addwf	(_i),f
	skipnc
	incf	(_i+1),f
	movlw	high(01h)
	addwf	(_i+1),f
	movlw	high(04E20h)
	subwf	(_i+1),w
	movlw	low(04E20h)
	skipnz
	subwf	(_i),w
	skipc
	goto	u3001
	goto	u3000
u3001:
	goto	l2839
u3000:
	goto	l513
	
l512:	
	line	83
	
l513:	
	return
	opt stack 0
GLOBAL	__end_of_delay1
	__end_of_delay1:
;; =============== function _delay1 ends ============

	signat	_delay1,88
	global	_delay2
psect	text421,local,class=CODE,delta=2
global __ptext421
__ptext421:

;; *************** function _delay2 *****************
;; Defined at:
;;		line 49 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_PING
;; This function uses a non-reentrant model
;;
psect	text421
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	49
	global	__size_of_delay2
	__size_of_delay2	equ	__end_of_delay2-_delay2
	
_delay2:	
	opt	stack 5
; Regs used in _delay2: [wreg+status,2]
	line	50
	
l2827:	
;main.h: 50: for(i=0;i<2500;i++);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(_i)
	clrf	(_i+1)
	
l2829:	
	movlw	high(09C4h)
	subwf	(_i+1),w
	movlw	low(09C4h)
	skipnz
	subwf	(_i),w
	skipc
	goto	u2971
	goto	u2970
u2971:
	goto	l2833
u2970:
	goto	l498
	
l2831:	
	goto	l498
	
l496:	
	
l2833:	
	movlw	low(01h)
	addwf	(_i),f
	skipnc
	incf	(_i+1),f
	movlw	high(01h)
	addwf	(_i+1),f
	movlw	high(09C4h)
	subwf	(_i+1),w
	movlw	low(09C4h)
	skipnz
	subwf	(_i),w
	skipc
	goto	u2981
	goto	u2980
u2981:
	goto	l2833
u2980:
	goto	l498
	
l497:	
	line	51
	
l498:	
	return
	opt stack 0
GLOBAL	__end_of_delay2
	__end_of_delay2:
;; =============== function _delay2 ends ============

	signat	_delay2,88
	global	_delay
psect	text422,local,class=CODE,delta=2
global __ptext422
__ptext422:

;; *************** function _delay *****************
;; Defined at:
;;		line 44 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_OPTION_SELECT
;; This function uses a non-reentrant model
;;
psect	text422
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	44
	global	__size_of_delay
	__size_of_delay	equ	__end_of_delay-_delay
	
_delay:	
	opt	stack 5
; Regs used in _delay: [wreg]
	line	45
	
l2821:	
;main.h: 45: for(i=1;i<2000;i++);
	movlw	low(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(_i)
	movlw	high(01h)
	movwf	((_i))+1
	movlw	high(07D0h)
	subwf	(_i+1),w
	movlw	low(07D0h)
	skipnz
	subwf	(_i),w
	skipc
	goto	u2951
	goto	u2950
u2951:
	goto	l2825
u2950:
	goto	l493
	
l2823:	
	goto	l493
	
l491:	
	
l2825:	
	movlw	low(01h)
	addwf	(_i),f
	skipnc
	incf	(_i+1),f
	movlw	high(01h)
	addwf	(_i+1),f
	movlw	high(07D0h)
	subwf	(_i+1),w
	movlw	low(07D0h)
	skipnz
	subwf	(_i),w
	skipc
	goto	u2961
	goto	u2960
u2961:
	goto	l2825
u2960:
	goto	l493
	
l492:	
	line	46
	
l493:	
	return
	opt stack 0
GLOBAL	__end_of_delay
	__end_of_delay:
;; =============== function _delay ends ============

	signat	_delay,88
	global	_interrupts
psect	text423,local,class=CODE,delta=2
global __ptext423
__ptext423:

;; *************** function _interrupts *****************
;; Defined at:
;;		line 35 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text423
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	35
	global	__size_of_interrupts
	__size_of_interrupts	equ	__end_of_interrupts-_interrupts
	
_interrupts:	
	opt	stack 6
; Regs used in _interrupts: []
	line	36
	
l2819:	
;main.h: 36: GIE =1;
	bsf	(95/8),(95)&7
	line	37
;main.h: 37: PEIE =1;
	bsf	(94/8),(94)&7
	line	38
;main.h: 38: INTEDG =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1038/8)^080h,(1038)&7
	line	39
;main.h: 39: INTF =0;
	bcf	(89/8),(89)&7
	line	40
;main.h: 40: INTE =1;
	bsf	(92/8),(92)&7
	line	41
	
l488:	
	return
	opt stack 0
GLOBAL	__end_of_interrupts
	__end_of_interrupts:
;; =============== function _interrupts ends ============

	signat	_interrupts,88
	global	_init
psect	text424,local,class=CODE,delta=2
global __ptext424
__ptext424:

;; *************** function _init *****************
;; Defined at:
;;		line 16 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text424
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\main.h"
	line	16
	global	__size_of_init
	__size_of_init	equ	__end_of_init-_init
	
_init:	
	opt	stack 6
; Regs used in _init: [wreg+status,2]
	line	17
	
l2791:	
;main.h: 17: PORTA =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(5)	;volatile
	line	18
	
l2793:	
;main.h: 18: TRISA0 =1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1064/8)^080h,(1064)&7
	line	19
	
l2795:	
;main.h: 19: TRISA1 =0;
	bcf	(1065/8)^080h,(1065)&7
	line	20
	
l2797:	
;main.h: 20: TRISA2 =0;
	bcf	(1066/8)^080h,(1066)&7
	line	21
	
l2799:	
;main.h: 21: TRISA6 =1;
	bsf	(1070/8)^080h,(1070)&7
	line	22
	
l2801:	
;main.h: 22: TRISA7 =1;
	bsf	(1071/8)^080h,(1071)&7
	line	23
;main.h: 23: PORTB =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(6)	;volatile
	line	24
	
l2803:	
;main.h: 24: TRISB0 =1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1072/8)^080h,(1072)&7
	line	25
	
l2805:	
;main.h: 25: TRISB1 =0;
	bcf	(1073/8)^080h,(1073)&7
	line	26
	
l2807:	
;main.h: 26: TRISB2 =1;
	bsf	(1074/8)^080h,(1074)&7
	line	27
	
l2809:	
;main.h: 27: TRISB3 =0;
	bcf	(1075/8)^080h,(1075)&7
	line	28
	
l2811:	
;main.h: 28: TRISB4 =0;
	bcf	(1076/8)^080h,(1076)&7
	line	29
	
l2813:	
;main.h: 29: TRISB5 =1;
	bsf	(1077/8)^080h,(1077)&7
	line	30
	
l2815:	
;main.h: 30: SSPEN =0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(165/8),(165)&7
	line	31
	
l2817:	
;main.h: 31: OSCCON =0b01110100;
	movlw	(074h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(143)^080h	;volatile
	line	32
	
l485:	
	return
	opt stack 0
GLOBAL	__end_of_init
	__end_of_init:
;; =============== function _init ends ============

	signat	_init,88
	global	_ISR
psect	text425,local,class=CODE,delta=2
global __ptext425
__ptext425:

;; *************** function _ISR *****************
;; Defined at:
;;		line 237 in file "G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\Main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          4       0       0       0
;;      Totals:         4       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text425
	file	"G:\Active\Projects\TRI002\TRI002-Sensor Embedded\TRIG software PIR modified 21.01.14\Main.c"
	line	237
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 5
; Regs used in _ISR: [wreg+status,2]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_ISR+0)
	movf	fsr0,w
	movwf	(??_ISR+1)
	movf	pclath,w
	movwf	(??_ISR+2)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	btemp+1,w
	movwf	(??_ISR+3)
	ljmp	_ISR
psect	text425
	line	238
	
i1l2841:	
;Main.c: 238: if(INTF ==1)
	btfss	(89/8),(89)&7
	goto	u301_21
	goto	u301_20
u301_21:
	goto	i1l626
u301_20:
	line	240
	
i1l2843:	
;Main.c: 239: {
;Main.c: 240: if((OR ==1) && (END !=1))
	movlw	01h
	xorwf	(_OR),w
	iorwf	(_OR+1),w
	skipz
	goto	u302_21
	goto	u302_20
u302_21:
	goto	i1l2849
u302_20:
	
i1l2845:	
	movlw	01h
	xorwf	(_END),w
	iorwf	(_END+1),w
	skipnz
	goto	u303_21
	goto	u303_20
u303_21:
	goto	i1l2849
u303_20:
	line	242
	
i1l2847:	
;Main.c: 241: {
;Main.c: 242: RB1 =0;
	bcf	(49/8),(49)&7
	line	243
;Main.c: 243: RA1 =1;
	bsf	(41/8),(41)&7
	goto	i1l2849
	line	244
	
i1l624:	
	line	245
	
i1l2849:	
;Main.c: 244: }
;Main.c: 245: if((AND ==1) && (T ==2))
	movlw	01h
	xorwf	(_AND),w
	iorwf	(_AND+1),w
	skipz
	goto	u304_21
	goto	u304_20
u304_21:
	goto	i1l2855
u304_20:
	
i1l2851:	
	movlw	02h
	xorwf	(_T),w
	iorwf	(_T+1),w
	skipz
	goto	u305_21
	goto	u305_20
u305_21:
	goto	i1l2855
u305_20:
	line	247
	
i1l2853:	
;Main.c: 246: {
;Main.c: 247: RB1 =0;
	bcf	(49/8),(49)&7
	line	248
;Main.c: 248: RA1 =1;
	bsf	(41/8),(41)&7
	goto	i1l2855
	line	249
	
i1l625:	
	line	250
	
i1l2855:	
;Main.c: 249: }
;Main.c: 250: IN =1;
	movlw	low(01h)
	movwf	(_IN)
	movlw	high(01h)
	movwf	((_IN))+1
	line	251
	
i1l2857:	
;Main.c: 251: INTE =0;
	bcf	(92/8),(92)&7
	line	252
	
i1l2859:	
;Main.c: 252: INTF =0;
	bcf	(89/8),(89)&7
	line	253
	
i1l2861:	
;Main.c: 253: INTE =1;
	bsf	(92/8),(92)&7
	line	254
	
i1l2863:	
;Main.c: 254: c =0;
	clrf	(_c)
	clrf	(_c+1)
	goto	i1l626
	line	255
	
i1l623:	
	line	256
	
i1l626:	
	movf	(??_ISR+3),w
	movwf	btemp+1
	movf	(??_ISR+2),w
	movwf	pclath
	movf	(??_ISR+1),w
	movwf	fsr0
	swapf	(??_ISR+0)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_ISR
	__end_of_ISR:
;; =============== function _ISR ends ============

	signat	_ISR,88
psect	text426,local,class=CODE,delta=2
global __ptext426
__ptext426:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
