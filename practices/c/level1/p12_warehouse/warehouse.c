#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
HANDLE handle_out, handle_in;


void go(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle_out, pos);
    SetConsoleCursorPosition(handle_in, pos);
}

void prepare() {
    handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    handle_in = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible =  0;
    SetConsoleCursorInfo(handle_out, &cci);
}


struct item {
    int num;
    char name[1000];
} stock[3000];

char str[1000];
int total = 0;

void init() {
    freopen("stock.in", "r", stdin);
    while (scanf("%s", str) != EOF)
    {
        total++;
        int len = strlen(str);
        for (int i = 0; i < len; i++)
        {
            stock[total].name[i] = str[i];
        }
        scanf("%d", &stock[total].num);
    }
    fclose(stdin);
    freopen("CON", "r", stdin);
}



int getkey() {
    char ch;
    ch = getch();
    return ch - '0';
}

bool cmp(int x, int y) {
    int len1 = strlen(stock[x].name);
    int len2 = strlen(stock[y].name);
    if (len1 != len2)
        return 0;
    return memcmp(stock[x].name, stock[y].name, sizeof(stock[x].name)) == 0;
}


int main() {
    init();
    prepare();
    for (;;)
    {
        int key = getkey();
        Sleep(100);
        printf("%d\n", key);
        switch (key)
        {
        case 2:
        {
            system("cls");
            if (total == 0)
            {
                puts("Your stock is empty.");
            }
            for (int i = 1; i <= total; i++)
            {
                if (stock[i].num)
                {
                    printf("%s %d\n", stock[i].name, stock[i].num);
                }
            }
            break;
        }
        case 3:
        {
            system("cls");
            total++;
            scanf("%s", stock[total].name);
            scanf("%d", &stock[total].num);
            for (int i = 1; i < total; i++)
            {
                if (cmp(i, total))
                {
                    stock[i].num += stock[total].num;
                    total--;
                    break;
                }
            }
            break;
        }
        case 4:
        {
            system("cls");
            total++;
            scanf("%s", stock[total].name);
            scanf("%d", &stock[total].num);
            for (int i = 1; i < total; i++)
            {
                if (cmp(i, total))
                {
                    if (stock[i].num < stock[total].num)
                    {
                        puts("There are not enough such items.");
                        break;
                    }
                    stock[i].num -= stock[total].num;
                    break;
                }
            }
            total--;
            break;
        }
        case 5:
        {
            system("cls");
            freopen("stock.in", "w", stdout);
            for (int i = 1; i <= total; i++)
            {
                if (stock[i].num)
                {
                    printf("%s %d\n", stock[i].name, stock[i].num);
                }
            }
            fclose(stdout);
            return 0;
            break;
        }
        }
    }
    return 0;
}