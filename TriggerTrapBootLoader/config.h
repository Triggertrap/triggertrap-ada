/*
 Triggertrap Ada Source - High Speed Camera Trigger and Intervalometer
 Copyright (C) 2015  Triggertrap
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// XBoot config header file
// MCU: atxmega128a3
// F_CPU: 2000000

#define ATTACH_LED_INV 1
#define ATTACH_LED_PIN 1
#define ATTACH_LED_PORT_NAME A
#define ENABLE_API yes
#define ENABLE_API_FIRMWARE_UPDATE yes
#define ENABLE_API_LOW_LEVEL_FLASH yes
#define ENABLE_API_SPM_WRAPPER yes
#define ENABLE_BLOCK_SUPPORT yes
#define ENABLE_CRC_SUPPORT yes
#define ENABLE_EEPROM_BYTE_SUPPORT yes
#define ENABLE_FLASH_BYTE_SUPPORT yes
#define ENABLE_FLASH_ERASE_WRITE yes
#define ENABLE_FUSE_BITS yes
#define ENABLE_LOCK_BITS yes
#define ENTER_BLINK_COUNT 3
#define ENTER_BLINK_WAIT 30000
//#define ENTER_PIN 1
#define ENTER_PIN_PUEN 0
#define ENTER_PIN_STATE 0
#define ENTER_PORT_NAME A
#define FIFO_BIT_REVERSE yes
#define FIFO_CTL_PORT_NAME D
#define FIFO_DATA_PORT_NAME C
#define FIFO_RD_N_bm (1<<1)
#define FIFO_RXF_N_bm (1<<3)
#define FIFO_TXE_N_bm (1<<2)
#define FIFO_WR_N_bm (1<<0)
#define I2C_ADDRESS 0x10
#define I2C_AUTONEG_DIS_GC 0
#define I2C_AUTONEG_DIS_PROMISC 1
#define I2C_AUTONEG_PIN 2
#define I2C_AUTONEG_PORT_NAME A
#define I2C_DEVICE_PORT C
#define I2C_GC_ENABLE 1
#define I2C_MATCH_ANY 1
#define LED_INV 0
#define LED_PIN 6
#define LED_PORT_NAME F
#define UART_BAUD_RATE 115200
#define UART_EN_PIN 4
#define UART_EN_PIN_INV 0
#define UART_EN_PORT_NAME C
#define UART_NUMBER 0
#define UART_PORT_NAME E
#define UART_RX_PUEN yes
#define USE_API_VERSION 1
#define USE_ENTER_PIN yes
//#define USE_ENTER_DELAY yes
#define USE_LED yes
#define USE_UART yes
#define WATCHDOG_TIMEOUT WDT_PER_1KCLK_gc
