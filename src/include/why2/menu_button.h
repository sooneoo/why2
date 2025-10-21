#ifndef _MENU_BUTTON_H_
#define _MENU_BUTTON_H_ 

#include "object/object.h"
#include <raylib.h>


typedef struct {
    Object super;
    Texture2D texture;
    const char * text;    
    Vector2 size;
    Vector2 position;
    Color bg_color;
} MenuButton;


MenuButton menu_button(Texture2D texture, Vector2 position, Vector2 size, const char * text);

#endif
