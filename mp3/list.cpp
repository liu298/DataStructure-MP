/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */
#include "rgbapixel.h"
#include <iostream>
using namespace std;

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{

   if(head == NULL)
    return;
else
{
   ListNode * curr = head;
   ListNode * coming;

 while(curr->next != NULL)
   {
    coming = curr->next;

    curr->next = NULL;
    curr->prev = NULL;
    delete curr;
    curr = coming;

   }

   delete curr;
   curr= NULL;
   length = 0;
 }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    ListNode * temp = new ListNode(ndata);
    if(head==NULL)
    {
        head = temp;
        tail = temp;
        head->prev = NULL;
        tail->next = NULL;
       length++;
    }
    else
    {
        head->prev = temp;
        temp->next = head;
        head = temp;
        length++;
    }
    // delete temp;
    //temp = NULL;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    ListNode * temp = new ListNode(ndata);
    if(head==NULL)
    {
        head = temp;
        tail = temp;
	head->prev = NULL;
        tail->next = NULL;
       length++;
    }
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        length++;
    }
   // delete temp;
   // temp = NULL;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
   if(startPoint == NULL && endPoint == NULL)
    {
        return;
    }

    ListNode * t_head;
    ListNode * t_tail;

    ListNode * curr;
    ListNode * coming;

   // t_head = startPoint;
   // t_tail = endPoint;

    //maintain the rest points in the list
    t_head =  startPoint->prev;
    t_tail = endPoint->next;
    curr = startPoint;

    while(curr != endPoint)
    {
        coming = curr->next;
        curr->next = curr->prev;
        curr->prev = coming;
        curr = coming;
    }

    curr->next = curr->prev;

    if(t_tail != NULL)
    //link the reversed part with the rest of the list
    {
    t_tail->prev = startPoint;
    startPoint->next = t_tail;
    }
    else
    {
    startPoint->next = NULL;
    }

    if(t_head != NULL)
    {
    endPoint->prev = t_head;
    t_head->next = endPoint;
     }
    else
    {
        endPoint->prev = NULL;
    }

     curr = startPoint;
     startPoint = endPoint;
     endPoint = curr;
    // cout << "Reached line 197" << endl;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{   ListNode * curr;
    ListNode * _head;
    ListNode * _tail;
    ListNode * last_head;
    ListNode * last_tail;

   if (n >= length)
    {
        reverse( head, tail);
        return;
    }
    if (n <= 1)
    {
        return;
    }
   else
   {

        _head = head;
        _tail = _head->next;

    while(_tail != NULL)//!!!!!!!!!
        {
            //find the head node and end node in a nth list
            int i=1;
            while(i < n-1 && _tail->next != NULL)
            {
                _tail = _tail->next;
                i++;
            }
            if(_tail->next != NULL)
            {
            reverse( _head,  _tail);

            last_head = _head;
            last_tail = _tail;

            _head = last_tail->next;
	    _tail = _head->next;
            }
            else break;
        }

            _tail = tail;
            reverse(_head, _tail);
	    last_head = _head;
            last_tail = _tail;

	tail = last_tail;
	curr = tail->prev;
	while( curr->prev !=NULL)
	{
	curr = curr->prev;
	}
	head = curr;
   }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{

    ListNode * curr;
    ListNode * coming;
    if(head == NULL && tail == NULL)
    {
        return;
    }
    else
    {
        curr = head->next;
        coming = curr->next ->next;

       while (coming != NULL)
       {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        curr->prev = tail;
        tail->next = curr;
        tail = curr;
        tail->next = NULL;

        curr = coming;
        coming = curr->next ->next;

       }
       if (curr != tail)
       {
       curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        curr->prev = tail;
        tail->next = curr;
        tail = curr;
        tail->next = NULL;

       }
   }

      /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
            length = splitPoint;

    }

    // set up the returned list

    List<T> ret;

    ret.head = secondHead;

    ret.tail = secondHead;

    if (ret.tail != NULL) {

        while (ret.tail->next != NULL)

            ret.tail = ret.tail->next;

    }

    ret.length = oldLength - splitPoint;

    return ret;

}

/**

 * Helper function to split a sequence of linked memory at the node

 * splitPoint steps **after** start. In other words, it should disconnect

 * the sequence of linked memory after the given number of nodes, and

 * return a pointer to the starting node of the new sequence of linked

 * memory.

 *

 * This function **SHOULD NOT** create **ANY** new List objects!

 *

 * @param start The node to start from.

 * @param splitPoint The number of steps to walk before splitting.

 * @return The starting node of the sequence that was split off.

 */

template <class T>

typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)

{

    if(splitPoint == 0) return head;
    else
    {
    ListNode * curr;
    ListNode * second;
    curr = start;

    for(int i=1;i<splitPoint;i++)
        {
        curr = curr->next;
        }

    second = curr->next;
    curr->next = NULL;
    second->prev = NULL;
    return second;
    }

}

/**

 * Merges the given sorted list into the current sorted list.

 *

 * @param otherList List to be merged into the current list.

 */

template <class T>

void List<T>::mergeWith(List<T>& otherList)

{
    // set up the current list

    head = merge(head, otherList.head);

    tail = head;

    // make sure there is a node in the new list

    if (tail != NULL) {

        while (tail->next != NULL)

            tail = tail->next;

    }

    length = length + otherList.length;

    // empty out the parameter list

    otherList.head = NULL;

    otherList.tail = NULL;

    otherList.length = 0;

}

