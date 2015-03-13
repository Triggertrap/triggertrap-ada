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

#ifndef PIRMIC_H
#define	PIRMIC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PIR_RESET_COUNT             750
#define PIR_LOW_THRESHOLD           66
#define PIR_HIGH_THRESHOLD          188

#define MIC_RESET_COUNT             250
#define MIC_LOW_THRESHOLD           89
#define MIC_HIGH_THRESHOLD          178


void pir_mic (unsigned int reset_count, unsigned char low_thold, unsigned char high_thold);

#ifdef	__cplusplus
}
#endif

#endif

