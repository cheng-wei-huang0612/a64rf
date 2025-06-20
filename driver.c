#include <stdio.h>
#include <stdint.h>

extern void foo(uint64_t *dst, const uint64_t *src);

int main() {
    printf("Hello, world!\n");

    uint64_t src[2] = {3,1};
    uint64_t dst[2] = {0,0};


    foo(dst, src);

    printf("src: [%llu, %llu]\n", src[0], src[1]);
    printf("dst: [%llu, %llu]\n", dst[0], dst[1]);

    printf("Bye Bye, world!\n");
    return 0;
}