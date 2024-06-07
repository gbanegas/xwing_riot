lib25519 is a microlibrary for the X25519 encryption system and the
Ed25519 signature system, both of which use the Curve25519 elliptic
curve. Curve25519 is the fastest curve in TLS 1.3, and the only curve in
Wireguard, Signal, and many other applications (see Nicolai Brown's page
<https://ianix.com/pub/curve25519-deployment.html>).

lib25519 has a very simple stateless [API](api.html) based on the SUPERCOP API, with
wire-format inputs and outputs, providing functions that directly match
the central cryptographic operations in X25519 and Ed25519:

* `lib25519_dh_keypair(pk,sk)`: X25519 key generation
* `lib25519_dh(k,pk,sk)`: shared-secret generation
* `lib25519_sign_keypair(pk,sk)`: Ed25519 key generation
* `lib25519_sign(sm,&smlen,m,mlen,sk)`: signing
* `lib25519_sign_open(m,&mlen,sm,smlen,pk)`: verification + message recovery

Internally, lib25519 includes implementations designed for [performance](speed.html)
on various CPUs, implementations designed to work portably across CPUs,
and automatic run-time selection of implementations.

lib25519 is intended to be called by larger multi-function libraries,
including libraries in other languages via FFI. The idea is that
lib25519 will take responsibility for the details of X25519/Ed25519
computation, including optimization, timing-attack protection, and
eventually verification, freeing up the calling libraries to concentrate
on application-specific needs such as protocol integration. Applications
can also call lib25519 directly.
