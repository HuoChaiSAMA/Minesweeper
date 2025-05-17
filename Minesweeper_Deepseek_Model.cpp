#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;

struct Point
{
    int x;
    int y;
};

void generate_map(int mine_map[13][13])
{
    srand(time(0));
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            mine_map[i][j] = (rand() % 2);
        }
    }
}

void show_map(const int mine_map[13][13], sf::RenderWindow &window, const Point &point)
{
    // 绘制背景
    sf::Color background = sf::Color(0, 25, 25);
    window.draw(sf::Rectangle(0, 0, 640, 480, background));

    // 设置字体和布局
    sf::Font font = sf::Font();
    font.loadFromFile("Arial.ttf");
    int cell_size = 40;
    int grid_offset = (window.getSize().width - 13 * cell_size) / 2;

    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            if (mine_map[i][j] == 1)
            {
                // 绘制地雷
                sf::Circle(grid_offset + j * cell_size + cell_size / 2,
                           grid_offset + i * cell_size + cell_size / 2,
                           10,
                           sf::Color::red);
            }
            else
            {
                // 检查周围是否有地雷，设置数字
                int neighboring Mines = 0;
                for (int dx = -1; dx <= 1; ++dx)
                {
                    for (int dy = -1; dy <= 1; ++dy)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        int x = i + dx;
                        int y = j + dy;
                        if (x >= 0 && x < 13 && y >= 0 && y < 13)
                        {
                            if (mine_map[x][y] == 1)
                                neighboring Mines++;
                        }
                    }
                }
                if (neighboring Mines > 0)
                {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(to_string(neighboring Mines));
                    text.setFillColor(sf::Color(0, 255, 0));
                    text.setPosition(grid_offset + j * cell_size + cell_size / 2,
                                     grid_offset + i * cell_size + cell_size / 2 - 10);
                    window.draw(text);
                }
            }
        }
    }
}

int main()
{
    // 初始化SFML
    sf::RenderWindow window(sf::Context());
    window.setSize(800, 600);

    // 隐蔽图形绘制错误
    window.setExceptionHandling(true);

    while (true)
    {
        // 检查用户输入
        sf::Event event;
        while (event = window.pollEvent())
        {
            if (event.type == sf::MouseEvent)
            {
                Point click_pos;
                click_pos.x = event.mouseX;
                click_pos.y = event.mouseY;

                int cell_x = (click_pos.x - grid_offset) / cell_size;
                int cell_y = (click_pos.y - grid_offset) / cell_size;

                if (cell_x >= 0 && cell_x < 13 && cell_y >= 0 && cell_y < 13)
                {
                    if (mine_map[cell_y][cell_x] == 1)
                    {
                        cout << "游戏结束！" << endl;
                        return 0;
                    }
                }
            }
        }

        // 绘制
        show_map(mine_map, window, Point());
        window.display();
    }

    return 0;
}