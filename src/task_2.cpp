#include "task_2.hpp"

#include <cstdlib>
#include <exception>
#include <functional>
#include <stdio.h>

static size_t MAX_LENGTH = 1024; 

namespace task_2
{
	void dups_remove( char* data, size_t len )
	{
		if( len >= MAX_LENGTH ) throw std::bad_function_call();

		char* buffer = ( char* )malloc( MAX_LENGTH );
		auto cursor = buffer;
		for( auto i = 0; i < len; ++i )
		{
			if( i == 0 || *( cursor - 1 ) != *( data + i ) )
			{
				*cursor = *( data + i );
				++cursor;
			}
		}
		*cursor = '\0';
		memcpy( data, buffer, strlen( buffer ) + 1 );
		free( buffer );
	}

} // namespace task_2
