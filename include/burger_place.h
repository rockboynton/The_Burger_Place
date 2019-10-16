#ifndef BURGER_PLACE_H
#define BURGER_PLACE_H

#include "ll.h"

#include <pthread.h>
#include <stdio.h>

ll_t burger_tray;
ll_t fry_tray;

int burger_cooks;
int burger_cook_time; // microseconds
int bugers_per_cook;

int fryers;
int fry_cook_time; // microseconds
int fry_servings_per_cook;

int customers;


void simulate(FILE* input);

// Customers:

// wait in line

// order

// eat


// Cooks

// cook burger

// place on warming tray


// Fryer Operator

// fry fries

// place on warming tray

#endif

