/*******************************************************************************
* PROJECT: gLib
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include <string.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

#include "frame.h"
#include "utils.h"

static void TFrame_Init(TFrame *this, const char *frame_id);

TFrame* New_TFrame(const char *frame_id)
{
    TFrame *this = malloc(sizeof(TFrame));

    if(!this) return (NULL);
    TFrame_Init(this, frame_id);
    this->Free = TFrame_New_Free;
    return (this);
}

static void TFrame_Init(TFrame *this, const char *frame_id)
{
    if (!this || !frame_id) return;

    this->Add_Drawable = TFrame_Add_Drawable;
    this->Remove_Drawable = TFrame_Remove_Drawable;
    this->Remove_Drawable_Obj = TFrame_Remove_Drawable_Obj;
    this->Free_Drawable = TFrame_Free_Drawable;
    this->Free_Drawable_Obj = TFrame_Free_Drawable_Obj;
    this->Free_Drawables = TFrame_Free_Drawables;
    this->Get_Drawable = TFrame_Get_Drawable;
    this->Draw_Drawables = TFrame_Draw_Drawables;
    this->Free_All_Drawables = TFrame_Free_All_Drawables;
    this->window = NULL;
    this->frame_id = strdup(frame_id);
    this->initialized = 0;
    this->drawables_head = NULL;
}

void TFrame_Add_Drawable(TFrame *this, TDrawable *drawable, const char *id, unsigned int priority, unsigned int free_strategy)
{
    TDrawable_Node *drawable_node;

    if (!this || !drawable || !id) return;

    drawable_node = malloc(sizeof(TDrawable_Node));
    if (!drawable_node) return;

    drawable_node->id = hash(id);
    drawable_node->drawable = drawable;
    drawable_node->priority = priority;
    drawable_node->free_strategy = free_strategy;
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
    if (!this || !id) return (NULL);

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
            return (drawable);
        }
        previous = current;
        current = current->next;
    }
    return (drawable);
}

unsigned int TFrame_Remove_Drawable_Obj(TFrame *this, TDrawable *drawable)
{
    if (!this || !drawable) return (0);

    TDrawable_Node *current = this->drawables_head;
    TDrawable_Node *previous = NULL;

    while (current != NULL) {
        if (current->drawable == drawable) {
            if (!previous)
                this->drawables_head = current->next;
            else
                previous->next = current->next;
            free(current);
            return (1);
        }
        previous = current;
        current = current->next;
    }
    return (0);
}

unsigned int TFrame_Free_Drawable(TFrame *this, const char *id)
{
    if (!this || !id) return (0);

    TDrawable *drawable = this->Remove_Drawable(this, id);

    if (drawable && drawable->Free) {
        drawable->Free(drawable);
        return (1);
    }
    return (0);
}

unsigned int TFrame_Free_Drawable_Obj(TFrame *this, TDrawable *drawable)
{
    if (!this || !drawable) return (0);

    unsigned int result = this->Remove_Drawable_Obj(this, drawable);

    if (result && drawable->Free) {
        drawable->Free(drawable);
        return (1);
    }
    return (0);
}

unsigned int TFrame_Free_Drawables(TFrame *this, const char *id)
{
    if (!this || !id) return (0);

    unsigned int drawables_count = 0;
    unsigned int res = 0;

    do {
        res = this->Free_Drawable(this, id);
        if (res) drawables_count++;
    } while (res);

    return (drawables_count);
}

TDrawable *TFrame_Get_Drawable(TFrame *this, const char *id)
{
    if (!this || !id) return (NULL);

    TDrawable_Node *current = this->drawables_head;
    unsigned long uid = hash(id);

    while (current != NULL) {
        if (current->id == uid)
            return (current->drawable);
        current = current->next;
    }

    return (NULL);
}

void TFrame_Draw_Drawables(TFrame *this)
{
    if (!this) return;

    TDrawable_Node *current = this->drawables_head;
    TDrawable_Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        if (current->drawable && current->drawable->is_visible) {
            if (current->drawable->Draw) {
                current->drawable->Draw(current->drawable, this);
            }

        }
        current = next;
    }
}

void TFrame_Free_All_Drawables(TFrame *this, unsigned int free_strategy)
{
    if (!this) return;

    TDrawable_Node *current = this->drawables_head;
    TDrawable_Node *tmp = NULL;

    while (current != NULL) {
        tmp = current;
        current = current->next;
        if (tmp->drawable && tmp->drawable->Free) {
            if (free_strategy != GLIB_NO_FREE) {
                if ((free_strategy & GLIB_FREE_ON_FINISH) != 0) {
                    this->Free_Drawable_Obj(this, tmp->drawable);
                }
                else if ((free_strategy & GLIB_FREE_ON_UNLOAD) != 0 &&
                         (tmp->free_strategy & GLIB_FREE_ON_UNLOAD) != 0) {
                    this->Free_Drawable_Obj(this, tmp->drawable);
                }
            }
        }
    }
}

void TFrame_New_Free(TFrame *this)
{
    if (this) {
        this->Free_All_Drawables(this, GLIB_FREE_ON_FINISH | GLIB_FREE_ON_UNLOAD);
        free(this->frame_id);
    }
    free(this);
}
