# project setting
# -----------------------------------------------------------------
project(
    'rx-nostr-cpp',
    'cpp',
    default_options : [
      'warning_level=3',
      'cpp_std=c++17'
    ],
    link_args : [
      '-lstdc++', '-lstdc++fs',
      '-lpthread', '-lhv', '-lssl',
      '-lyyjson'
    ]
)
CXX='g++'
# -----------------------------------------------------------------

# yyjson install
# -----------------------------------------------------------------
cmake = import('cmake')
yyjson_subproject = cmake.subproject('yyjson')
yyjson_dep = yyjson_subproject.dependency('yyjson')
# -----------------------------------------------------------------

# libhv install
# -----------------------------------------------------------------
cdata_libhv = configuration_data()
cdata_libhv.set('WITH_OPENSSL', 'ON')
#libhv_subproject = cmake.subproject('libhv', cmake_options: cdata_libhv)
libhv_subproject = cmake.subproject('libhv', cmake_options: ['-DWITH_OPENSSL=ON'])
libhv_dep = libhv_subproject.dependency('hv')
# -----------------------------------------------------------------

sources = ['../src/main.cpp']

#install_headers('../src/*.hpp', subdir: 'rx-nostr')

#executable('example', sources, dependencies: [yyjson_dep, libhv_dep], install: false)
executable(
  'example',
  sources, dependencies: [yyjson_dep, libhv_dep],
  install: false)
