#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int walls;
} Player;

Player Pl[2] = {
    {8, 4, 10},
    {0, 4, 10}
};

int hwall[8][8] = {0};
int vwall[8][8] = {0};

void print_hwall(int r, int c) {
    if ((c < 8 && hwall[r][c]) ||
        (c > 0 && hwall[r][c - 1]))
        printf("---");
    else
        printf("   ");
}

void print_vwall(int r, int c) {
    if ((r < 8 && vwall[r][c]) ||
        (r > 0 && vwall[r - 1][c]))
        printf("|");
    else
        printf(" ");
}

// int can(int r, int c, char dir){
//     if (dir == 'w' && r == 0)
//         return 0;
//     if (dir == 's' && r == 8)
//         return 0;
//     if (dir == 'a' && c == 0)
//         return 0;
//     if (dir == 'd' && c == 8)
//         return 0;
// }

int move(int p, int dir){
    int nr = Pl[p].row;
    int nc = Pl[p].col;
    // int ok = can(nr, nc, dir);
    // if(!ok){
    //     return 0;
    // }

    if (dir == 'w' && nr != 0) nr--; else {printf("Invaid move\n");return 0;}
    if (dir == 's' && nr != 8) nr++; else {printf("Invaid move\n");return 0;}
    if (dir == 'a' && nc != 0) nc--; else {printf("Invaid move\n");return 0;}
    if (dir == 'd' && nc != 8) nc++; else {printf("Invaid move\n");return 0;}

    Pl[p].row = nr;
    Pl[p].col = nc;
    return 1;
}

void draw(){
    system("clear");

    printf("\n     1   2   3   4   5   6   7   8   9 \n");
    for (int r = 0; r < 9; r++){
    printf("   %d", r+1);
    for (int c=0; c<9; c++){
        char ch = '.';
        if(r==Pl[0].row && c==Pl[0].col) ch='1';
        if(r==Pl[1].row && c==Pl[1].col) ch='2';
        printf(" %c ", ch);
        print_vwall(r,c);
    }
    printf("\n");
    // a buffer line 
    if (r<8){
        for (int c=0; c<9; c++){
        print_hwall(r,c);
        if(c<8){
        if (vwall[r][c])
            printf("|");
        else if (hwall[r][c])
            printf("-");
        else
            printf(" ");
        }
        }
        printf("\n");
    }
    }
    
}

int main(){
    int p=0;
    char cmd;
    int row, col;
    while(1){
        draw();
        printf("\n");
        printf("Player %d's turn\n", p + 1);
        printf("Move: w/a/s/d\n");
        printf("Wall: h or v followed by row and column\n");
        printf("Quit: q\n");

        printf("> ");
        scanf(" %c", &cmd);
        int ok=0;
        if(cmd=='q'){
            break;
        }
        if(cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd'){
            ok = move(p, cmd);
            if (ok){
                p = 1 - p;
            }
            else printf("Invalid move!\n");
        }
        else if(cmd == 'h' || cmd == 'v'){
            scanf("%d %d", &row, &col);
            // place_wall(p, cmd, row, col);
            // p=1=p;
        }
    }
}