#include "patch.h"

#include <cstring>
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
	  if(patch->head==nullptr){
		  patch->head=line;
		  patch->tail=line;}
	  else{
		  patch->tail->next=line;
		  patch->tail=line;
	  }
}

/**
* Delete the patch and the resources owned by it.
*
* @param patch, a patch pointer.
*/
void clear(Patch *&patch)
{
Line*cur= patch->head;
Line*next=nullptr;
while (cur != NULL)
{
    next = cur->next;
    delete cur;
    cur = next;
}
  delete patch;
}


/**
* Reverse the linked list of lines.
*
* @param patch, a patch pointer.
*/
void reverse(Patch *patch)
{
if(patch->head==nullptr){return;}
else{
	patch->tail=patch->head;
	Line*cur=patch->head;
	Line*p=nullptr;
	Line*n=nullptr;
	while(cur!=nullptr){
		n=cur->next;
		cur->next=p;
		p=cur;
		cur=n;
	}
	patch->head=p;
	}
}
