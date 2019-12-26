/*
 * A point class with and without fixed-size memory manager guided by USE_MM.
 *
 * Created by: WeeSan Lee <weesan@weesan.com>
 */

#include "point.h"

#ifdef USE_MM

MEMMGR_IMPLEMENT(Point, 1000);

#endif
