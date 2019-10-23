#ifndef BURGER_PLACE_H
#define BURGER_PLACE_H

#include "ll.h"

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

static const char* BURGER = "BURGER";
static const char* FRY_ORDER = "FRY_ORDER";

int done;
int max_burgers;
int max_fries;

ll_t *burger_tray;
ll_t *fry_tray;
ll_t *line;

sem_t burgers_ready;
sem_t fries_ready;

pthread_mutex_t order_counter;

typedef struct {
    int burger_cook_time; // microseconds
    int burgers_per_cook;
} Burger_Cook;

typedef struct {
    int fry_serving_cook_time; // microseconds
    int fry_servings_per_cook;
} Fryer;

typedef struct {
    int burgers;
    int fry_orders;
    int wait_time;
    int orders_filled;
} Customer;

int num_customers;
int num_burger_cooks;
int num_fryers;

void simulate(FILE* input);

/**
 * @brief Initialize warming tray linked lists, semaphores, and all structs
 * 
 */
void burger_place_init();


void burger_place_destroy();

// Customers:

// wait in line

// order

/**
 * @brief Customer thread routine
 * 
 * A customer waits in line
 * 
 * @param Customers 
 * @return void* 
 */
void *customer_thread(void *Customers);


// Cooks

/**
 * @brief burger_cook thread routine
 * 
 * @param burger_cook - a burger cook
 * @return void* 
 */
void *burger_cook_thread(void *burger_cook);

/**
 * @brief fryer thread routine
 * 
 * @param fryer - a fryer
 * @return void* 
 */
void *fryer_thread(void *fryer);

// place on warming tray


// Fryer Operator

// place on warming tray

// Helper functions defined here to facilitate testing
void parse_input(FILE* input);

void burger_cooks_init();

void fryers_init();

Customer **customers_init(FILE *input, pthread_t customers[]);

#endif

