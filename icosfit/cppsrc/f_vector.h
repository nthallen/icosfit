#ifndef F_VECTOR_H_INCLUDED
#define F_VECTOR_H_INCLUDED
#include "config.h"

class f_vector {
  public:
    ICOS_Float *data; //< The data vector
    int n_data; //< The number of elements in the data vector
    int datasize; //< The allocated size of the data vector
    int min_size;
    int offset;
    f_vector( int minsize, int offset=0 );
    void clear();
    void check( int size );
    void append( ICOS_Float f );
};

#endif
