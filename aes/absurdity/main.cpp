#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <random>

uint8_t sbox[256] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
        0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
        0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
        0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
        0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
        0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
        0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
        0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
        0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
        0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
        0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
        0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
        0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
        0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
        0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
        0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
        0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

uint8_t invsbox[256] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
        0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
        0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
        0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
        0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
        0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
        0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
        0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
        0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
        0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
        0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
        0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
        0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
        0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
        0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
        0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
        0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,
};

void gsbox(uint8_t *r) {
    for (int i = 0; i < 16; i++)
        r[i] = sbox[r[i]];
}

void gshiftrow(uint8_t *r, int i, int n) {
    uint8_t tmp[4];
    for (int j = 0; j < 4; j++)
        tmp[j] = r[i + j * 4];
    for (int j = 0; j < 4; j++)
        r[i + j * 4] = tmp[(j + n) % 4];
}

void gshift(uint8_t *r) {
    gshiftrow(r, 1, 1);
    gshiftrow(r, 2, 2);
    gshiftrow(r, 3, 3);
}

void gshiftinv(uint8_t *r) {
    gshiftrow(r, 1, 4 - 1);
    gshiftrow(r, 2, 4 - 2);
    gshiftrow(r, 3, 4 - 3);
}

uint8_t gmul2(uint8_t v) {
    const auto h = (uint8_t) ((signed char) v >> 7);
    auto r = v << 1;
    r ^= 0x1B & h;
    return r;
}

uint8_t gmul3(uint8_t v) {
    return gmul2(v) ^ v;
}

void gmix_column(uint8_t *r) {
    uint8_t a[4];
    uint8_t b[4];
    uint8_t c;
    uint8_t h;

    for (c = 0; c < 4; c++) {
        a[c] = r[c];

        h = (uint8_t) ((signed char) r[c] >> 7);
        b[c] = r[c] << 1;
        b[c] ^= 0x1B & h;
    }

    r[0] = (b[1] ^ a[1]) ^ b[0] ^ a[3] ^ a[2]; /* 3 * a1  +  2 * a0  +  a3 + a2 */
    r[1] = (b[2] ^ a[2]) ^ b[1] ^ a[0] ^ a[3]; /* 3 * a2  +  2 * a1  +  a0 + a3 */
    r[2] = (b[3] ^ a[3]) ^ b[2] ^ a[1] ^ a[0]; /* 3 * a3  +  2 * a2  +  a1 + a0 */
    r[3] = (b[0] ^ a[0]) ^ b[3] ^ a[2] ^ a[1]; /* 3 * a0  +  2 * a3  +  a2 + a1 */
}

void grkey(uint8_t *r, uint8_t *k) {
    for (int c = 0; c < 16; c++) {
        r[c] ^= k[c];
    }
}

uint64_t mod_inverse(uint64_t a) {
    uint64_t x;
    x = 3 * a ^ 2;       //  5 bits
    x *= 2 - a * x;        // 10
    x *= 2 - a * x;        // 20
    x *= 2 - a * x;        // 40 -- 32 low bits
    x *= 2 - a * x;        // 80
    return x;
}

struct wbroundcontrolstate {
    // total size: big
    uint8_t xor_te1[16][256][256];
    uint8_t xor_te2[16][256][256];
    uint8_t xor_te3[16][256][256];
};

struct wbroundbuilderstate {
    struct tbox {
        uint8_t tbox[256];

        uint8_t ilbox[256];
        uint8_t lbox[256];

        uint8_t decode(uint8_t x) {
            return ilbox[tbox[x]];
        }
    };

    tbox tp1[16];
    tbox tp2[16];
    tbox tp3[16];
};

struct rclut {
    uint8_t rand_lut[13][256];
    uint8_t rand_ilut[13][256];
};

