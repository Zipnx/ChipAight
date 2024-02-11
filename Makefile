
CC := /usr/bin/gcc
CFLAGS := -pg -Wall -Wextra -ggdb -MMD -MP

SDL_CFLAGS  := $(shell /usr/bin/sdl2-config --cflags)
SDL_LDFLAGS := $(shell /usr/bin/sdl2-config --libs)

BUILDDIR 	:= ./build/
SRCROOT 	:= ./src/
BINDIR 		:= ./
BINNAME 	:= emulator

SRCS := $(shell find $(SRCROOT) -name *.c)
OBJS := $(SRCS:%=$(BUILDDIR)%.o)
DEPS := $(OBJS:.o=.d)

INCLUDEDIRS := $(shell find $(SRCROOT) -type d)

INFLAGS := $(addprefix -I,$(INCLUDEDIRS))

.PHONY: bnr build clean

bnr:
	@echo ==== Building ====
	$(MAKE) build
	@echo ==== Completed ====
	$(BINDIR)$(BINNAME)

build:
	$(MAKE) $(BINDIR)$(BINNAME)

$(BINDIR)$(BINNAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(SDL_LDFLAGS)

$(BUILDDIR)%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)

-include $(DEPS)

