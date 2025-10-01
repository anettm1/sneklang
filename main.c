#include <stdlib.h>
#include <stdio.h>
#include "snekobject.h"

int main(){
    snek_object_t* num = new_snek_ineteger(2);
    printf("%d\n", num->data.v_int);
}