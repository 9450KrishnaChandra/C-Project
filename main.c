#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int walls;
} Player;

Player p[2] = {
    {8, 4, 10},
    {0, 4, 10}
};

void draw(){
    system("clear");
    printf("\n     1  2  3  4  5  6  7  8  9 \n");
    for (int r = 0; r < 9; r++){
    printf("   %d", r+1);
    for (int c=0; c<9; c++){
        char ch = '.';
        if(r==p[0].row && c==p[0].col) ch='1';
        if(r==p[1].row && c==p[1].col) ch='2';
        printf(" %c ", ch);
        if(c<8){

        }
    }

    printf("\n");
    }
    
}

int main(){
    draw();
}