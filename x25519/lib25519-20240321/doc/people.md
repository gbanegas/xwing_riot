lib25519 draws on many previous implementations listed below, plus new
speedups from Kaushik Nath and new infrastructure work and factoring
from Daniel J. Bernstein.
Nath's work on this project was
[initially funded](https://nlnet.nl/project/lib25519)
through the
[Internet Hardening Fund](https://nlnet.nl/internethardening),
a fund established by
[NLnet](https://nlnet.nl/)
with financial support from the
[Netherlands Ministry of Economic Affairs and Climate Policy](https://www.rijksoverheid.nl/ministeries/ministerie-van-economische-zaken-en-klimaat),
and received
[further funding](https://nlnet.nl/project/lib25519-ARM/)
through the
[NGI0 Entrust Fund](https://nlnet.nl/entrust),
another fund from NLnet established with financial support
from the European Commission's
[Next Generation Internet](https://ngi.eu) program.

Some code was originally copied from public-domain code in the SUPERCOP
benchmarking framework. See <https://bench.cr.yp.to/supercop.html>
for SUPERCOP releases. The following small changes from code available
in SUPERCOP are made in lib25519 without further comment:

   * Returning `void` rather than `int` for functions that never fail in
     lib25519.
   * Message lengths `long long` rather than `unsigned long long`.
   * Defining various constants in `.c` files (to simplify PIC handling)
     instead of `.S` files.
   * Moving some C files to `shared-*.c` (which in lib25519 means that
     these files are compiled by only one compiler).
   * Using `CRYPTO_SHARED_NAMESPACE` rather than `CRYPTO_NAMESPACE` for
     symbols defined in `*.S` and `shared-*.c`.
   * Adding various `linker define` and `linker use` lines.

Larger changes from code in SUPERCOP, such as new code divisions across
lib25519 primitives, are indicated below.

Sources of Curve25519 software (this is not a comprehensive list, just
the software that lib25519 is derived from):

   * Daniel J. Bernstein. "Curve25519: new Diffie-Hellman speed
     records." Pages 207–228 in Public key cryptography—PKC 2006, 9th
     international conference on theory and practice in public-key
     cryptography, New York, NY, USA, April 24–26, 2006, proceedings,
     edited by Moti Yung, Yevgeniy Dodis, Aggelos Kiayias, Tal Malkin,
     Lecture Notes in Computer Science 3958, Springer, 2006, ISBN
     3-540-33851-9.

     This is the source of the Curve25519 design, the X25519 design, and
     various speedups. Most of the software from that paper is specific
     to a variety of 32-bit platforms (radix 2^25.5^ or radix 2^21.25^),
     but the portable `supercop/crypto_scalarmult/curve25519/ref10`
     (radix 2^25.5^) is derived from this.

     `lib25519/crypto_nP/montgomery25519/ref10` starts with
     `supercop/crypto_scalarmult/curve25519/ref10`, and tweaks the API to
     provide `crypto_nP` instead of `crypto_scalarmult`. Inversion is
     factored out, producing `crypto_pow/inv25519/ref10`. The trivial
     `crypto_scalarmult_base` wrapper is factored out, producing
     `crypto_nG/montgomery25519/ref/base.c`; lib25519 has faster `nG`
     functions, but intentionally provides `ref` for situations where
     speed is outweighed by simplicity, assurance, code size, etc.

   * `supercop/crypto_scalarmult/curve25519/donna_c64` (radix 2^51^) from
     Adam Langley.

     `lib25519/crypto_nP/montgomery25519/donna_c64` starts from this and
     tweaks the API to provide `crypto_nP` instead of `crypto_scalarmult`
     (and removes `crypto_scalarmult_base`).
     `crypto_pow/inv25519/donna_c64` is factored out.

   * Daniel J. Bernstein, Niels Duif, Tanja Lange, Peter Schwabe, Bo-Yin
     Yang. "High-speed high-security signatures." Pages 124–142 in
     Cryptographic hardware and embedded systems—CHES 2011, 13th
     international workshop, Nara, Japan, September 28–October 1, 2011,
     proceedings, edited by Bart Preneel, Tsuyoshi Takagi, Lecture Notes
     in Computer Science 6917, Springer, 2011, ISBN 978-3-642-23950-2.
     Journal version: Journal of Cryptographic Engineering 2 (2012),
     77–89.

     This is the source of the Ed25519 design and various X25519/Ed25519
     speedups for 64-bit Intel/AMD platforms, in particular producing
     `supercop/crypto_{scalarmult/curve,sign/ed}25519/amd64-{51,64}*`
     (radix 2^51^ and radix 2^64^ respectively). Peter Schwabe led the
     implementation work.

     `lib25519/crypto_nP/montgomery25519/amd64-51` starts from
     `supercop/crypto_scalarmult/curve25519/amd64-51` and tweaks the API
     to provide `crypto_nP` instead of `crypto_scalarmult` (and removes
     `crypto_scalarmult_base`). `crypto_nG/merged25519/amd64-51` (for
     fixed-base-point multiplication), `crypto_mGnP/ed25519/amd64-51` (for
     double-scalar multiplication), and `crypto_sign/ed25519/amd64` (for
     the remaining signing components) factor
     `supercop/crypto_sign/ed25519/amd64-51` into smaller pieces.
     `crypto_pow/inv25519/amd64-51` is also factored out. `SMALLTABLES`
     support is removed. Support for batch verification is removed,
     although it could reappear in a subsequent lib25519 release.

     Similar comments apply to `amd64-64` and `ref10`. A compiler warning
     is eliminated (window size 64 in `amd64-64-24k/sc25519.h`).

   * Tung Chou. "Sandy2x: New Curve25519 Speed Records." SAC 2015.

     This is the source of various X25519 speedups using 256-bit vector
     instructions, specifically AVX vector instructions in Intel's Sandy
     Bridge, in particular producing
     `supercop/crypto_scalarmult/curve25519/sandy2x` (radix 2^25.5^).

     `lib25519/crypto_{nP,nG}/montgomery25519/sandy2x` start from
     `supercop/crypto_scalarmult/curve25519/sandy2x`, and tweak the API
     to provide `crypto_nP` and `crypto_nG` instead of
     `crypto_scalarmult` and `crypto_scalarmult_base` respectively. The
     top bit of the incoming point is cleared.
     `crypto_pow/inv25519/sandy2x` is factored out.

   * Kaushik Nath and Palash Sarkar, "Efficient arithmetic in
     (pseudo-)Mersenne prime order fields", Advances in Mathematics of
     Communications 16 (2022), pages 303–348.
     Original release:

     - <https://github.com/kn-cs/pmp-farith/tree/master/gf-p2-255-19/SL>
     - <https://github.com/kn-cs/pmp-farith/tree/master/gf-p2-255-19/USL1>

     The `SL` software is the source of various speedups to the `amd64-64`
     software, producing the `maa4` versions of `fe25519_mul.S`,
     `fe25519_square.S`, and `fe25519_nsquare.S`. These `.S` files are used
     inside the following lib25519 directories:

     - `crypto_mGnP/ed25519/amd64-avx2-10l-maa4`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-maa4`
     - `crypto_mGnP/ed25519/amd64-maa4`
     - `crypto_nG/merged25519/amd64-avx2-10l-maa4`
     - `crypto_nG/merged25519/amd64-avx2-9l-maa4`
     - `crypto_nG/merged25519/amd64-maa4`
     - `crypto_nP/montgomery25519/amd64-avx2-hey10l-maa4`
     - `crypto_nP/montgomery25519/amd64-avx2-hey9l-maa4`
     - `crypto_nP/montgomery25519/amd64-avx2-ns10l-maa4`
     - `crypto_nP/montgomery25519/amd64-avx2-ns9l-maa4`
     - `crypto_nP/montgomery25519/amd64-maa4`
     - `crypto_pow/inv25519/amd64-maa4`

     The `USL` software is the source of various speedups to the
     `amd64-51` software, producing the `maa5` versions of `fe25519_mul.S`
     and `fe25519_nsquare.S`. These `.S` files are used inside the
     following lib25519 directories:

     - `crypto_nP/montgomery25519/amd64-avx2-hey10l-maa5`
     - `crypto_nP/montgomery25519/amd64-avx2-hey9l-maa5`
     - `crypto_nP/montgomery25519/amd64-avx2-ns10l-maa5`
     - `crypto_nP/montgomery25519/amd64-avx2-ns9l-maa5`
     - `crypto_pow/inv25519/amd64-maa5`

   * Kaushik Nath and Palash Sarkar, "Security and efficiency trade-offs
     for elliptic curve Diffie-Hellman at the 128-bit and 224-bit
     security levels." J. Cryptogr. Eng. 12(1): 107-121 (2022).
     Original release:

     - <https://github.com/kn-cs/x25519/tree/master/intel64-mxaa-4limb>
     - <https://github.com/kn-cs/x25519>

     This `mxaa-4limb` software is the source of various speedups to
     `maa4` on CPUs supporting BMI2 instructions (e.g., Intel Haswell
     from 2013), in particular producing the `mxaa` versions of
     `fe25519_mul.S` and `fe25519_nsquare.S`. These `.S` files are used
     inside the following lib25519 directories:

     - `crypto_mGnP/ed25519/amd64-avx2-10l-mxaa`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-mxaa`
     - `crypto_mGnP/ed25519/amd64-mxaa`
     - `crypto_nG/merged25519/amd64-avx2-10l-mxaa`
     - `crypto_nG/merged25519/amd64-avx2-9l-mxaa`
     - `crypto_nG/merged25519/amd64-mxaa`
     - `crypto_nP/montgomery25519/amd64-avx2-hey10l-mxaa`
     - `crypto_nP/montgomery25519/amd64-avx2-hey9l-mxaa`
     - `crypto_nP/montgomery25519/amd64-avx2-ns10l-mxaa`
     - `crypto_nP/montgomery25519/amd64-avx2-ns9l-mxaa`
     - `crypto_nP/montgomery25519/amd64-mxaa`
     - `crypto_pow/inv25519/amd64-mxaa`

     This software is also the source of the following three different
     Montgomery-ladder functions, where the third also builds on the
     `maax` work listed below:

     - `crypto_nP/montgomery25519/amd64-maa4/mladder.S`
     - `crypto_nP/montgomery25519/amd64-mxaa/mladder.S`
     - `crypto_nP/montgomery25519/amd64-maax/mladder.S`

   * Kaushik Nath and Palash Sarkar, "Efficient arithmetic in
     (pseudo-)Mersenne prime order fields", Advances in Mathematics of
     Communications 16 (2022), pages 303–348. Original release:

     - <https://github.com/kn-cs/pmp-farith/tree/master/gf-p2-255-19/SLDCC>

     This is the source of various speedups to `mxaa` on CPUs that also
     support ADX instructions (e.g., Intel Broadwell from 2014), in
     particular producing the `maax` versions of `fe25519_mul.S`,
     `fe25519_square.S`, and `fe25519_nsquare.S`. These `.S` files are used
     inside the following lib25519 directories:

     - `crypto_mGnP/ed25519/amd64-avx2-10l-maax`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-maax`
     - `crypto_mGnP/ed25519/amd64-avx512ifma-5l-maax`
     - `crypto_mGnP/ed25519/amd64-maax`
     - `crypto_nG/merged25519/amd64-avx2-10l-maax`
     - `crypto_nG/merged25519/amd64-avx2-9l-maax`
     - `crypto_nG/merged25519/amd64-avx512ifma-5l-maax`
     - `crypto_nG/merged25519/amd64-maax`
     - `crypto_nP/montgomery25519/amd64-avx2-hey10l-maax`
     - `crypto_nP/montgomery25519/amd64-avx2-hey9l-maax`
     - `crypto_nP/montgomery25519/amd64-avx2-ns10l-maax`
     - `crypto_nP/montgomery25519/amd64-avx2-ns9l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512-hey10l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512-hey9l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512-ns10l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512-ns9l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512ifma-hey5l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512ifma-ns5l-maax`
     - `crypto_nP/montgomery25519/amd64-maax`
     - `crypto_pow/inv25519/amd64-maax`

   * Kaushik Nath and Palash Sarkar, "Efficient 4-Way Vectorizations of
     the Montgomery Ladder". IEEE Trans. Computers 71(3): 712-723
     (2022). Original release:

     - <https://github.com/kn-cs/vec-ladder/tree/master/Curve25519>

     This is the source of the `hey10l` (radix 2^25.5^), `hey9l` (radix
     2^29^), `ns10l` (radix 2^25.5^), and `ns9l` (radix 2^29^) versions of
     `mladder.S` for CPUs that also support 256-bit AVX2 instructions
     (e.g., Intel Haswell from 2013). In lib25519, these four `.S` files
     are used in 16 directories:

     - `crypto_nP/montgomery25519/amd64-avx2-hey10l-{maa4,maa5,maax,mxaa}`
     - `crypto_nP/montgomery25519/amd64-avx2-hey9l-{maa4,maa5,maax,mxaa}`
     - `crypto_nP/montgomery25519/amd64-avx2-ns10l-{maa4,maa5,maax,mxaa}`
     - `crypto_nP/montgomery25519/amd64-avx2-ns9l-{maa4,maa5,maax,mxaa}`

   * Kaushik Nath, new Montgomery-ladder code new in lib25519 (no paper
     yet) for CPUs supporting AVX-512 instructions (e.g., Intel
     Skylake-X from 2017). These are six files in lib25519:

     - `crypto_nP/montgomery25519/amd64-avx512-hey10l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512-hey9l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512-ns10l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512-ns9l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512ifma-hey5l-maax`
     - `crypto_nP/montgomery25519/amd64-avx512ifma-ns5l-maax`

   * Kaushik Nath, nine versions of fixed-base-point
     scalar-multiplication code new in lib25519 (no paper yet) for
     various platforms:

     - `crypto_nG/merged25519/amd64-avx2-10l-maa4/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-avx2-10l-maax/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-avx2-10l-mxaa/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-avx2-9l-maa4/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-avx2-9l-maax/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-avx2-9l-mxaa/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-avx512ifma-5l-maax/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-maa4/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-maax/ge25519_base.S`
     - `crypto_nG/merged25519/amd64-mxaa/ge25519_base.S`

   * Kaushik Nath, ten versions of double-scalar-multiplication code new
     in lib25519 (no paper yet) for various platforms. Each version has
     `precompute.S` and `process.S`:

     - `crypto_mGnP/ed25519/amd64-avx2-10l-maa4/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-avx2-10l-maax/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-avx2-10l-mxaa/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-maa4/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-maax/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-mxaa/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-avx512ifma-5l-maax/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-maa4/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-maax/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-mxaa/ge25519_double_scalarmult_precompute.S`
     - `crypto_mGnP/ed25519/amd64-avx2-10l-maa4/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-avx2-10l-maax/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-avx2-10l-mxaa/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-maa4/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-maax/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-avx2-9l-mxaa/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-avx512ifma-5l-maax/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-maa4/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-maax/ge25519_double_scalarmult_process.S`
     - `crypto_mGnP/ed25519/amd64-mxaa/ge25519_double_scalarmult_process.S`

   * Kaushik Nath, batch scalar-multiplication code new in lib25519 (no
     paper yet):

     - `crypto_nPbatch/montgomery25519/amd64-avx512ifma-8x1`

Almost all of the `crypto_pow/inv25519` implementations use
exponentiation, but there is also a different implementation from the
following source:

   * Daniel J. Bernstein, Bo-Yin Yang. "Fast constant-time gcd
     computation and modular inversion." IACR Transactions on
     Cryptographic Hardware and Embedded Systems 2019 issue 3 (2019),
     340–398.

     This is the source of the "safegcd" algorithm and software. Further
     speedups (no paper yet; ideas from Peter Dettman, Gregory Maxwell,
     and Pieter Wuille) have produced the "inverse25519skylake" software
     available here: <https://gcd.cr.yp.to/software.html>

     `lib25519/crypto_pow/inv25519/amd64-safegcd` is inverse25519skylake,
     tweaked to provide the `crypto_pow` API and to clear the top bit of
     the input.

For lower-layer SHA-512 functions:

   * Daniel J. Bernstein, `supercop/crypto_hash*/sha512/*`. In lib25519,
     some unused variables are removed in `crypto_hashblocks/sha512/avx`
     to eliminate compiler warnings.

Most of the lib25519 infrastructure, such as the run-time implementation
selector automatically guided by CPU type and previous benchmarks, is
new in lib25519 from Daniel J. Bernstein. Portions of `autogen/speed`
(generating `lib25519-speed.c`) and `autogen/test` (generating
`lib25519-test.c`) are based on benchmarking software and test software in
SUPERCOP by Daniel J. Bernstein. The symmetric-cryptography code for
generating pseudorandom test inputs and hashing test outputs is adapted
from TweetNaCl, a library by Daniel J. Bernstein, Wesley Janssen, Tanja
Lange, and Peter Schwabe.
