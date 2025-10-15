#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "snekobject.h"

snek_object_t *_new_snek_object(){
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if(obj == NULL){return NULL;}
    obj->refcount = 1;
    return obj;
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b){
    if(a == NULL || b == NULL){return NULL;}
    switch(a->kind){
        case INTEGER:
            switch(b->kind){
                case INTEGER:
                    return new_snek_integer(a->data.v_int + b->data.v_int);
                case FLOAT:
                    return new_snek_float((float)a->data.v_int + b->data.v_float);
                default:
                    return NULL;
            }
        case FLOAT:
            switch(b->kind){
                case INTEGER: 
                    return new_snek_float(a->data.v_float + (float)b->data.v_int);
                case FLOAT:
                    return new_snek_float(a->data.v_float + b->data.v_float);
                default:
                    return NULL;
            }
        case STRING:
            switch(b->kind){
                case STRING:
                    size_t a_len = strlen(a->data.v_string);
                    size_t b_len = strlen(b->data.v_string);
                    size_t len = a_len + b_len + 1;
                    char *dst = calloc(len, sizeof(char));
                    if(dst == NULL){return NULL;}
                    memcpy(dst, a->data.v_string, a_len);
                    memcpy(dst + a_len, b->data.v_string, b_len + 1);
                    snek_object_t *obj = new_snek_string(dst);
                    free(dst);
                    return obj;
                default:
                    return NULL;
            }
        case VECTOR3:
            switch(b->kind){
                case VECTOR3:
                    return new_snek_vector3(
                            snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
                            snek_add(a->data.v_vector3.y, b->data.v_vector3.y),
                            snek_add(a->data.v_vector3.z, b->data.v_vector3.z)
                        );
                default:
                    return NULL;
            }
        case ARRAY:
            switch(b->kind){
                case ARRAY:
                    size_t a_len = a->data.v_array.size;
                    size_t b_len = b->data.v_array.size;
                    size_t len = a_len + b_len;
                    snek_object_t *arr = new_snek_array(len);
                    for(size_t i = 0; i < a_len; i++){
                        snek_array_set(arr, i, snek_array_get(a, i));
                    }
                    for(size_t i = 0; i < b_len; i++){
                        snek_array_set(arr, i + a_len, snek_array_get(b, i));
                    }
                    return arr;
                default:
                    return NULL;
            }
        default:
            return NULL;
    }
}

int snek_length(snek_object_t *obj){
    if(obj == NULL){return -1;}
    switch(obj->kind){
        case INTEGER:
        case FLOAT:
            return 1;
        case STRING:
            return (int)strlen(obj->data.v_string);
        case VECTOR3:
            return 3;
        case ARRAY:
            return (int)obj->data.v_array.size;
        default:
            return -1;
    }
}

bool snek_array_set(snek_object_t *snek_obj, size_t idx, snek_object_t *value){
    if(snek_obj == NULL && value == NULL){return false;}
    if(snek_obj->kind != ARRAY){return false;}
    if(idx >= snek_obj->data.v_array.size){return false;}
    snek_obj->data.v_array.elements[idx] = value;
    return true;
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t idx){
    if(snek_obj == NULL){return NULL;}
    if(snek_obj->kind != ARRAY){return NULL;}
    if(idx >= snek_obj->data.v_array.size){return NULL;}
    return snek_obj->data.v_array.elements[idx];
}

snek_object_t *new_snek_array(size_t size){
    snek_object_t *obj = _new_snek_object();
    if(obj == NULL){return NULL;}

    obj->kind = ARRAY;

    snek_object_t **elements = calloc(size, sizeof(snek_object_t*));
    if(elements == NULL){
        free(obj);
        return NULL;
    }
    obj->data.v_array = (snek_array_t){
        .size = size,
        .elements = elements
    };
    return obj;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
){
    if(x == NULL || y == NULL || z == NULL){return NULL;}
    snek_object_t *obj = _new_snek_object();
    if(obj == NULL){return NULL;}
    obj->kind = VECTOR3;
    obj->data.v_vector3 = (snek_vector_t){.x=x, .y=y, .z=z};
    return obj;
}

snek_object_t *new_snek_string(char* value){
    snek_object_t *obj = _new_snek_object();
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
    snek_object_t *obj = _new_snek_object();
    if(obj == NULL){return NULL;}
    obj->kind = FLOAT;
    obj->data.v_float = value;
    return obj;
}

snek_object_t *new_snek_integer(int value){
    snek_object_t *obj = _new_snek_object();
    if(obj == NULL){return NULL;}
    obj->kind = INTEGER;
    obj->data.v_int = value;
    return obj;
}

