#include "burger_place.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void simulate(FILE* input) {
    burger_place_init();
    parse_input(input);
    
}

void burger_place_init() {
    // initialize trays
    burger_tray = ll_new(ll_no_teardown); // ll values are not malloced
    fry_tray = ll_new(ll_no_teardown); // ll values are not malloced

    // initialize customer line
    line = ll_new(ll_no_teardown);

    // initialize semaphores
    sem_init(&burgers_ready, 0, 0);
    sem_init(&fries_ready, 0, 0); 

    // initialize mutex
    pthread_mutex_init(&order_counter, NULL); // fast mutex

    // initialize burger and fry info structs
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


void *customer_thread(void *customer) {
    while (ll_get_first(line) != customer) {
        usleep(1);
    }
    ll_remove_first(line);

    for (int i = 0; i < ((Customer *)customer)->burgers; i++) {
        // pthread_mutex_lock(&order_counter);
        sem_wait(&burgers_ready);
        ll_get_first(burger_tray); // ? do I even need this?
        // pthread_mutex_unlock(&order_counter);
    }
    for (int i = 0; i < ((Customer *)customer)->fry_orders; i++) {
        // pthread_mutex_lock(&order_counter);
        sem_wait(&fries_ready);
        ll_get_first(fry_tray); // ? do I even need this?
        // pthread_mutex_unlock(&order_counter);
    }
    ((Customer *)customer)->orders_filled++;
    usleep(((Customer *)customer)->wait_time);
    ll_insert_last(line, customer);
}


void *cook_thread(void *cook) {
    // TODO
    for (int i = 0; i < ((B)))
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
        ll_insert_first(line, customer);

        pthread_create(&customers[i], NULL, customer_thread, (void *)customer);
    }

    //  ? do i need to create the linked list first, then spawn the threads?
}