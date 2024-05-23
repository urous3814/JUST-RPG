#include "mapMake.h"

char* firstMenu[4] = { "  ��     ��     ��     ��  ", "  ��     ��     ��     ��  ", "  ȯ     ��     ��     ��  "};

void printLogo(int x, int y)
{
    gotoxy(x, y);
    printscr("   ####  ##   ##    #####   ######           ######   ######     ####   \n");
    gotoxy(x, y + 1);
    printscr("    ##    ##  ##   ### ##   # ## #            ##  ##   ##  ##   ##  ##  \n");
    gotoxy(x, y + 2);
    printscr("    ##    ##  ##   ###        ##              ##  ##   ##  ##   ##      \n");
    gotoxy(x, y + 3);
    printscr("    ##    ##  ##    ####      ##              #####    #####    ## ###  \n");
    gotoxy(x, y + 4);
    printscr(" ## ##    ##  ##      ###     ##              ## ##    ##       ##  ##  \n");
    gotoxy(x, y + 5);
    printscr(" ## ##    ##  ##   ## ###     ##              ## ##    ##       ##  ##  \n");
    gotoxy(x, y + 6);
    printscr("  ###      ####    #####     ####            ### ###  ####       #####  \n");
    gotoxy(x, y + 7);
    printscr("                                                                         \n");
}

void printStartPage(int nowIndx){
    printLogo(25, 10);
    draw_boxL(0, 0, 120, 46);
    draw_boxL(80, 30, 116, 42);
    gotoxy(5, 44);
    printscr("github.com/urous3814/JUST-RPG");
    printFirstMenu(nowIndx);
}

void printSettingPage(int nowIndx){
    printLogo(25, 10);
    draw_boxB(18, 19, 102, 43);
    draw_boxL(20, 20, 100, 24);
    gotoxy(54, 22);
    printscr("  ȯ �� �� �� ");
    draw_boxL(20, 25, 60, 42);
    draw_boxL(60, 25, 100, 42);
    gotoxy(60, 25);
    printscr("��");
    gotoxy(60, 42);
    printscr("��");
    //ȯ�漳�� â���� ���� ���� ũ��, ���� on/off, ȿ���� ũ��, ȿ���� on/off, �ڷΰ���, �ڵ����� �ϼ� �ɼ� ���� ����
}

void printGamePage() {
    // ���� ��� ��ų ����
    draw_boxL(1, 1, 20, 15);
    gotoxy(3, 2);
    printscr("# # # ���� (H) ���� �Ҹ� 10\n");
    gotoxy(3, 4);
    printscr("���ݷ� 3-5 ��ȭ 1-2��\n");
    gotoxy(3, 6);
    printscr("# # # ���� (J) ���� �Ҹ� 5\n");
    gotoxy(3, 8);
    printscr("���ݷ� 4-9\n");
    gotoxy(3, 10);
    printscr("### ���� (K) ���� �Ҹ� 25\n");
    gotoxy(3, 12);
    printscr("���ݷ� 1-20 ��ȭ 0-1��\n");
    gotoxy(3, 14);
    printscr("���� 0-1��\n");

    // ���� �ϴ� ������ ����
    draw_boxL(1, 16, 20, 20);
    gotoxy(3, 17);
    printscr("������ ����\n");
    gotoxy(3, 18);
    printscr("10-50%%�� hp�� �һ�\n");
    gotoxy(3, 19);
    printscr("5-40%%�� EXP �ս�\n");

    // �߾� ��� �þ� ǥ��
    draw_boxL(21, 1, 101, 37);
    gotoxy(61, 19);
    printscr("�þ߹��� ����\n");
    gotoxy(61, 20);
    printscr("�þ� ǥ��\n");

    // ���� ��� ���� ����
    draw_boxL(102, 1, 122, 15);
    gotoxy(104, 2);
    printscr("[ ��� ]\n");
    gotoxy(104, 3);
    printscr("LV 1 HP 3\n");
    gotoxy(104, 4);
    printscr("STATUS ��ȭ[2]\n");
    gotoxy(104, 6);
    printscr("[ ��� ]\n");
    gotoxy(104, 7);
    printscr("LV 1 HP 10\n");
    gotoxy(104, 8);
    printscr("STATUS ����\n");
    gotoxy(104, 10);
    printscr("[ ���� ]\n");
    gotoxy(104, 11);
    printscr("LV 7 HP 95\n");
    gotoxy(104, 12);
    printscr("STATUS ����[4]\n");

    // �ϴ� �߾� �÷��̾� ����
    draw_boxL(21, 38, 101, 46);
    gotoxy(23, 39);
    printscr("UROUS\n");
    gotoxy(23, 40);
    printscr("HP 250  MP 40  TURN 108\n");
    gotoxy(23, 41);
    printscr("ROOM 13  ITEM 7\n");
    gotoxy(23, 42);
    printscr("ATK 13  DEF 7  LEV 2  LUC 10\n");
    gotoxy(23, 43);
    printscr("��� : 250  ų ī��Ʈ : 12\n");
    gotoxy(23, 44);
    printscr("LV 2  ����ġ ��\n");
    gotoxy(23, 45);
    printscr("55/250 ü�� ��\n");
    gotoxy(23, 46);
    printscr("10/40 ���� ��\n");

    // ���� �ϴ� �޴�
    draw_boxL(102, 16, 122, 46);
    gotoxy(104, 17);
    printscr("�κ��丮 (I)\n");
    gotoxy(104, 19);
    printscr("��� (O)\n");
    gotoxy(104, 21);
    printscr("�޴� (ESC)\n");
}

