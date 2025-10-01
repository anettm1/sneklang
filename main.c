#include <stdlib.h>
#include <stdio.h>
#include "snekobject.h"

int main(){
    snek_object_t* num = new_snek_integer(2);
    printf("%d\n", num->data.v_int);
    free(num);

    snek_object_t* float_num = new_snek_float(3.5);
    printf("%.2f\n", float_num->data.v_float);

    char* message = "My name is Snek.";
    snek_object_t* string = new_snek_string(message);
    printf("%s\n", string->data.v_string);
    return 0;
}