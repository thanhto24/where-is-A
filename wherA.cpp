#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <iomanip>

#define ci pair<char, int>
#define f first
#define s second

using namespace std;

const int X = 5, Y = 5;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int animation_time;

void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
void printLetter(ci a[], int N)
{
    gotoxy(X, Y);
    for (int i = 0; i < N; i++)
        cout << a[i].f << "  ";
    Sleep(1000);
}
void printX(ci a[], int N)
{
    gotoxy(X, Y);
    for (int i = 0; i < N; i++)
    {
        SetConsoleTextAttribute(hConsole, i % 6 + 1);
        if (a[i].s == -1)
            SetConsoleTextAttribute(hConsole, 7);
        cout << char(254) << "  ";
    }
    SetConsoleTextAttribute(hConsole, 7);
}
void animation(int x, int y)
{
    int a = 1, b = -1;
    if (rand() % 100 >= 50)
        swap(a, b);
    gotoxy(X + x * 3, Y);
    cout << "  ";
    gotoxy(X + y * 3, Y);
    cout << "  ";
    gotoxy(X + x * 3, Y + a);
    cout << char(254);
    gotoxy(X + y * 3, Y + b);
    cout << char(254);
    Sleep(animation_time * 2);
    gotoxy(X + x * 3, Y + a);
    cout << "  ";
    gotoxy(X + y * 3, Y + b);
    cout << "  ";
    int tmp = (y - x) * 3;
    while (tmp)
    {
        gotoxy(X + x * 3 + tmp, Y + a);
        cout << char(254);
        gotoxy(X + y * 3 - tmp, Y + b);
        cout << char(254);
        Sleep(animation_time);
        gotoxy(X + x * 3 + tmp, Y + a);
        cout << "  ";
        gotoxy(X + y * 3 - tmp, Y + b);
        cout << "  ";
        tmp--;
    }
    Sleep(animation_time);
    gotoxy(X + x * 3, Y);
    cout << char(254);
    gotoxy(X + y * 3, Y);
    cout << char(254);
    Sleep(animation_time * 2);
}
void randSwap(ci a[], int N, char ask)
{
    int x = rand() % N;
    if (rand() % 100 < 69)
        x = a[N].s;
    int y = rand() % N;
    while (y == x)
        y = rand() % N;
    if (x > y)
        swap(x, y);
    swap(a[x], a[y]);
    a[x].s = a[y].s = -1;
    if (a[x].f == ask)
        a[N].s = x;
    if (a[y].f == ask)
        a[N].s = y;
    printX(a, N);
    animation(x, y);
}

// int poww(int levv)
// {
//     int res = 1;
//     for (int i = 1; i <= levv; i++)
//         res *= 2;
//     if (res > 1000)
//         return 1;
//     return res;
// }

void process(int level)
{
    if (level > 26 - 3)
        level = 999999;
    system("cls");
    gotoxy(0, 1);
    cout << "Level: " << level;
    if (level > 26 - 3)
    {
        cout << " WTFFFFF!!!\n";
        Sleep(2345);
        return;
    }
    int N = 3 + level;
    gotoxy(0, 2);
    int ask = rand() % N + 65;
    cout << "Where is " << char(ask) << " ?\n";
    animation_time = 1;
    ci *a = new ci[N + 1];
    for (int i = 0; i < N; i++)
    {
        a[i].f = 'A' + i;
        a[i].s = 0;
    }
    printLetter(a, N);
    gotoxy(X, Y + 2);
    for (int j = 1; j <= N; j++)
        cout << setw(2) << left << j << " ";
    Sleep(1000);
    //Hehe
    if (rand() % 100 < 10)
    {
        gotoxy(0, 2);
        ask = rand() % N + 65;
        cout << "Where is " << char(ask) << " ?\n";
    }
    a[N].s = ask - 'A';
    printX(a, N);
    Sleep(1000);
    for (int i = 0; i <= level + 3; i++)
    {
        Sleep(1000);
        randSwap(a, N, char(ask));
    }

    gotoxy(0, Y + 3);
    int guest = 1;
    cout << "Enter position: ";
    cin >> guest;

    // Cheat
    // guest = a[N].s + 1;

    bool flag = false;
    if (a[guest - 1].f == ask)
    {
        cout << "Correct!!\n";
        flag = true;
    }
    else
        cout << "Loser!!\n";
    printLetter(a, N);
    gotoxy(0, Y + 6);
    system("pause");
    delete[] a;
    if (flag)
        return process(level + 1);
    cout << "Press 0 to start again or other key to exit\n";
    int ch;
    cin >> ch;
    if (ch == 0)
        return process(1);
    return;
}
int main()
{
    srand(time(0));
    process(1);
    system("cls");
    return 0;
}