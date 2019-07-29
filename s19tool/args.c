/*
 *  args.c -- version 0.1
 *
 *  This module is responsible for parsing command-line arguments.
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
extern void print_usage(void);
extern int h_to_i(char);

// Prototypes not defined in the header file.
int process_args(int argc, char *argv[]);

// Function to process the command-line arguments.
int process_args(int argc, char *argv[]) {
  int i;
  
  while ((argc > 1) && (argv[1][0] == '-')) {
    switch (argv[1][1]) {
      case 'b':
        i = parse_number(&argv[1][2]);
        if (i < 0) {
          fprintf(stderr, "Value for option -%s is invalid.\n", &argv[1][1]);
          return(ERR_OPT_INVALID);
        }
        s19.byte_offset = i;
        break;
      case 'a':
        i = parse_number(&argv[1][2]);
        if (i < 0) {
          fprintf(stderr, "Value for option -%s is invalid.\n", &argv[1][1]);
          return(ERR_OPT_INVALID);
        }
        s19.data_start = i;
        break;
      case 's':
        i = parse_number(&argv[1][2]);
        if (i < 0) {
          fprintf(stderr, "Value for option -%s is invalid.\n", &argv[1][1]);
          return(ERR_OPT_INVALID);
        }
        s19.data_size = i;
        break;
      case 'o':
        // strncpy(s19.output_file, &argv[1][2], 32);
        s19.output_file = &argv[1][2];
        break;
      case 'i':
        // strncpy(s19.input_file, &argv[1][2], 32);
        s19.input_file = &argv[1][2];
        break;
      case 'x':
        s19.conversion_mode = 1;
        break;
      case 'h':
        print_usage();
        return (ERR_EXIT);
        break;
      default:
        fprintf(stderr, "Bad option -%s.\n", &argv[1][1]);
        print_usage();
        return (ERR_OPT_INVALID);
    }
    argv++;
    argc--;
  }  
  return (0);
}

int parse_number(char *param) {
  unsigned char string[8];
  unsigned char *string_ptr;
  int size;
  int index;
  int value;
  int i;
  
  size = sizeof(string);
  string_ptr = strncpy(string, param, size);
  string[size-1] = '\0';

  index = size;
  while (index > 0) {
    index--;
    if (string[index] != '\0') {
      break;
    }
  }
  if (string[index] == 'k') {
    // Treat the parameter as a number of kilobytes.
    string[index] = '\0';
    value = atoi(string_ptr);
    value = value*1024;
    return value;
  }
  if (string[index] == 'b') {
    // Treat the parameter as a number of 256-byte blocks.
    string[index] = '\0';
    value = atoi(string_ptr);
    value = value*256;
    return value;
  }
  if (string[index] == 'h') {
    // Treat the parameter as a hexadecimal number.
    string[index] = '\0';
    value = 0;
    index = 0;
    while (string[index] != '\0') {
      value = value*16;
      i = h_to_i(string[index]);
      if (i < 0) {
        return (-1);
      }
      value += i;
      index++;
    }
    return value;
  }
  // Otherwise, treat the string as a pure number.
  value = atoi(string_ptr);
  return value;
}

