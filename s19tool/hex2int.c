/*
 *  hex2int.c -- version 0.1
 * 
 *  A little routine to convert an ASCII
 *  hex digit into it's decimal equivalent.
 *  Returns a -1 if there was no valid hex data.
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

int h_to_i(char a) {
  int i;
  // First, assume it is a digit (0-9).
  i = a - 48;
  if ((i > 16) && (i < 23)) {
    // If it's an uppercase letter (A-F)...
    i -= 7;
  }
  if ((i > 48) && (i < 55)) {
    // If it's a lowercase letter (a-f)...
    i -= 39;
  }
  if ((i < 0) || (i > 15)) {
    // Finally, if it wasn't a valid hex digit...
    return (-1);
  }
  return i;
}

