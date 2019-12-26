/*
 * A point class with and without fixed-size memory manager guided by USE_MM.
 *
 * Created by: WeeSan Lee <weesan@weesan.com>
 */

#ifndef POINT_H
#define POINT_H

#ifdef USE_MM
#include "memmgr.h"
#endif

class Point {
private:
    int _x, _y;

public:
    Point(int x = 0, int y = 0) :
	_x(x),
	_y(y) {
    }
    int x(void) const {
	return (_x);
    }
    int y(void) const {
	return (_y);
    }
#ifdef USE_MM
    MEMMGR_DECLARE(Point)
#endif
};

#endif // POINT_H
