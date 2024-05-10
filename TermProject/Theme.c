#include "mapMake.h"

char* firstMenu[4] = { "  ��     ��     ��     ��  ", "  ��     ��     ��     ��  ", "  ȯ     ��     ��     ��  "};

void printStartPage(int nowIndx){
    printLogo(25, 10);
    draw_boxL(0, 0, 120, 46);
    draw_boxL(80, 30, 116, 42);
    gotoxy(5, 43);
    printf("Made By UROUS3814");
    gotoxy(5, 44);
    printf("github.com/urous3814/TermProject");
    printFirstMenu(nowIndx);
}

void printSettingPage(int nowIndx){
    printLogo(25, 10);
    draw_boxB(18, 19, 102, 43);
    draw_boxL(20, 20, 100, 24);
    gotoxy(54, 22);
    printf("  ȯ �� �� �� ");
    draw_boxL(20, 25, 60, 42);
    draw_boxL(60, 25, 100, 42);
    gotoxy(60, 25);
    printf("��");
    gotoxy(60, 42);
    printf("��");
}

char* AskMenu[2] = { "      Y      ", "      N      "};
void printAskModalItem(int x, int y, int color, char* text){
    if(color == 0)
        textcolor(BLACK, WHITE);
    else
        textcolor(WHITE, BLACK);
    gotoxy(x, y);
    printf("%s", text);
    textcolor(WHITE, BLACK);
}

void printAskModalYN(int nowIndx){
    for(int i = 0; i < 2; i++)
    {
        if(i == 0)
            printAskModalItem(47, 27, i != nowIndx, AskMenu[i]);
        else
            printAskModalItem(62, 27, i != nowIndx, AskMenu[i]);
    }
}

void printAskModal(int nowIndx){
    draw_boxB(42, 20, 78, 30);
    gotoxy(46, 22);
    printf("������ ���� �����Ͻðڽ��ϱ�?");
    gotoxy(48, 24);
    printf("���� �����ʹ� �����˴ϴ�.");
    draw_boxL(45, 26, 75, 28);
    printAskModalYN(nowIndx);
}

void eraseAskModal(){
    for(int i = 0; i <= 10; i++)
    {
        gotoxy(42, 20 + i);
        printf("                                      ");
    }
}

void printMapStr(int y)
{
    gotoxy(11, 10);
    for(int i = 0; i < 30; i++)
    {
        printf("%s", map[i + y]);
        gotoxy(11, 11 + i);
    }
}

void printMenuItemSimple(int x, int y, int color, char* text){
    if(color == 0)
        textcolor(BLACK, WHITE);
    else
        textcolor(WHITE, BLACK);
    gotoxy(x, y);
    printf("%s", text);
}

char* mapMakeMenu[4] = { "   �ѷ�����   ", "   �õ庯��   ", "   ��  Ȯ��   ", "   �ڷΰ���   "};
void printMapMakeMenu(int nowIndx){
    for(int i = 0; i < 4; i++)
    {
        if(i == nowIndx)
            printMenuItemSimple(14 + i * 26, 42, 0, mapMakeMenu[i]);
        else
            printMenuItemSimple(14 + i * 26, 42, 1, mapMakeMenu[i]);
    }
    textcolor(WHITE, BLACK);
}


void printMakeMapPage(int nowIndx){
    cls(0, 15);
    draw_boxB(6, 3, 114, 45);
    draw_boxL(8, 4, 112, 8);
    gotoxy(57, 6);
    printf("�� �� ��");
    draw_boxL(90, 5, 110, 7);
    gotoxy(92, 6);
    srand(time(NULL));
    int seed = rand() % 10000;
    printf("�õ�: %d", seed);
    draw_boxL(8, 9, 112, 40);
    draw_boxL(8, 41, 112, 43);
    printMapMakeMenu(nowIndx);
    generateDungeon(seed);
    printMapStr(0);
    //112 - 8 = 104 / 4 = 26
    //�� �ѷ����� | �õ� ���� | �� Ȯ�� | �ڷΰ���
}



void printLogo(int x, int y)
{
    cls(0, 15);
    gotoxy(x, y);
    printf("   ####  ##   ##    #####   ######           ######   ######     ####   \n");
    gotoxy(x, y+1);
    printf("    ##    ##  ##   ### ##   # ## #            ##  ##   ##  ##   ##  ##  \n");
    gotoxy(x, y+2);
    printf("    ##    ##  ##   ###        ##              ##  ##   ##  ##   ##      \n");
    gotoxy(x, y+3);
    printf("    ##    ##  ##    ####      ##              #####    #####    ## ###  \n");
    gotoxy(x, y+4);
    printf(" ## ##    ##  ##      ###     ##              ## ##    ##       ##  ##  \n");
    gotoxy(x, y+5);
    printf(" ## ##    ##  ##   ## ###     ##              ## ##    ##       ##  ##  \n");
    gotoxy(x, y+6);
    printf("  ###      ####    #####     ####            ### ###  ####       #####  \n");
    gotoxy(x, y+7);
    printf("                                                                         \n");
}

void printMenuItem(int x, int y, int color, char* text){
    if(color == 0)
        textcolor(BLACK, WHITE);
    else
        textcolor(WHITE, BLACK);
    gotoxy(x, y - 1);
    printf("                           ");
    gotoxy(x, y);
    printf("%s", text);
    gotoxy(x, y + 1);
    printf("                           ");
}

void printFirstMenu(int nowIndx)
{
    for(int i = 0; i < 3; i++)
    {
        if(i == nowIndx)
            printMenuItem(85, 33 + i * 3, 0, firstMenu[i]);
        else
            printMenuItem(85, 33 + i * 3, 1, firstMenu[i]);
    }
    textcolor(WHITE, BLACK);
}

