#include "task_1.hpp"
#include "task_2.hpp"
#include "task_3.hpp"

#include <cstdio>
// #include <stdio.h>

int main()
{
	/* ---- task 1 ---- */
	task_1::print_binary_representation( INT64_MIN );

	/* ---- task 2 ---- */
	char data[] = "hello wwwoorlld";
	task_2::dups_remove( data, strlen( data ) );
	printf( "%s\n", data );

	/* ---- task 3 ---- */
	task_3::List serialize_list{ { "one", "two", "three" } };
	auto fname = "serialized_data";
	FILE* file = fopen( fname, "wb" );
	serialize_list.Serialize( file );
	fclose( file );

	task_3::List deserialize_list;
	file = fopen( fname, "rb" );
	deserialize_list.Deserialize( file );
	deserialize_list.IterAll(
		[]( const task_3::ListNode* node )
		{
			printf( "----- list node -----\n");
			printf( "Node data: %s\n", node->mData.c_str() );
			printf( "Rand node data: %s\n\n", node->mRand ? node->mRand->mData.c_str() : "none" );
		} );

	fclose( file );

	return 0;
}