{
  'variables': {
    'clang%': 0,
    'profiler%': 0,
    'tcmalloc%': 1,
  },

  'includes': [
    'configs.gypi',
  ],

  'target_defaults': {
    'dependencies': [
      '<(DEPTH)/third_party/libcxx/libcxx.gyp:c++',
      '<(DEPTH)/third_party/libcxxabi/libcxxabi.gyp:c++abi',
    ],
    'cflags': [
      '-std=c++11',
      '-stdlib=libc++',
      '-pipe',
      '-pthread',
      '-fno-exceptions',
      '-Wall',
      '-Wsign-compare',
      '-Werror',
    ],
    'ldflags': [
      '-lpthread',
    ],
    'xcode_settings': {
      'ARCHS': ['x86_64'],
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
      'CLANG_CXX_LIBRARY': 'libc++',
      'WARNING_CFLAGS': [
        '-Wall',
        '-Wsign-compare',
        '-Werror',
      ],
      'OTHER_CFLAGS': [
        '-pipe',
        '-pthread',
        '-fno-exceptions',
      ],
    },
    'include_dirs': [
      '..',
    ],
    'sources/': [
      ['exclude', '_(linux|mac)\\.cc$'],
    ],
    'conditions': [
      ['OS=="linux"', {
        'defines': [
          'OS_LINUX',
        ],
        'sources/': [
          ['include', '_linux\\.cc$'],
        ],
      }],
      ['OS=="mac"', {
        'defines': [
          'OS_MACOSX',
        ],
        'sources/': [
          ['include', '_mac\\.cc$'],
        ],
      }],
      ['profiler==1 and OS=="linux"', {
        'defines': [
          'PROFILER',
        ],
        'ldflags': [
          '-lprofiler',
        ],
      }],
      ['tcmalloc==1 and OS=="linux"', {
        'ldflags': [
          '-ltcmalloc',
        ],
      }],
    ],
    'target_conditions': [
      ['_type=="shared_library"', {
        'cflags': [
          '-fPIC',
        ],
      }],
    ],
  },
}
