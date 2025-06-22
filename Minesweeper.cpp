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
// 0123456789
//     1   2   3   4   5   6   7   8   9
//   +---+---+---+---+---+---+---+---+---+ y = 37
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
//   |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+ x = 19
// p(x,y) (x,y [1,9])
// display( ((x-1)*4)+2 , 2*y-1 )
int mine_map[13][13];
char display_map[19][37];
int calc_map[13][13];
int special_map[13][13];
struct point
{
    int x;
    int y;
} mine[11], selector, p1;
point locate_point(point p)
{
    p.x = (p.x - 1) * 4 + 2;
    p.y = p.y * 2 - 1;
    return p;
}
void print_screen()
{
    system("cls");
    cout << "    1   2   3   4   5   6   7   8   9" << endl;
    for (int i = 0; i <= 18; i++)
    {
        if (i % 2 == 1)
        {
            cout << i / 2 + 1 << ' ';
        }
        else
        {
            cout << "  ";
        }
        for (int j = 0; j <= 36; j++)
        {
            cout << display_map[i][j];
        }
        cout << endl;
    }
    cout << "输入以下字符以操控(不区分大小写)：" << endl;
    cout << "W A S D : 移动选框" << endl;
    cout << "Z : 标记/问号/取消   X : 安全展开(对数字方格有效)   C : 直接展开" << endl;
    cout << "(num1,num2) : 连续输入两个数字，快速移动选框至目标方格" << endl;
    cout << "请输入：";
    return;
}

void send_error(int style)
{
    // style : 1: 操作字符错误   2：无法操作
    system("cls");
    if (style == 1)
    {
        cout << "Wrong Command!" << endl;
        cout << "Please use the supported letter & format!";
    }
    else if (style == 2)
    {
        cout << "Unable to perform the operation!";
    }
    Sleep(2);
    print_screen();
    return;
}

void draw_selector()
{
    // display_map[(selector.x - 1) * 4 + 2][selector.y * 2 + 1]
    display_map[(selector.x - 1) * 4][selector.y * 2] = 'X';
    display_map[(selector.x - 1) * 4][selector.y * 2 + 2] = 'X';
    display_map[(selector.x - 1) * 4 + 4][selector.y * 2] = 'X';
    display_map[(selector.x - 1) * 4 + 4][selector.y * 2 + 2] = 'X';
}

void erase_selector()
{
    display_map[(selector.x - 1) * 4][selector.y * 2] = '+';
    display_map[(selector.x - 1) * 4][selector.y * 2 + 2] = '+';
    display_map[(selector.x - 1) * 4 + 4][selector.y * 2] = '+';
    display_map[(selector.x - 1) * 4 + 4][selector.y * 2 + 2] = '+';
}

void gameover;

queue<point> q;
void bfs_reveal_map()
{
    int delta_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int delta_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    while (!q.empty())
    {
        point p = q.front();
        q.pop();
        point ps = locate_point(p);
        if (!mine_map[p.x][p.y])
        {
            display_map[ps.x][ps.y] = ' ';
        }
        else
        {
            gameover();
        }
        for (int i = 0; i < 8; i++)
        {
            if (p.x + delta_x[i] >= 1 && p.x + delta_x[i] <= 9 && p.y + delta_y[i] >= 1 && p.y + delta_y[i] <= 9)
            {
            }
        }
    }

    return;
}

