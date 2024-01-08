###############################################################################
# File        : Malefile
# Description : Makefile for example
# Author      : hakkadaikon
###############################################################################

#------------------------------------------------------------------------------
# Program name
#------------------------------------------------------------------------------
PROGRAM  := example

#------------------------------------------------------------------------------
# Compiler name
#------------------------------------------------------------------------------
CXX      := g++

#------------------------------------------------------------------------------
# Directories
#------------------------------------------------------------------------------
SRCROOT  := .
OBJROOT  := ./obj
BINROOT  := ./bin
SRCDIRS  := $(shell find $(SRCROOT) -type d)
OBJDIRS  := $(addprefix $(OBJROOT)/, $(SRCDIRS))

#------------------------------------------------------------------------------
# Files
#------------------------------------------------------------------------------
SRCFILES    := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
OBJFILES    := $(addprefix $(OBJROOT)/, $(SRCFILES:.cpp=.o))
DEPENDFILES := $(OBJFILES:.o=.d)

#------------------------------------------------------------------------------
# Flags
#------------------------------------------------------------------------------
CPPFLAGS := -O2 -std=c++2a -Wall
LDLIBS   := -L/usr/local/lib/libhv.so
LDLIBS   += -L/usr/local/lib/libyyjson.a
LDFLAGS  := -lstdc++ -lstdc++fs
LDFLAGS  += -lpthread -lhv -lssl
LDFLAGS  += -lyyjson

#------------------------------------------------------------------------------
# Make rules
#------------------------------------------------------------------------------
$(BINROOT)/$(PROGRAM): $(OBJFILES)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS)

$(OBJROOT)/%.o: $(SRCROOT)/%.cpp
	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CPPFLAGS) $(INCLUDE) -o $@ -c $<

#------------------------------------------------------------------------------
# Build options
#------------------------------------------------------------------------------
.PHONY: all clean format
# libhv build command
#   ./configure --with-openssl --with-http_realip_module --with-http_ssl_module \
#               --with-stream --with-stream_ssl_module --with-http_slice_module
#   make
#   sudo make install

# format (use clang)
format:
	@clang-format -i \
		-style="{    \
			BasedOnStyle: Google,                      \
			AlignConsecutiveAssignments: true,         \
			AlignConsecutiveDeclarations: true,        \
			ColumnLimit: 0,                            \
			IndentWidth: 4,                            \
			AllowShortFunctionsOnASingleLine: None,    \
			AllowShortLoopsOnASingleLine: false,       \
			BreakBeforeBraces: Linux,                  \
			SortIncludes: false,                       \
			DerivePointerAlignment: false,             \
			PointerAlignment: Left,                    \
			AlignOperands: true,                       \
		}"                                             \
		$(shell find . -name '*.cpp' -o -name '*.hpp') \
		$(shell find . -name '*.c' -o -name '*.h')

all:
	$(OBJROOT)/$(PROGRAM)

clean:
	rm -f  $(BINROOT)/$(PROGRAM)
	rm -rf $(OBJROOT)/*
	rm -rf $(DEPENDFILES)

ifneq "$(MAKECMDGOALS)" "clean"
	-include $(DEPENDFILES)
endif
