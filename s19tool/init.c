/*
 *  init.c -- version 0.1
 *
 *  This module defines default values for the
 *  struct s19 so command-line options not
 *  used will be set to something useful. It also
 *  fills the buffer with all zeroes (0x00).
 *
 *  Copyright (C)2003 Jason Woodford
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  The author of this program my be contacted at:
 *  19A Greenwood Avenue, Apt.E
 *  Grand Falls-Windsor, NL, Canada
 *  A2A 1S6
 *  woody@mail.woodyweb.ca
 */

#include "s19tool.h"

extern struct s19tool s19;

void init(void) {
   unsigned int index;
   
   // Some defaults.
   s19.output_file = "output";
   s19.input_file = "input";
   s19.data_start = 0;
   s19.data_size = 0;
   s19.byte_offset = 0;
   s19.conversion_mode = 0;

   // The buffer should be filled with NULLs before we begin.
   for (index = 0; index < 64*1024; index++) {
     s19.buffer[index] = 0;
   }
   return;
}

