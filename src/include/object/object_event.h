#ifndef _OBJECT_EVENT_H_
#define _OBJECT_EVENT_H_

#include "object.h"
#include "slot.h"


typedef struct Object_Event {
    Object super;
    void (*on_event) (struct Object_Event *, void *);
} Object_Event;


#endif


