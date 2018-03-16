#include "Skiplist.h"

Skiplist::Skiplist()
{
    //initialize startnode of skiplist
    _StartNode = new ListNode(std::numeric_limits<int>::min(), nullptr, nullptr);
    //set random seed to current time in milliseconds
    std::srand(std::time(0));
}

Skiplist::~Skiplist()
{
    ListNode *curNode = _StartNode;

    //iterate over rows
    while(curNode != nullptr)
    {
        //store first pointer of next row
        ListNode *curNodeDown = curNode->_down;
        //iterate over columns
        while(curNode != nullptr)
        {
            //set pointer to current node
            ListNode *prevNode = curNode;
            //move right
            curNode = curNode->_right;
            //remove previous node
            delete prevNode;
        }
        //move down
        curNode = curNodeDown;
    }
}

unsigned Skiplist::GetRandomLevel()
{
    unsigned counter = 0;

    //flip coin
    while((std::rand() % 2))
    {
        counter++;
    }

    return counter;
}

unsigned Skiplist::height() const
{
    unsigned height_counter = 0;

    ListNode *curNode = _StartNode;

    //move down till end, increment height at each level
    while(curNode->_down != nullptr)
    {
        height_counter++;
        curNode = curNode->_down;
    }

    return height_counter;
}

size_t Skiplist::numElem() const
{
    unsigned numElem_counter = 0;

    ListNode *curNode = _StartNode;

    //move down to last row (contains all elements)
    while(curNode->_down != nullptr)
    {
        curNode = curNode->_down;
    }

    //count elements of last row
    while(curNode->_right != nullptr)
    {
        numElem_counter++;
        curNode = curNode->_right;
    }

    return numElem_counter;
}

bool Skiplist::insert(const int iVal)
{
    //flip coin and get level of element
    unsigned insertLevel = GetRandomLevel();
    //get height of current skiplist
    unsigned curLevel = height();

    //if new insert increases height of skiplist
    if(curLevel <= insertLevel)
    {
        //increase skiplist height till one above highest element
        while(curLevel <= insertLevel)
        {
            _StartNode->_down = new ListNode(std::numeric_limits<int>::min(), nullptr, _StartNode->_down);
            curLevel++;
        }
    }

    ListNode *curNode = _StartNode;
    //pointer to inserted node in previous row
    ListNode *lastNode = nullptr;


    //iterate over rows
    while(curNode->_down != nullptr)
    {
        //moving down and decrement current level
        curLevel--;
        curNode = curNode->_down;

        bool elemInserted = false;
        //iterate over columns
        while(curNode->_right != nullptr)
        {
            //element allready in skiplist (duplicate)
            if(iVal == (curNode->_right)->_val)
            {
                return false;
            }
            //element to the right smaller, move to right
            else if(iVal > (curNode->_right)->_val)
            {
                curNode = curNode->_right;
            }
            //element to right bigger, insert poistion fund
            else
            {
                //only start inserting, if insert level of element reached
                if(curLevel <= insertLevel)
                {
                    //create new node with given value and insert it before the node right of curNode
                    ListNode *node = new ListNode(iVal, curNode->_right, nullptr);
                    //set new right neighbor of curNode to inserted node
                    curNode->_right = node;

                    if(lastNode != nullptr)
                    {
                        //if node was inserted in previous row, construct link
                        lastNode->_down = node;
                    }

                    //remember inserted node for next iteration
                    lastNode = node;
                    //signal, that node was inserted at this level
                    elemInserted = true;
                }
                break;
            }
        }
        //if newly inserted element would be new right-most element of row
        if(curLevel <= insertLevel && !elemInserted)
        {
            ListNode *node = new ListNode(iVal, curNode->_right, nullptr);
            curNode->_right = node;

            if(lastNode != nullptr)
            {
                lastNode->_down = node;
            }

            lastNode = node;
        }
    }

    return true;
}

bool Skiplist::find(const int sVal)
{
    ListNode *curNode = _StartNode;

    //iterate over rows
    while(curNode->_down != nullptr)
    {
        curNode = curNode->_down;
        //iterate over columns
        while(curNode->_right != nullptr)
        {
            //we found the value and can stop
            if(sVal == (curNode->_right)->_val)
            {
                return true;
            }
            //move to the right
            else if(sVal > (curNode->_right)->_val)
            {
            	curNode = curNode->_right;
            }
            //element not in this row, move down
            else
            {
                break;
            }
        }
    }

    return false;
}

bool Skiplist::remove(const int rVal)
{
	ListNode *curNode = _StartNode;
	bool nodeRemoved = false;

    //iterate over rows
	while(curNode->_down != nullptr)
	{
		curNode = curNode->_down;
		//iterate over columns
		while(curNode->_right != nullptr)
		{
            //node was found
			if(rVal == (curNode->_right)->_val)
			{
                //relink
				ListNode *delNode = curNode->_right;
				curNode->_right = (curNode->_right)->_right;
				//delete
				delete delNode;
				//a node was found and deleted
				nodeRemoved = true;
				//move down
				break;
			}
			//move to right
			else if(rVal > (curNode->_right)->_val)
			{
				curNode = curNode->_right;
			}
			//move down
			else
			{
				break;
			}
		}
	}

	return nodeRemoved;
}

void Skiplist::visualize()
{
    ListNode *curNode = _StartNode;

    //iterate over rows
    while(curNode != nullptr)
    {
        //set pointer to first node of next row
        ListNode *curNodeD = curNode->_down;
        //iterate over columns
        while(curNode != nullptr)
        {
            //print node
            std::cout << curNode->_val << "   " << std::flush;
            //move right
            curNode = curNode->_right;
        }
        std::cout << std::endl;
        //move down to first pointer of next row
        curNode = curNodeD;

    }
}




