#include "canvas.h"

#include <iostream>

using namespace std;

/**
 * Append to the bottom.
 *
 * @param canvas: a canvas pointer
 * @param patch: a patch pointer
 */
void append_to_bottom(Canvas *canvas, Patch *patch)
{
	PatchNode *p = new PatchNode;
	p->patch = patch;

	if (canvas->top == nullptr)
	{

		canvas->top = p;
		canvas->bottom = p;
		p->above = nullptr;
		p->below = nullptr;
	}
	else
	{
		p->above = canvas->bottom;
		canvas->bottom->below = p;
		canvas->bottom = p;
		p->below = nullptr;
	}
}

/**
 * Delete the canvas and the resources owned by it.
 *
 * @param canvas, a canvas pointer.
 */
void clear(Canvas *&canvas)
{
	if(canvas==nullptr){
		return;
	}

	PatchNode *cur = canvas->top;
	PatchNode *next = nullptr;
	PatchNode *finish = canvas->bottom;
	while (cur != NULL)
	{	if(cur!=canvas->bottom){next = cur->below;}else{next=nullptr;}
		
		clear(cur->patch);
		delete cur;
		
		cur = next;
	}
	delete canvas;
}

/**
 * Render the canvas to a buffer without border. Selected patch will be hightlighted as '@'.
 *
 * @param canvas, a canvas pointer.
 * @return buffer, a height x width 2d array, required by the provided print function.
 */

char **render(const Canvas *canvas)
{
	if(canvas==nullptr){
		return 0;
	}

	char **a = new char *[canvas->height];
	for (int i = 0; i < canvas->height; i++)
	{
		a[i] = new char[canvas->width];
	}

	for (int i = 0; i < canvas->height; i++)
	{
		for (int j = 0; j < canvas->width; j++)
		{
			a[i][j] = ' ';
		}
	}

	PatchNode *current = canvas->top;
	Patch *cur = current->patch;
	Line *b = cur->head;
	for (int q = 0; q <= 10000; q++)
	{
		for (int i = cur->x; i < canvas->height; i++)
		{
			for (int j = cur->y, k = 0; (k < b->data.size() && j<canvas->width); j++, k++)
			{
				if (a[i][j] == ' ')
				{
					a[i][j] = b->data.at(k);
				}
			}
			if (b != cur->tail)
			{
				b = b->next;
			}
			else
			{
				break;
			}
		}

		if (current != canvas->bottom)
		{
			current = current->below;
		}
		else
		{
			break;
		}
		cur = current->patch;
		b = cur->head;
	}

	if (canvas->selected != nullptr)
	{
		for (int i = 0; i < canvas->height; i++)
		{
			for (int j = 0; j < canvas->width; j++)
			{
				if (a[i][j] == canvas->selected->patch->head->data.at(0))
				{
					a[i][j] = '@';
				}
			}
		}
	}


	return a;
	
}

/**
 * Bring the selected patch node above by one node, do nothing if not applicable.
 *
 * @param canvas, a canvas pointer.
 */
void bring_selected_above(Canvas *canvas)
{
	PatchNode *pre = nullptr;
	if (canvas->selected->above != nullptr)
	{
		pre = canvas->selected->above;
	}
	PatchNode *cur = nullptr;
	cur = canvas->selected;
	PatchNode *nex = nullptr;
	if (canvas->selected->below != nullptr)
	{
		nex = canvas->selected->below;
	}

	if (canvas->selected == canvas->top)
	{
		return;
	}

	if (canvas->selected == canvas->bottom)
	{
		cur->above = pre->above;
		pre->above->below = cur;
		pre->below = nullptr;
		cur->below = pre;
		pre->above = cur;
		canvas->bottom = pre;
	}
	else if (pre->above == nullptr)
	{
		canvas->top = cur;
		cur->above = nullptr;
		pre->below = nex;
		pre->above = cur;
		cur->below = pre;
		nex->above = pre;
	}
	else
	{
		cur->above = pre->above;
		pre->above->below = cur;
		pre->above = cur;
		pre->below = nex;
		cur->below = pre;
		nex->above = pre;
	}
}

/**
 * Send the selected patch node below by one node, do nothing if not applicable.
 *
 * @param canvas, a canvas pointer.
 */
