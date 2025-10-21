#ifndef _SLOT_H_
#define _SLOT_H_

typedef void (*Object_Callback)(void);


#define O_CALLBACK(T) ((Object_Callback) (T))


typedef struct {
    Object_Callback callback;
    void * param;
} Slot;


#endif


