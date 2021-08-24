#include <stdio.h>
#include <stdlib.h>
#include "dbl_vector.h"

/* macros to return the MAX/MIN of 2 numbers */
#define MAX(a, b) {(a > b) ? a : b}
#define MIN(a, b) {(a < b) ? a : b}


/* INITIALISE DEFAULT VALUES TO VECTOR STRUCT */
void dv_init( dbl_vector_t* vec ) {
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->size = 0;
    vec->data = malloc(DV_INITIAL_CAPACITY * sizeof(double));
}


/**

 * POST: 
 * AND
 *   IF new_size <= old_capacity
 *   THEN
 *     vec->capacity == old_capacity
 *     AND vec->data == old_data
 *   OTHERWISE
 *     vec->capacity == new_capacity
 *     AND vec->data == realloc(old_data, new_mem_size)
 * 
 * 
 * \param vec A vector to process.
 * \param new_size The required minimum capacity for the vector.
 */
void dv_ensure_capacity( dbl_vector_t* vec, size_t new_size ) {
    /**
    * Given a specific number of items to store, this function
    * ensures that the vector's storage capacity is large enough to  
    * hold the designated number of items. 
    * 
    * If vector is not large enough, the capacity will be resized
    * while keeping the items unchanged.
    **/


    /* temporarily store the capacity, num of items, and the data */
    size_t old_capacity = vec->capacity;
    size_t old_size = vec->size;
    double* old_data = vec->data;

    /* check if the new size is larger than the current using macro max() */
    size_t new_capacity = MAX(old_capacity * DV_GROWTH_FACTOR, new_size);


    /* get the size in bytes by multiplying num of items by item type (double) */
    size_t new_mem_size = (new_capacity * sizeof(double));

    vec->size = old_size;

    /* if the new size is greater, then update the capacity and realloc the data */
    if (new_size <= old_capacity) {
        vec->capacity = old_capacity;
        vec->data = old_data;
    } else {
        vec->capacity = new_capacity;
        vec->data = realloc(old_data, new_mem_size);
    }
}

/**
 * Destroy a vector. After this, it will not be fit for further use.
 *
 * PRE: dv_init(vec) has been invoked.
 *
 * POST: vec->capacity == 0,
 * AND vec->size == 0,
 * AND vec->data has been freed,
 * AND vec->data == NULL.
 *
 * \param vec The address of a dbl_vector_t to be destroyed.
 */
void dv_destroy( dbl_vector_t* vec ) {
    // INSERT SOLUTION HERE
    vec->capacity = 0;
    vec->size = 0;
    free(vec->data);
    vec->data = NULL;
}


/**
 * Duplicate the contents of a vector (the source) into another (the destination).
 *
 * PRE: vec != dest
 * AND dv_init(vec) has been previously invoked,
 * AND dv_init(dest) has been previously invoked.
 *
 * POST: dest->size == vec->size
 * AND dv_ensure_capacity(dest, vec->size) has been invoked
 * AND for all i in [1..vec->size) dest->data[i] == vec->data[i].
 *
 * \param vec The address of a dbl_vector_t from which data is to be copied.
 * \param dest The address of a dbl_vector_t into which data is to be copied.
 */
void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    // INSERT SOLUTION HERE
    if (vec == dest ) {
        puts("Vector #1 and #2 cannot be the same:");
        printf("\t%p\n\t%p\n", vec, dest);
        return;
    }

    dest->size = vec->size;
    
    //printf("%p, %p/n", &dest->size, &vec->size);

    dv_ensure_capacity(dest, vec->size);
    int i;
    for (i = 0; i < vec->size; i++) {
        dest->data[i] = vec->data[i];
    }
}

/**
 * Remove all elements from the vector, but keep storage and capacity as-is to
 * enable efficient regrowth if necessary.
 * 
 * PRE: dv_init(vec) has previously been invoked.
 * 
 * POST: vec->size == 0.
 * 
 * \param  The address of a dbl_vector_t to be cleared.
 */
