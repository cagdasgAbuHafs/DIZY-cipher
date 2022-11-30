#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sboxCnt_dizy80 24
#define ROUNDS 15


unsigned char S[32] = {
        0x00, 0x04, 0x0e, 0x09, 0x0d, 0x0b, 0x1e, 0x1b, 0x1c, 0x14, 0x13, 0x18, 0x17, 0x1d, 0x05, 0x0c,
        0x0f, 0x11, 0x08, 0x15, 0x03, 0x1f, 0x19, 0x06, 0x10, 0x02, 0x16, 0x07, 0x1a, 0x0a, 0x01, 0x12
};

void sBox(unsigned char *sboxes, int count) {
    int k;
    for (k = 0; k < count; k++) {
        sboxes[k] = S[sboxes[k]];
    }
}

void lfsr_4(unsigned char *lfsr_consts, unsigned char *initial_value) {

    int i;
    unsigned char fb;
    for (i = 0; i < 15; i++) {
        unsigned char output = (initial_value[0] << 3 | initial_value[1] << 2 | initial_value[2] << 1 |
                                initial_value[3]);
        lfsr_consts[i] = output;

        fb = initial_value[0] ^ initial_value[3];
        initial_value[0] = initial_value[1];
        initial_value[1] = initial_value[2];
        initial_value[2] = initial_value[3];
        initial_value[3] = fb;
    }
}

void matrix(unsigned char *sboxes) {
    int i;
    unsigned char temp_sboxes[6];
    for (i = 0; i < 24; i += 6) {
        temp_sboxes[i % 6] = (((sboxes[i + 1] & 8) << 1) ^ ((sboxes[i + 4] & 4) << 2)) +
                             ((sboxes[i + 3] & 8) ^ ((sboxes[i + 3] & 2) << 2)) +
                             (((sboxes[i] & 16) >> 2) ^ ((sboxes[i + 3] & 2) << 1)) + ((sboxes[i + 3] & 16) >> 3) +
                             ((sboxes[i] & 8) >> 3);
        temp_sboxes[(i % 6) + 1] = (((sboxes[i + 1] & 4) << 2) ^ ((sboxes[i + 5] & 4) << 2)) +
                                   (((sboxes[i + 4] & 16) >> 1) ^ ((sboxes[i + 2] & 2) << 2)) +
                                   ((sboxes[i] & 4) ^ ((sboxes[i + 4] & 2) << 1)) + ((sboxes[i + 4] & 8) >> 2) +
                                   ((sboxes[i + 2] & 8) >> 3);
        temp_sboxes[(i % 6) + 2] = (((sboxes[i + 2] & 4) << 2) ^ ((sboxes[i + 3] & 4) << 2)) +
                                   ((sboxes[i + 5] & 8) ^ ((sboxes[i] & 2) << 2)) +
                                   (((sboxes[i + 2] & 16) >> 2) ^ ((sboxes[i + 5] & 2) << 1)) +
                                   ((sboxes[i + 5] & 16) >> 3) + ((sboxes[i + 1] & 16) >> 4);
        temp_sboxes[(i % 6) + 3] = (((sboxes[i] & 4) << 2) ^ ((sboxes[i + 5] & 4) << 2)) +
                                   ((sboxes[i + 4] & 8) ^ ((sboxes[i + 1] & 1) << 3)) +
                                   (((sboxes[i + 2] & 8) >> 1) ^ ((sboxes[i + 4] & 1) << 2)) +
                                   ((sboxes[i + 3] & 8) >> 2) + ((sboxes[i] & 16) >> 4);
        temp_sboxes[(i % 6) + 4] = (((sboxes[i + 1] & 4) << 2) ^ ((sboxes[i + 3] & 4) << 2)) +
                                   (((sboxes[i + 3] & 16) >> 1) ^ ((sboxes[i + 2] & 1) << 3)) +
                                   (((sboxes[i] & 8) >> 1) ^ ((sboxes[i + 5] & 1) << 2)) + ((sboxes[i + 4] & 16) >> 3) +
                                   ((sboxes[i + 2] & 16) >> 4);
        temp_sboxes[(i % 6) + 5] = (((sboxes[i + 2] & 4) << 2) ^ (sboxes[i + 5] & 16)) +
                                   (((sboxes[i + 4] & 4) << 1) ^ ((sboxes[i] & 1) << 3)) +
                                   (((sboxes[i + 1] & 16) >> 2) ^ ((sboxes[i + 3] & 1) << 2)) +
                                   ((sboxes[i + 5] & 8) >> 2) + ((sboxes[i + 1] & 8) >> 3);
        for (int j = 0; j < 6; ++j) {
            sboxes[i] = temp_sboxes[j];
        }
    }
}

void key_add(const unsigned char *key, unsigned char *sboxes, unsigned char loop_count,
             unsigned char key_offSet) {
    int i;
    for (i = 0; i < loop_count; ++i) {
        sboxes[i * 4] ^= (key[i + key_offSet] & 192) >> 6;
        sboxes[(i * 4) + 1] ^= (key[i + key_offSet] & 48) >> 4;
        sboxes[(i * 4) + 2] ^= (key[i + key_offSet] & 12) >> 2;
        sboxes[(i * 4) + 3] ^= (key[i + key_offSet] & 3);
    }
}

