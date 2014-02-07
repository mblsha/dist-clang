{
  'includes': [
    '../../build/configs.gypi',
  ],

  'targets': [
    {
      'target_name': 'c++',
      'type': 'shared_library',
      'all_dependent_settings': {
        'include_dirs': [
          'include',
        ],
      },
      'defines': [
        'cxx_EXPORTS',
      ],
      'cflags': [
        '-O3',
        '-std=c++11',
        '-nostdinc++',
        '-fPIC',
        '-pedantic',
        '-Wall',
        '-Wno-unused-parameter',
        '-Wwrite-strings',
        '-Wno-long-long',
        '-Wno-error',
      ],
      'cflags!': [
        '-O0',  # libc++.so loses |~basic_string()| with this flag.
      ],
      'ldflags': [
        '-nodefaultlibs',
        '--no-undefined',
      ],
      'link_settings': {
        'libraries': [
          '-lc',
          '-lm',
          '-lpthread',
        ],
      },
      'include_dirs': [
        'include',
      ],
      'sources': [
        'include/algorithm',
        'include/array',
        'include/atomic',
        'include/bitset',
        'include/cassert',
        'include/ccomplex',
        'include/cctype',
        'include/cerrno',
        'include/cfenv',
        'include/cfloat',
        'include/chrono',
        'include/cinttypes',
        'include/ciso646',
        'include/climits',
        'include/clocale',
        'include/cmath',
        'include/codecvt',
        'include/complex',
        'include/condition_variable',
        'include/csetjmp',
        'include/csignal',
        'include/cstdarg',
        'include/cstdbool',
        'include/cstddef',
        'include/cstdint',
        'include/cstdio',
        'include/cstdlib',
        'include/cstring',
        'include/ctgmath',
        'include/ctime',
        'include/cwchar',
        'include/cwctype',
        'include/deque',
        'include/dynarray',
        'include/exception',
        'include/forward_list',
        'include/fstream',
        'include/functional',
        'include/future',
        'include/initializer_list',
        'include/iomanip',
        'include/ios',
        'include/iosfwd',
        'include/iostream',
        'include/istream',
        'include/iterator',
        'include/limits',
        'include/list',
        'include/locale',
        'include/map',
        'include/memory',
        'include/mutex',
        'include/new',
        'include/numeric',
        'include/optional',
        'include/ostream',
        'include/queue',
        'include/random',
        'include/ratio',
        'include/regex',
        'include/scoped_allocator',
        'include/set',
        'include/shared_mutex',
        'include/sstream',
        'include/stack',
        'include/stdexcept',
        'include/streambuf',
        'include/string',
        'include/strstream',
        'include/system_error',
        'include/thread',
        'include/tuple',
        'include/type_traits',
        'include/typeindex',
        'include/typeinfo',
        'include/unordered_map',
        'include/unordered_set',
        'include/utility',
        'include/valarray',
        'include/vector',
        'src/algorithm.cpp',
        'src/bind.cpp',
        'src/chrono.cpp',
        'src/condition_variable.cpp',
        'src/debug.cpp',
        'src/exception.cpp',
        'src/future.cpp',
        'src/hash.cpp',
        'src/ios.cpp',
        'src/iostream.cpp',
        'src/locale.cpp',
        'src/memory.cpp',
        'src/mutex.cpp',
        'src/new.cpp',
        'src/optional.cpp',
        'src/random.cpp',
        'src/regex.cpp',
        'src/shared_mutex.cpp',
        'src/stdexcept.cpp',
        'src/string.cpp',
        'src/strstream.cpp',
        'src/system_error.cpp',
        'src/thread.cpp',
        'src/typeinfo.cpp',
        'src/utility.cpp',
        'src/valarray.cpp',
      ],
      'conditions': [
        ['OS=="linux"', {
          'dependencies': [
            '../libcxxabi/libcxxabi.gyp:c++abi',
          ],
        }],
        ['OS=="mac"', {
          'ldflags!': [
            '--no-undefined',
          ],
          'link_settings': {
            'libraries': [
              '-lc++abi',
            ],
          },
          'xcode_settings': {
            'ARCHS': ['x86_64'],
          },
        }],
      ],
    },
  ],
}
