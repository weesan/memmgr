/*
 * The fixed-size memory manager.
 *
 * Created by: WeeSan Lee <weesan@weesan.com>
 */

#ifndef MEM_MGR_H
#define MEM_MGR_H

#include <stdio.h>
#include <assert.h>

class MemMgr {
private:
    int _size;
    int _count;
    void *_list;
    void *_free;

public:
    MemMgr(int size, int count) :
	_size(size),
	_count(count),
	_list(NULL),
	_free(NULL) {
	assert(_size >= sizeof(void *));
    }
    ~MemMgr(void) {
	while (_list) {
	    char *p = (char *)_list;
	    _list = *(void **)_list;
	    delete []p;
	}
    }
    void *malloc(void) {
	if (!_free) {
	    // Allocate a big page + the size of a pointer.
	    int page_size = _size * _count;
	    char *p = new char[page_size + sizeof(void *)];
	    if (!p) {
		return (NULL);
	    }
	    // Link the pages together using the first few bytes of the page.
	    *(void **)p = _list;
	    _list = p;
	    // Free memory starts after.
	    _free = p += sizeof(void *);
	    // Initialize the page.
	    for (int i = 0; i < _count - 1; i++) {
		*(void **)p = p + _size;
		p += _size;
	    }
	    *(void **)p = NULL;
	}

	void *ret = _free;
	_free = *(void **)_free;

	return (ret);
    }
    void free(void *p) {
	*(void **)p = _free;
	_free = p;
    }
};

#endif // MEM_MGR_H
