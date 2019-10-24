/**
 * @file main.c
 * @author Rock Boynton (boyntonrl@msoe.edu)
 * @brief Main for simulating a burger shop
 * @version 0.1
 * @date 2019-10-22
 * 
 * INTRODUCTION: 
 *  The purpose of this lab is to practice implementing multithreading in C
 *  programs. It simulates a burger shop where there are a ccertain number of
 *  cooks, fryers, and customers per simulation. Each entity can be a thread,
 *  with its corresponding thread routine determined by its action. Burger cooks
 *  have a burger_cook_thread, etc. 
 * 
 * The cooks take a certain amount of time to cook their food, which is modeled
 * by a usleep call
 * 
 * DESIGN:
 * 
 * BUILD INSTRUCTIONS:
 * 
 * ANALYSIS:
 * 
 * CONCLUSION:
 * 
 * 
 */

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
        }
    } else if (argc < 3 || argc > 4) {
        printf("ERROR: Please specify a single input file\n");
        return -1;
    }

    return 0;
}