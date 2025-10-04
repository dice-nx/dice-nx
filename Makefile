
default :
	@echo "\n  Please read BUILDING.md to find out how to buid DICE. It's not straightforward!\n"
	@false

BIN=$(abspath bin1-bootstrap)
DTMP=/tmp/dtmp
DINCLUDE=$(abspath include)

ENV_COMMON = PATH="$(BIN):$(PATH)" INSTDIR="$(abspath .)/" DLIB="$(abspath dlib1)/"

ENV1A = $(ENV_COMMON) OD="$(DTMP)/obj1-bootstrap/" BIN="$(BIN)/"          CROSS_COMPILE=1
ENV1B = $(ENV_COMMON) OD="$(DTMP)/obj1/"           BIN="$(BIN)/"          DCCOPTS="-3.2 -//" DTMP=$(DTMP)/ DINCLUDE=$(DINCLUDE)/
ENV1C = $(ENV_COMMON) OD="$(DTMP)/obj1/"           BIN="$(abspath bin1)/" DCCOPTS="-3.2 -//"

stage1 : stage1a stage1b stage1c
stage1a : $(BIN)/dmake
	( cd suplib && $(ENV1A) dmake all install )
	$(ENV1A) dmake bin-core install-bin-core
stage1b :
	mkdir -p dlib1
	cp dlib/amiga32l.lib dlib1/amiga32l.lib
	( cd lib && $(ENV1B) dmake core )
stage1c :
	mkdir -p bin1 $(DTMP)/obj1
	$(ENV1C) dmake bin-core install-bin-core

.PHONY : stage1 stage1a stage1b stage1c

$(BIN)/dmake :
	mkdir -p $(BIN)
	$(MAKE) -C src/dmake EXED="$(BIN)" all install

clean :
	$(MAKE) -C src/dmake SUBDIR=src/dmake clean
	( cd suplib && $(ENV1A) dmake clean )
	( cd lib && $(ENV1B) dmake clean )
	rm -rf dlib1 bin1 bin1-bootstrap /tmp/dtmp include/amiga20
.PHONY : clean
