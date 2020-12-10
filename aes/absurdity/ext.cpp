#include <cstdint>
#include <cstring>
#include <cstdio>
#include <fstream>

struct wbroundcontrolstate {
    uint8_t xor_te1[16][256][256];
    uint8_t xor_te2[16][256][256];
    uint8_t xor_te3[16][256][256];
};

static constexpr int statec = 8;

static wbroundcontrolstate controls[10][statec];
static uint8_t rstates[statec][16];

void run_impl (wbroundcontrolstate(&statearr)[statec], uint8_t* outptr) {
    for (int i = 0; i < statec; i++) {
        auto &r = rstates[i];
        auto &c = statearr[i];

        uint8_t a[16] {r[0], r[5], r[10], r[15], r[4], r[9], r[14], r[3], r[8], r[13], r[2], r[7], r[12], r[1], r[6], r[11] };
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
            for (auto & rstate : rstates)
                outptr[i] ^= rstate[i];
        }
    }
}

int main(int argc, char** argv) {
    std::ifstream inf("funnytables", std::ios::binary);
    inf.read(reinterpret_cast<char*>(controls), sizeof(controls));

    for (auto & rstate : rstates) {
        for (int i = 0; i < 16; i++) {
            char k[3]{};
            memcpy(k, &argv[1][i * 2], 2);
            rstate[i] = std::stoi(k, nullptr, 16);
        }
    }

    for (int j = 0; j < 8; j++)
        run_impl(controls[j], nullptr);

    uint8_t r[16]{};
    run_impl(controls[8], r);

    uint8_t os[16] {r[0], r[5], r[10], r[15], r[4], r[9], r[14], r[3], r[8], r[13], r[2], r[7], r[12], r[1], r[6], r[11] };

    for (unsigned char c : os)
        printf("%02X", c);

    printf("\n");
}