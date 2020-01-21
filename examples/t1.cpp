/**
 * @file t1.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <cstdio>
#include <cstdlib>

void inner(void){
    puts("inner()");
}

void myfun(void){
    puts("enter myfun()");
    for(int i = 0; i < 10; ++i){
	printf("something %d\n",i);
	inner();
    }
    puts("leave myfun");
}

int main(int argc, char **argv){
    puts("in main");
    myfun();
    puts("after myfun()");
    return 0;
}
