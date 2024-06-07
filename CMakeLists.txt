cmake_minimum_required(VERSION 3.10)
project(xwing_riot C)

set(CMAKE_C_STANDARD 11)

add_executable(xwing_riot test/test_xkem_functionality.c xkem.c test/cpucycles.c test/speed_print.c
        mlkem/reduce.c mlkem/ntt.c mlkem/poly.c mlkem/polyvec.c mlkem/randombytes.c mlkem/fips202.c mlkem/cbd.c
        mlkem/indcpa.c mlkem/kem.c mlkem/symmetric-fips202.c
        )

target_link_libraries(xwing_riot PRIVATE 25519)
target_link_libraries(xwing_riot PRIVATE crypto)
target_link_libraries(xwing_riot PRIVATE randombytes)