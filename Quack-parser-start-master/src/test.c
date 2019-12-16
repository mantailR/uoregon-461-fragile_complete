#include <stdio.h>
int main(int argc, char **argv) {
int tmp__0;
tmp__0=int_literal(3);
int tmp__1;
tmp__1=int_literal(2);
int tmp__2;
tmp__2= (obj_Obj) ((obj_Int) tmp__0)->clazz->PLUS((obj_Int) tmp__0, (obj_Int) tmp__1);
int tmp__3;
printf("-> %d\n",tmp__0);
}
