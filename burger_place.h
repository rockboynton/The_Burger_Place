#ifndef BURGER_PLACE_H
#define BURGER_PLACE_H

#include "ll.h"

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

ll_t burger_tray;
ll_t fry_tray;

sem_t burgers_ready;
sem_t fries_ready;

Burgers* burgers;
Fries* fries;
Customers* customers;


typedef struct {
    int burger_cooks;
    int burger_cook_time; // microseconds
    int bugers_per_cook;
} Burgers;

typedef struct {
    int fryers;
    int fry_cook_time; // microseconds
    int fry_servings_per_cook;
} Fries;

typedef struct {
    int customers;
    int orders_filled;
} Customers;


void simulate(FILE* input);

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

