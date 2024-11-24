// Zachary Gmyr
// 11/23/2024
// CS 4250
// Project 4: Runtime Stack and Heap Exploration in C
// Description: in this program we use 3 functions, f1(), f2(), and f3() to experiment with stack & heap during runtime of subprograms. During
//      the execution of each of these functions we see the call # (implemented as a static integer 'n'), the (estimated) current address of the
//      activation record (measured as the size of some local variable within each function), and the (estimated) size of the activation record
//      (measured by the distance between one variable for each recurring call to the subprogram).

/*  f1(): this function uses a stack dynamic local variable (array, of size 500 -- adjustable) to measure size of the activation record. By default
    this array should be 500 integers (2000 bytes), and should be allocated as a local variable through the activation record (so the activation
    record size should be at least 2000 bytes). We see 10 recursive calls to this function.
    
    f2(): this function uses the same approach as f1(), but has infinite recursion through an infinite loop. This causes segmentation fault, showing
    us that the stack is a limited resource.
    
    f3(): this function also creates an array like in f1() and f2(), but uses malloc() to dynamically allocate the array using the heap. We measure
    size of the activation record instead through a char variable 'c'. Because the array in this function is not allocated to the stack, we should see
    a much smaller activation record size compared to f1() and f2(). */

#include <stdio.h>
#include <stdlib.h>

// adjust this for different array size
// default array (500) should be 500*4=2000 bytes
#define ARRAY_SIZE 500

void f1();
void f2();
void f3();

void f1() {
    // local array
    int array[ARRAY_SIZE];

    // static variables
    static int n = 0;
    static long long last_addr = 0; // NOTE: long long used instead of long, otherwise loss of precision & compile error

    // increment the function call counter
    n++;

    // get the current address of the local array
    long current_addr = (long long)&array;

    // calculate the size of the current activation record (0 if first activation record)
    long ar_size = (last_addr == 0) ? 0 : (last_addr - current_addr);

    // print activation record details:
    // - current activation record number (n)
    // - memory address of current local array
    // - diff. between current & previous activation record
    printf("Call #%d at 0x%lx\n", n, current_addr);
    if (n > 1) {
        printf("AR Size #%d is %ld\n\n", n, ar_size);
    }

    // update the stored address
    last_addr = current_addr;

    // run x10
    if (n < 10) {
        f1();
    }
}

void f2() {
    // local array
    int array[ARRAY_SIZE];

    // static variables
    static int n = 0;
    static long long last_addr = 0;

    n++; // increment

    // get the current address of the local array
    long current_addr = (long long)&array;

    // calculate the size of the current activation record (0 if first activation record)
    long ar_size = (last_addr == 0) ? 0 : (last_addr - current_addr);

    // print activation record details:
    // - current activation record number (n)
    // - memory address of current local array
    // - diff. between current & previous activation record
    printf("Call #%d at 0x%lx\n", n, current_addr);
    if (n > 1) {
        printf("AR Size #%d is %ld\n", n, ar_size);
    }

    // print (estimated) total stack size so far (n * AR size)
    printf("(estimated) Stack Size #%d is %ld\n\n", n, n * ar_size);

    // update the stored address
    last_addr = current_addr;

    // INFINITE recursive calls
    while (true) {
        f2();
    }
}

void f3() {
    // dynamically allocate an array (NOTE: this is allocated on the HEAP => should see smaller AR size)
    int *dynamic_array = (int *)malloc(ARRAY_SIZE * sizeof(int));

    // check for error in allocation
    if (!dynamic_array) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // local variable for tracking activation record
    char c;

    // static variables for recursion tracking
    static int n = 0;
    static long long last_addr = 0;

    n++; // increment the recursion counter

    // get current address of local variable `c` (on stack)
    long long current_addr = (long long)&c;

    // calculate activation record size (difference between last_addr and current_addr)
    long ar_size = (last_addr == 0) ? 0 : (last_addr - current_addr);

    // print details for the current call
    printf("Call #%d at 0x%llx\n", n, current_addr);
    if (n > 1) {
        printf("AR Size #%d is %ld\n\n", n, ar_size);
    }

    // update last_addr to the current address
    last_addr = current_addr;

    // free dynamic array & avoid memory leaks
    free(dynamic_array);

    // run x10
    if (n < 10) {
        f3();
    }
}

int main() {

    // comment out other functions here & run one at a time

    // f1();
    // f2();
    f3();

    return 0;
}