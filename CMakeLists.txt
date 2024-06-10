cmake_minimum_required(VERSION 3.10)
project(xwing_riot C)

set(CMAKE_C_STANDARD 11)

add_executable(xwing_riot test/test_xkem_functionality.c xkem.c test/cpucycles.c test/speed_print.c
        mlkem/reduce.c mlkem/ntt.c mlkem/poly.c mlkem/polyvec.c mlkem/randombytes.c mlkem/fips202.c mlkem/cbd.c
        mlkem/indcpa.c mlkem/kem.c mlkem/symmetric-fips202.c
        ed255/burn.c ed255/burnstack.c ed255/ed.c ed255/ed25519-sha512.c ed255/fld.c ed255/sc.c ed255/sha512.c ed255/x25519.c
        ed255/x25519.h
)

#target_link_libraries(xwing_riot PRIVATE 25519)
target_link_libraries(xwing_riot PRIVATE crypto)



add_executable(255tmp main.c ed255/burn.c ed255/burnstack.c ed255/ed.c ed255/ed25519-sha512.c ed255/fld.c ed255/sc.c ed255/sha512.c ed255/x25519.c
        ed255/x25519.h)

target_link_libraries(255tmp PRIVATE 25519)
target_link_libraries(255tmp PRIVATE crypto)
target_link_libraries(255tmp PRIVATE randombytes)