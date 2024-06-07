Security model: X25519 is designed to be strong as a component of
various well-known "hashed DH" applications, and in particular is
designed to make the CDH problem difficult with respect to the standard
base. Ed25519 is designed to provide EUF-CMA, the standard notion of
unforgeability of a signature system under chosen-message attacks.
However, some applications need other security notions that are not
provided by X25519 and Ed25519.

Security level: X25519 and Ed25519 are more difficult to break by any
known attacks than a typical 128-bit cipher. They have an extremely
stable security track record, with two decades of research changing
security levels by only a fraction of a bit. They also proactively avoid
various potential risks. However, large quantum computers will break
both X25519 and Ed25519.

Software verification: lib25519 is intended to become a central target
for verification of full functional correctness of implementations of
X25519 and Ed25519. However, only certain portions have been verified so
far, and at this point the code should be presumed to have critical
bugs.

API safety: The lib25519 API is systematically designed to simplify
correct use and complicate incorrect use. As in the SUPERCOP/NaCl API,
inputs and outputs are in wire format rather than requiring conversion
to an internal format; signing a message uses simply a secret key, not
taking the public key as a separate input; and verification recovers a
message from a signed message, not treating the signature as a separate
object that one can forget to verify.

Timing attacks: lib25519 is designed to avoid all data flow from secret
data to memory addresses and branch conditions. Fully protecting the
user against timing attacks requires addressing more issues, such as the
following:

   * Other common instructions used by lib25519 take variable time on
     some CPUs. In particular, there are some embedded CPUs with
     variable-time multipliers.

   * Many CPUs include dynamic frequency-selection mechanisms such as
     Turbo Boost, exposing power information via timing information.
     Fortunately, these CPUs are normally shipped with simple options to
     disable Turbo Boost etc., closing this leak; unfortunately, Turbo
     Boost is enabled by default on CPUs that support it.

   * Cryptographic keys are normally handled by cryptographic software,
     but other user secrets are handled by many different pieces of
     software.

See [https://timing.attacks.cr.yp.to](https://timing.attacks.cr.yp.to)
for a timing-attack survey and many references.

Speculative-execution attacks: Some countermeasures against
speculative-execution attacks are planned but are not included in the
current version of lib25519. Full protection again requires addressing
issues at other system layers.

Further side-channel attacks: Even if all legitimate user sensors are
successfully kept isolated from attackers, attackers can set up their
own power sensors, electromagnetic sensors, acoustic sensors, etc.
Keeping cryptographic operations physically separated from sensors tends
to make such attacks much more expensive but is often infeasible.
"Masking" cryptographic computations seems to help and can be
affordable, although the security of masking is difficult to evaluate
and there are many broken masked implementations. Currently lib25519
does not include any masked implementations, so presumably it is easily
breakable by power attacks in environments where attackers can see power
consumption.

Further attacks: lib25519 creates an Ed25519 signing nonce as a hash of
the message, a long-term secret, and new randomness (specifically, the
nonce is a keyed hash of the message, where the key is the hash of the
long-term secret and new randomness). The literature identifies various
advantages and disadvantages of including these hash inputs:

   * Including the message and a long-term secret protects against
     signing-time RNG failures. This is a standard feature of Ed25519
     signers.

   * To the extent that the RNG works, including new randomness has the
     advantage of stopping (e.g.) fault attacks that rely on a nonce
     being reused for multiple signatures of the same message.

   * Including new randomness has the disadvantage of requiring state
     for the RNG. However, lib25519 runs within an OS that in any case
     maintains state and provides an RNG.

   * Including new randomness also has the disadvantage of interfering
     with the use of test vectors. This disadvantage does not apply to
     lib25519: lib25519's test vectors already handle randomness.

lib25519 includes a few further steps that could be useful in stopping
fault attacks (for example, signature verification internally converts
invalid public keys to the key (...,26), which does not have a known
discrete logarithm), but in general lib25519 should be presumed
breakable by fault attacks.
