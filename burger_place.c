#include "burger_place.h"

#include <stdio.h>
#include <stdlib.h>

static void parse_input(FILE* input);

void simulate(FILE* input) {
    burger_place_init();
    parse_input(input);
}

void burger_place_init() {
    burger_tray = ll_new(ll_no_teardown); // ll values are not malloced
    fry_tray = ll_new(ll_no_teardown); // ll values are not malloced

    sem_init(burgers_ready, 0, 0);
    sem_init(fries_ready, 0, 0);

    burgers = malloc(sizeof(Burgers));
    fries = malloc(sizeof(Fries));
}

static void parse_input(FILE* input) {
    // line 1
    fscanf(input, "%d", &(burgers->burger_cooks));
    fscanf(input, "%d", &(burgers->burger_cook_time));
    fscanf(input, "%d", &(burgers->burgers_per_cook));
    // TODO create burger cook threads

    // line 2
    fscanf(input, "%d", &(fries->fryers));
    fscanf(input, "%d", &(fries->fry_serving_cook_time));
    fscanf(input, "%d", &(fries->fry_servings_per_cook));
    // TODO create fry cook threads

    // line 3
    fscanf(input, "%d", &(num_customers));

    // line 4 to num_customers
    pthread_t customers[num_customers];
    for (int i = 0; i < num_customers; i++) {
        Customer *customer = malloc(sizeof(Customer));
        fscanf(input, "%d", &(customer->burgers));
        fscanf(input, "%d", &(customer->fry_orders));
        fscanf(input, "%d", &(customer->wait_time));
        customer->orders_filled = 0;

        pthread_create(&customers[i], NULL, customer_thread, (void *)customer);
    }
    // TODO create customer threads
}


void *customer_thread(void *Customer) {
    // TODO
}


void *cook_thread(void *Cook) {
    // TODO
}
