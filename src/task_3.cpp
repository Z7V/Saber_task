#include "task_3.hpp"

#include <string>
#include <unordered_map>
#include <cstring>

#define INDEX_TYPE uint16_t
#define DATA_LENGTH_SPECIFIER_TYPE size_t
#define FIRST_ELEMENT_INDEX 1

namespace task_3
{

static size_t MAX_LIST_LENGTH = UINT16_MAX - FIRST_ELEMENT_INDEX;

static const size_t BUFFER_MAX_SIZE = 2048;
static const size_t DATA_LENGTH_SPECIFIER = sizeof( DATA_LENGTH_SPECIFIER_TYPE );
static const size_t INDEX_LENGTH = sizeof( INDEX_TYPE );
static const DATA_LENGTH_SPECIFIER_TYPE DATA_MAX_LENGTH = BUFFER_MAX_SIZE - DATA_LENGTH_SPECIFIER - INDEX_LENGTH;

List::List()
	: mHead( nullptr )
	, mTail( nullptr )
{}

List::List( const std::vector< std::string >& data_list )
	: List()
{
	for( const auto& data : data_list )
	{
		auto new_node = new ListNode{ nullptr, mTail, mHead, data };

		if( mTail )
		{
			mTail->mNext = new_node;
			mTail = new_node;
		}
		else
		{
			mHead = mTail = new_node;
		}
	}
}

List::~List()
{
	auto target = mTail;
	while( target && target->mPrev )
	{
		target = target->mPrev;
		delete target->mNext;
	}
	if( mHead ) delete mHead;
}

void List::Serialize( FILE* file ) const
{
	if( !file || !mHead || !mTail ) return;

	std::unordered_map< ListNode*, INDEX_TYPE > nodes_map;
	INDEX_TYPE i = FIRST_ELEMENT_INDEX;
	for( auto cursor = mHead; cursor; cursor = cursor->mNext )
	{
		nodes_map.insert( std::make_pair( cursor, i ) );
		++i;
	}

	auto buffer = ( char* )malloc( BUFFER_MAX_SIZE );
	if( ! buffer )
	{
		printf( "List::Serialize() Error: no buffer memory allocated!" );
		return;
	}

	for( auto cursor = mHead; cursor; cursor = cursor->mNext )
	{
		auto rand_idx_itr = cursor->mRand ? nodes_map.find( cursor->mRand ) : nodes_map.end();
		auto data = cursor->mData.c_str();
		auto data_size = std::min( DATA_MAX_LENGTH, static_cast< DATA_LENGTH_SPECIFIER_TYPE >( cursor->mData.size() ) );
		auto rand_idx = rand_idx_itr != nodes_map.end() ? rand_idx_itr->second : 0;

		memcpy( buffer, reinterpret_cast< char* >( &data_size ), DATA_LENGTH_SPECIFIER );
		memcpy( buffer + DATA_LENGTH_SPECIFIER, reinterpret_cast< char* >( &rand_idx ), INDEX_LENGTH );
		memcpy( buffer + DATA_LENGTH_SPECIFIER + INDEX_LENGTH, data, data_size );
		fwrite( buffer, sizeof( char ), DATA_LENGTH_SPECIFIER + INDEX_LENGTH + data_size, file );
	}
	free( buffer );
}

void List::Deserialize( FILE* file )
{
	if( !file ) return;

	auto buffer = ( char* )malloc( BUFFER_MAX_SIZE );
	if( !buffer )
	{
		printf( "List::Deserialize() Error: no buffer memory allocated!" );
		return;
	}

	std::unordered_map< INDEX_TYPE, std::pair< ListNode*, INDEX_TYPE > > node_map;
	DATA_LENGTH_SPECIFIER_TYPE data_len;
	INDEX_TYPE rand_idx;
	ListNode* node;

	for( INDEX_TYPE i = FIRST_ELEMENT_INDEX; i < MAX_LIST_LENGTH; ++i )
	{
		auto more_data = ( bool )fread( buffer, sizeof( INDEX_TYPE ) + sizeof( DATA_LENGTH_SPECIFIER_TYPE ), 1, file );
		if( !more_data ) break;

		memcpy( &data_len, buffer, DATA_LENGTH_SPECIFIER );
		memcpy( &rand_idx, buffer + DATA_LENGTH_SPECIFIER, INDEX_LENGTH );

		fread( buffer, sizeof( char ), data_len, file );
		node = new ListNode{ nullptr, nullptr, nullptr, std::string( buffer, data_len ) };
		node_map.insert( std::make_pair( i, std::make_pair( node, rand_idx ) ) );
	}

	for( const auto& item : node_map )
	{
		auto curr_idx = item.first;
		auto rand_idx = item.second.second;
		node = item.second.first;
		if( curr_idx == FIRST_ELEMENT_INDEX ) 								mHead = node;
		else if( curr_idx == FIRST_ELEMENT_INDEX + node_map.size() - 1 )	mTail = node;

		if( curr_idx > FIRST_ELEMENT_INDEX )	node->mPrev = node_map[ curr_idx - 1 ].first;
		if( node_map.count( curr_idx + 1 ) )	node->mNext = node_map[ curr_idx + 1 ].first;
		if( rand_idx ) 						 	node->mRand = node_map[ rand_idx ].first;
	}

	free( buffer );
}

void List::IterAll( std::function< void( const ListNode* ) > callable ) const
{
	for( auto cursor = mHead; cursor; cursor = cursor->mNext )
	{
		callable( cursor );
	}
}

} // namespace task_3