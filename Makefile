LIB_NAME = mos-library

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
PROGRAM_DIR = $(SELF_DIR)programs/
LIB_DIR = $(SELF_DIR)lib/

CUBE_REPO = beta-cube-library/
CUBE_SRC_DIR = $(CUBE_REPO)firmware/
CUBE_APP_DIR = $(CUBE_SRC_DIR)examples/

FIRMWARE_DIR = $(SELF_DIR)spark-firmware/firmware/

LIB_SOURCES = $(wildcard $(LIB_DIR)*)

all:
	echo $(LIB_SOURCES)

mos.bin: $(LIB_SOURCES)
	$(eval PROGRAM_NAME=$(notdir $(basename $@)))
	echo $(PROGRAM_NAME)
	cp $(LIB_DIR)* $(CUBE_SRC_DIR)
	cp $(PROGRAM_DIR)/$(PROGRAM_NAME).cpp $(CUBE_APP_DIR)
	cd $(CUBE_REPO) && $(MAKE) bin/$(PROGRAM_NAME).bin
	cp $(CUBE_REPO)bin/$(PROGRAM_NAME).bin .

