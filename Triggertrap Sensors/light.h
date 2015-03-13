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

#ifndef LIGHT_H
#define	LIGHT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LIGHT_RESET_COUNT               250 //12500
#define LIGHT_LOW_THRESHOLD             5
#define LIGHT_HIGH_THRESHOLD            120

void light (void);

#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_H */

