/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the frame of GLib.
*/

#include <string.h>

#include "frame.h"
#include "utils.h"

static void TFrame_Init(TFrame *this, const char *frame_id);
static void TFrame_Free_All_Drawables(TFrame *this);

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
    this->Free_Drawable = TFrame_Free_Drawable;
    this->Free_Drawables = TFrame_Free_Drawables;
    this->Get_Drawable = TFrame_Get_Drawable;
    this->Draw_Drawables = TFrame_Draw_Drawables;
    this->window = NULL;
    this->frame_id = strdup(frame_id);
    this->initialized = 0;
    this->drawables_head = NULL;
}

static void TFrame_Free_All_Drawables(TFrame *this)
{
    TDrawable_Node *current = this->drawables_head;
    TDrawable_Node *tmp = NULL;

    while (current != NULL) {
        current->drawable->Free(current->drawable);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void TFrame_Add_Drawable(TFrame *this, TDrawable *drawable, const char *id, unsigned int priority)
{
    TDrawable_Node *drawable_node;

    if (drawable && this && id)
        drawable_node = malloc(sizeof(TDrawable_Node));
    else
        return;
    drawable_node->id = hash(id);
    drawable_node->drawable = drawable;
    drawable_node->priority = priority;
    if (this->drawables_head == NULL) {
        drawable_node->next = NULL;
        this->drawables_head = drawable_node;
    } else {
        TDrawable_Node *current = this->drawables_head;
        TDrawable_Node *previous = NULL;
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

TDrawable *TFrame_Remove_Drawable(TFrame *this, const char *id)
{
    if (!this || !id)
        return (NULL);

    TDrawable_Node *current = this->drawables_head;
    TDrawable_Node *previous = NULL;
    TDrawable *drawable = NULL;
    unsigned long uid = hash(id);

    while (current != NULL) {
        if (current->id == uid) {
            drawable = current->drawable;
            if (!previous)
                this->drawables_head = current->next;
            else
                previous->next = current->next;
            free(current);
            return drawable;
        }
        previous = current;
        current = current->next;
    }
    return drawable;
}

unsigned int TFrame_Free_Drawable(TFrame *this, const char *id)
{
    TDrawable *drawable = this->Remove_Drawable(this, id);

    if (drawable) {
        drawable->Free(drawable);
        return (1);
    }
    return (0);
}

unsigned int TFrame_Free_Drawables(TFrame *this, const char *id)
{
    unsigned int drawables_count = 0;
    unsigned int res;

    do {
        res = this->Free_Drawable(this, id);
        if (res) drawables_count++;
    } while (res);

    return (drawables_count);
}

TDrawable *TFrame_Get_Drawable(TFrame *this, const char *id)
{
    if (!this || !id)
        return (NULL);

    TDrawable_Node *current = this->drawables_head;
    unsigned long uid = hash(id);

    while (current != NULL) {
        if (current->id == uid)
            return current->drawable;
        current = current->next;
    }

    return (NULL);
}

void TFrame_Draw_Drawables(TFrame *this)
{
    TDrawable_Node *current = this->drawables_head;

    while (current != NULL) {
        if (current->drawable->is_visible)
            current->drawable->Draw(current->drawable, this);
        current = current->next;
    }
}

void TFrame_New_Free(TFrame *this)
{
    if (this) {
        TFrame_Free_All_Drawables(this);
        free(this->frame_id);
    }
    free(this);
}
