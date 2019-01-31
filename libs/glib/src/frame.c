/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the frame of GLib.
*/

#include <string.h>

#include "frame.h"

static void TFrame_Init(TFrame *this, const char *frame_id);
static void TFrame_Free_Drawables(TFrame *this);

TFrame* New_TFrame(const char *frame_id)
{
    TFrame *this = malloc(sizeof(TFrame));

    if(!this) return NULL;
    TFrame_Init(this, frame_id);
    this->Free = TFrame_New_Free;
    return this;
}

static void TFrame_Init(TFrame *this, const char *frame_id)
{
    this->Add_Drawable = TFrame_Add_Drawable;
    this->Remove_Drawable = TFrame_Remove_Drawable;
    this->Get_Drawable = TFrame_Get_Drawable;
    this->Draw_Drawables = TFrame_Draw_Drawables;
    this->frame_id = strdup(frame_id);
    this->initialized = 0;
    this->drawables_head = NULL;
}

static void TFrame_Free_Drawables(TFrame *this)
{
    Drawable_Node *current = this->drawables_head;
    Drawable_Node *tmp = NULL;

    while (current != NULL) {
        drawableCallFree(current);

        tmp = current;
        current = current->next;
        free(tmp->id);
        free(tmp);
    }
}

void TFrame_Add_Drawable(TFrame *this, void *drawable, drawables_e type, const char *id, unsigned int priority)
{
    Drawable_Node *drawable_node;

    if (drawable && this && id)
        drawable_node = malloc(sizeof(Drawable_Node));
    else
        return;
    drawable_node->id = strdup(id);
    drawable_node->drawable = drawable;
    drawable_node->type = type;
    drawable_node->priority = priority;
    if (this->drawables_head == NULL) {
        drawable_node->next = NULL;
        this->drawables_head = drawable_node;
    } else {
        Drawable_Node *current = this->drawables_head;
        Drawable_Node *previous = NULL;
        unsigned int found = 0;

        while (current != NULL && !found) {
            if (current->priority < priority)
                found = 1;
            else {
                previous = current;
                current = current->next;
            }
        }
        drawable_node->next = current;
        if (!previous)
            this->drawables_head = drawable_node;
        else
            previous->next = drawable_node;
    }
}

void *TFrame_Remove_Drawable(TFrame *this, const char *id)
{
    if (!this || !id)
        return (NULL);

    Drawable_Node *current = this->drawables_head;
    Drawable_Node *previous = NULL;
    void *drawable = NULL;

    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            drawable = current->drawable;
            if (!previous)
                this->drawables_head = current->next;
            else
                previous->next = current->next;
            free(current->id);
            free(current);
            return drawable;
        }
        previous = current;
        current = current->next;
    }
    return drawable;
}

void *TFrame_Get_Drawable(TFrame *this, const char *id)
{
    if (!this || !id)
        return (NULL);

    Drawable_Node *current = this->drawables_head;

    while (current != NULL) {
        if (strcmp(current->id, id) == 0)
            return current->drawable;
        current = current->next;
    }

    return (NULL);
}

void TFrame_Draw_Drawables(TFrame *this, TWindow *win)
{
    Drawable_Node *current = this->drawables_head;

    while (current != NULL) {
        drawableCallDraw(current, win);
        current = current->next;
    }
}

void TFrame_New_Free(TFrame *this)
{
    if (this) {
        TFrame_Free_Drawables(this);
        free(this->frame_id);
    }
    free(this);
}