char* AskMenu[2] = { "      Y      ", "      N      "};
char* diffMenu[3] = {" NORMAL ", " HARD ", " Extream "};
void printAskModalItem(int x, int y, int color, char* text){
    if(color == 0)
        textcolor(BLACK, WHITE);
    else
        textcolor(WHITE, BLACK);
    gotoxy(x, y);
    printscr("%s", text);
    textcolor(WHITE, BLACK);
}

void printAskModalYN(int nowIndx, int nowStatus){
    switch (nowStatus)
    {
    case 0:
        for(int i = 0; i < 2; i++)
        {
            if(i == 0)
                printAskModalItem(47, 27, i != nowIndx, AskMenu[i]);
            else
                printAskModalItem(62, 27, i != nowIndx, AskMenu[i]);
        }
        break;
    case 1:
        for(int i = 0; i < 3; i++)
        {
            if(i == nowIndx)
                printAskModalItem(47 + i * 9, 27, 0, diffMenu[i]);
            else
                printAskModalItem(47 + i * 9, 27, 1, diffMenu[i]);
        }
        break;
    default:
        break;
    }
    
}

void printAskModal(int nowIndx, int nowStatus){
    eraseAskModal();
    draw_boxB(42, 20, 78, 30);
    if(nowStatus == 0)
    {
        gotoxy(46, 22);
        printscr("������ ���� �����Ͻðڽ��ϱ�?");
        gotoxy(48, 24);
        printscr("���� �����ʹ� �����˴ϴ�.");
    }
    else if (nowStatus == 1)
    {
        gotoxy(46, 22);
        printscr("������ ���̵��� �������ּ���.");
        
    }
    draw_boxL(45, 26, 75, 28);
    printAskModalYN(nowIndx, nowStatus);
}


void eraseAskModal(){
    for(int i = 0; i <= 10; i++)
    {
        gotoxy(42, 20 + i);
        printscr("                                      ");
    }
}

void printMapStr(int y)
{
    gotoxy(11, 10);
    for(int i = 0; i < 30; i++)
    {
        printscr("%s", map[i + y]);
        gotoxy(11, 11 + i);
    }
}

void printMenuItemSimple(int x, int y, int color, char* text){
    if(color == 0)
        textcolor(BLACK, WHITE);
    else
        textcolor(WHITE, BLACK);
    gotoxy(x, y);
    printscr("%s", text);
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
    printscr("�� �� ��");
    draw_boxL(90, 5, 110, 7);
    gotoxy(92, 6);
    srand(time(NULL));
    int seed = rand() % 10000;
    printscr("�õ�: %d", seed);
    draw_boxL(8, 9, 112, 40);
    draw_boxL(8, 41, 112, 43);
    printMapMakeMenu(nowIndx);
    generateDungeon(seed);
    printMapStr(0);
    //112 - 8 = 104 / 4 = 26
    //�� �ѷ����� | �õ� ���� | �� Ȯ�� | �ڷΰ���
}





void printMenuItem(int x, int y, int color, char* text){
    if(color == 0)
        textcolor(BLACK, WHITE);
    else
        textcolor(WHITE, BLACK);
    gotoxy(x, y - 1);
    printscr("                           ");
    gotoxy(x, y);
    printscr("%s", text);
    gotoxy(x, y + 1);
    printscr("                           ");
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
//���⿡������ ���� ����

