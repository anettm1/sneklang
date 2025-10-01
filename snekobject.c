#include <stdlib.h>
#include "snekobject.h"

snek_object_t *new_snek_ineteger(int value){
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if(obj == NULL){return NULL;}
    obj->kind = INTEGER;
    obj->data.v_int = value;
    return obj;
}