/*
 * This file contains Umbra's external API.
 */

#ifndef UMBRA_H_
#define UMBRA_H_

#include <stdarg.h>
#include <stddef.h>

#include "umbracfg.h"

typedef struct um_MachineArgs um_MachineArgs;

struct um_MachineArgs {

    um_FAlloc alloc;
    void *alloc_ptr;   /**< The allocator's data pointer. */

    um_FLock lock;     /**< A read/write locker.
                            This is an important property for multi-threaded
                            applications accessing data from a parent machine,
                            to avoid concurrent access to data from multiple
                            threads without protection.
                            This also has the advantage of not penalizing
                            single-threaded applications with global or
                            useless locks.
                            Everytime data needs to be retrieved from or
                            written to the machine, a lock will be attempted.
                            This lock only happens internally, at the 
                            library's discretion. */
    void *lock_ptr;    /**< The lock's data pointer. */

    const char *name;  /**< The name of the new machine.
                           This can also represent a filename, from where
                           Umbra will get input data, if neither @a input nor
                           @a buffer are given. */
    um_EInputFormat fmt; /**< The source input's format. */
    const char *enc;   /**< The name of the source's encoding.
                           This property is only valid when the source is
                           either a file or a string. When a buffer function is
                           passed, no conversion will be done, and all data read
                           from it will be considered to be in Umbra's special
                           encoding. If not given, the library will consider
                           the input file or string to be in Umbra's special
                           encoding. */
    const char *input; /**< Source code input, as a string.
                           If @a buffer is given, it'll be preferred over 
                           @a input. */
    size_t input_size; /**< Source code string's size, in bytes. */
    um_FBuffer buffer; /**< The input buffer reader.
                           This function will read source code input based on
                           a given buffer pointer, and the data read will be
                           considered to be in a form the library can
                           understand, meaning that no conversion will be
                           tried on it. If any conversion is needed, the buffer
                           function should make it by the time of the call. */
    void *buffer_ptr;  /**< The input buffer's data. */
};

um_API um_Machine* umbra_new(um_MachineArgs *args);
um_API um_Machine* umbra_from(um_Machine *M, um_MachineArgs *args);
um_API um_EEcode umbra_run(um_Machine *U);
um_API um_EEcode umbra_runargv(um_Machine* U, int argc, char** argv);
um_API void umbra_close(um_Machine* U);
um_API const char* um_EEnum_tostring(um_EEcode errnum);

#endif
