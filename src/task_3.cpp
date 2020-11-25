#include "task_3.hpp"

namespace task_3
{

List::List( const std::vector< std::string >& data_list )
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
}

void List::Deserialize( FILE* file )
{
	if( !file ) return;
}

} // namespace task_3