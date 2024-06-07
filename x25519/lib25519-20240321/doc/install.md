Prerequisites:

* `python3`
* `gcc` and/or `clang`
* [`libcpucycles`](https://cpucycles.cr.yp.to)
* [`librandombytes`](https://randombytes.cr.yp.to)

### For sysadmins

To install in `/usr/local/{include,lib,bin,man}`:

    ./configure && make -j8 install

### For developers with an unprivileged account

Typically you'll already have

    export LD_LIBRARY_PATH="$HOME/lib"
    export LIBRARY_PATH="$HOME/lib"
    export CPATH="$HOME/include"
    export PATH="$HOME/bin:$PATH"

in `$HOME/.profile`. To install in `$HOME/{include,lib,bin,man}`:

    ./configure --prefix=$HOME && make -j8 install

### For distributors creating a package

Run

    ./configure --prefix=/usr && make -j8

and then follow your usual packaging procedures for the
`build/0/package` files:

    build/0/package/include/lib25519.h
    build/0/package/lib/lib25519*
    build/0/package/bin/lib25519*
    build/0/package/man/man3/*.3
    build/0/package/man/man1/*.1

The `libcpucycles` and `librandombytes` packages are build-time and
run-time prerequisites; the `python3` and compiler packages are only
build-time prerequisites.

### More options

Before `./configure` you can run `./use-s2n-bignum`
to download various `.S` files from
[s2n-bignum](https://github.com/awslabs/s2n-bignum)
and integrate them into lib25519.
The critical feature of these `.S` files
is that they are formally verified to work correctly on all inputs.
The files cover, for 64-bit Intel/AMD/ARM,
the main `nG` and `nP` subroutines used in X25519 key generation and shared-secret generation;
the files also save some time on some of these CPUs, although not all.
If you want to disable the other `nG` and `nP` implementations,
you can run
`chmod +t crypto_{nP,nG}/montgomery25519/*` before running `./use-s2n-bignum`.

You can run

    ./configure --host=amd64

to override `./configure`'s guess of the architecture that it should
compile for. The architecture controls which implementations to try
(see `crypto_*/*/*/architectures`) and which compilers to try (see
`compilers/*`).

Inside the `build` directory, `0` is symlinked to `amd64` for
`--host=amd64`. Running `make clean` removes `build/amd64`. Re-running
`./configure` automatically starts with `make clean`.

A subsequent `./configure --host=arm64` will create `build/arm64` and
symlink `0 -> arm64`, without touching an existing `build/amd64`. However,
cross-compilers aren't yet selected automatically.
