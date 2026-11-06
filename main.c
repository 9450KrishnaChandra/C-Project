#include <stdio.h>
#include <stdlib.h>


void draw(){
    printf("\n   1  2  3  4  5  6  7  8  9 \n");
    for (int r = 0; r < 9; r++){
    printf("%d ", r+1);
    for (int c=0; c<9; c++){
        printf(" . ");
    }
    printf("\n\n");
    }
    
}

int main(){
    draw();
}