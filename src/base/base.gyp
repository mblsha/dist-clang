{
  'includes': [
    '../build/defaults.gypi',
  ],
  'targets': [
    {
      'target_name': 'base',
      'type': 'static_library',
      'sources': [
        'attributes.h',
        'c_utils.h',
        'constants.cc',
        'constants.h',
        'net_utils.h',
        'process.cc',
        'process.h',
        'string_utils.h',
      ],
    },
    {
      'target_name': 'futex',
      'type': 'static_library',
      'sources': [
        'futex/futex_helpers.h',
        'futex/scoped_lock.cc',
        'futex/scoped_lock.h',
      ],
    },
  ],
}