void iv_add(const unsigned char *iv, unsigned char *sboxes, unsigned char loop_count,
            unsigned char iv_offSet) {
    int i;
    for (i = 0; i < loop_count; ++i) {
        sboxes[i * 4] ^= (iv[i + iv_offSet] & 192) >> 6;
        sboxes[(i * 4) + 1] ^= (iv[i + iv_offSet] & 48) >> 4;
        sboxes[(i * 4) + 2] ^= (iv[i + iv_offSet] & 12) >> 2;
        sboxes[(i * 4) + 3] ^= (iv[i + iv_offSet] & 3);
    }
}

void const_add_dizy80(unsigned char round_consts, unsigned char *sboxes) {
    unsigned char sbox_cnt;
    for (sbox_cnt = 0; sbox_cnt < sboxCnt_dizy80; sbox_cnt++) {
        sboxes[sbox_cnt] ^= (round_consts);
    }
}

void sboxes_to_output(const unsigned char sboxes[24]) {
    unsigned char states[4];
    states[0] = ((sboxes[0] & 16) << 3) + ((sboxes[0] & 2) << 5) + ((sboxes[1] & 8) << 2) + ((sboxes[1] & 1) << 4) +
                ((sboxes[2] & 4) << 1) + ((sboxes[3] & 16) >> 2) + (sboxes[3] & 2) + ((sboxes[4] & 8) >> 3);
    states[1] = ((sboxes[4] & 1) << 7) + ((sboxes[5] & 4) << 4) + ((sboxes[6] & 16) << 1) + ((sboxes[6] & 2) << 3) +
                (sboxes[7] & 8) + ((sboxes[7] & 1) << 2) + ((sboxes[8] & 4) >> 1) + ((sboxes[9] & 16) >> 4);
    states[2] = ((sboxes[9] & 2) << 6) + ((sboxes[10] & 8) << 3) + ((sboxes[10] & 1) << 5) + ((sboxes[11] & 4) << 2) +
                ((sboxes[12] & 16) >> 1) + ((sboxes[12] & 2) << 1) + ((sboxes[13] & 8) >> 2) + (sboxes[13] & 1);
    states[3] = ((sboxes[14] & 4) << 5) + ((sboxes[15] & 16) << 2) + ((sboxes[15] & 2) << 4) + ((sboxes[16] & 8) << 1) +
                ((sboxes[16] & 1) << 3) + (sboxes[17] & 4) + ((sboxes[18] & 16) >> 3) + ((sboxes[18] & 2) >> 1);

    printf("\nState: %02x%02x%02x%02x\n", states[0], states[1], states[2], states[3]); //32 bits keystream output
}

void permute_classes(unsigned char *sboxes) {
    unsigned char temp[3];

    temp[0] = sboxes[6];
    temp[1] = sboxes[7];
    temp[2] = sboxes[8];

    sboxes[6] = sboxes[3];
    sboxes[7] = sboxes[4];
    sboxes[8] = sboxes[5];

    sboxes[3] = sboxes[12];
    sboxes[4] = sboxes[13];
    sboxes[5] = sboxes[14];

    sboxes[12] = temp[0];
    sboxes[13] = temp[1];
    sboxes[14] = temp[2];

    temp[0] = sboxes[9];
    temp[1] = sboxes[10];
    temp[2] = sboxes[11];

    sboxes[9] = sboxes[15];
    sboxes[10] = sboxes[16];
    sboxes[11] = sboxes[17];

    sboxes[15] = sboxes[18];
    sboxes[16] = sboxes[19];
    sboxes[17] = sboxes[20];

    sboxes[18] = temp[0];
    sboxes[19] = temp[1];
    sboxes[20] = temp[2];
}

void dizy80_ksg(unsigned char *key, unsigned char *round_consts, unsigned char *iv) {
    unsigned char *sboxes = calloc(sboxCnt_dizy80, sizeof(char));
    int l;
    int i;
    for (l = 0; l < 3; l++) {
        for (i = 0; i < ROUNDS; i++) {
            if (l == 0) {
                if (i == 0 || i == 1) {
                    key_add(key, sboxes, (-2 * i) + 6, i * 6);
                }
            }
            if (l == 1) {
                if (i == 0 || i == 1) {
                    iv_add(iv, sboxes, (-2 * i) + 6, i * 6);
                }
            }
            const_add_dizy80(round_consts[i], sboxes);
            sBox(sboxes, sboxCnt_dizy80);
            matrix(sboxes);
            permute_classes(sboxes);
        }
        sboxes_to_output(sboxes);

    }
}



int main() {
    clock_t t;
    t = clock();

    unsigned char *round_consts = calloc(ROUNDS, sizeof(char));
    unsigned char init_poly[4] = {1, 0, 0, 0};
    unsigned char key[10] = {1, 0, 1, 1, 0, 1, 1, 0, 1, 1};
    unsigned char iv[10] = {1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    lfsr_4(round_consts, init_poly);
    dizy80_ksg(key, round_consts, iv);

    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
    printf("Execute time: %f", time_taken);
    return 0;

}


