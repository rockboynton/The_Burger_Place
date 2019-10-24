#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "burger_place.h"
#include "test_burger_place.h"


int main(int argc, char* argv[]) {
    printf("The Burger Place\n");
    if (argc == 2) {
        if (!strcmp("--test", argv[1])) {
            burger_test_suite();
            return 0;
        } else {
            FILE* input = fopen(argv[1], "r");
            if (input == NULL) {
                printf("ERROR: File invalid\n");
                return -1;
            }
            simulate(input);
            fclose(input);
        }
    } else if (argc < 3 || argc > 4) {
        printf("ERROR: Please specify a single input file\n");
        return -1;
    }

    return 0;
}