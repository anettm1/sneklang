#include <stdlib.h>
#include <stdio.h>
#include "snekobject.h"

int main(){
    //integer
    snek_object_t* num = new_snek_integer(2);
    printf("Int: %d\n", num->data.v_int);
    free(num);

    //float
    snek_object_t* float_num = new_snek_float(3.5);
    printf("Float: %.2f\n", float_num->data.v_float);
    free(float_num);

    //string
    char* message = "My name is Snek.";
    snek_object_t* string = new_snek_string(message);
    printf("String: %s\n", string->data.v_string);
    free(string->data.v_string);
    free(string);

    //vector
    snek_object_t *x = new_snek_integer(2);
    snek_object_t *y = new_snek_float(2.4);
    snek_object_t *z = new_snek_string("hello user");
    snek_object_t *vec = new_snek_vector3(x, y, z);
    printf("Vector[1st el.]: %d\n", vec->data.v_vector3.x->data.v_int);
    printf("Vector[2nd el.]: %.2f\n", vec->data.v_vector3.y->data.v_float);
    printf("Vector[3rd el.]: %s\n", vec->data.v_vector3.z->data.v_string);
    free(x);
    free(y);
    free(z);
    free(vec);

    //array
    snek_object_t *array = new_snek_array(2);
    printf("Array kind: %d\n", array->kind);
    printf("Array size: %zu\n", array->data.v_array.size);
    

    //array get and set
    snek_object_t *el1 = new_snek_string("hi");
    snek_object_t *el2 = new_snek_integer(2);
    snek_array_set(array, 0, el1);
    snek_array_set(array, 1, el2);
    snek_object_t *retrieved_el1 = snek_array_get(array, 0);
    snek_object_t *retrieved_el2 = snek_array_get(array, 1);

    printf("Array[1st el.]: %s\n", retrieved_el1->data.v_string);
    printf("Array[2nd el.]: %d\n", retrieved_el2->data.v_int);
    free(el1->data.v_string);
    free(el1);
    free(el2);
    free(array->data.v_array.elements);
    free(array);
    

    return 0;
}