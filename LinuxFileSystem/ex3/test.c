#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("Số lượng đối số: %d\n", argc);
    for (int i = 0; i < argc; ++i) {
        printf("Đối số thứ %d: %s\n", i, argv[i]);
    }
    return 0;
}