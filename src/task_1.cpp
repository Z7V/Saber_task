#include "task_1.hpp"

#include <iostream>
#include <sstream>

namespace task_1
{

void print_binary_representation( int64_t value )
{
	std::stringstream result;
	for( auto i = sizeof( value ) * 8; i > 0; --i )
		result << ( bool )( ( ( int64_t )1 << ( i - 1 ) ) & value );
	std::cout << result.str() << std::endl;
}

} // namespace task_1