std::random_device rnd{};
 void generatecontrol(int i, uint8_t* roundkey, wbroundcontrolstate& zstate, wbroundbuilderstate& bstate, rclut& lut) {
     for (int j = 0; j < 16; j++) {
         auto &tb1 = bstate.tp1[j];
         auto &tb2 = bstate.tp2[j];
         auto &tb3 = bstate.tp3[j];

         auto tbn = {&tb1, &tb2, &tb3};
         for (auto tb : tbn) {
             for (int x = 0; x < 256; x++)
                 tb->lbox[x] = x;

             std::shuffle(tb->lbox, tb->lbox + 256, rnd);

             for (int x = 0; x < 256; x++)
                 tb->ilbox[tb->lbox[x]] = x;
         }

         for (int k = 0; k < 256; k++) {
             tb1.tbox[k] = sbox[roundkey[16 * i + j] ^ (uint8_t) k];
             if (i == 9)
                 tb1.tbox[k] ^= roundkey[16 * 10 + j];

             tb2.tbox[k] = gmul2(tb1.tbox[k]);
             tb3.tbox[k] = gmul3(tb1.tbox[k]);

             tb1.tbox[k] = tb1.lbox[tb1.tbox[k]];
             tb2.tbox[k] = tb2.lbox[tb2.tbox[k]];
             tb3.tbox[k] = tb3.lbox[tb3.tbox[k]];
         }
     }

     uint8_t flut[16];
     for (int j = 0; j < 4; j++) {
         flut[j * 4 + 0] = j * 4 + 3;
         flut[j * 4 + 1] = j * 4 + 0;
         flut[j * 4 + 2] = j * 4 + 1;
         flut[j * 4 + 3] = j * 4 + 2;
     }

     for (int j = 0; j < 16; j++) {
         for (int k = 0; k < 256; k++) {
             for (int l = 0; l < 256; l++) {
                 auto xk = k;
                 auto xl = l;

                 if (i != 0) {
                     xk = lut.rand_ilut[i + 3][xk];
                     xl = lut.rand_ilut[i + 3][xl];
                 }

                 zstate.xor_te1[j][k][l] = lut.rand_lut[0][bstate.tp1[j].decode(xk) ^ bstate.tp1[flut[j]].decode(xl)];
                 zstate.xor_te3[j][k][l] = lut.rand_lut[1][bstate.tp3[j].decode(xk) ^ lut.rand_ilut[0][l]];
                 zstate.xor_te2[j][k][l] = bstate.tp2[j].decode(xk) ^ lut.rand_ilut[1][l];

                 if (i != 8)
                     zstate.xor_te2[j][k][l] = lut.rand_lut[i + 4][zstate.xor_te2[j][k][l]];
             }
         }
     }
 }
template<int rc>
struct wbroundstate_i {
    constexpr static auto num_states = rc;

    wbroundcontrolstate controls[rc]{};
    wbroundbuilderstate builders[rc]{};

    void setup(int i, uint8_t* roundkey, rclut* rcluts) {
        for (int j = 0; j < rc; j++)
            generatecontrol(i, roundkey, controls[j], builders[j], rcluts[j]);
    }

    void finalize(wbroundstate_i* last) {
        static uint8_t outx[16][256][rc]{};

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 256; j++) {
                uint8_t rv = 0;
                for (int k = 0; k < rc - 1; k++) {
                    outx[i][j][k] = rnd();
                    rv ^= outx[i][j][k];
                }
                outx[i][j][rc - 1] = rv;
            }
        }


        for (int x = 0; x < rc; x++) {
            auto &zstate = controls[x];
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 256; k++) {
                        auto& z = zstate.xor_te2[i][j][k];
                        z = (last->builders[x].tp1[i].decode(z) & (1U << x)) ^ outx[i][z][x];
                    }
                }
            }
        }
    }

    void run(uint8_t states[][16], uint8_t* outptr) {
        for (int i = 0; i < num_states; i++) {
            auto &r = states[i];
            auto &c = controls[i];

            uint8_t a[16];
            memcpy(a, r, sizeof(a));
            gshift(a);

            for (int j = 0; j < 4; j++) {
                r[j * 4 + 0] = c.xor_te2[j * 4 + 0][a[j * 4 + 0]][c.xor_te3[j * 4 + 1][a[j * 4 + 1]][c.xor_te1[j * 4 + 3][a[j * 4 + 3]][a[j * 4 + 2]]]];
                r[j * 4 + 1] = c.xor_te2[j * 4 + 1][a[j * 4 + 1]][c.xor_te3[j * 4 + 2][a[j * 4 + 2]][c.xor_te1[j * 4 + 0][a[j * 4 + 0]][a[j * 4 + 3]]]];
                r[j * 4 + 2] = c.xor_te2[j * 4 + 2][a[j * 4 + 2]][c.xor_te3[j * 4 + 3][a[j * 4 + 3]][c.xor_te1[j * 4 + 1][a[j * 4 + 1]][a[j * 4 + 0]]]];
                r[j * 4 + 3] = c.xor_te2[j * 4 + 3][a[j * 4 + 3]][c.xor_te3[j * 4 + 0][a[j * 4 + 0]][c.xor_te1[j * 4 + 2][a[j * 4 + 2]][a[j * 4 + 1]]]];
            }
        }

        if (outptr) {
            for (int i = 0; i < 16; i++) {
                outptr[i] = 0;
                for (int j = 0; j < num_states; j++)
                    outptr[i] ^= states[j][i];
            }
        }
    }
};

