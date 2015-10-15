#include <stdio.h>

int main(int argc, char const *argv[]) {
    // unsigned char r = 255;
    // unsigned char g = 16;
    // unsigned char b = 145;
    int i = 1;
    i = i << 24;
    printf("%d\n", i);
    // int sum = r + i;
    // sum = sum << 8;
    // sum = sum + g;
    // sum = sum << 8;
    // sum = sum + b;
    // printf("%d\n", r);
    // printf("%d\n", g);
    // printf("%d\n", b);
    // printf("0x%x\n", sum);
    // unsigned char re = sum >> 16;
    // unsigned char gr = (sum >> 8) - (re << 8);
    // unsigned char bl = sum - (gr << 8) - (re << 16);
    // printf("%d\n", re);
    // printf("%d\n", gr);
    // printf("%d\n", bl);
    return 0;
}
