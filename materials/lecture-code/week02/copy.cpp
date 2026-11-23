#include <iostream>


void copy (char *to, const char *from) {
    while (*from != '\0') {
        *to = *from;
        to++;
        from++;
    }
    *to = '\0';
}


int main() {

    const char *src = "Hello, World!";
    char dest[50];

    copy(dest, src);

    return 0;
}
