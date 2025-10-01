#include <stdlib.h>
#include <string.h>
#include "snekobject.h"

snek_object_t *new_snek_string(char* value){
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if(obj == NULL){return NULL;}
    size_t len = strlen(value);
    char* dst = malloc(len + 1);
    if(dst == NULL){
        free(obj);
        return NULL;
    }
    memcpy(dst, value, len + 1);
    obj->kind = STRING;
    obj->data.v_string = dst;
    return obj;
}

snek_object_t *new_snek_float(float value){
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if(obj == NULL){return NULL;}
    obj->kind = FLOAT;
    obj->data.v_float = value;
    return obj;
}

snek_object_t *new_snek_integer(int value){
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if(obj == NULL){return NULL;}
    obj->kind = INTEGER;
    obj->data.v_int = value;
    return obj;
}

