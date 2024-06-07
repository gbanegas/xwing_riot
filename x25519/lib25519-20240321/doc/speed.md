In the following speed table, smaller numbers are better.
The numbers are median single-core cycle counts on various microarchitectures.
Overclocking is disabled.

The table reports cycle counts from lib25519 and, for comparison,
OpenSSL and s2n-bignum.
For comparability to OpenSSL's speed-testing utility,
the OpenSSL cycle counts omit various OpenSSL overheads; see below for details.
The s2n-bignum and lib25519 cycle counts include all overheads.
There is also a lib25519+s2n line showing separate measurements of lib25519
after the optional pre-configuration `./use-s2n-bignum` step.


| μarch | software | X key | X dh | X batch | Ed key | Ed sign | Ed verif | Ed MSM |
| :---- | :------- | ----: | ---: | ------: | -----: | ------: | -------: | -----: |
| Golden Cove (2021) | <span class=openssl>OpenSSL</span> | <span class=openssl>119777</span> | <span class=openssl>103594</span> | | <span class=openssl>121526</span> | <span class=openssl>95750</span> | <span class=openssl>319234</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>23332</span> | <span class=lib25519>69037</span> | <span class=lib25519>49966</span> | <span class=lib25519>24373</span> | <span class=lib25519>28697</span> | <span class=lib25519>91956</span> | <span class=lib25519>37103
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>23889</span> | <span class=lib25519>68964</span> | <span class=lib25519>49907</span> | <span class=lib25519>24401</span> | <span class=lib25519>28030</span> | <span class=lib25519>93962</span> | <span class=lib25519>36701
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>24257</span> | <span class=s2n>75395</span> | | | | | |
| Firestorm (2020) | <span class=openssl>OpenSSL</span> | <span class=openssl>59900</span> | <span class=openssl>65400</span> | | <span class=openssl>60800</span> | <span class=openssl>55900</span> | <span class=openssl>195400</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>28500</span> | <span class=lib25519>57100</span> | <span class=lib25519>56750</span> | <span class=lib25519>28500</span> | <span class=lib25519>31300</span> | <span class=lib25519>204200</span> | <span class=lib25519>59900
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>21700</span> | <span class=lib25519>57900</span> | <span class=lib25519>56831</span> | <span class=lib25519>29500</span> | <span class=lib25519>32400</span> | <span class=lib25519>215900</span> | <span class=lib25519>61662
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>14300</span> | <span class=s2n>44200</span> | | | | | |
| Zen 3 (2020) | <span class=openssl>OpenSSL</span> | <span class=openssl>121785</span> | <span class=openssl>112526</span> | | <span class=openssl>124551</span> | <span class=openssl>111757</span> | <span class=openssl>372577</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>25621</span> | <span class=lib25519>73101</span> | <span class=lib25519>47967</span> | <span class=lib25519>26438</span> | <span class=lib25519>29800</span> | <span class=lib25519>111248</span> | <span class=lib25519>41567
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>25614</span> | <span class=lib25519>73250</span> | <span class=lib25519>47816</span> | <span class=lib25519>26476</span> | <span class=lib25519>29876</span> | <span class=lib25519>111301</span> | <span class=lib25519>41346
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>26238</span> | <span class=s2n>89699</span> | | | | | |
| Tiger Lake (2020) | <span class=openssl>OpenSSL</span> | <span class=openssl>116192</span> | <span class=openssl>119125</span> | | <span class=openssl>119341</span> | <span class=openssl>111360</span> | <span class=openssl>371294</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>26662</span> | <span class=lib25519>64680</span> | <span class=lib25519>21684</span> | <span class=lib25519>27321</span> | <span class=lib25519>31241</span> | <span class=lib25519>107766</span> | <span class=lib25519>39736
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>26245</span> | <span class=lib25519>64685</span> | <span class=lib25519>21695</span> | <span class=lib25519>27542</span> | <span class=lib25519>31152</span> | <span class=lib25519>108605</span> | <span class=lib25519>39347
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>26474</span> | <span class=s2n>83168</span> | | | | | |
| Zen 2 (2019) | <span class=openssl>OpenSSL</span> | <span class=openssl>131187</span> | <span class=openssl>114889</span> | | <span class=openssl>133766</span> | <span class=openssl>121192</span> | <span class=openssl>393580</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>27538</span> | <span class=lib25519>100750</span> | <span class=lib25519>73662</span> | <span class=lib25519>28448</span> | <span class=lib25519>31621</span> | <span class=lib25519>130793</span> | <span class=lib25519>46115
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>26700</span> | <span class=lib25519>94659</span> | <span class=lib25519>74817</span> | <span class=lib25519>28253</span> | <span class=lib25519>31487</span> | <span class=lib25519>130884</span> | <span class=lib25519>46111
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>27058</span> | <span class=s2n>92075</span> | | | | | |
| Goldmont (2016) | <span class=openssl>OpenSSL</span> | <span class=openssl>255650</span> | <span class=openssl>273638</span> | | <span class=openssl>269190</span> | <span class=openssl>228278</span> | <span class=openssl>746606</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>93894</span> | <span class=lib25519>280998</span> | <span class=lib25519>282937</span> | <span class=lib25519>182176</span> | <span class=lib25519>106552</span> | <span class=lib25519>348154</span> | <span class=lib25519>111511
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>76252</span> | <span class=lib25519>255310</span> | <span class=lib25519>258451</span> | <span class=lib25519>97018</span> | <span class=lib25519>106718</span> | <span class=lib25519>341734</span> | <span class=lib25519>97353
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>77436</span> | <span class=s2n>255312</span> | | | | | |
| Cortex-A72 (2016) | <span class=openssl>OpenSSL</span> | <span class=openssl>165596</span> | <span class=openssl>424757</span> | | <span class=openssl>173844</span> | <span class=openssl>134485</span> | <span class=openssl>423509</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>107170</span> | <span class=lib25519>331177</span> | <span class=lib25519>331403</span> | <span class=lib25519>108422</span> | <span class=lib25519>116220</span> | <span class=lib25519>407344</span> | <span class=lib25519>118316
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>66463</span> | <span class=lib25519>136554</span> | <span class=lib25519>136521</span> | <span class=lib25519>108048</span> | <span class=lib25519>115264</span> | <span class=lib25519>410675</span> | <span class=lib25519>117761
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>67271</span> | <span class=s2n>136516</span> | | | | | |
| Skylake (2015) | <span class=openssl>OpenSSL</span> | <span class=openssl>134951</span> | <span class=openssl>118458</span> | | <span class=openssl>138768</span> | <span class=openssl>124961</span> | <span class=openssl>411673</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>27802</span> | <span class=lib25519>83452</span> | <span class=lib25519>62451</span> | <span class=lib25519>28608</span> | <span class=lib25519>32026</span> | <span class=lib25519>107652</span> | <span class=lib25519>41742
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>27816</span> | <span class=lib25519>83223</span> | <span class=lib25519>63022</span> | <span class=lib25519>28583</span> | <span class=lib25519>31979</span> | <span class=lib25519>105726</span> | <span class=lib25519>41853
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>28806</span> | <span class=s2n>84561</span> | | | | | |
| Airmont (2015) | <span class=openssl>OpenSSL</span> | <span class=openssl>314248</span> | <span class=openssl>618875</span> | | <span class=openssl>326604</span> | <span class=openssl>276991</span> | <span class=openssl>852228</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>143716</span> | <span class=lib25519>449155</span> | <span class=lib25519>449333</span> | <span class=lib25519>151077</span> | <span class=lib25519>167509</span> | <span class=lib25519>555437</span> | <span class=lib25519>155354
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>115797</span> | <span class=lib25519>432042</span> | <span class=lib25519>432588</span> | <span class=lib25519>150556</span> | <span class=lib25519>168440</span> | <span class=lib25519>557483</span> | <span class=lib25519>155190
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>116864</span> | <span class=s2n>432414</span> | | | | | |
| Broadwell (2014) | <span class=openssl>OpenSSL</span> | <span class=openssl>128717</span> | <span class=openssl>121228</span> | | <span class=openssl>132360</span> | <span class=openssl>120321</span> | <span class=openssl>393241</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>29156</span> | <span class=lib25519>84649</span> | <span class=lib25519>73313</span> | <span class=lib25519>29705</span> | <span class=lib25519>33972</span> | <span class=lib25519>109784</span> | <span class=lib25519>41100
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>29034</span> | <span class=lib25519>87200</span> | <span class=lib25519>72483</span> | <span class=lib25519>29905</span> | <span class=lib25519>33799</span> | <span class=lib25519>109508</span> | <span class=lib25519>41852
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>31396</span> | <span class=s2n>87934</span> | | | | | |
| Haswell (2013) | <span class=openssl>OpenSSL</span> | <span class=openssl>134317</span> | <span class=openssl>163773</span> | | <span class=openssl>139345</span> | <span class=openssl>125387</span> | <span class=openssl>407967</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>41558</span> | <span class=lib25519>115276</span> | <span class=lib25519>76694</span> | <span class=lib25519>42365</span> | <span class=lib25519>46236</span> | <span class=lib25519>153852</span> | <span class=lib25519>58279
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>41508</span> | <span class=lib25519>117407</span> | <span class=lib25519>76569</span> | <span class=lib25519>42406</span> | <span class=lib25519>46859</span> | <span class=lib25519>155814</span> | <span class=lib25519>57725
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>45860</span> | <span class=s2n>160318</span> | | | | | |
| Cortex-A53 (2012) | <span class=openssl>OpenSSL</span> | <span class=openssl>271122</span> | <span class=openssl>523848</span> | | <span class=openssl>277838</span> | <span class=openssl>216810</span> | <span class=openssl>547938</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>152424</span> | <span class=lib25519>467492</span> | <span class=lib25519>466748</span> | <span class=lib25519>154103</span> | <span class=lib25519>163666</span> | <span class=lib25519>598089</span> | <span class=lib25519>173073
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>116946</span> | <span class=lib25519>163009</span> | <span class=lib25519>165112</span> | <span class=lib25519>153300</span> | <span class=lib25519>162717</span> | <span class=lib25519>600206</span> | <span class=lib25519>170632
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>120158</span> | <span class=s2n>163155</span> | | | | | |
| Core 2 (2006) | <span class=openssl>OpenSSL</span> | <span class=openssl>274293</span> | <span class=openssl>326943</span> | | <span class=openssl>282501</span> | <span class=openssl>240597</span> | <span class=openssl>741906</span> | |
| | <span class=lib25519>lib25519</span> | <span class=lib25519>95814</span> | <span class=lib25519>301014</span> | <span class=lib25519>299719</span> | <span class=lib25519>99243</span> | <span class=lib25519>108216</span> | <span class=lib25519>359289</span> | <span class=lib25519>105870
| | <span class=lib25519>lib25519+s2n</span> | <span class=lib25519>73170</span> | <span class=lib25519>262746</span> | <span class=lib25519>262705</span> | <span class=lib25519>99027</span> | <span class=lib25519>108315</span> | <span class=lib25519>360225</span> | <span class=lib25519>105163
| | <span class=s2n>s2n-bignum</span> | <span class=s2n>80703</span> | <span class=s2n>262971</span> | | | | | |


