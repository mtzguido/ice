.PHONY:clean all re run doc
CFLAGS=-Wall -funroll-loops $(CFLAGS_EXTRA)
LFLAGS=
SHELL=/bin/bash
TARGET=chess
CC=gcc

include .config

ifeq (${CONFIG_ALPHABETA},y)
	CFLAGS += -DCFG_ALPHABETA
endif

ifeq (${CONFIG_KILLER},y)
	CFLAGS += -DCFG_KILLER
endif

ifeq (${CONFIG_COUNTERMOVE},y)
	CFLAGS += -DCFG_COUNTERMOVE
endif

ifeq (${CONFIG_EXTEND},y)
	CFLAGS += -DCFG_DEPTH_EXTENSION
endif

ifeq (${CONFIG_TRANSPOSITION},y)
	CFLAGS += -DCFG_TRANSPOSITION
endif

ifeq (${CONFIG_OWNMEM},y)
	CFLAGS += -DCFG_OWNMEM
endif

ifeq (${CONFIG_RELEASE},y)
	CFLAGS += -O99 -DNDEBUG
endif

ifeq (${CONFIG_RANDOMIZE},y)
	CFLAGS += -DCFG_RANDOMIZE
endif

ifeq (${CONFIG_SHUFFLE},y)
	CFLAGS += -DCFG_SHUFFLE
endif

ifeq (${CONFIG_PROFILE},y)
	LFLAGS += -pg
	CFLAGS += -pg
endif

ifeq (${CONFIG_DEBUG},y)
	CFLAGS += -g
endif

CFLAGS += -DCFG_DEPTH=${CONFIG_DEPTH}
CFLAGS += -DCFG_MEMSZ=${CONFIG_MEMSZ}

mods=main ai board move succs pgn mem
objs=$(patsubst %,%.o,$(mods))

all: $(TARGET)

$(TARGET): $(objs)
	$(CC) $(LFLAGS) $(objs) -o $(TARGET)

%.o: %.c $(wildcard *.h) .config
	$(CC) $(CFLAGS) -c $<	-o $@

clean:
	rm -f $(TARGET) $(objs) gmon.out
	rm -f bpipe wpipe
	$(MAKE) -C doc clean
	rm -f FINISHLOG full_log gamelog_*

re: clean all

run: $(TARGET)
	./$(TARGET)

prof: $(TARGET) prof_input
	time ./$(TARGET) w < prof_input || true # >/dev/null
	gprof $(TARGET) gmon.out >prof

vprof: prof
	gprof2dot.py prof | xdot

test: | $(TARGET)
	./scripts/make_tests.sh

doc:
	$(MAKE) -C doc
