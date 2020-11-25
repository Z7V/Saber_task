#pragma once

#include <string>
#include <vector>

namespace task_3
{

struct ListNode
{
	ListNode* mNext;
	ListNode* mPrev;
	ListNode* mRand;
	std::string mData;
};

class List
{
public:
	List( const std::vector< std::string >& data_list );
	~List();

	void Serialize( FILE* file ) const;
	void Deserialize( FILE* file );

private:
	ListNode* mHead;
	ListNode* mTail;
};

} // namespace task_3