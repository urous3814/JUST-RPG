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

enum magicType {Ice, Scare, Mabi, None};
char* maginName[4] = {"����", "����", "����", "�ɷ� ����"};

typedef struct skill{
    char* name;
    char* Hit[3];
    int mana;
    int damage[2];
    char key;
    enum magicType magic;
} skillType;

skillType skill[3] = {
    {"����", {"###", "   ", " P "}, 10, {3, 5}, 'H', Ice},
    {"����", {" # ", " # ", " P "}, 5, {4, 9}, 'J', Scare},
    {"����", {"###", "###", "#P#"}, 25, {0, 20}, 'K', Mabi}
};

void printSkill(int height, int index) {
    gotoxy(3, 2+height);
    printscr("%s %s   (%c)", skill[index].Hit[0], skill[index].name, skill[index].key);
    gotoxy(3, 3+height);
    printscr("%s �����Ҹ� %d", skill[index].Hit[1], skill[index].mana);
    gotoxy(3, 4+height);
    printscr("%s ���ݷ� %d-%d", skill[index].Hit[2], skill[index].damage[0], skill[index].damage[1]);
    gotoxy(3, 5+height);
    printscr("%s", maginName[skill[index].magic]);
}

void drawPlayerView() {

}

void printGamePage() {
    // ���� ��� ��ų ����
    draw_boxL(1, 1, 21, 3);
    gotoxy(10, 2);
    printscr("��ų");
    draw_boxL(1, 3, 21, 18);
    gotoxy(1, 3);
    printscr("��");
    gotoxy(21, 3);
    printscr("��");
    printSkill(2, 0);
    printSkill(7, 1);
    printSkill(12, 2);

    // ���� �ϴ� ������ ����
    draw_boxL(1, 19, 21, 22);
    gotoxy(3, 19);
    printscr("������ ����\n");
    gotoxy(3, 20);
    printscr("10-50%%�� hp�� �һ�\n");
    gotoxy(3, 21);
    printscr("5-40%%�� EXP �ս�\n");

    // �߾� ��� �þ� ǥ��
    draw_boxL(22, 1, 100, 37);
    gotoxy(61, 19);
    printscr("�þ߹��� ����\n");
    gotoxy(61, 20);
    printscr("�þ� ǥ��\n");
    //(100+22)/2=61 61 + 3*5 + 2 = 78     2 * 11 = 22
    // 61-4*5-1 = 40 
    draw_boxL(40, 10, 82, 32);

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

void printPlayerMapSight() {
    int startX;
    int size;
    int color;
    for (int i = 0; i < 11; i++)
    {
        startX = playerViewSight.startX[i];
        size = playerViewSight.size[i];
        if (playerViewSight.mapSight[i][1] < 0 || playerViewSight.mapSight[i][1] >= MAP_SIZE)
        {
            for (int l = 0; l < size; l++)
                printMapBlock(startX + l, i, 0, BLACK);
        }
        else
        {
            for (int j = 0; j < size; j++)
            {
                if (playerViewSight.mapSight[i][0] < 0)
                {
                    for (int l = 0; l < -playerViewSight.mapSight[i][0]; l++)
                        printMapBlock(startX + l, i, 0, BLACK);
                    j -= playerViewSight.mapSight[i][0];
                }
                else if (playerViewSight.mapSight[i][0] + j > MAP_SIZE)
                {
                    for (int l = j; l < size; l++)
                        printMapBlock(startX + l, i, 0, BLACK);
                    break;
                }
                switch (map[playerViewSight.mapSight[i][0] + j][playerViewSight.mapSight[i][1]])
                {
                case EMPTY_SPACE:
                    color = BLACK;
                    break;
                case ROOM:
                    color = GRAY2;
                    break;
                default:
                    color = BLACK;
                }
                printMapBlock(startX + j, i, 0, color);
            }
        }
        
    }
    
}
void printPlayerzLayerSight() {
    int startX;
    int size;
    int color;
    int addX, addY;
    int mapSightX, mapSightY;
    for (int i = 0; i < 11; i++)
    {
        startX = playerViewSight.startX[i];
        size = playerViewSight.size[i];
        mapSightY = playerViewSight.mapSight[i][1];
        if(mapSightY < 0 || mapSightY >= MAP_SIZE)
        {
            continue;
        }
        for (int j = 0; j < size; j++)
        {
            mapSightX = playerViewSight.mapSight[i][0];
            if(mapSightX < 0)
            {
                j -= mapSightX;
            }
            else if(mapSightX > MAP_SIZE)
            {
                break;
            }
            if(zLayer[mapSightX + j][mapSightY].type != -1)
            {
                switch (zLayer[mapSightX + j][mapSightY].type)
                {
                case objMONSTER:
                    color = RED1;
                    break;
                case objBOSS:
                    color = RED2;
                    break;
                case objELITE:
                    color = YELLOW1;
                    break;
                case objTREASURE:
                    color = YELLOW2;
                    break;
                case objMIMIC: 
                    color = YELLOW2;
                    break;
                case objSTORE:
                    color = GREEN1;
                    break;
                default:
                    color = BLACK;
                    break;
                }
                printMapBlock(startX + j, i, 1, color);
            }
        }
    }
}