
#ifndef UMBRA_STREAM_H_
#define UMBRA_STREAM_H_

#include "umbra/ctype.h"
#include "umbra/types.h"

typedef enum umZ_StreamType umZ_StreamType;
typedef struct umZ_Stream umZ_Stream;

enum umZ_StreamType {

    umZ_ST_FILE,    /** An opened file. */
    umZ_ST_SOCKET,  /** A network socket. */
    umZ_ST_STRING,  /** A simple, non-expandable string. */
    umZ_ST_BUFFER   /** An expandable string. */
};

struct umZ_Stream {
    
    umZ_StreamType type; /** The stream's type. */
    umZ_Ctrait *enc;     /** The stream's character traits.
                             In other words, the stream's encoding. If an
                             encoding is set for a stream, the stream is
                             considered to be a character stream. If not, it's
                             a mere byte stream.
                          */
};


#endif
