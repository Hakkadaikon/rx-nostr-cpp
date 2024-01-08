###############################################################################
# File        : Malefile
# Description : Makefile for dependency install / format
# Author      : hakkadaikon
###############################################################################

#------------------------------------------------------------------------------
# Build options
#------------------------------------------------------------------------------
.PHONY: format
# libhv build command
#   ./configure --with-openssl --with-http_realip_module --with-http_ssl_module \
#               --with-stream --with-stream_ssl_module --with-http_slice_module
#   make
#   sudo make install
# yyjson build command
#   cmake .
#   make
#   sudo make install

install-dep:
	# yyjson
	sudo rm -rf deps/
	mkdir deps/
	git clone --depth 1 https://github.com/ibireme/yyjson.git deps/yyjson
	cmake -S deps/yyjson -B deps/yyjson
	make -C deps/yyjson
	sudo make -C deps/yyjson install
	# libhv
	git clone --depth 1 --recursive git@github.com:ithewei/libhv.git deps/libhv
	cd deps/libhv &&                    \
	./configure                         \
		--with-openssl              \
		--with-http_realip_module   \
		--with-http_ssl_module      \
		--with-stream               \
		--with-stream_ssl_module    \
		--with-http_slice_module && \
	cd ../..
	make -C deps/libhv
	sudo make -C deps/libhv install

install:
	sudo mkdir -p /usr/local/include/rx-nostr
	sudo cp -rp src/* /usr/local/include/rx-nostr/

uninstall:
	sudo rm -rf /usr/local/include/rx-nostr

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
