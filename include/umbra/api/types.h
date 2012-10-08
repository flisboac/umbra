/**
 * @file include/umbra/api/types.h
 */

#ifndef UMBRA_API_TYPES_H_
#define UMBRA_API_TYPES_H_

#include <stddef.h>

typedef void* (*um_FAlloc)(void* state, void* ptr, size_t old_sz, size_t new_sz, int align);


#endif /* UMBRA_API_TYPES_H_ */