void send_selected_below(Canvas *canvas)
{

	PatchNode *pre = nullptr;
	if (canvas->selected->above != nullptr)
	{
		pre = canvas->selected->above;
	}
	PatchNode *cur = nullptr;
	cur = canvas->selected;
	PatchNode *nex = nullptr;
	if (canvas->selected->below != nullptr)
	{
		nex = canvas->selected->below;
	}

	if (canvas->selected == canvas->bottom)
	{
		return;
	}
	//if (nex == canvas->bottom)
	//{
	//	canvas->bottom = cur;
	//}

	if (canvas->selected == canvas->top)
	{
		nex->above = nullptr;
		cur->below = nex->below;
		nex->below->above = cur;
		nex->below = cur;
		cur->above = nex;
		canvas->top = nex;
	}
	else if (nex->below == nullptr)
	{
		canvas->bottom = cur;
		pre->below = nex;
		cur->below = nullptr;
		nex->below = cur;
		nex->above = pre;
		cur->above = nex;
	}
	else
	{

		cur->below = nex->below;
		nex->below->above = cur;
		cur->above = nex;
		nex->below = cur;
		nex->above = pre;
		pre->below = nex;
	}
}

/**
 * Select the top patch among the patches that covers (x, y). A patch conver a position means it has an non-transparant character on it. Selection of out of bound position should be allowed, despite that the position is not rendered.
 *
 * @param canvas, a canvas pointer.
 * @param x, canvas row to select.
 * @param y, canvas column to select.
 */

void select_at(Canvas *canvas, int x, int y)
{
	bool loopback = true;
	PatchNode *cur = canvas->top;
	Line *curr = nullptr;
	while (loopback)
	{
		loopback = false;
		int row_diff = x - cur->patch->x;
	
		if (row_diff < 0)
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		} //switch between patch

		curr = cur->patch->head;
		for (; row_diff != 0 && curr != cur->patch->tail; row_diff--)
		{
			curr = curr->next;
		}

		if (row_diff > 0 && curr == cur->patch->tail)
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		}

		int col_diff = y - cur->patch->y;
		
		if (curr->data.size() <= col_diff)
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		}
		//cout<<curr->data.at(col_diff);
		//cout<<row_diff<<","<<col_diff;
		if (curr->data.size() > col_diff && curr->data.at(col_diff) != ' ')
		{
			canvas->selected = cur;
		}
		else //if (curr->data.size() > col_diff && curr->data.at(col_diff) == ' ')
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		}

		//switch between line
		// check column
	}
}
/**
 * Erase all characters at (x, y) until there is no non-transparant character on (x, y). If a patch node contains no non-transparant character after the erasing, it will be deleted. Erasing of out of bound position should be allowed, despite that the position is not rendered.
 *
 * @param canvas, a canvas pointer.
 * @param x, canvas row to erase.
 * @param y, canvas column to erase.
 */
void checkEmptyPatch(Canvas *canvas,PatchNode *currr){
	PatchNode *cur = currr;
	Line *curr = nullptr;
	bool needclean = false;
	curr=cur->patch->head;

	do{
		for(int i=0;i<curr->data.size();i++){
			if(curr->data.at(i)!=' '){return;}
			if(curr!=cur->patch->tail){curr=curr->next;}
		}
		needclean=true;
	}
	while(curr!=cur->patch->tail);
		if(needclean){
			if(cur==canvas->top){
							PatchNode* idontwant=cur;
							PatchNode* next=cur->below;
							canvas->top=next;
							clear(idontwant->patch);
							delete idontwant;
							idontwant=nullptr;
							
							next=nullptr;
						}
						else if(cur==canvas->bottom){
							PatchNode* idontwant=cur;
							PatchNode* pre=cur->above;
							canvas->bottom=pre;
							clear(idontwant->patch);
							delete idontwant;
							idontwant=nullptr;
							pre=nullptr;
							
						}
						else {
							PatchNode* idontwant=cur;
							PatchNode* pre=cur->above;
							PatchNode* next=cur->below;
							pre->below=next;
							next->above=pre;
							clear(idontwant->patch);
							delete idontwant;
							idontwant=nullptr;
							pre=nullptr;
							next=nullptr;
						}
	}
}
void erase_pixel_at(Canvas *canvas, int x, int y)
{
		bool loopback = true;
	PatchNode *cur = canvas->top;
	Line *curr = nullptr;
	while (loopback)
	{
		loopback = false;
		int row_diff = x - cur->patch->x;
		if (row_diff < 0)
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		} //switch between patch

		curr = cur->patch->head;
		for (; row_diff != 0 && curr != cur->patch->tail; row_diff--)
		{
			curr = curr->next;
		}

		if (row_diff > 0 && curr == cur->patch->tail)
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		}

		int col_diff = y - cur->patch->y;
		if (curr->data.size() <= col_diff)
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		}

		if (curr->data.size() > col_diff && curr->data.at(col_diff) != ' ')
		{
			curr->data.at(col_diff) = ' ';
			checkEmptyPatch(canvas,cur);
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		}
		else if (curr->data.size() > col_diff && curr->data.at(col_diff) == ' ')
		{
			loopback = true;
			if (cur != canvas->bottom)
			{
				cur = cur->below;
				continue;
			}
			else
			{
				canvas->selected = nullptr;
				return;
			}
		}

		//switch between line
		// check column
	}
}
