/*
 * A point class with and without fixed-size memory manager guided by USE_MM.
 *
 * Created by: WeeSan Lee <weesan@weesan.com>
 */

#include "point.h"

#ifdef USE_MM

// Fixed-size memory manager for class Point
static MemMgr cMemMgr(sizeof(Point), 1000);

// Overload operator new for class Point
void *Point::operator new(size_t size) {
    return (cMemMgr.malloc());
}

// Overload operator delete for class Point
void Point::operator delete(void *p) {
    cMemMgr.free(p);
}

#endif
