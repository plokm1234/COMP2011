#include "patch.h"

#include <iostream>
using namespace std;

/**
* Append a new line to the tail.
*
* @param patch: a patch pointer
* @param line: a line pointer
*/
void append_to_bottom(Patch *patch, Line *line)
{
    // edge case
    if (patch == nullptr || line == nullptr)
    {
        return;
    }

    // append to the tail, take care if there is no line.
    if (patch->tail == nullptr)
    {
        patch->tail = patch->head = line;
    }
    else
    {
        patch->tail->next = line;
        patch->tail = line;
    }
}

/**
* Delete the patch and the resources owned by it.
*
* @param patch, a patch pointer.
*/
void clear(Patch *&patch)
{
    // edge case
    if (patch == nullptr)
        return;

    // delete from head to tail
    Line *cur = patch->head;
    while (cur != nullptr)
    {
        Line *to_be_deleted = cur;
        cur = cur->next;
        delete to_be_deleted;
    }

    // avoid dangling pointers
    patch->head = nullptr;
    patch->tail = nullptr;

    // delete the allocated Patch
    delete patch;

    // set to nullptr
    patch = nullptr;
}

// helper function for reverse, a recursive version
void reverse_helper(Line *&head)
{
    // edge case
    if (head == nullptr || head->next == nullptr)
        return;

    // example to illustrate
    //
    // a  ->  b  ->  c  ->  ...  ->  z  -> nullptr
    // ^      ^
    // head   head->next

    // keep a pointer to the tail of the sub linked list, i.e. b
    Line *sub_tail = head->next;

    // now we have
    //
    // a  ->  b  ->  c  ->  ...  ->  z -> nullptr
    // ^      ^
    // head   head->next
    //        sub_tail

    // apply reverse starting from head->next
    reverse_helper(head->next);

    // after this, we have
    //
    // a  ->  z  ->  y  ->  ...  ->  b -> nullptr
    // ^      ^                      ^
    // head   head->next             sub_tail

    // put the old head next to the sub_tail
    sub_tail->next = head;
    // update the head pointer
    head = head->next;

    // now we have
    //
    // ┌ - - - - - - - - - - - - - - - ┐
    // v                               |
    // z  ->  y  ->  ...  ->  b  ->  a ┘
    // ^      ^               ^
    // head   head->next      sub_tail

    sub_tail->next->next = nullptr;

    // finally we get
    //
    // z  ->  y  ->  ...  ->  b  ->  a -> nullptr
    // ^      ^               ^
    // head   head->next      sub_tail
}

/**
* Reverse the linked list of lines.
*
* @param patch, a patch pointer.
*/
void reverse(Patch *patch)
{
    // change the tail to the head first
    patch->tail = patch->head;
    // apply the recursive helper function which only utilize head and next, no tail is needed.
    reverse_helper(patch->head);
}
