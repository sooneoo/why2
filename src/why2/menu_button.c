#include "why2/menu_button.h"


static void menu_button_draw(MenuButton * self) {
    // left upper corner
    DrawTexturePro(
            self->texture
            , (Rectangle){0, 0, self->texture.width/3, self->texture.height/3}
            , (Rectangle){self->position.x, self->position.y, self->size.x/3, self->size.y/3}
            , (Vector){0, 0}
            , 0
            , self->bg_color);
}


static Vector2 menu_button_size(MenuButton * self) {
    return self->size;
}


static Vector2 menu_button_position(MenuButton * self) {
    return self->position;
}


MenuButton menu_button(Texture2D texture, Vector2 position, Vector2 size, const char * text);
   return (MenuButton) {
        .super = {
            .draw = (void (*)(Object*)) menu_button_draw
            , .size = (Vector2(*)(Object*) menu_nutton_size)
            , .position = (Vector2(*)(Object*)) menu_button_position
        }
        , .text = text
        , .texture = texture
   };      
}



