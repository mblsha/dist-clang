require 'formula'

class DistClang < Formula
  homepage 'https://github.com/mblsha/dist-clang'
  head "https://github.com/mblsha/dist-clang.git"

  depends_on "ninja"

  def install
    system "./src/build/gyp", "-Dversion=#{version}"
    system "ninja", "-C", "src/out/Release"

    prefix.install "src/out/Release/clang", "src/out/Release/clangd"
    File.symlink prefix+'clang', prefix+'clang++'
    prefix.install Dir["src/out/Release/*.dylib"]
  end

  def caveats; <<-EOS.undent
    Installed to /usr/local/opt/dist-clang
    EOS
  end
end
