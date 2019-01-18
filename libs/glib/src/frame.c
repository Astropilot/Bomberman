#include <string.h>

#include "frame.h"

static void TFrame_Init(TFrame *this, const char *frame_id);
static void TFrame_Free_Sprites(TFrame *this);

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
    this->Add_Sprite = TFrame_Add_Sprite;
    this->Get_Sprite = TFrame_Get_Sprite;
    this->Draw_Sprites = TFrame_Draw_Sprites;
    this->frame_id = strdup(frame_id);
    this->initialized = 0;
    this->sprites_head = NULL;
}

static void TFrame_Free_Sprites(TFrame *this)
{
    TSprite_Node *current = this->sprites_head;
    TSprite_Node *tmp = NULL;

    while (current != NULL) {
        current->sprite->Free(current->sprite);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void TFrame_Add_Sprite(TFrame *this, TSprite *sprite)
{
    if (!this->sprites_head) {
        TSprite_Node *sprite_node = malloc(sizeof(TSprite_Node));

        sprite_node->sprite = sprite;
        sprite_node->next = NULL;
        this->sprites_head = sprite_node;
    } else {
        TSprite_Node *current = this->sprites_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TSprite_Node));
        current->next->sprite = sprite;
        current->next->next = NULL;
    }
}

TSprite *TFrame_Get_Sprite(TFrame *this, const char *id)
{
    TSprite_Node *current = this->sprites_head;

    while (current != NULL) {
        if (strcmp(current->sprite->sprite_id, id) == 0)
            return current->sprite;
        current = current->next;
    }

    return (NULL);
}

void TFrame_Draw_Sprites(TFrame *this, TWindow *win)
{
    TSprite_Node *current = this->sprites_head;

    while (current != NULL) {
        current->sprite->Draw(current->sprite, win);
        current = current->next;
    }
}

void TFrame_New_Free(TFrame *this)
{
    if (this) {
        TFrame_Free_Sprites(this);
        free(this->frame_id);
    }
    free(this);
}
