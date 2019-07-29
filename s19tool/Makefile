#
# Makefile -- Motorola S-record conversion tool, v0.1
#
# Edit the following variables to suit your system.
# Most likely, you will only need to edit the variable
# INSTALL_DIR if you want the executable placed elsewhere.
#

VERSION=0.1
PREFIX_DIR=/usr/local
BINARY_DIR=/bin
MANUAL_DIR=/man/man1

CC=gcc
CFLAGS=-O2 -Wall

CP=cp
CHMOD=chmod

#
# Nothing the edit beyond here.
#

OBJECTS=args.o file_s19.o hex2int.o init.o main.o print_usage.o

all: s19tool

s19tool: $(OBJECTS)
	$(CC) $(CFLAGS) -o s19tool $(OBJECTS)

install: s19tool
	$(CP) -v s19tool $(PREFIX_DIR)$(BINARY_DIR)
	$(CHMOD) 755 $(PREFIX_DIR)$(BINARY_DIR)/s19tool
	$(CP) -v s19tool.1 $(PREFIX_DIR)$(MANUAL_DIR)
	$(CHMOD) 644 $(PREFIX_DIR)$(MANUAL_DIR)/s19tool.1
clean:
	rm -rf s19tool *.o

args.o: 	s19tool.h args.c

file_s19.o: 	s19tool.h file_s19.c

hex2int.o: 	s19tool.h hex2int.c

init.o: 	s19tool.h init.c

main.o: 	s19tool.h main.c

print_usage.o: 	s19tool.h print_usage.c

