LIB_NAME = mos-library

# Either 'core' or 'photon'. (Ensure no blank space at the end of the line.)
PLATFORM = core

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
PROGRAM_DIR = $(SELF_DIR)programs/
LIB_DIR = $(SELF_DIR)lib/
TMP_DIR = $(SELF_DIR)build_tmp/
BUILD_DIR = $(SELF_DIR)$(PLATFORM)-bin/

PROGRAMS = $(wildcard $(PROGRAM_DIR)*)
LIB_SOURCES = $(wildcard $(LIB_DIR)*)

PROGRAM_BINNAMES = $(notdir $(patsubst %.cpp,%.bin,$(PROGRAMS)))
PROGRAM_BINS = $(addprefix $(BUILD_DIR), $(PROGRAM_BINNAMES))

all:
	@echo "Targets are: " $(PROGRAM_BINNAMES)
	@echo "To build one, type 'make mos.bin' replacing mos.bin with your choice."
	@echo "To choose a platform, put "PLATFORM=photon" (or =core) after 'make'."
	@echo "For example: 'make PLATFORM=photon mos.bin'"
	@echo "Your .bin file will be placed in 'core-bin' (or 'photon-bin')."

$(PROGRAM_BINNAMES): %.bin : $(BUILD_DIR)%.bin
	echo $@

$(PROGRAM_BINS) : $(BUILD_DIR)%.bin : $(PROGRAM_DIR)%.cpp $(LIB_SOURCES) cubelibs | $(BUILD_DIR)
	rm -rf $(TMP_DIR)
	mkdir $(TMP_DIR)
	cp cubelibs/* $(TMP_DIR)
	cp $(LIB_DIR)/* $(TMP_DIR)
	$(eval PROGRAM_NAME=$(notdir $(basename $@)))
	echo $(PROGRAM_NAME)
	cp $(PROGRAM_DIR)$(PROGRAM_NAME).cpp $(TMP_DIR)
	particle compile $(PLATFORM) $(TMP_DIR) --saveTo $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

cubelibs:
	wget -np -r -nH -P cubelibs --cut-dirs=3 \
	    -A ".cpp,.h" \
	    http://cubetube.org/media/cloudware/library/

# Start off from a completely clean 
clean:
	-rm -rf $(TMP_DIR)
	-rm -rf $(BUILD_DIR)
