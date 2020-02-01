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
    // edge case
    if (canvas == nullptr || patch == nullptr)
        return;

    // initialize a new patch node
    PatchNode *node = new PatchNode;
    node->below = nullptr;
    node->above = nullptr;
    node->patch = patch;

    // append to bottom, take care of the case where nothing in the canvas
    if (canvas->bottom == nullptr)
    {
        canvas->bottom = canvas->top = node;
    }
    else
    {
        node->above = canvas->bottom;
        canvas->bottom->below = node;
        canvas->bottom = node;
    }
}

/**
* Delete the canvas and the resources owned by it.
*
* @param canvas, a canvas pointer.
*/
void clear(Canvas *&canvas)
{
    // edge case
    if (canvas == nullptr)
        return;

    // clear from top to bottom
    PatchNode *current = canvas->top;
    while (current != nullptr)
    {
        PatchNode *to_be_deleted = current;
        // clear the memory of its patch
        clear(current->patch);
        current = current->below;
        delete to_be_deleted;
    }

    // avoid dangling pointer
    canvas->selected = nullptr;
    canvas->top = nullptr;
    canvas->bottom = nullptr;

    // delete the allocated canvas
    delete canvas;

    // set the pointer to nullptr
    canvas = nullptr;
}

/**
* Render the canvas to a buffer without border. Selected patch will be hightlighted as '@'.
*
* @param canvas, a canvas pointer.
* @return buffer, a height x width 2d array, required by the provided print function.
*/
char **render(const Canvas *canvas)
{
    // edge case
    if (canvas == nullptr)
    {
        return nullptr;
    }

    // initialize the buffer
    char **buffer = new char *[canvas->height];
    for (int i = 0; i < canvas->height; ++i)
    {
        buffer[i] = new char[canvas->width];
        for (int j = 0; j < canvas->width; ++j)
        {

            buffer[i][j] = ' ';
        }
    }

    // draw the patches, first draw the bottom ones and then the above to guarantee the correct overlaps
    for (PatchNode *node = canvas->bottom; node; node = node->above)
    {
        Patch *patch = node->patch;
        int x = patch->x;
        int y = patch->y;

        Line *line = patch->head;
        int i = 0;
        while (line != nullptr && x + i < canvas->height)
        {
            if (x + i >= 0)
            {
                int j = 0;
                while (j < line->data.size() && y + j < canvas->width)
                {
                    if (y + j >= 0)
                    {
                        // draw the non-transperant character
                        if (line->data[j] != ' ')
                        {
                            if (node == canvas->selected)
                            {
                                // highlight the selected
                                buffer[x + i][y + j] = '@';
                            }
                            else
                            {
                                // normal drawing
                                buffer[x + i][y + j] = line->data[j];
                            }
                        }
                    }
                    j++;
                }
            }
            i++;
            line = line->next;
        }
    }

    // return the buffer for printing
    return buffer;
}

// helper function to swap the current and the above
void bring_selected_above_helper(Canvas *canvas, PatchNode *current, PatchNode *above)
{
    // edge case, do nothing
    if (canvas == nullptr || current == nullptr || above == nullptr)
        return;

    // update the far away nodes first
    // the above of above
    if (above->above)
    {
        above->above->below = current;
    }
    else
    {
        canvas->top = current;
    }

    // the below of current
    if (current->below)
    {
        current->below->above = above;
    }
    else
    {
        canvas->bottom = above;
    }

    // update those pointing to the far away nodes
    above->below = current->below;
    current->above = above->above;

    // update the rest
    current->below = above;
    above->above = current;
}

/**
* Bring the selected patch node above by one node, do nothing if not applicable.
*
* @param canvas, a canvas pointer.
*/
void bring_selected_above(Canvas *canvas)
{
    if (canvas && canvas->selected)
    {
        bring_selected_above_helper(canvas, canvas->selected, canvas->selected->above);
    }
}

/**
* Send the selected patch node below by one node, do nothing if not applicable.
*
* @param canvas, a canvas pointer.
*/
void send_selected_below(Canvas *canvas)
{
    if (canvas && canvas->selected)
    {
        bring_selected_above_helper(canvas, canvas->selected->below, canvas->selected);
    }
}

// helper function to select a coordinate, node_out and char_out will be set to the corresponding node and char
void select_helper(Canvas *canvas, int x, int y, PatchNode **node_out = nullptr, char **char_out = nullptr)
{
    // set default value for outputs
    if (node_out != nullptr)
    {
        *node_out = nullptr;
    }

    if (char_out != nullptr)
    {
        *char_out = nullptr;
    }

    // edge case
    if (canvas == nullptr)
        return;

    // check from top to bottom
    for (PatchNode *node = canvas->top; node; node = node->below)
    {
        // relative position to the patch
        int i = x - node->patch->x;
        int j = y - node->patch->y;

        // find the correct line, line != nulltpr and i = 0 means found
        Line *line = node->patch->head;
        while (line != nullptr && i > 0)
        {
            line = line->next;
            i--;
        }

        // find the correct column, only select when it is not transperant
        if (line != nullptr && i == 0 && j >= 0 && j < line->data.size() && line->data[j] != ' ')
        {
            if (node_out != nullptr)
            {
                *node_out = node;
            }

            if (char_out != nullptr)
            {
                *char_out = &line->data[j];
            }
            return;
        }
    }
}

/**
* Select the top patch among the patches that covers (x, y). A patch cover a position means it has an non-transparant character on it. Selection of out of bound position should be allowed, despite that the position is not rendered.
*
* @param canvas, a canvas pointer.
* @param x, canvas row to select.
* @param y, canvas column to select.
*/
void select_at(Canvas *canvas, int x, int y)
{
    select_helper(canvas, x, y, &canvas->selected);
}

// helper function to check whether a patch is empty
bool is_empty_patch(const Patch *patch)
{
    for (Line *line = patch->head; line; line = line->next)
    {
        for (int i = 0; i < line->data.size(); ++i)
        {
            if (line->data[i] != ' ')
            {
                return false;
            }
        }
    }
    return true;
}

/**
* Erase all characters at (x, y) until there is no non-transparant character on (x, y). If a patch node contains no non-transparant character after the erasing, it will be deleted. Erasing of out of bound position should be allowed, despite that the position is not rendered.
*
* @param canvas, a canvas pointer.
* @param x, canvas row to erase.
* @param y, canvas column to erase.
*/
void erase_pixel_at(Canvas *canvas, int x, int y)
{
    // keep selecting until nothing can be selected.
    while (true)
    {
        PatchNode *node = nullptr;
        char *ch = nullptr;

        select_helper(canvas, x, y, &node, &ch);

        // nothing to erase already, finished.
        if (ch == nullptr || node == nullptr)
        {
            break;
        }

        // erase this character
        *ch = ' ';

        if (is_empty_patch(node->patch))
        {
            // deselect the erased node
            if (canvas->selected == node)
            {
                canvas->selected = nullptr;
            }

            // if only one node in the list
            if (node->above == nullptr && node->below == nullptr)
            {
                canvas->bottom = canvas->top = nullptr;
            }
            // the selected is the top one
            else if (node->above == nullptr)
            {
                canvas->top = node->below;
                canvas->top->above = nullptr;
            }
            // the selected is the bottom one
            else if (node->below == nullptr)
            {
                canvas->bottom = node->above;
                canvas->bottom->below = nullptr;
            }
            // the selected is of the middle ones
            else
            {
                node->above->below = node->below;
                node->below->above = node->above;
            }

            // finally delete the node
            clear(node->patch);
            delete node;
        }
    }
}
