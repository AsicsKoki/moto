/*
 *  file_s19.c -- version 0.1
 *
 *  This module is responsible for converting data in
 *  the Motorola S-record format for either importing or
 *  exporting.
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
extern int h_to_i(char);

int read_file_s19(void) {
  unsigned int index;
  unsigned int address;
  unsigned int record_length;
  unsigned int value;
  unsigned char record[80];
  unsigned char *record_ptr;
  FILE *fh;
  
  fh = fopen(s19.input_file, "r");
  if (fh == NULL) {
    fprintf(stderr, "Cannot open input file %s for reading.\n", s19.input_file);
    return (ERR_OPEN_READ_FAIL);
  }
  printf("Opened %s for data retrieval.\n", s19.input_file);
  
  // S19 file format decoding goes here.....
  while (1) {
    index = 0;
    
    record_ptr = fgets(record, sizeof(record), fh);
    if (record_ptr == NULL) {
      // Assume this means an error occured, though it
      // technically could mean EOF. However, S-record
      // files contain an EOF record anyways, so it
      // probably is an error.
      fprintf(stderr, "Corrupted S-record file.\n");
      return (ERR_S19_INVALID);
    }
    if (record[index] != 'S') {
      // If it doesn't begin with S, it's not an S-record file.
      fprintf(stderr, "Corrupted S-record file.\n");
      return (ERR_S19_INVALID);
    }
    if (record[index+1] == '9') {
      // This denotes the EOF record.
      return (0);
    }
    if (record[index+1] != '1') {
      // Don't know what these records are.
      fprintf(stderr, "Unknown S-record.\n");
      return (ERR_S19_INVALID);
    }
    
    index = 2;
    record_length = 0;
    
    while (index < 4) {
      record_length = record_length << 4;
      value = h_to_i(record[index]);
      if (value < 0) {
        fprintf(stderr, "Corrupt S-record hex data.\n");
        return (ERR_S19_INVALID);
      }
      record_length += value;
      index++;
    }
    
    address = 0;
    
    while (index < 8) {
      address = address << 4;
      value = h_to_i(record[index]);
      if (value < 0) {
        fprintf(stderr, "Corrupt S-record hex data.\n");
        return (ERR_S19_INVALID);
      }
      address += value;
      index++;
    }
    
    address -= s19.byte_offset;
    record_length -= 3;

    while (record_length > 0) {
      s19.buffer[address] = 0;
      value = h_to_i(record[index]);
      if (value < 0) {
        fprintf(stderr, "Corrupt S-record hex data.\n");
        return (ERR_S19_INVALID);
      }
      s19.buffer[address] = value << 4;
      value = h_to_i(record[index+1]);
      if (value < 0) {
        fprintf(stderr, "Corrupt S-record hex data.\n");
        return (ERR_S19_INVALID);
      }
      s19.buffer[address] += value;

      index += 2;
      address++;
      record_length--;
    }
    // Note that idealy a Checksum should be performed here. Perhaps later,
    // but for now I just want the bloody code to work!
  }
  
  printf("EPROM write buffer written.\n");
  return (0);
}

int write_file_s19(void) {
  unsigned int index;
  unsigned int address;
  unsigned int record_length;
  unsigned int word;
  unsigned char byte;
  unsigned char checksum;
  FILE *fh;
  
  fh = fopen(s19.output_file, "w");
  if (fh == NULL) {
    // Cannot open file for output.
    fprintf(stderr, "Cannot open %s for writing.\n", s19.output_file);
    return (ERR_OPEN_WRITE_FAIL);
  }
  index = s19.data_start;
  while (index+32 < (s19.data_start + s19.data_size)) {
    // While there is more than 32 bytes of data left...
    record_length = 32;
    // "word" is a number that holds a byte-wise sum of record-length, address and data.
    word = record_length+3;
    address = index + s19.byte_offset;
    word += address / 256;         // Calculate the MSB.
    word += address % 256;         // Then the LSB.
    fprintf(fh, "S1%.2X%.4X", record_length+3, address);
    while (record_length > 0) {
      byte = s19.buffer[index];
      word += byte;                // Add our byte values.
      fprintf(fh, "%.2X", byte);
      index++;
      record_length--;
    }
    // Calculate checksum here.
    checksum = word % 256;         // Force the running sum to be an 8-bit value.
    checksum = ~checksum;          // Finally, do a twos-complement.
    fprintf(fh, "%.2X\n", checksum);
  }
  // Now, do it all once more for the remaining data.
  record_length = s19.data_start + s19.data_size - index;
  word = record_length+3;
  address = index + s19.byte_offset;
  word += address / 256;
  word += address % 256;
  fprintf(fh, "S1%.2X%.4X", record_length+3, address);
  while (record_length > 0) {
    byte = s19.buffer[index];
    word += byte;
    fprintf(fh, "%.2X", byte);
    index++;
    record_length--;
  }
  checksum = word % 256;
  checksum = ~checksum;
  fprintf(fh, "%.2X\n", checksum);
  // The end of file record seems to always be the same.
  fprintf(fh, "S9030000FC\n");
  fclose(fh);

  return (0);
}

