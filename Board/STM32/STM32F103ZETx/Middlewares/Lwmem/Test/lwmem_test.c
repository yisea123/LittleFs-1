/**
 * \file            lwmem_test.c
 * \brief           Main file
 */

/*
 * Copyright (c) 2019 Tilen MAJERLE
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Version:         $_version_$
 */

#include "lwmem.h"
#include "printf.h"

extern int lwmem_init(void);

/**
 * \brief           Program entry point
 */
int
lwmem_test(void) {
    void* ptr1, *ptr2;

    printf("Application running on STM32L496G-Discovery!\r\n");
    
    /* Initialize LwMEM */
    if (lwmem_init() == 0) {
        /* test Env demo */
        printf("lwmem init successful!\r\n");
    }

    /* Allocate */
    ptr1 = lwmem_malloc(128);                   /* Allocate 128 bytes */
    if (ptr1 == NULL) {
        printf("Cannot allocate 128 bytes of memory\r\n");
    }

    /* Reallocate */
    ptr2 = lwmem_realloc(ptr1, 256);            /* Extend to 256 bytes */
    if (ptr2 == NULL) {
        printf("Cannot reallocate to 256 bytes of memory\r\n");
    } else {
        printf("Ptr1 reallocated to 256 bytes of memory\r\n");

        /* Set new pointer */
        ptr1 = ptr2;
        ptr2 = NULL;
    }

    /* Reallocate again down to 64 bytes */
    if (lwmem_realloc_s(&ptr1, 64)) {
        printf("Ptr1 reallocated to 64 bytes of memory\r\n");

        /* No need to set new pointer */
        /* It is set inside realloc_s function */
    } else {
        printf("Cannot reallocate ptr1 to 64 bytes\r\n");

        /* ptr1 still points to original memory and needs to be freed */
    }

    /* Free */
    lwmem_free(ptr1);                           /* Free memory */

    while (1) {}
}
