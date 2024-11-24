# Stack and Heap Exploration in C

This program experiments with stack and heap memory during the runtime of subprograms using three functions: `f1()`, `f2()`, and `f3()`. 

During the execution of each function, the following metrics are measured:
- The call number, implemented as a static integer `n`.
- The current address of the activation record, estimated by the size of a local variable within each function.
- The size of the activation record, estimated by the distance between variables for each recurring call to the subprogram.

## Functions

### `f1()`
This function uses a stack-dynamic local variable (an array of size 500, adjustable) to measure the size of the activation record. By default, the array contains 500 integers (2000 bytes) and is allocated as a local variable through the activation record. Therefore, the activation record size should be at least 2000 bytes. The function demonstrates 10 recursive calls.

### `f2()`
This function operates similarly to `f1()`, but introduces infinite recursion through an infinite loop. This causes a segmentation fault, illustrating that the stack is a limited resource.

### `f3()`
This function creates an array like `f1()` and `f2()`, but it uses `malloc()` to dynamically allocate the array on the heap. The size of the activation record is measured through a `char` variable `c`. Since the array is allocated on the heap rather than the stack, the activation record size is expected to be much smaller compared to `f1()` and `f2()`.
<br>
<br>
(This project was completed for Programming Languages (CS4250) with the University of Missouri-St Louis)