/* GCC */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <sstream>

#define X first
#define Y second
#define mp(a, b) make_pair((a), (b))

using namespace std;

const int ch = 30;
const int wd = 1;
const int h1 = 0;
const int h2 = 999;
const int w1 = 0;
const int w2 = 999;

sf::Texture textures[13];

vector < vector <int> > m;
vector < vector <sf::Sprite> > v;
vector <int> bombs;
int i, j, k, w, h, n;
double sc, clock0, speed;
bool flag = true;

void draw(sf::RenderWindow &window)
{
    int i, j;
    window.clear(sf::Color::Black);

    for(i = 0; i < h; i++)
        for(j = 0; j < w; j++)
        {
            //cout << i << " " << j << " " << v[i][j].getPosition().x << " " << v[i][j].getPosition().y << endl;
            window.draw(v[i][j]);
        }
    window.display();
}

void set_texture(sf::Sprite &sp, int num)
{
    sp.setTexture(textures[num]);
    sc = double(ch - 2 * wd)/textures[num].getSize().x;
    //if(num != 9)
      //  sc = 1;
    //sc /= sp.getScale().x;
    sp.setScale(sc, sc);
    //v[i][j].setTextureRect(sf::IntRect(i * ch + wd, j * ch + wd, ch - 2 * wd, ch - 2 * wd));
}

void change_textures()
{
    int i, j, k, l;

    for(i = 0; i < h; i++)
        for(j = 0; j < w; j++)
        {
            if(m[i][j] < 0)
            {
                if( !flag &&  m[i][j] < -1)
                    set_texture(v[i][j], 9 - m[i][j]);
                else
                    set_texture(v[i][j], 10);
            }
            else
            {
                k = l = 0;
                if(i     >  0 && j     >  0 && m[i - 1][j - 1] < 0) {k++; if(m[i - 1][j - 1] < -1) {l++;} }
                if(i     >  0 && j     >= 0 && m[i - 1][j - 0] < 0) {k++; if(m[i - 1][j - 0] < -1) {l++;} }
                if(i     >  0 && j + 1 <  w && m[i - 1][j + 1] < 0) {k++; if(m[i - 1][j + 1] < -1) {l++;} }
                if(i     >= 0 && j     >  0 && m[i - 0][j - 1] < 0) {k++; if(m[i - 0][j - 1] < -1) {l++;} }
                if(i     >= 0 && j + 1 <  w && m[i - 0][j + 1] < 0) {k++; if(m[i - 0][j + 1] < -1) {l++;} }
                if(i + 1 <  h && j     >  0 && m[i + 1][j - 1] < 0) {k++; if(m[i + 1][j - 1] < -1) {l++;} }
                if(i + 1 <  h && j     >= 0 && m[i + 1][j - 0] < 0) {k++; if(m[i + 1][j - 0] < -1) {l++;} }
                if(i + 1 <  h && j + 1 <  w && m[i + 1][j + 1] < 0) {k++; if(m[i + 1][j + 1] < -1) {l++;} }

                if(k == 0)
                    m[i][j] = 9;
                else
                    m[i][j] = l;

                set_texture(v[i][j], m[i][j]);
            }
        }
}

void set_bombs()
{
    int i, j, k;

    bombs.resize(n / 3);
    for(i = 0; i < n / 3; i++)
        bombs[i] = rand() % n;
    sort(bombs.begin(), bombs.end());

    j = -1;
    k = 0;
    for(i = 0; i < w * h; i++)
        if(m[i / w][i % w] < 0)
        {
            j++;
            m[i / w][i % w] = -1;
            while(k < bombs.size() && j == bombs[k])
            {
                m[i / w][i % w] = -2;
                k++;
            }

            //cout << m[i / w][i % w] << " ";
            //if(i % w == w - 1)
              //  cout << endl;
        }

    change_textures();
}

