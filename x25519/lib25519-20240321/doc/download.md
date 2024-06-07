To download and unpack the latest version of lib25519:

    wget -m https://lib25519.cr.yp.to/lib25519-latest-version.txt
    version=$(cat lib25519.cr.yp.to/lib25519-latest-version.txt)
    wget -m https://lib25519.cr.yp.to/lib25519-$version.tar.gz
    tar -xzf lib25519.cr.yp.to/lib25519-$version.tar.gz
    cd lib25519-$version

Then [install](install.html).

### Archives and changelog (reverse chronological) {#changelog}

[`lib25519-20240321.tar.gz`](lib25519-20240321.tar.gz) [browse](lib25519-20240321.html)

Add `./use-s2n-bignum` compile-time option,
along with lib25519+s2n benchmarks and separate s2n-bignum benchmarks.

Speed up `amd64-{maa4,maax,mxaa}` for `nP`, `nG`, `mGnP`.
Add `amd64-avx512-8x1-ns10l-maax` for `nP`.

Add initial code for 64-bit ARM.

MacOS X port: `dylib`; deal with `s` and `S` in `checknamespace`;
use `-flat_namespace` so `lib25519-test` can substitute `randombytes`;
add `crypto_asm_rodata.h` abstraction;
expand `#define` for assembly to eliminate semicolons.

Add benchmarks for more platforms.

Support empty compiler lists.

Improve selection for Zen 2, Zen 3, and Golden Cove.

Add background colors to speed table.

Improve HTML formatting for code.

Add NGI0 information.

[`lib25519-20230630.tar.gz`](lib25519-20230630.tar.gz) [browse](lib25519-20230630.html)

Add `powbatch`, `nPbatch`, and `multiscalar` APIs
with various implementations for basic amd64, BMI, ADX, AVX2, and AVX-512,
plus portable implementations.

Include benchmarks on more microarchitectures.
Add auto-generated table in documentation
summarizing [speeds](speed.html),
with OpenSSL speeds as a baseline for comparison.

For compatibility with musl etc.,
support `constructor` as an alternative to `ifunc` for dispatch.
Select `constructor` automatically if an `ifunc` compile-time test fails,
or if `--notryifunc` is passed to `./configure`.

Add command-line interface for shell scripts.

Rely on separate [libcpucycles](https://cpucycles.cr.yp.to)
to automatically use RDPMC etc.,
and separate [librandombytes](https://randombytes.cr.yp.to)
to automatically use `getrandom` etc.

Reorganize documentation into `doc/*.md` directory,
with auto-generation of HTML and manual pages.

Inside auto-generation of `command/lib25519-test.c`,
automatically cache Python computations of nP etc.

Reorganize precomputed tests to handle APIs with variable-length inputs and outputs.

Import infrastructure improvements from libmceliece.

[`lib25519-20221222.tar.gz`](lib25519-20221222.tar.gz) [browse](lib25519-20221222.html)

[`lib25519-20220726.tar.gz`](lib25519-20220726.tar.gz) [browse](lib25519-20220726.html)

[`lib25519-20220426.tar.gz`](lib25519-20220426.tar.gz) [browse](lib25519-20220426.html)
