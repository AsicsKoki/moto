/*
 *  s19tool.h -- version 0.1
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
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

/*
 * Error codes defines.
 */
#define ERR_EXIT		1
#define ERR_OPT_INVALID		2
#define ERR_OPEN_READ_FAIL	8
#define ERR_OPEN_WRITE_FAIL	9
#define ERR_SIZE_OVERFLOW	16
#define ERR_S19_INVALID		32

/*
 * Initialization.
 */
void init(void);

/*
 * Writes.
 */
int write_file_s19(void);

/*
 * Reads.
 */
int read_file_s19(void);

/*
 * Miscellaneous.
 */
int h_to_i(char a);
int parse_number(char *param);

/*
 * The "maple" structure that holds all public variables.
 */
struct s19tool {
  // Allocate 32KB of memory for data storage for the buffer.
  unsigned char buffer[64*1024];
  // Filename vars.
  unsigned char *output_file;
  unsigned char *input_file;
  // Global variables.
  unsigned char *program_name;
  unsigned int data_start;
  unsigned int data_size;
  unsigned int byte_offset;
  unsigned int conversion_mode;
};

