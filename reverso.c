/**
 * @author Halle Countryman
 * @brief Demo reverse commands in GDB
 */

#include <stdio.h>

void foo() {
    int a = 1;
    int b = 2;
    int c = a + b;
    printf("%d + %d = %d\n", a, b, c);
}

int main(int argc, char **argv) {
    foo();
    return 0;
}