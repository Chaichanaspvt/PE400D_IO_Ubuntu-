# Copyright (C) 2007, 2012  Jean Delvare <khali@linux-fr.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

TOOLS_DIR       := .

TOOLS_BIN_DIR	:= ../bin

TOOLS_CFLAGS	:= -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
		   -Wcast-align -Wwrite-strings -Wnested-externs -Winline \
		   -W -Wundef -Wmissing-prototypes -Iinclude

TOOLS_TARGETS	:= DO0 DO1 DO2 DO3 DI0 DI1 DI2 DI3

all: all-tools

#
# Programs
#

DO0: DO0.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)

DO1: DO1.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)

DO2: DO2.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)

DO3: DO3.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)

DI0: DI0.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)

DI1: DI1.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)

DI2: DI2.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)

DI3: DI3.o common.o
	$(CC) -o $@ $^
	@cp $@ $(TOOLS_BIN_DIR)


#
# Objects
#

$(TOOLS_DIR)/DO0.o: $(TOOLS_DIR)/DO0.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/DO1.o: $(TOOLS_DIR)/DO1.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/DO2.o: $(TOOLS_DIR)/DO2.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/DO3.o: $(TOOLS_DIR)/DO3.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/DI0.o: $(TOOLS_DIR)/DI0.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/DI1.o: $(TOOLS_DIR)/DI1.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/DI2.o: $(TOOLS_DIR)/DI2.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/DI3.o: $(TOOLS_DIR)/DI3.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

$(TOOLS_DIR)/common.o: $(TOOLS_DIR)/common.c $(TOOLS_DIR)/common.h
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@


#
# Commands
#

all-tools: $(addprefix $(TOOLS_DIR)/,$(TOOLS_TARGETS))

strip-tools: $(addprefix $(TOOLS_DIR)/,$(TOOLS_TARGETS))
	strip $(addprefix $(TOOLS_DIR)/,$(TOOLS_TARGETS))

clean-tools:
	$(RM) $(addprefix $(TOOLS_DIR)/,*.o $(TOOLS_TARGETS))
	$(RM) $(addprefix $(TOOLS_BIN_DIR)/,$(TOOLS_TARGETS))


strip: strip-tools

clean: clean-tools


