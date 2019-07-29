/*
 *  print_usage.c -- version 0.1
 *
 *  Self-explanatory :)
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

#include <stdio.h>

void print_usage(void) {
  printf("S19tool version 0.1, Copyright (C) 2003 Jason Woodford\n");
  printf("S19tool comes with ABSOLUTELY NO WARRANTY.\n");
  printf("This is free software, and you are welcome to redistribute it\n");
  printf("under certain conditions. See the file COPYING for details.\n");
  printf("\nMotorola S-record conversion tool.\n");
  printf("Usage:  s19tool [-option]...\nOptions:\n");
  printf("  -h      Display this help message.\n");
  printf("  -an     The start address of data.\n");
  printf("  -sn     The size of data.\n");
  printf("  -bn     The byte-offset.\n");
  printf("  -x      Export S-record file to binary file (default is to import).\n");
  printf("  -ofile  Set output file to `file'.\n");
  printf("  -ifile  Set input file to `file'.\n");
  printf("The numerical values above can either be decimal (ie. 1024), hexadecimal\n");
  printf("(ie. 400h), kilobytes (ie. 1k), or 256-byte blocks (ie. 4b).\n");

  return;
}