Microarchitectures are listed in reverse chronological order of when they were introduced.
Each library is assigned one foreground color in the table.

In the lib25519 distribution,
`command/lib25519-speed.c` measures lib25519;
`benchmarks/*-*` is the output of `lib25519-speed` on various machines;
`speedcomparison/openssl/*` has code to measure OpenSSL, and measurements from various machines;
`speedcomparison/s2n/*` has code to measure s2n-bignum, and measurements from various machines;
and `autogen/md-speed` extracts the table from those measurements.
OpenSSL benchmarks use version 3.2.1 (2024.01.30);
s2n-bignum benchmarks use commit acbb18e6343f12a7944de72c1ec0991739600f8c (2024.03.18).

The table reports only median cycle counts;
see the full output files
for differences between multiple measurements and the median.
The table reports the following major operations:

* "X key": Generating an X25519 public key and secret key.
    This is `dh_x25519_keypair selected 32` in the `lib25519-speed` output
    (`lib25519_dh_keypair` in the stable API).

    For s2n-bignum,
    this is `x25519-keygen` in the `s2n25519speed` output,
    measuring the cost of `curve25519_x25519base_byte_alt`,
    or `curve25519_x25519base_byte` on machines where that works and is faster.

    For OpenSSL,
    this is `x25519-keygen-main` in the `openssl25519speed` output,
    measuring the cost of `EVP_PKEY_Q_keygen(0,0,"X25519")`.
    This does not include small OpenSSL overheads for converting the public key and secret key to storage format.

