LIB_NAME = mos-library

# Either 'core' or 'photon'. (Ensure no blank space at the end of the line.)
PLATFORM = core

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
PROGRAM_DIR = $(SELF_DIR)programs/
LIB_DIR = $(SELF_DIR)lib/
TMP_DIR = $(SELF_DIR)build_tmp/
BUILD_DIR = $(SELF_DIR)$(PLATFORM)-bin/

LIB_SOURCES = $(wildcard $(LIB_DIR)*)

mos.bin: $(LIB_SOURCES) cubelibs
	-rm -rf $(TMP_DIR)
	mkdir $(TMP_DIR)
	cp cubelibs/* $(TMP_DIR)
	cp $(LIB_DIR)/* $(TMP_DIR)
	$(eval PROGRAM_NAME=$(notdir $(basename $@)))
	echo $(PROGRAM_NAME)
	cp $(PROGRAM_DIR)$(PROGRAM_NAME).cpp $(TMP_DIR)
	-mkdir $(BUILD_DIR)
	particle compile $(PLATFORM) $(TMP_DIR) --saveTo $(BUILD_DIR)$@

cubelibs:
	wget -np -r -nH -P cubelibs --cut-dirs=3 \
	    -A ".cpp,.h" \
	    http://cubetube.org/media/cloudware/library/

# Start off from a completely clean 
clean:
	-rm -rf $(TMP_DIR)
	-rm -rf $(BUILD_DIR)
