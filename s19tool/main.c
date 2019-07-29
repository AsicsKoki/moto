/*
 *  main.c -- version 0.1
 *
 *  This is the main portion of the programming
 *  software that defines the CLI interaction.
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

struct s19tool s19;

extern void init(void);
extern int process_args(int, char*[]);
extern int write_file_s19(void);
extern int read_file_s19(void);

int main(int argc, char *argv[]) {
  int rcode = 0;
  unsigned int binary_size;
  FILE *binary_fh;
  
  init();
  
  rcode = process_args(argc, argv);
  if (rcode) {
    printf("Exiting.\n");
    return rcode;
  }
  
  // Import binary data to S-record format.
  if (s19.conversion_mode == 0) {
     binary_fh = fopen(s19.input_file, "rb");
     if (binary_fh == NULL) {
       fprintf(stderr, "Unable to open `%s' for reading.\n", s19.input_file);
       return(ERR_OPEN_READ_FAIL);
     }
     binary_size = fread(&s19.buffer, 1, sizeof(s19.buffer), binary_fh);
     fclose(binary_fh);
     if (binary_size > 64*1024) {
       // Note that technically this will always be false
       // due to the sizeof() in the read above. It should be fixed
       // to indicate an under-read.
       fprintf(stderr, "File size exceeds S-record limits.\n");
       return(ERR_SIZE_OVERFLOW);
     }
     if ((binary_size + s19.byte_offset) > 64*1024) {
       fprintf(stderr, "File size plus offset exceeds S-record limits.\n");
       return(ERR_SIZE_OVERFLOW);
     }
     if (s19.data_size == 0) {
       s19.data_size = binary_size - s19.data_start;
     }
     printf("Converting binary data to S-record file...\n");
     rcode = write_file_s19();
     if (rcode) {
       return rcode;
     }
     printf("Input file: %s (%d bytes read)\n", s19.input_file, binary_size);
     printf("Output file: %s (address range %.4X-%.4X)\n", s19.output_file, \
       (s19.data_start + s19.byte_offset), (s19.data_start + s19.data_size + s19.byte_offset));
  }
  else {
     rcode = read_file_s19();
     if (rcode) {
       return rcode;
     }
     if (s19.data_size == 0) {
       s19.data_size = 64*1024;
     }
     printf("Converting S-record file to binary data...\n");
     binary_fh = fopen(s19.output_file, "wb");
     if (binary_fh == NULL) {
       fprintf(stderr, "Unable to open `%s' for writing.\n", s19.output_file);
       return(ERR_OPEN_WRITE_FAIL);
     }
     binary_size = fwrite(((&s19.buffer) + s19.data_start), 1, s19.data_size, binary_fh);
     printf("Input file: %s\n", s19.input_file);
     printf("Output file: %s (%d bytes written)\n", s19.output_file, binary_size);
  }
  return (0);
}