void read_command()
{
    char c;
    cin >> c;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        erase_selector();
        if (c >= 'A' && c <= 'Z')
        {
            c -= 'A' - 'a';
        }
        if (c == 'w')
        {
            if (selector.x > 1)
            {
                selector.x -= 1;
            }
            else
            {
                send_error(2);
            }
        }
        else if (c == 'a')
        {
            if (selector.y > 1)
            {
                selector.y -= 1;
            }
            else
            {
                send_error(2);
            }
        }
        else if (c == 's')
        {
            if (selector.y < 9)
            {
                selector.y += 1;
            }
            else
            {
                send_error(2);
            }
        }
        else if (c == 'd')
        {
            if (selector.x < 9)
            {
                selector.y += 1;
            }
            else
            {
                send_error(2);
            }
        }
        else if (c == 'z')
        {
            p1 = locate_point(selector);
            if (display_map[p1.x][p1.y] == ' ' || display_map[p1.x][p1.y] == 'P' || display_map[p1.x][p1.y] == '?')
            {
                if (display_map[p1.x][p1.y] == 'M')
                {
                    // special_map[selector.x][selector.y] = 1;
                    display_map[p1.x][p1.y] = 'P';
                }
                else if (display_map[p1.x][p1.y] == 'P')
                {
                    // special_map[selector.x][selector.y] = 2;
                    display_map[p1.x][p1.y] = '?';
                }
                else if (display_map[p1.x][p1.y] == '?')
                {
                    // special_map[selector.x][selector.y] = 0;
                    display_map[p1.x][p1.y] = 'M';
                }
            }
            else
            {
                send_error(1);
            }
            draw_selector();
        }
        // NOW
    }
    return;
}

void developer_show_map()
{
    cout << "mine_map:" << endl;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cout << mine_map[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "calc_map:" << endl;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cout << calc_map[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "display_map" << endl;
    for (int i = 0; i <= 18; i++)
    {
        for (int j = 0; j <= 36; j++)
        {
            cout << display_map[i][j];
        }
        cout << endl;
    }
    return;
}

void draw_map()
{
    memset(display_map, 'M', sizeof(display_map));
    for (int i = 0; i <= 18; i += 2)
    {
        for (int j = 0; j <= 36; j++)
        {
            if (j % 4 == 0)
            {
                display_map[i][j] = '+';
            }
            else
            {
                display_map[i][j] = '-';
            }
        }
    }
    for (int i = 1; i <= 17; i += 2)
    {
        for (int j = 0; j <= 37; j += 4)
        {
            display_map[i][j] = '|';
        }
    }

    return;
}

void generate()
{
    memset(mine_map, 0, sizeof(mine_map));
    srand(time(NULL));
    int i = 1;
    int randx, randy;
    bool judge_edge[4]; // 0 == left; 1 == top; 2 == button; 3 == right;
    memset(judge_edge, 0, sizeof(judge_edge));
    int cnt_edge = 0;
    while (i <= 10)
    {
        randx = rand() % 9 + 1;
        randy = rand() % 9 + 1;
        if (mine_map[randx][randy] == 0)
        {
            if (cnt_edge < 4)
            {
                if (randx == 1 && judge_edge[0] == 0)
                {
                    judge_edge[0] = 1;
                    cnt_edge++;
                    mine_map[randx][randy] = 1;
                    mine[i].x = randx;
                    mine[i].y = randy;
                    i++;
                    continue;
                }
                else if (randx == 9 && judge_edge[3] == 0)
                {
                    judge_edge[3] = 1;
                    cnt_edge++;
                    mine_map[randx][randy] = 1;
                    mine[i].x = randx;
                    mine[i].y = randy;
                    i++;
                    continue;
                }
                else if (randy == 1 && judge_edge[1] == 0)
                {
                    judge_edge[1] = 1;
                    cnt_edge++;
                    mine_map[randx][randy] = 1;
                    mine[i].x = randx;
                    mine[i].y = randy;
                    i++;
                    continue;
                }
                else if (randy == 9 && judge_edge[2] == 0)
                {
                    judge_edge[2] = 1;
                    cnt_edge++;
                    mine_map[randx][randy] = 1;
                    mine[i].x = randx;
                    mine[i].y = randy;
                    i++;
                    continue;
                }
            }
            else
            {
                mine_map[randx][randy] = 1;
                mine[i].x = randx;
                mine[i].y = randy;
                i++;
            }
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
    generate();
    draw_map();
    print_screen();
    read_command();
    // developer_show_map();
    // initialize();
    return 0;
}
