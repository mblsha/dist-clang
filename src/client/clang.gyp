{
  'includes': [
    '../build/defaults.gypi',
  ],

  'targets': [
    {
      'target_name': 'clang',
      'type': 'executable',
      'dependencies': [
        '../base/base.gyp:constants',
        '../base/base.gyp:headers_only',
        '../base/base.gyp:process',
        '../net/net.gyp:net',
        '../proto/proto.gyp:proto',
      ],
      'sources': [
        'clang.cc',
        'clang_flag_set.cc',
        'clang_flag_set.h',
      ],
    },
  ],
}