/**

 * Helper function to merge two **sorted** and **independent** sequences of

 * linked memory. The result should be a single sequence that is itself

 * sorted.

 *

 * This function **SHOULD NOT** create **ANY** new List objects.

 *

 * @param first The starting node of the first sequence.

 * @param second The starting node of the second sequence.

 * @return The starting node of the resulting, sorted sequence.

 */

template <class T>

typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)

{

    if(first == NULL && second != NULL) return second;
    else if (second == NULL && first != NULL) return first;
    else if (first == NULL && second == NULL) return NULL;
    else
    {

    ListNode * sec_curr = second;
    ListNode * curr = first;
    ListNode * temp;

    while(curr != NULL && sec_curr != NULL)
        {
            if((curr->data) < (sec_curr->data))
            {
	      temp = curr;
            curr = curr->next;
            }

	    else
	    {
	      if(curr->prev != NULL)
	      {
               temp = sec_curr->next;
	       curr->prev->next = sec_curr;
	       sec_curr->prev = curr->prev;

               curr->prev = sec_curr;
               sec_curr->next = curr;
               sec_curr = temp;
	      }
	      else
		{
		temp = sec_curr->next;
		// curr->prev->next = sec_curr;
		 sec_curr->prev = curr->prev;

                curr->prev = sec_curr;
                sec_curr->next = curr;
                sec_curr = temp;
		}
            }
        }

    if(curr == NULL)
      {
	temp->next = sec_curr;
	sec_curr->prev = temp;
       	curr = sec_curr;

      }
    /*
//only reach to the tail of first list
    if(curr->next == NULL && sec_curr->next != NULL)
    {
	if((sec_curr->data) < (curr->data)) //big first tail
	{
 	while(sec_curr->next != NULL && ((sec_curr->data) < (curr->data)))
	    {
 	    temp = sec_curr->next;
	    curr->prev->next = sec_curr;
	    sec_curr->prev = curr->prev;

            curr->prev = sec_curr;
            sec_curr->next = curr;
            sec_curr = temp;
            }

	if(sec_curr->next == NULL) //both tail
	   {
		if((curr->data) < (sec_curr->data))
		{
		curr->next = sec_curr;
		sec_curr->prev = curr;
		}
		else
		{
		curr->prev->next = sec_curr;
		sec_curr->prev = curr->prev;

		curr->prev = sec_curr;
		sec_curr->next = curr;
		}
           }
	else 	  //finally first tail less than or equals second
	   {
    		curr->next = sec_curr;
		sec_curr->prev = curr;
           }
	}
	else //small first tail
	{
	curr->next = sec_curr;
	sec_curr->prev = curr;
	}
    }

//only reach to the tail of second list
 	if(curr->next != NULL && sec_curr->next == NULL)
    {
	if((sec_curr->data) < (curr->data))  //small second tail
	{
	    curr->prev->next = sec_curr;
	    sec_curr->prev = curr->prev;

            curr->prev = sec_curr;
            sec_curr->next = curr;
	}
	else         //big second tail
	{
	while(curr->next != NULL && ((curr->data) < (sec_curr->data)))
	curr = curr->next;

	if(curr->next == NULL)    //both tail
	   {
           	if((curr->data) < (sec_curr->data))
		{
		curr->next = sec_curr;
		sec_curr->prev = curr;
		}
		else
		{
            	curr->prev->next = sec_curr;
	        sec_curr->prev = curr->prev;

		curr->prev = sec_curr;
		sec_curr->next = curr;
		}
	   }
	else          //second tail finally less than or equals to first
	   {
	    curr->prev->next = sec_curr;
	    sec_curr->prev = curr->prev;

	    curr->prev = sec_curr;
            sec_curr->next = curr;
           }

      	}
    }

//reach to both tail
    else
    {
	if((curr->data) < (sec_curr->data))
		{
		curr->next = sec_curr;
		sec_curr->prev = curr;
		}
		else
		{
	    curr->prev->next = sec_curr;
	    sec_curr->prev = curr->prev;

		curr->prev = sec_curr;
		sec_curr->next = curr;
		}
		}*/

    if((second->data)<(first->data)) return second;
    else return first;

    }

}

/**

 * Sorts the current list by applying the Mergesort algorithm.

 */

template <class T>

void List<T>::sort()

{

    if (empty())

        return;

    head = mergesort(head, length);

    tail = head;

    while (tail->next != NULL)

        tail = tail->next;

}

/**

 * Sorts a chain of linked memory given a start node and a size.

 * This is the recursive helper for the Mergesort algorithm (i.e., this is

 * the divide-and-conquer step).

 *

 * @param start Starting point of the chain.

 * @param chainLength Size of the chain to be sorted.

 * @return A pointer to the beginning of the now sorted chain.

 */

template <class T>

typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)

{
    ListNode * second ;
    ListNode * first;
    ListNode * l1 ;
    ListNode * l2;

    if(chainLength <= 1)
	return start;
    else
    {
	second = split(start,chainLength/2);
	l1 = mergesort(start, chainLength/2);
        l2 = mergesort(second,chainLength-(chainLength/2));
        first = merge(l1, l2);

	return first ;
      }
}
