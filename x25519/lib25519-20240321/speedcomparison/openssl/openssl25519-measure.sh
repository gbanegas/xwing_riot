#!/bin/sh

# Prerequisites:
# * 64-bit CPU
# * Debian
# * packages: wget build-essential
# * dedicated account to run this script
# * openssl25519speed.c in the account's home directory

cd

export LD_LIBRARY_PATH="$HOME/lib:$HOME/lib64"
export LIBRARY_PATH="$HOME/lib:$HOME/lib64"
export CPATH="$HOME/include"
export PATH="$HOME/bin:$PATH"

[ -f $HOME/bin/cpucycles-info ] ||
(
  wget -m https://cpucycles.cr.yp.to/libcpucycles-latest-version.txt
  version=$(cat cpucycles.cr.yp.to/libcpucycles-latest-version.txt)
  wget -m https://cpucycles.cr.yp.to/libcpucycles-$version.tar.gz
  tar -xzf cpucycles.cr.yp.to/libcpucycles-$version.tar.gz
  cd libcpucycles-$version
  ./configure --prefix=$HOME && make -j8 install
)

[ -f $HOME/lib*/libcrypto.so ] ||
(
  wget https://www.openssl.org/source/openssl-3.2.1.tar.gz
  tar -xf openssl-3.2.1.tar.gz
  cd openssl-3.2.1
  ./Configure --prefix=$HOME
  make -j8
  make install
)

gcc -o openssl25519speed openssl25519speed.c \
-O3 -I include lib*/libcrypto.so lib/libcpucycles.so

./openssl25519speed > openssl25519speed.out
