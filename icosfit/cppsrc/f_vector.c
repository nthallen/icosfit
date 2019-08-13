#include <string.h>
#include "f_vector.h"
#include "nl.h"

/**
  @param min the minimum number of ICOS_Floats for the first allocation
  @param off the index of the first element. Defaults to 0, but 1 is the only common value.
  f_vector is a class of resizable vectors of ICOS_Floats.
 */
f_vector::f_vector( int min, int off ) {
  data = 0;
  n_data = 0;
  datasize = 0;
  if ( min <= 0 || off < 0 )
    nl_error( 4, "Invalid minimum size or offset to f_vector" );
  offset = off;
  min_size = min+off;
}

/**
  Sets the number of points in the vector to 0.
 */
void f_vector::clear() { n_data = 0; }

/**
  @param size The requested minimum size
  Checks that the vector has room for size elements, reallocating
  if necessary. Aborts if unable to allocate sufficient memory.
 */
void f_vector::check( int size ) {
  ICOS_Float *newdata;
  if ( size+offset > datasize ) {
    if ( datasize == 0 )
      datasize = min_size;
    while ( datasize < size+offset && datasize >= 0 ) datasize *= 2;
    if ( datasize <= 0  )
      nl_error( 4, "datasize overflow in f_vector::check" );
    newdata = new ICOS_Float[datasize];
    if ( newdata == 0 ) nl_error( 4, "Out of memory in f_vector::check" );
    if ( data != 0 ) {
      if ( n_data > 0 )
        memcpy( newdata+offset, data+offset, n_data * sizeof(ICOS_Float) );
      delete data;
    }
    data = newdata;
  }
}

/**
  @param f Value to append to vector
  Increases the length of the vector by 1, setting the new last element
  to f.
 */
void f_vector::append( ICOS_Float f ) {
  check(n_data+1);
  data[offset+n_data++] = f;
}
