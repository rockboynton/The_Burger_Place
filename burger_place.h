#ifndef BURGER_PLACE_H
#define BURGER_PLACE_H

#include "ll.h"

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

ll_t* burger_tray;
ll_t* fry_tray;

sem_t burgers_ready;
sem_t fries_ready;

typedef struct {
    int burger_cooks;
    int burger_cook_time; // microseconds
    int burgers_per_cook;
} Burgers;

typedef struct {
    int fryers;
    int fry_serving_cook_time; // microseconds
    int fry_servings_per_cook;
} Fries;

typedef struct {
    int num_customers;
    int orders_filled;
} Customers;

typedef struct {
    int burgers;
    int orders_filled;
} Customer;

Burgers* burgers;
Fries* fries;
Customers* customers;

void simulate(FILE* input);

/**
 * @brief Initialize warming tray linked lists, semaphores, and all structs
 * 
 */
void burger_place_init();

// Customers:

// wait in line

// order

/**
 * @brief Customer thread routine
 * 
 * @param Customers 
 * @return void* 
 */
void *customer(void *Customers);


// Cooks

/**
 * @brief Cook thread routine
 * 
 * @param Cook - either a burger cook or a fry cook 
 * @return void* 
 */
void *cook(void *Cook);

// place on warming tray


// Fryer Operator

// place on warming tray

#endif