static const uint8_t Rcon[11] = { 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

// This function produces Nb(Nr+1) round keys. The round keys are used in each round to decrypt the states.
// (copy-pasted from somewhere else which is kind of obvious due to the difference in style)
static void KeyExpansion(uint8_t* RoundKey, const uint8_t* Key) {
    unsigned i, j, k;
    uint8_t tempa[4]; // Used for the column/row operations

    // The first round key is the key itself.
    for (i = 0; i < 4; ++i) {
        RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
        RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
        RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
        RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
    }

    // All other round keys are found from the previous round keys.
    for (i = 4; i < 4 * (10 + 1); ++i) {
        {
            k = (i - 1) * 4;
            tempa[0] = RoundKey[k + 0];
            tempa[1] = RoundKey[k + 1];
            tempa[2] = RoundKey[k + 2];
            tempa[3] = RoundKey[k + 3];

        }

        if (i % 4 == 0) {
            // This function shifts the 4 bytes in a word to the left once.
            // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

            // Function RotWord()
            {
                const uint8_t u8tmp = tempa[0];
                tempa[0] = tempa[1];
                tempa[1] = tempa[2];
                tempa[2] = tempa[3];
                tempa[3] = u8tmp;
            }

            // SubWord() is a function that takes a four-byte input word and
            // applies the S-box to each of the four bytes to produce an output word.

            // Function Subword()
            {
                tempa[0] = sbox[tempa[0]];
                tempa[1] = sbox[tempa[1]];
                tempa[2] = sbox[tempa[2]];
                tempa[3] = sbox[tempa[3]];
            }

            tempa[0] = tempa[0] ^ Rcon[i / 4];
        }
        j = i * 4;
        k = (i - 4) * 4;
        RoundKey[j + 0] = RoundKey[k + 0] ^ tempa[0];
        RoundKey[j + 1] = RoundKey[k + 1] ^ tempa[1];
        RoundKey[j + 2] = RoundKey[k + 2] ^ tempa[2];
        RoundKey[j + 3] = RoundKey[k + 3] ^ tempa[3];
    }
}

const uint8_t key[] = { 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB };

int main() {
    srand(time(nullptr));

    uint8_t round_key[16 * 11];
    KeyExpansion(round_key, key);

    //printf("LRK: ");
    //for (int i = 0; i < 16; i++)
    //    printf("%02X", round_key[10 * 16 + i]);
    //printf("\n");

    {
        uint8_t state[16]{};

        for (int i = 1; i <= 9; i++) {
            grkey(state, &round_key[16 * (i - 1)]);
            gshift(state);
            gsbox(state);
            gmix_column(state);
            gmix_column(state + 4);
            gmix_column(state + 8);
            gmix_column(state + 12);
        }

        grkey(state, &round_key[16 * 9]);
        gsbox(state);
        gshift(state);
        grkey(state, &round_key[16 * 10]);

        for (unsigned char i : state)
            printf("%02X", i);

        printf("\n");
    }

    /*
        for i = 0, 8 do
            ShiftRows
            AddRoundKey + SubBytes + MixColumns
        end

        ShiftRows
        AddRoundKey + SubBytes + MixColumns + AddRoundKey + SubBytes + AddRoundKey

        ShiftRows
     */

    for (int i = 0; i < 10; i++) {
        if (i == 9)
            gshiftinv(&round_key[16 * 10]);
        else
            gshift(&round_key[16 * i]);
    }

    using wbroundstate = wbroundstate_i<8>;

    static rclut rcluts[wbroundstate::num_states]{};

    for (auto &rclut : rcluts) {
        for (int i = 0; i < sizeof(rclut.rand_lut) / sizeof(rclut.rand_lut[0]); i++) {
            for (int x = 0; x < 256; x++)
                rclut.rand_lut[i][x] = x;

            std::shuffle(rclut.rand_lut[i], rclut.rand_lut[i] + 256, rnd);

            for (int x = 0; x < 256; x++)
                rclut.rand_ilut[i][rclut.rand_lut[i][x]] = x;
        }
    }

    static wbroundstate states[10]{};
    for (int i = 0; i < 10; i++)
        states[i].setup(i, round_key, rcluts);

    states[8].finalize(&states[9]);

    static wbroundcontrolstate controls[10][8];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 8; j++)
            controls[i][j] = states[i].controls[j];

    std::ofstream out("funnytables", std::ios::binary);
    out.write(reinterpret_cast<char *>(controls), sizeof(controls));
    out.flush();

    //for (int i = 0; i < 50000; i++)
    {
        static uint8_t rstates[wbroundstate::num_states][16]{};
        memset(rstates, 0, wbroundstate::num_states * 16);

        uint8_t os[16]{};
        for (int j = 0; j < 8; j++)
            states[j].run(rstates, nullptr);

        //if (i != 0) {
        //    auto x1 = rand() % 16, x2 = rand() & 0xFF;
        //    for (auto& s : rstates)
        //        s[x1] ^= x2;
        //}

        states[8].run(rstates, os);
        gshift(os);

        for (unsigned char c : os)
            printf("%02X", c);

        printf("\n");
    }
}