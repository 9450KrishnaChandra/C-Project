#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int row;
    int col;
    int walls;
} Player;

Player Pl[2] ={
   {8, 4, 10},
   {0, 4, 10}
};

int hwall[8][8] ={0};
int vwall[8][8] ={0};

void print_hwall(int r, int c){
    if ((c<8 && hwall[r][c]) || (c>0 && hwall[r][c - 1]))
        printf("---");
    else
        printf("   ");
}

void print_vwall(int r, int c){
    if (c<8 && ((r<8 && vwall[r][c])||(r>0 && vwall[r-1][c])))
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
// Check wall
//     if (wall(Pl[player].row, Pl[player].col, dir)){
//         printf("Wall blocking movement\n");
//         return 0;
//     }
//     return 1;
// }

int wall(int r, int c, char dir){
    if (dir == 'w') return (c < 8 && hwall[r-1][c]) || (c > 0 && hwall[r-1][c-1]);
    if (dir == 's') return (c < 8 && hwall[r][c])   || (c > 0 && hwall[r][c-1]);
    if (dir == 'a') return (r < 8 && vwall[r][c-1]) || (r > 0 && vwall[r-1][c-1]);
    if (dir == 'd') return (r < 8 && vwall[r][c])   || (r > 0 && vwall[r-1][c]);
    return 1;
}

int place_wall(int p, char dir, int r, int c){
    if (r < 0 || r > 7 || c < 0 || c > 7)
        return 0;

    if (Pl[p].walls == 0)
        return 0;

    if (dir == 'h'){
        if (hwall[r][c] || (c > 0 && hwall[r][c-1]) || (c < 7 && hwall[r][c+1]) || vwall[r][c]){
            return 0;
        }
        hwall[r][c] = 1;
    }else if (dir == 'v'){
        if (vwall[r][c] || (r > 0 && vwall[r-1][c]) || (r < 7 && vwall[r+1][c]) || hwall[r][c]){
            return 0;
        }
        vwall[r][c] = 1;
    }
    else return 0;

    Pl[p].walls--;
    return 1;
}


int move(int p, char dir){
    int nr = Pl[p].row;
    int nc = Pl[p].col;
    // int ok = can(nr, nc, dir);
    // if(!ok){
    //     return 0;
    // }

    // oher player in front
    // if (nr == Pl[other].row && nc == Pl[other].col){
    //     nr = nr+=2;;
    // }

    if (dir == 'w' && nr != 0) nr--;
    else if (dir == 's' && nr != 8) nr++;
    else if (dir == 'a' && nc != 0) nc--;
    else if (dir == 'd' && nc != 8) nc++;
    else{
        return 0;
    }

    // Check wall
    if (wall(Pl[p].row, Pl[p].col, dir)){
        printf("Can't go through the wall\n");
        return 0;
    }

    if (nr == Pl[1-p].row && nc == Pl[1-p].col){ 
        if      (dir == 'w' && nr > 0 && !wall(nr, nc, dir)) nr--;
        else if (dir == 's' && nr < 8 && !wall(nr, nc, dir)) nr++;
        else if (dir == 'a' && nc > 0 && !wall(nr, nc, dir)) nc--;
        else if (dir == 'd' && nc < 8 && !wall(nr, nc, dir)) nc++;
        else return 0;                        
    }
    
    Pl[p].row = nr;
    Pl[p].col = nc;
    return 1;
}

void draw(){
    system("clear");

    printf("\n      1   2   3   4   5   6   7   8   9 \n\n");
    for (int r = 0; r < 9; r++){
    printf("   %d ", r+1);
    for (int c=0; c<9; c++){
        char ch = '*';
        if(r==Pl[0].row && c==Pl[0].col) ch='1';
        if(r==Pl[1].row && c==Pl[1].col) ch='2';
        printf(" %c ", ch);
        print_vwall(r,c);
    }
    printf("\n");
    // a buffer line 
    if (r<8){
        printf("     ");
        for (int c=0; c<9; c++){
        print_hwall(r,c);
        if(c<8){
        if (vwall[r][c])       printf("|");
        else if (hwall[r][c])  printf("-");
        else                   printf(" ");
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
    const char *msg = "";

    while(1){
        draw();

        if (msg[0]) printf("\n%s\n", msg);
        msg = "";

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
                if (ok && ((p == 0 && Pl[0].row == 0) || (p == 1 && Pl[1].row == 8))){
                    draw();
                    printf("\nPlayer %d wins!\n", p + 1);
                    break;
                }
                p = 1 - p;
            }
            else msg="Invalid Move!";
        }
        else if(cmd == 'h' || cmd == 'v'){
            if (scanf("%d %d", &row, &col) == 2)
            ok = place_wall(p, cmd, row-1, col-1);
            if(ok){
                p=1-p;
            }
            else msg="Invalid Move!";
        }
        else{
            msg = "Unknown cmd!";
        }
        scanf("%*[^\n]");
        getchar();
    }
}