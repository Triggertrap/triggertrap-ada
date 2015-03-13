/*
 * delays.c
 *
 * Various useful delay routines
 *
 * Mark Crosbie  9/15/98
 */

#ifndef __DELAYS_H
#define __DELAYS_H

/* PIC18 cycle-count delay routines.
 *
 *   Functions:
 *		 Delay1TCY()
 *               Delay10TCY()  // 17Cxx only
 *               Delay10TCYx()
 *               Delay100TCYx()
 *               Delay1KTCYx()
 *               Delay10KTCYx()
 */

/* For definition of Nop() */
#include <p18cxxx.h>

/* Delay of exactly 1 Tcy */
#define Delay1TCY() Nop() 

#define PARAM_SCLASS auto

/* Delay of exactly 10 Tcy */
#define Delay10TCY() Delay10TCYx(1)

/* Delay10TCYx
 * Delay multiples of 10 Tcy
 * Passing 0 (zero) results in a delay of 2560 cycles.
 * The 18Cxxx version of this function supports the full range [0,255]
 * The 17Cxxx version supports [2,255] and 0.
 */
void Delay10TCYx(PARAM_SCLASS unsigned char);

/* Delay100TCYx
 * Delay multiples of 100 Tcy
 * Passing 0 (zero) results in a delay of 25,600 cycles.
 * The full range of [0,255] is supported.
 */
void Delay100TCYx(PARAM_SCLASS unsigned char);

/* Delay1KTCYx
 * Delay multiples of 1000 Tcy
 * Passing 0 (zero) results in a delay of 256,000 cycles.
 * The full range of [0,255] is supported.
 */
void Delay1KTCYx(PARAM_SCLASS unsigned char);

/* Delay10KTCYx
 * Delay multiples of 10,000 Tcy
 * Passing 0 (zero) results in a delay of 2,560,000 cycles.
 * The full range of [0,255] is supported.
 */
void Delay10KTCYx(PARAM_SCLASS unsigned char);

#endif
