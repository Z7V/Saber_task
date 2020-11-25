#include "task_1.hpp"
#include "task_2.hpp"
#include "task_3.hpp"

#include <stdio.h>

int main()
{
	task_1::print_binary_representation( INT64_MIN );

	char data[] = "hello wwworlld";
	task_2::dups_remove( data, strlen( data ) );
	printf( "%s\n", data );


	return 0;
}