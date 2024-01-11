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

# rocksdb install
# -----------------------------------------------------------------
rocksdb_subproject = cmake.subproject(
  'rocksdb',
  cmake_options: [
    '-DCMAKE_BUILD_TYPE=Release',
    '-DBENCHMARK_ENABLE_GTEST_TESTS=0',
    '-DWITH_GFLAGS=0',
    '-DROCKSDB_BUILD_SHARED=0'
  ],
)

rocksdb_dep = rocksdb_subproject.dependency('rocksdb')
# -----------------------------------------------------------------

# rx-nostr install
# -----------------------------------------------------------------
#install_headers('../src/*.hpp', subdir: 'rx-nostr')
# -----------------------------------------------------------------

# build example
# -----------------------------------------------------------------
sources = ['../src/main.cpp']

executable(
  'example',
  sources,
  link_args : [
    '-lstdc++',
    '-lpthread', '-lssl'
  ],
  #dependencies: [yyjson_dep, libhv_dep, gflags_dep, rocksdb_dep],
  dependencies: [yyjson_dep, libhv_dep, rocksdb_dep],
  install: false)
# -----------------------------------------------------------------
