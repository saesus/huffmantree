#ifndef SVECTOR_CPP_
#define SVECTOR_CPP_

#include "svector.h"

template <class Object>
const svector<Object> & svector<Object>::operator=( const svector<Object> & rhs )
{
    if( this != &rhs )
    {
#ifdef WIN32
      if( currentSize != 0 )
#endif
        delete [ ] objects;
        currentSize = rhs.size( );
        objects = new Object[ currentSize ];
        for( int k = 0; k < currentSize; k++ )
            objects[ k ] = rhs.objects[ k ];
    }
    return *this;
}

template <class Object>
void svector<Object>::resize( int newSize )
{
    Object *oldArray = objects;
    int numToCopy = newSize < currentSize ? newSize : currentSize;

    objects = new Object[ newSize ];

    for( int k = 0; k < numToCopy; k++ )
        objects[ k ] = oldArray[ k ];

#ifdef WIN32
  if( currentSize != 0 )
#endif
    delete [ ] oldArray;
    currentSize = newSize;
}

#endif
