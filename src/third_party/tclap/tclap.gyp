{
  'includes': [
    '../../build/defaults.gypi',
  ],
  'targets': [
    {
      'target_name': 'tclap',
      'type': 'none',
      'direct_dependent_settings': {
        'cflags!': [
          '-fno-exceptions',  # TCLAP uses exceptions.
        ],
        'ldflags!': [
          '-fno-exceptions',
        ],
        'include_dirs': [
          'include',
        ],
      },
      'sources': [
        'include/tclap/Arg.h',
        'include/tclap/ArgException.h',
        'include/tclap/ArgTraits.h',
        'include/tclap/CmdLine.h',
        'include/tclap/CmdLineInterface.h',
        'include/tclap/CmdLineOutput.h',
        'include/tclap/Constraint.h',
        'include/tclap/DocBookOutput.h',
        'include/tclap/HelpVisitor.h',
        'include/tclap/IgnoreRestVisitor.h',
        'include/tclap/MultiArg.h',
        'include/tclap/MultiSwitchArg.h',
        'include/tclap/OptionalUnlabeledTracker.h',
        'include/tclap/StandardTraits.h',
        'include/tclap/StdOutput.h',
        'include/tclap/SwitchArg.h',
        'include/tclap/UnlabeledMultiArg.h',
        'include/tclap/UnlabeledValueArg.h',
        'include/tclap/ValueArg.h',
        'include/tclap/ValuesConstraint.h',
        'include/tclap/VersionVisitor.h',
        'include/tclap/Visitor.h',
        'include/tclap/XorHandler.h',
        'include/tclap/ZshCompletionOutput.h',
      ],
    },
  ],
}
