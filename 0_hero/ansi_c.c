#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#define tab_to_spaces 4

char * detab(char * str) {
    char * res;
    int ptr = 0;
    int res_ctr = 0;
    for(; str[ptr] != '\0'; ptr++, res_ctr++) {
        if (str[ptr] == '\t') {
            int ctr_spaces = 0;
            while (ctr_spaces < tab_to_spaces) {
                res[res_ctr] = ' ';
                res_ctr ++;
                ctr_spaces += 1;
            }
        } else {
            res[res_ctr] = str[ptr];
        }
    }
    res[res_ctr] = '\0';
    return res;
}
/*
int htoi(char * str) {
    u_int64_t buffer_1;
    char buffer_2;
    int isScanned = sscanf(str, "%", SCNd64 "%c", &buffer_1, &buffer_2);
    if(isScanned > 0) {
        return (int)buffer_1;
    }
    return 0;
}*/

const int LSB(const int idx) {
	return idx & (-1 * idx);
}

int bitcount(unsigned x) {
    if (x == 0) {
        return 0;
    }
    int b = 1;
    while(x != 0) {
        if (x &= (x - 1)) {
            b++;
        }
        
    }
    return b;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return (x >> (p + 1 - n) | (y & ((1 << n) - 1)));
}