void dfs(int x, int y)
{
    n--;
    m[x][y] = 20;

    if((rand() % 2) != 0 && x > 0 && m[x - 1][y] == -1)
        dfs(x - 1, y);
    if((rand() % 2) != 0 && y > 0 && m[x][y - 1] == -1)
        dfs(x, y - 1);
    if((rand() % 2) != 0 && x + 1 < h && m[x + 1][y] == -1)
        dfs(x + 1, y);
    if((rand() % 2) != 0 && y + 1 < w && m[x][y + 1] == -1)
        dfs(x, y + 1);

}

void end_1()
{
    flag = false;
    cout << "!!!!! YOU DIED !!!!!\n";
}

void end_2()
{
    flag = false;
    cout << "!!!!! YOU WIN !!!!!\n";
    cout << "Only you have enough skills\n";
    cout << "And power to win this game.\n";
    cout << "Thank you that you are!\n";
    cout << "The world can sleep safe now\n";
}



int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("input.in", "r", stdin);
    //freopen("output.out", "w", stdout);

    srand(time(0));

    textures[0].loadFromFile("0.jpg");
    textures[1].loadFromFile("1.jpg");
    textures[2].loadFromFile("2.jpg");
    textures[3].loadFromFile("3.jpg");
    textures[4].loadFromFile("4.jpg");
    textures[5].loadFromFile("5.jpg");
    textures[6].loadFromFile("6.jpg");
    textures[7].loadFromFile("7.jpg");
    textures[8].loadFromFile("8.jpg");
    textures[10].loadFromFile("9.jpg");
    textures[11].loadFromFile("mine.png");
    textures[12].loadFromFile("red_mine.png");
    textures[9].loadFromFile("12.jpg");

    cout << "Speed (in seconds): "; cin >> speed; speed *= 1000;
    cout << "Height (< 30): "; cin >> h;
    cout << "Width (< 40): "; cin >> w;
    //speed = 3000;
    //h = w = 10;

    sf::RenderWindow window(sf::VideoMode(w * ch, h * ch), "Game");

    n = (w * h);

    /*for(i = 0; i < n / 2; i++)
        cout << bombs[i] << " ";
    cout << endl;*/

    m.resize(h, vector <int> (w, -1));
    v.resize(h, vector <sf::Sprite> (w));
    for(i = 0; i < h; i++)
        for(j = 0; j < w; j++)
            v[i][j].setPosition(j * ch + wd, i * ch + wd);
    set_bombs();
    /*for(i = 0; i < h; i++)
        for(j = 0; j < w; j++)
        {
            v[i][j].setPosition(i * ch + wd, j * ch + wd);
            set_texture(v[i][j], 9);
            //v[i][j].setTextureRect(sf::IntRect(i * ch + wd, j * ch + wd, ch - 2 * wd, ch - 2 * wd));
            //v[i][j].setOutlineThickness(float(wd));
            //v[i][j].setSize(sf::Vector2f(ch - 2 * wd, ch - 2 * wd));
            //v[i][j].setOutlineColor(sf::Color::Black);
        }*/

    draw(window);

    /*while (window.isOpen())
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition();
            cout << position.x << " " << position.y << endl;
        }
    }*/

    clock0 = clock();
    while(window.isOpen())
    {
        if(flag && clock() - clock0 > speed)
        {
            set_bombs();
            clock0 = clock();
            draw(window);
        }

        sf::Event event;
        while(window.pollEvent(event))
        {
            draw(window);

            //cout << event.mouseButton.x/ch << " " << event.mouseButton.y/ch << endl;

            if(flag && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                int x = event.mouseButton.x/ch;
                int y = event.mouseButton.y/ch;
                swap(x, y);

                //cout << x << " " << y << endl;

                if(m[x][y] < 0)
                {
                    if(m[x][y] == -2)
                    {
                        m[x][y] = -3;
                        end_1();
                    }
                    else
                    {
                        dfs(x, y);
                        if(n == 0)
                            end_2();
                    }

                    change_textures();
                    draw(window);
                }

                //v[x/ch][y/ch].setFillColor(sf::Color::Red);
                //set_texture(v[x][y], 0);
                //draw(window);
            }

            if(flag && clock() - clock0 > speed)
            {
                set_bombs();
                clock0 = clock();
                draw(window);
            }

            if(event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}






