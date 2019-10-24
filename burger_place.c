#include "burger_place.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void simulate(FILE* input) {
    burger_place_init();
    parse_input(input);
    burger_place_destroy();
}

void burger_place_init() {
    done = 0;
    max_burgers = 0;
    max_fries = 0;
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
}


void burger_place_destroy() {
    ll_delete(burger_tray);
    ll_delete(fry_tray);
    ll_delete(line);
    sem_destroy(&burgers_ready);
    sem_destroy(&fries_ready);
    pthread_mutex_destroy(&order_counter);
}

void parse_input(FILE* input) {
    // line 1
    fscanf(input, "%d", &(num_burger_cooks));
    pthread_t burger_cooks[num_burger_cooks];
    burger_cooks_init(input, burger_cooks);

    // line 2
    fscanf(input, "%d", &(num_fryers));
    pthread_t fryers[num_fryers];
    fryers_init(input, fryers);

    // line 3
    fscanf(input, "%d", &(num_customers));

    // line 4 to num_customers
    pthread_t customers[num_customers];
    customers_init(input, customers);

    // sim is now running...

    // wait for burger_cooks and friers to be done 
    for (int i = 0; i < num_burger_cooks; i++) {
        pthread_join(burger_cooks[i], NULL);
    }
    printf("Burger Cooks done:\n");

    for (int i = 0; i < num_fryers; i++) {
        pthread_join(fryers[i], NULL);
    }
    printf("Fry Cooks done:\n");

    done = 1; // ? do I need to wait for warming trays to be empty too?

    printf("Simulation finished:\n");
    printf("Max burgers in the burger warmer: %d\n", max_burgers);
    printf("Max fries in the fry warmer: %d\n", max_fries);

    for (int i = 0; i < num_customers; i++) {
        int orders_filled;
        pthread_join(customers[i], NULL);
        printf("Joined Customer: %d\n", i);
        printf("Customer %d got their order filled %d times\n", i, orders_filled);
    }

    printf("Goodbye!\n");

}


void *customer_thread(void *customer) {
    printf("In customer thread\n");
    while (!done) {
        while (ll_get_first(line) != customer && !done) {
            usleep(1);
        }
    
        pthread_mutex_lock(&order_counter);// ? do I even need this?
        for (int i = 0; i < ((Customer *)customer)->burgers; i++) {
            // pthread_mutex_lock(&order_counter);
            sem_wait(&burgers_ready);
            ll_remove_first(burger_tray); // ? do I even need this?
            // pthread_mutex_unlock(&order_counter);
        }
        // if (done == 1) {
        //     break;
        // }
        for (int i = 0; i < ((Customer *)customer)->fry_orders; i++) {
            // pthread_mutex_lock(&order_counter);
            sem_wait(&fries_ready);
            ll_remove_first(fry_tray); // ? do I even need this?
            // pthread_mutex_unlock(&order_counter);
        }
        pthread_mutex_unlock(&order_counter);// ? do I even need this?

        ((Customer *)customer)->orders_filled++;
        ll_remove_first(line);
        usleep(((Customer *)customer)->wait_time);
        ll_insert_last(line, customer);
    }
    printf("Exiting\n");
    int *orders_filled = malloc(sizeof(int));
    *orders_filled = ((Customer *)customer)->orders_filled;
    pthread_exit((void *) orders_filled);
}


void *burger_cook_thread(void *burger_cook) {
    printf("In burger_cook thread\n");
    for (int i = 0; i < ((Burger_Cook *)burger_cook)->burgers_per_cook; i++) {
        usleep(((Burger_Cook *)burger_cook)->burger_cook_time);
        ll_insert_last(burger_tray, "BURGER");
        int burgers_in_tray;
        sem_getvalue(&burgers_ready, &burgers_in_tray);
        if (burgers_in_tray + 1 > max_burgers) {
            max_burgers++; // maybe add a mutex
        }
        sem_post(&burgers_ready);
    }
    pthread_exit(EXIT_SUCCESS);
}


void *fryer_thread(void *fryer) {
    printf("In fryer thread\n");
    for (int i = 0; i < ((Fryer *)fryer)->fry_servings_per_cook; i++) {
        usleep(((Fryer *)fryer)->fry_serving_cook_time);
        ll_insert_last(fry_tray, "FRIES");
        int fries_in_tray;
        sem_getvalue(&fries_ready, &fries_in_tray);
        if (fries_in_tray + 1 > max_fries) {
            max_fries++; // maybe add a mutex
        }
        sem_post(&fries_ready);
    }
    pthread_exit(EXIT_SUCCESS);
}


void burger_cooks_init(FILE* input, pthread_t burger_cooks[]) {
    Burger_Cook *burger_cook = malloc(sizeof(Burger_Cook));
    fscanf(input, "%d", &(burger_cook->burger_cook_time));
    fscanf(input, "%d", &(burger_cook->burgers_per_cook));
    printf("Burger Cooks - Number: %d  Time: %d Total: %d\n", 
                num_burger_cooks, burger_cook->burger_cook_time, burger_cook->burgers_per_cook);
    for (int i = 0; i < num_burger_cooks; i++) {
        pthread_create(&burger_cooks[i], NULL, burger_cook_thread, (void *) burger_cook);
    }
}


void fryers_init(FILE* input, pthread_t fryers[]) {
    Fryer *fryer = malloc(sizeof(Fryer));
    fscanf(input, "%d", &(fryer->fry_serving_cook_time));
    fscanf(input, "%d", &(fryer->fry_servings_per_cook));
    printf("Fry Cooks - Number: %d  Time: %d Total: %d\n", 
                num_fryers, fryer->fry_serving_cook_time, fryer->fry_servings_per_cook);
    for (int i = 0; i < num_fryers; i++) {
        pthread_create(&fryers[i], NULL, fryer_thread, (void *) fryer);
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

        printf("Customer %d - Burgers: %d  Fries: %d Wait: %d\n", 
                i, customer->burgers, customer->fry_orders, customer->wait_time);
        pthread_create(&customers[i], NULL, customer_thread, (void *)customer);
    }

    //  ? do i need to create the linked list first, then spawn the threads?
}
