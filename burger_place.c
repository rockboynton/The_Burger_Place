#include "burger_place.h"

#include <stdio.h>
#include <stdlib.h>


void simulate(FILE* input) {
    burger_place_init();
    parse_input(input);
    // num_burger_cooks_init();
    // fry_cooks_init();
}

void burger_place_init() {
    burger_tray = ll_new(ll_no_teardown); // ll values are not malloced
    fry_tray = ll_new(ll_no_teardown); // ll values are not malloced

    sem_init(&burgers_ready, 0, 0);
    sem_init(&fries_ready, 0, 0); 

    burgers = malloc(sizeof(Burgers));
    fries = malloc(sizeof(Fries));
}

void parse_input(FILE* input) {
    // line 1
    fscanf(input, "%d", &(burgers->num_burger_cooks));
    fscanf(input, "%d", &(burgers->burger_cook_time));
    fscanf(input, "%d", &(burgers->burgers_per_cook));
    pthread_t burger_cooks[burgers->num_burger_cooks];
    burger_cooks_init(burger_cooks);

    // line 2
    fscanf(input, "%d", &(fries->num_fryers));
    fscanf(input, "%d", &(fries->fry_serving_cook_time));
    fscanf(input, "%d", &(fries->fry_servings_per_cook));
    pthread_t fryers[fries->num_fryers];
    fryers_init(fryers);

    // line 3
    fscanf(input, "%d", &(num_customers));

    // line 4 to num_customers
    pthread_t customers[num_customers];
    customers_init(input, customers);
}


void *customer_thread(void *Customer) {
    // TODO
    printf("in customer thread\n");
}


void *cook_thread(void *Cook) {
    // TODO
    printf("in cook thread\n");
}


void burger_cooks_init(pthread_t burger_cooks[]) {
    for (int i = 0; i < burgers->num_burger_cooks; i++) {
        pthread_create(&burger_cooks[i], NULL, cook_thread, (void *) burgers);
    }
}


void fryers_init(pthread_t fryers[]) {
    for (int i = 0; i < fries->num_fryers; i++) {
        pthread_create(&fryers[i], NULL, cook_thread, (void *) fries);
    }
}


void customers_init(FILE *input, pthread_t customers[]) {
    for (int i = 0; i < num_customers; i++) {
        Customer *customer = malloc(sizeof(Customer));
        fscanf(input, "%d", &(customer->burgers));
        fscanf(input, "%d", &(customer->fry_orders));
        fscanf(input, "%d", &(customer->wait_time));
        customer->orders_filled = 0;

        pthread_create(&customers[i], NULL, customer_thread, (void *)customer);
    }
}