void dv_clear( dbl_vector_t* vec ) {
    // INSERT SOLUTION HERE
    int i;
    //puts("before clear");
    for (i = 0; i < vec->size; i++) {
        printf("%f\n", vec->data[i]);
    }
    vec->size = 0;
    //puts("after cleared");
    for (i = 0; i < vec->size; i++) {
        printf("%f\n", vec->data[i]);
    }
}


/**
 * Append a new item to the end of the vector.
 * 
 * 
 * POST: vec->size == old_size + 1
 * AND dv_ensure_capacity(vec, old_size + 1) has been invoked
 * AND for all i in [0..old_size) vec->data[i] == old_data[i]
 * AND vec->data[old_size] == new_item
 * 
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data.
 * 
 * \param vec The address of a dbl_vector_t to which a new item is to be appended.
 * \param new_item A double value to be appended to the vector.
 */
void dv_push( dbl_vector_t* vec, double new_item ) {


    /* PUSHING ITEM TO THE END OF THE VECTOR */

    int i;

    /* first store the current vector size */
    size_t old_size = vec->size;
    /* next store the current vector's data */

    double old_data[vec->size];
    
    /* dupe over, don't assign pointer to pointer */
    for (i = 0; i < vec->size; i++) {
        old_data[i] = vec->data[i];
    }
    
    
    // printf("OLd data: %p\t current: %p\n", old_data, vec->data);

    
    /* the vectors' size is now 1 item longer */

    /* ensure the vectors capacity can hold the new item */
    dv_ensure_capacity(vec, old_size + 1);
    vec->size = old_size + 1;

    /* add the old data back into the newly sized array */
    for (i = 0; i < old_size; ++i) {
        vec->data[i] = old_data[i];
    }

    /* append the item */
    vec->data[old_size] = new_item;
}

/**
 * Remove the last item (if any) from the end of the vector.
 * 
 * PRE: dv_init(vec) has previously been invoked.
 * 
 * POST: vec->capacity == old_capacity
 * AND vec->data == old_data
 * AND
 *   IF old_size > 0
 *   THEN 
 *	   vec->size == old_size - 1
 *     AND for all i in [0..old_size-1) vec->data[i] == old_data[i]
 *   OTHERWISE 
 *     vec->size == 0
 * 
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data.
 * 
 * \param vec The address of a dbl_vector_t from which the last item is to be 
 * removed.
 */
void dv_pop( dbl_vector_t* vec ) {
    // INSERT SOLUTION HERE
    size_t old_size = vec->size;
    int i;
    /* dupe over, don't assign pointer to pointer */
    double old_data[vec->size]; // old data locally, no pointer needed
    for (i = 0; i < vec->size; i++) {
        old_data[i] = vec->data[i];
    }

    if (old_size > 0) {
        vec->size = old_size -1;
        /* add items back in but forget the last item */
        
        for (i = 0; i < vec->size; i++) {
            vec->data[i] = old_data[i];
        }
    } else {
        vec->size = 0;
    }
}

/**
 * Get the last item from the end of the vector, or NaN if the vector is empty.
 * 
 * PRE: dv_init(vec) has previously been invoked.
 * 
 * POST: vec->size == old_size
 * AND vec->capacity == old_capacity
 * AND vec->data == old_data
 * AND for all i in [0..vec->size) vec->data[i] == old_data[i]
 * AND
 *   IF vec->size > 0
 *   THEN 
 *	   returns vec->data[vec->size - 1]
 *   OTHERWISE 
 *	   returns NaN
 * 
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND old_capacity == previous value of vec->data.
 * 
 * \param vec The address of a dbl_vector_t from which the last item is to be obtained.
 */
double dv_last( dbl_vector_t* vec ) {
    double result = NAN;
    // INSERT SOLUTION HERE
    /*
    size_t old_size = vec->size;
    int i;
    // dupe over, don't assign pointer to pointer
    double old_data[vec->size]; // old data locally, no pointer needed
    for (i = 0; i < vec->size; i++) {
        old_data[i] = vec->data[i];
    }
    size_t old_capacity = vec->capacity;

    // boilerplate?
    vec->size = old_size;
    vec->capacity = old_capacity;

    for (i = 0; i < vec->size; i++) {
        vec->data[i] = old_data[i];
    }
    */

    // maybe this is all we need here
    if (vec->size > 0) {
        result = vec->data[vec->size - 1];
    }

    return result;
}

