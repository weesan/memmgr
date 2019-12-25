/*
 * The main program to test out fixed-size memory manager.
 *
 * Created by: WeeSan Lee <weesan@weesan.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "point.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
	fprintf(stderr, "Usage: %s count\n", argv[0]);
	return (1);
    }

    // Create/destroy a list of points randomly
    list<Point *> cPoints;
    for (int i = 0; i < atoi(argv[1]); i++) {
	if (random() % 2) {
	    // Create a point and add it to the end of the list
	    Point *pcPoint = new Point;
	    if (!pcPoint) {
		fprintf(stderr, "Failed to allocate memory!\n");
	    } else {
		cPoints.push_back(pcPoint);
	    }
	} else if (cPoints.size()) {
	    // Destroy a point from the front of the list
	    Point *p = cPoints.front();
	    cPoints.pop_front();
	    delete p;
	}
    }
    return (0);
}
