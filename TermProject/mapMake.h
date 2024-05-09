#ifndef MAPMAKE_HEADER
#define MAPMAKE_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

// ���� ����
#define DELAY 100

// �� ���� ����
#define MAX_NODE 5
#define MAP_SIZE 100
#define MAX_ROOM 32


// �� ��� ����
#define EMPTY_SPACE 'X'
#define ROOM ' '
#define PASSAGEWAY ' '
#define PLAYER 'P'
#define STORE 'S'
#define BOSS 'B'
#define TREASURE 'T'
#define ELITE 'E'
#define MIMIC 'M'

// ��ũ�� �Լ� ����
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define MAX(A,B) ((A) > (B) ? (A) : (B))

// ���� ����
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

// Ŀ�ǵ� ����
#define ESC 0x1b //  ESC ������ ����
#define ENTER 0x0d // Enter ������ ����
#define SPECIAL1 0xe0 // Ư��Ű�� 0xe0 + key ������ �����ȴ�.
#define SPECIAL2 0x00 // keypad ��� 0x00 + key �� �����ȴ�.

#define UP  0x48 // Up key�� 0xe0 + 0x48 �ΰ��� ���� ���´�.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d


#define UP2		'w'
#define DOWN2	's'
#define LEFT2	'a'
#define RIGHT2	'd'


typedef struct room {
    int roomIndx;
    int x;
    int y;
    int width;
    int height;
    int type;
} roomType;

typedef struct space {
    int x;
    int y;
    int width;
    int height;
} spaceType;

typedef struct spaceTree {
    spaceType space;
    roomType* room;
    struct spaceTree* left;
    struct spaceTree* right;
} SpaceTree;
//makeMap.c
void initializeDungeon();
void divideSpace(SpaceTree* node, int n);
void createRoom(SpaceTree* node, int n);
void drawRoom(roomType room);
void drawMap();
void generateRoad(SpaceTree* node, int n);
void generateDungeon();
int randint(int min, int max);
int randPer(int length, int* percent);

char map[MAP_SIZE][MAP_SIZE+1];
roomType rooms[MAX_ROOM];
enum roomList { Store, Monster, Boss, Treasure, Mimic, Elite };

//utility.c
void removeCursor(void);
void gotoxy(int x, int y);
void textcolor(int fg_color, int bg_color);
void cls(int bg_color, int text_color);
void draw_boxL(int x1, int y1, int x2, int y2);
void draw_boxB(int x1, int y1, int x2, int y2);

//Theme.c
void printLogo(int x, int y);
void printFirstMenu();
void printMenuItem(int x, int y, int color, char* text);
void printStartPage(int nowIndx);
void printSettingPage(int nowIndx);



#endif /* MAPMAKE_H */
