#include "burger_place.h"

#include <stdio.h>

static void parse_input(FILE* input);

void simulate(FILE* input) {
    burger_place_init();
    parse_input(input);
}

void burger_place_init() {

}

static void parse_input(FILE* input) {
    fscanf(input, "%d", &(burgers->burger_cooks));
    fscanf(input, "%d", &(burgers->burger_cook_time));
    fscanf(input, "%d", &(burgers->burgers_per_cook));

    fscanf(input, "%d", &(fries->fryers));
    fscanf(input, "%d", &(fries->fry_serving_cook_time));
    fscanf(input, "%d", &(fries->fry_servings_per_cook));

    fscanf(input, "%d", &(customers->num_customers));
    
    // TODO for loop here
}
