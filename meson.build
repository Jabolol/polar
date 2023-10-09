project(
  'polar',
  'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20']
)

sources = files(
  'main.cpp',
  'src/polar.cpp',
  'src/mime.cpp',
  'src/server.cpp',
)

cpp_flags = ['-Wall', '-Wextra']
cpp_include_dirs = include_directories('include')

executable(
  'polar',
  sources,
  include_directories : cpp_include_dirs,
  install : true
)
