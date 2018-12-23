#ifndef SVECTOR_H
#define SVECTOR_H

#include <stdio.h>	

#define svector Vector

class ArrayIndexOutOfBounds { };

template <class Object>
class svector
{
  public:
    explicit svector( int theSize = 0 ) : currentSize( theSize )
      { objects = new Object[ currentSize ]; }
    svector( const svector & rhs ) : objects( NULL )
      { operator=( rhs ); }
    ~svector( )
#ifndef WIN32
      { delete [ ] objects; }
#else
      { if( currentSize != 0 ) delete [ ] objects; }
#endif

    int size( ) const
      { return currentSize; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }


    const svector & operator = ( const svector & rhs );
    void resize( int newSize );
  private:
    int currentSize;
    Object * objects;
};

#endif


