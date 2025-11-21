// #include <bits/stdc++.h>
#include <cstdio>
#include <queue>
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
// x = 1, y = 1; X = 1, Y = 2;
// x = 1, X = 1; x = 2, X = 3; X = x * 2 - 1
// y = 1, Y = 2; y = 2, Y = 6; Y = y * 4 - 2
//     1   2   3   4   5   6   7   8   9
//   0123456789
//  0+---+---+---+---+---+---+---+---+---+ y = 37
// 11|   |   |   |   |   |   |   |   |   |
//  2+---+---+---+---+---+---+---+---+---+
// 23|   |   |   |   |   |   |   |   |   |
//  4+---+---+---+---+---+---+---+---+---+
// 35|   |   |   |   |   |   |   |   |   |
//  6+---+---+---+---+---+---+---+---+---+
// 47|   |   |   |   |   |   |   |   |   |
//  8+---+---+---+---+---+---+---+---+---+
// 59|   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
// 6 |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
// 7 |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
// 8 |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+
// 9 |   |   |   |   |   |   |   |   |   |
//   +---+---+---+---+---+---+---+---+---+ x = 19
// p(x,y) (x,y [1,9])
int mine_map[13][13];
char display_map[19][37];
int calc_map[13][13];
int special_map[13][13];
bool flag = 1;
struct point
{
    int x;
    int y;
} mine[11], selector, p1;
// x = 1, X = 1; x = 2, X = 3; X = x * 2 - 1
// y = 1, Y = 2; y = 2, Y = 6; Y = y * 4 - 2
point locate_point(point p)
{
    p.x = p.x * 2 - 1;
    p.y = p.y * 4 - 2;
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
    // style : 1: 操作字符错误   2：无法操作(所选方格越界)   3: 自动展开操作选择错误
    system("cls");
    if (style == 1)
    {
        cout << "指令错误!" << endl;
        cout << "请使用受支持的指令与格式!";
    }
    else if (style == 2)
    {
        cout << "无法操作!(所选方格不存在或越界)";
    }
    else if (style == 3)
    {
        cout << "无法执行展开!所选方格必须安全、已知且其周围标记的方格数已满足该格数量要求!";
    }
    else if (style == 4)
    {
        cout << "无法标记已经展开的方格!";
    }
    Sleep(2);
    print_screen();
    return;
}

void draw_selector()
{
    // WRONG!!!
    // display_map[(selector.x - 1) * 4 + 2][selector.y * 2 + 1]
    display_map[(selector.y - 1) * 4][selector.x * 2] = 'X';
    display_map[(selector.y - 1) * 4][selector.x * 2 + 2] = 'X';
    display_map[(selector.y - 1) * 4 + 4][selector.x * 2] = 'X';
    display_map[(selector.y - 1) * 4 + 4][selector.x * 2 + 2] = 'X';
}

void erase_selector()
{
    display_map[(selector.x - 1) * 4][selector.y * 2] = '+';
    display_map[(selector.x - 1) * 4][selector.y * 2 + 2] = '+';
    display_map[(selector.x - 1) * 4 + 4][selector.y * 2] = '+';
    display_map[(selector.x - 1) * 4 + 4][selector.y * 2 + 2] = '+';
}

void gameover()
{
    system("cls");
    cout << "Game Over";
    flag = 0;
    return;
}

queue<point> q;
void bfs_reveal_map()
{
    int delta_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int delta_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    point p, ps;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        ps = locate_point(p);
        // if (!mine_map[p.x][p.y])
        // {
        //     display_map[ps.x][ps.y] = ' ';
        // }
        // else
        // {
        //     gameover();
        // }
        display_map[ps.x][ps.y] = calc_map[p.x][p.y] + '0';
        if (calc_map[p.x][p.y] == 0)
        {
            display_map[ps.x][ps.y] = ' ';
        }
        if (display_map[ps.x][ps.y] == '0')
        {
            for (int i = 0; i < 8; i++)
            {
                if (p.x + delta_x[i] >= 1 && p.x + delta_x[i] <= 9 && p.y + delta_y[i] >= 1 && p.y + delta_y[i] <= 9)
                {
                    point it;
                    it.x = p.x + delta_x[i];
                    it.y = p.y + delta_y[i];
                    point itt = locate_point(it);
                    if (display_map[itt.x][itt.y] == 'N')
                    {
                        q.push(it);
                    }
                }
            }
        }
    }
    print_screen();
    return;
}

void click_to_show(point p)
{
    point pp = locate_point(p);
    if (mine_map[p.x][p.y] == 1)
    {
        gameover();
    }
    else
    {
        q.push(p);
        bfs_reveal_map();
    }
    return;
}

void click_to_help_show(point p)
{
    point pp = locate_point(p);
    point px;
    if (display_map[pp.x][pp.y] == 'N')
    {
        send_error(3);
    }
    else
    {
        int tot = 0;
        int delta_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int delta_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int i = 0; i <= 7; i++)
        {
            for (int j = 0; j <= 7; j++)
            {
                px.x = p.x + delta_x[i];
                px.y = p.y + delta_y[j];
                pp = locate_point(px);
                if (display_map[pp.x][pp.y] == 'P')
                {
                    tot++;
                }
            }
        }
        if (tot == calc_map[p.x][p.y])
        {
            q.push(p);
            bfs_reveal_map();
        }
    }
    return;
}

void read_command()
{
    // cout << "输入以下字符以操控(不区分大小写)：" << endl;
    // cout << "W A S D : 移动选框" << endl;
    // cout << "Z : 标记/问号/取消   X : 安全展开(对数字方格有效)   C : 直接展开" << endl;
    // cout << "(num1,num2) : 连续输入两个数字，快速移动选框至目标方格" << endl;
    // cout << "请输入：";
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
                send_error(4);
            }
        }
        else if (c == 'x')
        {
            click_to_help_show(selector);
        }
        else if (c == 'c')
        {
            click_to_show(selector);
        }
        draw_selector();
    }
    else if (c >= '0' && c <= '9')
    {
        int tx = c;
        int ty;
        cin >> ty;
        erase_selector();
        if (tx >= 1 && tx <= 9 && ty >= 1 && ty <= 9)
        {
            selector.x = tx;
            selector.y = ty;
        }
        else
        {
            send_error(1);
        }
        draw_selector();
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
    memset(display_map, ' ', sizeof(display_map));
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
    // p(x,y) (x,y [1,9])
    // display( ((x-1)*4)+2 , 2*y-1 )
    point p1, px;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            p1.x = i;
            p1.y = j;
            px = locate_point(p1);
            display_map[px.x][px.y] = 'N';
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

// p(x,y) (x,y [1,9])
// display( ((x-1)*4)+2 , 2*y-1 )
int main()
{
    generate();
    draw_map();
    selector.x = 1;
    selector.y = 1;
    draw_selector();
    print_screen();
    // while (flag)
    // {
    //     read_command();
    // }
    // read_command();
    // developer_show_map();
    // initialize();
    return 0;
}
