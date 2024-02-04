
CC := /usr/bin/gcc
CFLAGS := -Wall -Wextra -ggdb -MMD -MP

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
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)

-include $(DEPS)

