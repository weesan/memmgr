/*
 * The fixed-size memory manager.
 *
 * Created by: WeeSan Lee <weesan@weesan.com>
 */

#ifndef MEM_MGR_H
#define MEM_MGR_H

#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define MEMMGR_DECLARE(CLASS)                          \
    public:                                            \
        void *operator new(size_t size);               \
        void operator delete(void *p);

#define MEMMGR_IMPLEMENT(CLASS, N)                     \
    /* Fixed-size memory manager for class Point */    \
    static MemMgr _##CLASS(sizeof(CLASS), N);          \
                                                       \
    /* Overload operator new for class Point */        \
    void *CLASS::operator new(size_t size) {           \
        return (_##CLASS.malloc());                    \
    }                                                  \
                                                       \
    /* Overload operator delete for class Point */     \
    void CLASS::operator delete(void *p) {             \
        _##CLASS.free(p);                              \
    }


class MemMgr {
private:
    pthread_mutex_t _mutex;
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
	(void)pthread_mutex_init(&_mutex, NULL);
    }
    ~MemMgr(void) {
	(void)pthread_mutex_lock(&_mutex);
	while (_list) {
	    char *p = (char *)_list;
	    _list = *(void **)_list;
	    delete []p;
	}
	(void)pthread_mutex_unlock(&_mutex);
	(void)pthread_mutex_destroy(&_mutex);
    }
    void *malloc(void) {
        void *ret = NULL;
        
	(void)pthread_mutex_lock(&_mutex);
        do {
            if (!_free) {
                // Allocate a big page + the size of a pointer.
                int page_size = _size * _count;
                char *p = new char[page_size + sizeof(void *)];
                if (!p) {
                    break;
                }
                // Link the pages together using the first few bytes
                // of the page.
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

            // Return the 1st free chuck.
            ret = _free;
            // Move the free point to the next free one.
            _free = *(void **)_free;
            
        } while (false);

	(void)pthread_mutex_unlock(&_mutex);
	return ret;
    }
    void free(void *p) {
	(void)pthread_mutex_lock(&_mutex);
	*(void **)p = _free;
	_free = p;
	(void)pthread_mutex_unlock(&_mutex);
    }
};

#endif // MEM_MGR_H
