/**
 * @file main.c
 * @author Rock Boynton (boyntonrl@msoe.edu)
 * @brief Main for simulating a burger shop
 * @version 0.1
 * @date 2019-10-22
 * 
 * INTRODUCTION: 
 *  The purpose of this lab is to practice implementing multithreading in C
 *  programs. It simulates a burger shop where there are a certain number of
 *  cooks, fryers, and customers per simulation. Each entity can be a thread,
 *  with its corresponding thread routine determined by its action. Burger cooks
 *  have a burger_cook_thread, etc. 
 * 
 * DESIGN:
 *  I read in the threads using the same method I have previous which is trivial
 *  at this point. As I read the info in, I create the threads.
 * 
 *  The cooks take a certain amount of time to cook their food, which is modeled
 *  a usleep call. Their is a mutex that locks before inserting the food on
 *  its corresponding tray. It then updates its max if needed and unlocks the
 *  mutex. Each cook repeats that process for however many food servings they
 *  have to cook.
 * 
 *  The customers lock their mutex when they're at the order counter, then lock
 *  try to get their food off of the trays locking and unlocking the mutex when
 *  needed. Each time it checks for a food serving on the warming tray, it
 *  should check to see if the cooks are all done (using a global done variable)
 *  and exit if they are done. If the customers order was completely filled,
 *  then it records that and waits for its specified time and repeats that
 *  process until the day is over.
 * 
 * 
 * BUILD INSTRUCTIONS:
 * 
 * $ make
 * $ ./sim sim_file.txt
 * 
 * ANALYSIS:
 *  To be completely honest, I had a lot of help from Draven to get a working
 *  program. I was originally using semaphores to simplify some things rather
 *  than using flags and continuously attempting to remove. There is a lot of
 *  busy waiting in this implementation abd therefore I don't think the method
 *  that I used was the most efficient/best...but it works.
 * 
 *  Fairness:
 *      It seems relatively fair except for the fact that the last customer gets
 *      his order filled a lot more, but then again he is only getting fries and
 *      no burgers so it makes sense he will take longer.
 * 
 *      What I think of fair is when all threads have equal access to the 
 *      processor, proportional to the length of its process. 
 * 
 *      If the customer was skipped, instead of holding up the line until their 
 *      order was ready, it wouldn't be fair, because customers with more 
 *      burgers/fries in their order would be skipped more often, in favor of 
 *      customers with less.
 *  
 *  Number System:
 *      To use a number system, you couldn't just have the customer wait on a 
 *      burger/fry semaphore, you would have to have a semaphore increment when
 *      the full order is ready. 
 * 
 *  Warmer Limit:
 *      If there was a limit on the warmers, you would have to have the cooks 
 *      block when the warmers reach until the customer has taken the food from 
 *      the warmers, then they can add food again.
 * 
 * CONCLUSION:
 *  This was a VERY challenging lab. I think it would help a ton if we were
 *  given a thread safe version of a linked list that we know works so we could
 *  focus on the actual multithreaded program without having to worry about it.
 *  I ended up having a problem with the one that I used without knowing because
 *  I thought it was working. 
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
            fclose(input);
        }
    } else if (argc < 3 || argc > 4) {
        printf("ERROR: Please specify a single input file\n");
        return -1;
    }

    return 0;
}