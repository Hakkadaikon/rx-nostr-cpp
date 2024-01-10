###############################################################################
# File        : Malefile
# Description : Makefile for example
# Author      : hakkadaikon
###############################################################################

#------------------------------------------------------------------------------
# Build options
#------------------------------------------------------------------------------
.PHONY: clean setup build format

clean:
	@rm -rf \
		build \
		meson/subprojects/yyjson \
		meson/subprojects/libhv  \
		meson/subprojects/gflags \
		meson/subprojects/rocksdb

setup: clean
	meson setup meson build

build:
	ninja -C build

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
		}"                                                 \
		$(shell find src/ -name '*.cpp' -o -name '*.hpp') \
		$(shell find src/ -name '*.c' -o -name '*.h'    )
