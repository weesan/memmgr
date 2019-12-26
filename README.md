# C++ Memory Manager

## Introduction

This project implements a simple C++ Memory Manager, an efficient
fixed size memory allocator.  This is useful for allocating and
de-allocating memory for a set of fixed size objects efficiently.

This is accomplished by pre-allocating a large chunk of memory,
carving it into smaller fixed size memories, each of which is linked
using singly-linked list.  Collectively, they form a memory pool.
Each unused fixed size memory is handled to the caller upon allocation
and returned back to the memory pool upon de-allocation.

Please note that the memory pool will be expanded when needed;
however, there is no garbage collection.

## Performance

```
#'s alloc.      W/out MM   With MM    With MM + mutex
1000            0.006      0.006      0.005
10000		0.008      0.007      0.006
100000		0.024      0.016      0.015
1000000		0.147      0.092      0.098
2000000		0.277      0.166      0.188
3000000		0.415      0.239      0.273
4000000		0.534      0.314      0.359
5000000		0.660      0.385      0.422
6000000		0.786      0.464      0.524
7000000		0.922      0.537      0.617
8000000		1.050      0.613      0.701
9000000		1.177      0.685      0.787
10000000	1.324      0.776      0.888
50000000        6.446      3.922      0.481
100000000      12.948      7.631      8.890
```

![picture](https://github.com/weesan/memmgr/blob/master/test/performance.png)