/**
 * Insert an item at a designated position in the vector. If the position  
 * equals or exceeds the size of the vector, the new item is appended.
 *  
 * PRE: dv_init(vec) has previously been invoked.
 * 
 * POST: vec->size == old_size + 1
 * AND dv_ensure_capacity(vec,old_size+1) has been invoked
 * AND for all i in [0..loc) vec->data[i] == old_data[i]
 * AND for all i in [loc+1..vec->size) vec->data[i] == old_data[i-1]
 * AND vec->data[loc] == new_item
 * 
 * AND loc == min(pos, old_size).
 * 
 * \param vec The address of a dbl_vector_t from which the last item is to be obtained.
 * \param pos The position at which the new item is to be inserted.
 * \param new_item The value to insert.
 */
void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {
    // INSERT SOLUTION HERE
    size_t old_size = vec->size;
    int i;
    // dupe over, don't assign pointer to pointer
    double old_data[old_size]; // old data locally, no pointer needed
    //printf("SIZE;%zu\n", old_size);
    for (i = 0; i < vec->size; i++) {
        old_data[i] = vec->data[i];
        //printf("%.2f\n", old_data[i]);

    }

    // boilerplate?
    size_t loc = MIN(pos, old_size);


    vec->size = old_size + 1;
    dv_ensure_capacity(vec, old_size + 1);

    //printf("HERE \n%p\n%p\n", vec->data, old_data);
    // fill first half of array
    for (i = 0; i < loc; i++) {
        //printf("%.2f, %.2f\n", vec->data[i], old_data[i]);
        vec->data[i] = old_data[i];
        //printf("HERE: %.2f\n", vec->data[i]);
    }
    //puts("sdasdasdas");

    
    //fill 2nd half of array after loc (going backwards)
    for (i = loc + 1; i < vec->size; i++) {
        //printf("%.2f, %.2f\n", vec->data[i], old_data[i]);
        vec->data[i] = old_data[i - 1];
        //printf("HERE: %.2f\n", vec->data[i]);

    }
    //printf("%.2f\n", vec->data[0]);
    //printf("%ld\n", loc + 1);


    // add the new item
    vec->data[loc] = new_item;

    
    

}




/**
 * Remove the item at a designated position in the vector. If the position equals 
 * or exceeds the size of the vector, no change is made.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: for all i in [0..loc) vec->data[i] == old_data[i]
 * AND for all i in [loc+1..vec->size) vec->data[i] == old_data[i+1]
 * AND 
 *	IF pos >= old_size
 *  THEN
 *    vec->size == old_size
 *  OTHERWISE
 *    vec->size == old_size - 1
 * 
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND old_capacity == previous value of vec->data
 * AND loc == min(pos, old_size).
 *
 * \param vec The address of a dbl_vector_t from which the last item is to be obtained.
 * \param pos The position at which the item is to be removed.
 */
void dv_remove_at( dbl_vector_t* vec, size_t pos ) {
    // INSERT SOLUTION HERE
    int i;
    size_t old_size = vec->size;

    

    // if out of bounds
    if (pos >= vec->size) {
        return;
    }
    
    for (i = pos; i < vec->size - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }


    vec->size = old_size - 1;


}

/**
 * Traverses a vector, invoking the supplied function with each element in turn.
 * 
 * PRE: dv_init(vec) has previously been invoked.
 * 
 * POST: vec->capacity == old_capacity
 * AND vec->size == old_size
 * AND vec->data == old_data
 * AND for all i in [0..vec->size) callback(vec->data[i], info) has been invoked.
 * 
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND old_capacity == previous value of vec->data
 * 
 * \param vec The address of a dbl_vector_t which is to be processed.
 * \param callback A function which will be applied to each element of the vector. 
 * \param info The address of a user-supplied data object which will be passed 
 * to callback along with each value.
 */
void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    // INSERT SOLUTION HERE
    int i;

    

    for (i = 0; i < vec->size; i++) {
        callback(vec->data[i], info);
    }



}