* "X dh":
    Generating an X25519 shared secret.
    This is `dh_x25519 selected 32` in the `lib25519-speed` output
    (`lib25519_dh` in the stable API).

    For s2n-bignum,
    this is `x25519-dh` in the `s2n25519speed` output,
    measuring the cost of `curve25519_x25519_byte_alt`,
    or `curve25519_x25519_byte` on machines where that works and is faster.

    For OpenSSL,
    this is `x25519-dh-main` in the `openssl25519speed` output,
    measuring the cost of `EVP_PKEY_derive`
    (as in OpenSSL's speed-testing utility).
    This does not include the cost of `EVP_PKEY_new_raw_public_key`
    to decode the public key (8376 cycles on Tiger Lake),
    `EVP_PKEY_CTX_new` and `EVP_PKEY_derive_init` and `EVP_PKEY_derive_set_peer` for initialization
    (together 7660 cycles on Tiger Lake),
    and 
    `EVP_PKEY_new_raw_private_key` to decode the secret key if it is not decoded already
    (113498 cycles on Tiger Lake).

* "X batch":
    Cost _per secret_ of generating 16 separate shared secrets.
    This is `nPbatch_montgomery25519 selected 16` in the `lib25519-speed` output _divided by 16_.

* "Ed key": Generating an Ed25519 public key and secret key.
    This is `sign_ed25519_keypair selected 32` in the `lib25519-speed` output
    (`lib25519_sign_keypair` in the stable API).

    For OpenSSL,
    this is `ed25519-keygen-main` in the `openssl25519speed` output,
    measuring the cost of `EVP_PKEY_Q_keygen(0,0,"ED25519")`.
    This does not include small OpenSSL overheads for converting the public key and secret key to storage format.

* "Ed sign": Generating an Ed25519 signature of a 59-byte message.
    This is `sign_ed25519 selected 59` in the `lib25519-speed` output
    (`lib25519_sign` in the stable API).

    For OpenSSL,
    this is `ed25519-sign-main` in the `openssl25519speed` output,
    measuring the cost of `EVP_DigestSign`
    (as in OpenSSL's speed-testing utility).
    This does not include the cost of 
    `EVP_MD_CTX_new` and
    `EVP_DigestSignInit`
    (together 6258 cycles on Tiger Lake),
    and `EVP_PKEY_new_raw_private_key` to decode the secret key if it is not decoded already
    (116808 cycles on Tiger Lake).

* "Ed verif": Verifying an Ed25519 signature and recovering a 59-byte message.
    This is `sign_ed25519_open selected 59` in the `lib25519-speed` output
    (`lib25519_sign_open` in the stable API).

    For OpenSSL,
    this is `ed25519-verify-main` in the `openssl25519speed` output,
    measuring the cost of `EVP_DigestVerify`
    (as in OpenSSL's speed-testing utility).
    This does not include the cost of 
    `EVP_MD_CTX_new` and
    `EVP_DigestVerifyInit`
    (together 6054 cycles on Tiger Lake),
    and `EVP_PKEY_new_raw_public_key`
    to decode the public key being used for verification
    (9560 cycles on Tiger Lake).

* "Ed MSM": Cost _per point_ of multi-scalar multiplication with 16 points and 16 full-size scalars.
    This is `multiscalar_ed25519 selected 16` in the `lib25519-speed` output _divided by 16_.
