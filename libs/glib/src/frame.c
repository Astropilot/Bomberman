#include <string.h>

#include "frame.h"

static void TFrame_Init(TFrame *this, const char *frame_id);

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
       this->frame_id = strdup(frame_id);
       this->initialized = 0;
}

void TFrame_New_Free(TFrame *this)
{
    if (this) {
        free(this->frame_id);
    }
    free(this);
}
