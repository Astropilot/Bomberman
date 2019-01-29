/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the drawables of GLib.
*/

#include "drawables.h"

#include "sprite.h"
#include "sprite_animated.h"
#include "text.h"
#include "inputbox.h"
#include "button.h"

void drawableCallDraw(Drawable_Node *drawable, TWindow *win)
{
    switch (drawable->type) {
        case SPRITE: ;
            TSprite *sprite = (TSprite*)drawable->drawable;
            sprite->Draw(sprite, win);
            break;
        case TEXT: ;
            TText *text = (TText*)drawable->drawable;
            text->Draw(text, win);
            break;
        case INPUT: ;
            TInput *input = (TInput*)drawable->drawable;
            input->Draw(input, win);
            break;
        case BUTTON: ;
            TButton *button = (TButton*)drawable->drawable;
            button->Draw(button, win);
            break;
        case ANIMATED_SPRITE: ;
            TAnimatedSprite *anim_sprite = (TAnimatedSprite*)drawable->drawable;
            anim_sprite->Draw(anim_sprite, win);
            break;
    }
}

void drawableCallFree(Drawable_Node *drawable)
{
    switch (drawable->type) {
        case SPRITE: ;
            TSprite *sprite = (TSprite*)drawable->drawable;
            sprite->Free(sprite);
            break;
        case TEXT: ;
            TText *text = (TText*)drawable->drawable;
            text->Free(text);
            break;
        case INPUT: ;
            TInput *input = (TInput*)drawable->drawable;
            input->Free(input);
            break;
        case BUTTON: ;
            TButton *button = (TButton*)drawable->drawable;
            button->Free(button);
            break;
        case ANIMATED_SPRITE: ;
            TAnimatedSprite *anim_sprite = (TAnimatedSprite*)drawable->drawable;
            anim_sprite->Free(anim_sprite);
            break;
    }
}
