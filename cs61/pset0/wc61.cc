#include <cstdio>

int main() {
    unsigned long n = 0;
    while (true) {
        if (fgetc(stdin) == EOF) {
            break;
        }
        ++n;
    }
    fprintf(stdout, "%8lu\n", n);
}