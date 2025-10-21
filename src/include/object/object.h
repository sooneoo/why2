#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <stdbool.h>
#include <raylib.h>


typedef struct Object {
    void (*draw)(struct Object *);
    Vector2 (*size)(struct Object *);
    Vector2 (*position)(struct Object *);    
    bool visible;
} Object;


static inline void object_draw(Object * self) {
    if(self->visible == true) {
        self->draw(self);
    }
}

static inline Vector2 object_size(struct Object * self) {
    return self->size(self);
}


static inline Vector2 object_position(struct Object * self) {
    return self->position(self);
}


static inline bool object_visible(Object * self) {
    return self->visible;
}


static inline void object_set_visible(Object * self, bool visible) {
    self->visible = visible;
} 


#endif


