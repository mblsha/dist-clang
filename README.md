# dist-clang

Fork of https://code.google.com/p/dist-clang/

# Installation

`brew install --HEAD https://github.com/mblsha/dist-clang/raw/master/dist-clang.rb`

# Configuration

Note: comments in config files are *NOT* supported.

### compile-node

#### compile-node.config:

```
socket_path: "/tmp/clangd.socket"

local {
  host: "la-mac.local"
  port: 6001
  threads: 8
  disabled: false
}

versions {
  version: "clang version 3.4 (trunk 193323)"
  path: "/Users/mblsha/src/llvm-build/Release+Asserts/bin/clang"
  plugins {
    name: "find-bad-constructs"
    path: "/Users/mblsha/src/llvm-build/Release+Asserts/lib/libFindBadConstructs.dylib"
  }
}

verbosity {
  levels {
    right: 30
    left:   0
  }
}
```

#### Configuration

```
export CLANGD_CXX /Users/mblsha/src/llvm-build/Release+Asserts/bin/clang
export CLANGD_SOCKET_PATH /tmp/clangd.socket
/usr/local/opt/dist-clang/clangd --config ~/bin/dot-files/dist-clang/compile-node.config
```

### commander

#### commander.config:

```
socket_path: "/tmp/clangd.socket"

# caching is optional. cache_size is in bytes
cache_path: "/Users/mblsha/dist-clang/cache"
cache_size: 107374182400

remotes {
  host: "la-mac.local"
  port: 6001
  threads: 8
  disabled: false
}

# several versions at once are supported.
versions {
  version: "clang version 3.5 (trunk 19999)"
  path: "/Users/mblsha/src/llvm-build-19999/Release+Asserts/bin/clang"
  plugins {
    name: "find-bad-constructs"
    path: "/Users/mblsha/src/llvm-build-19999/Release+Asserts/lib/libFindBadConstructs.dylib"
  }
}

versions {
  version: "clang version 3.4 (trunk 193323)"
  path: "/Users/mblsha/src/llvm-build/Release+Asserts/bin/clang"
  plugins {
    name: "find-bad-constructs"
    path: "/Users/mblsha/src/llvm-build/Release+Asserts/lib/libFindBadConstructs.dylib"
  }
}

verbosity {
  levels {
    right: 30
    left:   0
  }
}
```

#### Configuration & Final Usage

```
export CLANGD_CXX /Users/mblsha/src/llvm-build/Release+Asserts/bin/clang
export CLANGD_SOCKET_PATH /tmp/clangd.socket

/usr/local/opt/dist-clang/clangd --config ~/bin/dot-files/dist-clang/commander.config

export CC /usr/local/opt/dist-clang/clang
export CXX /usr/local/opt/dist-clang/clang++

./configure
make
```
