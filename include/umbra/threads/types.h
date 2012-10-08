/**
 * @file include/umbra/threads/types.h
 */

#ifndef UMBRA_THREADS_TYPES_H_
#define UMBRA_THREADS_TYPES_H_

typedef struct umT_Lock_t umT_Lock;
typedef int (*umT_FLock)(void* lock);

struct umT_Lock_t {

	void *state;
	union {
		umT_FLock lock;
		umT_FLock read;
	};
	union {
		umT_FLock trylock;
		umT_FLock tryread;
	};
	umT_FLock write;
	umT_FLock trywrite;
};

#endif /* UMBRA_THREADS_TYPES_H_ */
