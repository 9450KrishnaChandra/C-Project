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

int hwall[8][8] = {0};
int vwall[8][8] = {0};

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
        // for wall check
        // if(c<8){
        //     if (if_wall_v(r, c) || if_wall_v(r - 1, c)){
        //         printf("|");}
        //     else printf(" ");
        // }
    }
    printf("\n");
    // a buffer line 
    if (r<8){
        for (int c=0; c<9; c++){
        //     if (if_wall_h(r, c) || if_wall_v(r, c-1)){
        //         printf("---");}
        //     else printf("   ");
        }
        // if(c<8){
        // if (vwall[r][c])
        //     printf("|");
        // else if (hwall[r][c])
        //     printf("-");
        // else
        //     printf(" ");
        // }
    }
    }
    
}

int main(){
    draw();
}