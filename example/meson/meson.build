# project setting
# -----------------------------------------------------------------
project(
  'rx-nostr-cpp',
  'cpp',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17'
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
libhv_subproject = cmake.subproject(
  'libhv',
  cmake_options: [
    '-DWITH_OPENSSL=ON'
  ]
)
libhv_dep = libhv_subproject.dependency('hv')
# -----------------------------------------------------------------

# # gflags install
# # -----------------------------------------------------------------
# gflags_subproject = cmake.subproject(
#   'gflags'
#   #'gflags',
#   #cmake_options: [
#   #  '-DGFLAGS_INCLUDE_DIR=ON',
#   #  '-DGFLAGS_LIBRARIES=ON'
#   #]
# )
# 
# gflags_dep = gflags_subproject.dependency('gflags_static')
# # -----------------------------------------------------------------
# 
# # rocksdb install
# # -----------------------------------------------------------------
# rocksdb_subproject = cmake.subproject(
#   'rocksdb',
#   cmake_options: [
#     '-DGFLAGS_INCLUDE_DIR=ON',
#     '-DGFLAGS_LIBRARIES=ON'
#   ],
#   dependencies: [gflags_dep]
# )
# 
# rocksdb_dep = rocksdb_subproject.dependency('rocksdb')
# # -----------------------------------------------------------------

# rx-nostr install
# -----------------------------------------------------------------
#install_headers('../src/*.hpp', subdir: 'rx-nostr')
# -----------------------------------------------------------------

# build example
# -----------------------------------------------------------------
sources = ['../src/main.cpp']

# Place librocksdb.a directly under meson.build.
executable(
  'example',
  sources,
  link_args : [
    meson.current_source_dir() / './librocksdb.a',
    '-lstdc++', '-lstdc++fs',
    '-lpthread', '-lhv', '-lssl',
    '-lyyjson'
  ],
  #dependencies: [yyjson_dep, libhv_dep, gflags_dep, rocksdb_dep],
  dependencies: [yyjson_dep, libhv_dep],
  install: false)
# -----------------------------------------------------------------
