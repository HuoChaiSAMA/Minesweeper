#include <bits/stdc++.h>
#include <cstdio>
#include <windows.h>
// windows.h for Sleep();
#include <iostream>
#include <stdlib.h>
// stdlib.h for system("cls");
// stdlib.h for rand() & srand()
// srand(time(NULL));  // 初始化随机数生成器
// int random_number = rand() % 100;  // 生成 0 到 99 之间的随机数

using namespace std;
// map_size:9x9
//+---+ x---x
//| P | | S |
//+---+ x---X
// +---+---+---+---+---+---+---+---+---+ y = 37
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+
// |   |   |   |   |   |   |   |   |   |
// +---+---+---+---+---+---+---+---+---+ x = 19
int mine_map[13][13];
char show_map[10][38];
int calc_map[13][13];
struct point
{
    int x;
    int y;
} mine[11], selector;
void show_map()
{
    for (int i = 1; i <= 9; i++)
    {
    }

    return;
}
void generate()
{
    memset(mine_map, 0, sizeof(mine_map));
    srand(time(NULL));
    int i = 1;
    int randx, randy;
    while (i <= 10)
    {
        randx = rand() % 9 + 1;
        randy = rand() % 9 + 1;
        if (mine_map[randx][randy] == 0)
        {
            mine_map[randx][randy] = 1;
            mine[i].x = randx;
            mine[i].y = randy;
            i++;
        }
        else
        {
            continue;
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            if (mine_map[i][j] == 0)
            {
                calc_map[i][j] = mine_map[i][j - 1] + mine_map[i][j + 1] + mine_map[i - 1][j - 1] + mine_map[i - 1][j] + mine_map[i - 1][j + 1] + mine_map[i + 1][j - 1] + mine_map[i + 1][j] + mine_map[i + 1][j + 1];
            }
            else
            {
                calc_map[i][j] = 9;
            }
        }
    }

    return;
}

int main()
{

    // initialize();
    return 0;
}