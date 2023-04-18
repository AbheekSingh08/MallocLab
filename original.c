#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "mm.h"
#include "memlib.h"
#include "align.h"

/* Alignment definitions
 * In align.h, there are three definitions relating to alignment. 
 * You should NOT change those. 
 *
 * Work on mm.c with the following assumption.
 * HEADER_SIZE is 8
 * ALIGNMENT is 16
 * ALIGN(size) rounds up size to the nearest ALIGNMENT
 * */

/* Global variables */
// TODO You may use global variables.

/* Helper functions 
 * You may change or redefine these to your liking
 * */
#define HEADER(size, alloc) ((size) | (alloc))
#define GET(p)          (*(uint64_t *)(p))
#define PUT(p, val)     (*(uint64_t *)(p) = (val))  
#define GET_SIZE(p)     (GET(p) & ~(ALIGNMENT-1))
#define GET_ALLOC(p)    (GET(p) & 0x1)
#define MAX(x, y)       ((x) > (y)? (x) : (y))  
#define PTR2BLK(ptr)    ((char *) ptr - HEADER_SIZE);
#define NEXT_BLK(bp)    ((char *) bp + GET_SIZE(bp))


/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    /*  Offsetting mem_sbrk's pointer by 8 from 16 alignment 
    *   mem_sbrk returns 8-byte aligned address on class server
    *   If p is aligned to 16-bytes,
    *   Then allocate another 8-byte
    *   So that p is now 8-byte offset from 16-byte alignment.
    *   This allows space for the 8-byte header.
    */
    void *p = mem_sbrk(0);
    if (((size_t)p % ALIGNMENT)==0){
        p = mem_sbrk(HEADER_SIZE);
    }

    /*  TODO: Initialize global variables, if any are used. 
    *   (Hint: You may use global variables.)
    */

    /*  TODO: If you use dummy headers and footers, 
    *   they should also be initialized.
    */
    return 0;
}

/* 
 * mm_malloc - Allocate a block 
 * This version calls sbrk to ask for more memory from the OS,
 * and will eventually run out of memory.
 *
 * Note: 
 * You are encouraged to implement a lazy coalesce, that coalesces during malloc, not free.
 * If you wish to receive extra credit, mm_free and any of its subroutines must not coalesce. 
 */
void *mm_malloc(size_t size)
{
    char *currBlk; 
    /*  Adjusting size to include header
    *   TODO If you use footers, asize would be different.
    */
    size_t asize = ALIGN(size+HEADER_SIZE); 

    /*  Allocating space
    *   TODO This naive version always calls sbrk for more memory. 
    *   You should instead keep track of block usage and re-use freed memory space.
    *   However, if there are no free space, you should resort to calling sbrk.
    *   Possibly coalesce while searching for space.
    */
    currBlk = (char *) mem_sbrk(asize);
    if (currBlk == (char *)-1)
            return NULL;

    PUT(currBlk, HEADER(asize, 1)); // Writing the header
    //mem_heap_print();             // You may optionally call mem_heap_print() for debugging
    return currBlk+HEADER_SIZE;     // Returning the location after the header
}

/*
 * mm_free - Freeing a block. 
 * This version does nothing.
 *
 * Note:
 * You are encouraged to implement a lazy coalesce, that coalesces during malloc, not free.
 * If you wish to receive extra credit, mm_free and any of its subroutines must not coalesce. 
 */
void mm_free(void *ptr)
{
    /* Free block
    * TODO Mark block as unallocated in the header
    * Possibly coalesce blocks (no bonus points if implemented here).
    */
}


/*
 * mm_coalesce - coalesce blocks
 *
 * Note:
 * If you wish to receive extra credit, this must be called only during malloc and/or its subroutines.
 */
static void mm_coalesce(void *ptr){
    /*  Coalesce
    *   TODO: The implementation of coalesce would vary significantly 
    *   depending on what kind of data structure you use to keep track of utilization.
    */
}
