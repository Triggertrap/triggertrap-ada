/*
 * delays.c
 *
 * Various useful delay routines
 *
 * Mark Crosbie  9/15/98
 */

/* delay for d microseconds on a 4Mhz clock
 */
void delay_us(char d) {
  char count;    
  char count2;

   count = d;

_dmsouter;
asm movlw D'20'
asm movwf _count2_delay_us

_dmsinner:
asm        NOP
asm        NOP
asm decfsz _count2_delay_us, f
asm goto $-3
asm decfsz _count_delay_us,f
asm goto $-7
}

/* delay for d milliseconds
 * Trashes W 
 */
void delay_ms(char d) {
  char loop2;
  char loop1;

  loop1 = d;

_DELAY_1:
asm     MOVLW   110    ; close to 1.0 msec delay when set to .110
asm     MOVWF   _loop2_delay_ms
_DELAY_2:
asm     NOP
asm     NOP
asm     NOP
asm     NOP
asm     NOP
asm     NOP
asm     DECFSZ  _loop2_delay_ms, F   ; decrement and leave result in LOOP2
asm                             ; skip next statement if zero
asm     GOTO $-7                ; goto _DELAY_2
asm     DECFSZ  _loop1_delay_ms, F
asm     GOTO $-0xb              ; goto _DELAY_1

}
                    
/* delay for d seconds */
void delay_s(char d) {

  char i;
  for(i=0; i < 10; i++) {
    delay_ms(100);
  }
}
