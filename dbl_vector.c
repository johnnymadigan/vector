#include <stdio.h>
#include <stdlib.h>
#include "dbl_vector.h"

/* {{{MACROS}}} */
/* returns the max/min of 2 numbers */
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

/**
 * {{{INITIALISE VECTOR STRUCT}}}
 * initial capacity = 4 items
 * initial number of items = 0 (none)
 * initial memory allocated to data array = 4 doubles
 */
void dv_init( dbl_vector_t* vec ) {
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->size = 0;
    vec->data = malloc(DV_INITIAL_CAPACITY * sizeof(double));
}

/**
 * {{{ENSURE THERE IS ENOUGH CAPACITY}}}
 * Given a specific number of items to store, this function 
 * ensures that the vector's storage capacity is large enough
 * to accomodate the designated number of items...
 * 
 * If the vector is not large enough, the capacity will be 
 * increased while keeping the items unchanged.
 */
void dv_ensure_capacity( dbl_vector_t* vec, size_t new_size ) {
    
    /* temporarily store the vector's members */
    size_t old_capacity = vec->capacity;

    /* new capacity will be whichever is largest */
    size_t new_capacity = MAX(old_capacity * DV_GROWTH_FACTOR, new_size);

    /* get the new size in bytes by multiplying num of items by item type (double) */
    size_t new_mem_size = (new_capacity * sizeof(double));

    /* if the new size is greater, then resize the capacity and realloc the data */
    if (new_size > old_capacity) {
        vec->capacity = new_capacity;
        vec->data = realloc(vec->data, new_mem_size);
    }
}

/* {{{DESTROY VECTOR}}} */
void dv_destroy( dbl_vector_t* vec ) {
    vec->capacity = 0;
    vec->size = 0;
    free(vec->data);
    vec->data = NULL;
}

/* {{{DUPLICATE VECTOR}}} */
void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    /* if vector #1 and #2 are the same, return early */
    if (vec == dest ) {
        puts("Vector #1 and #2 cannot be the same:");
        printf("\t%p\n\t%p\n", vec, dest);
        return;
    }

    /* same number of items and ensure capacity is enough */
    dest->size = vec->size;
    dv_ensure_capacity(dest, vec->size);

    /* copy data over */
    int i;
    for (i = 0; i < vec->size; i++) {
        dest->data[i] = vec->data[i];
    }
}

/* {{{REMOVE ALL ELEMENTS FROM VECTOR}}} */
void dv_clear( dbl_vector_t* vec ) {
    int i;
    
    puts("Data before cleared:");
    for (i = 0; i < vec->size; i++) {
        printf("%d.\t%f\n", i + 1, vec->data[i]);
    } 
    
    /* reducing the size of the vector struct will trim away the data */
    /* zero effectively removes all data */
    vec->size = 0;

    puts("Data after cleared:");
    for (i = 0; i < vec->size; i++) {
        printf("%d.\t%f\n", i + 1, vec->data[i]);
    }
}

/* {{{APPEND ITEM TO END OF VECTOR}}} */
void dv_push( dbl_vector_t* vec, double new_item ) {

    /* temporarily store the vector's members */
    size_t old_size = vec->size;

    /* dupe/copy over, don't assign pointer to pointer */
    int i;
    double old_data[vec->size];
    for (i = 0; i < vec->size; i++) {
        old_data[i] = vec->data[i];
    }

    /* for debugging, check if temporary data is @ a different address*/
    // printf("Old data: %p\t current: %p\n", old_data, vec->data);

    /* ensure the vectors capacity can hold 1 new item */
    dv_ensure_capacity(vec, old_size + 1);
    vec->size = old_size + 1;

    /* add the old data back into the newly sized array */
    for (i = 0; i < old_size; ++i) {
        vec->data[i] = old_data[i];
    }

    /* append the item to the end */
    vec->data[old_size] = new_item;
}

/* {{{REMOVE LAST ITEM AKA POP}}} */
void dv_pop( dbl_vector_t* vec ) {

    /* if vector is not empty, there is an item to pop */
    if (vec->size > 0) {
        /* reducing the size of the vector struct will trim away the data */
        /* zero effectively removes all data */
        vec->size = vec->size -1;
    }
}

/* {{{RETURN LAST ITEM}}} */
double dv_last( dbl_vector_t* vec ) {
    double result = NAN;

    /* if there is at least 1 item, return final item */
    if (vec->size > 0) {
        result = vec->data[vec->size - 1];
    }

    return result;
}

/* {{{INSERT @ POSITION}}} */
void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {

    /* temporarily store the vector's current size */
    size_t old_size = vec->size;

    /* dupe/copy over, don't assign pointer to pointer */
    int i;
    double old_data[vec->size];
    for (i = 0; i < vec->size; i++) {
        old_data[i] = vec->data[i];
    }

    /* if position is out of bounds, change position to be the last item */
    pos = MIN(pos, old_size);

    /* +1 element and ensure capacity */
    vec->size = old_size + 1;
    dv_ensure_capacity(vec, old_size);

    if(pos > vec->size) {
        printf("Position %zu out of bounds\n", pos);
        return;
    }

    /* fill first half of array */
    for (i = 0; i < pos; i++) {
        vec->data[i] = old_data[i];
    }

    /* fill 2nd half of array after loc  */
    for (i = pos + 1; i < vec->size; i++) {
        vec->data[i] = old_data[i - 1];
    }

    // add the new item in between
    vec->data[pos] = new_item;
}

/* {{{REMOVE @ POSITION}}} */
void dv_remove_at( dbl_vector_t* vec, size_t pos ) {

    /* temporarily store the vector's current size */
    size_t old_size = vec->size;

    /* if out of bounds */
    if (pos >= vec->size) {
        printf("Cannot remove - position %zu is out of bounds!\n", pos);
        return;
    }
    
    /* from wherever the element was removed, shift all elements left by 1 */
    int i;
    for (i = pos; i < vec->size - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }

    /* after all elements have been joined back together from the gap caused 
    by removing an element, trim the size of the array by 1 */
    vec->size = old_size - 1;
}

/* {{{FOR EACH}}} */
void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    
    /* info and callback function are supplied by the user,
    the purpose of this function is to call the callback function with info
    for EACH of the vector's elements */

    int i;
    for (i = 0; i < vec->size; i++) {
        /* callback func takes an element and some info */
        callback(vec->data[i], info);
    }
}