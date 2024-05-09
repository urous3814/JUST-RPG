#include "mapMake.h"

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int randPer(int length, int* percent) {
    int percentSum = 0;
    for (int i = 1; i < length; i++) {
        percent[i] += percent[i - 1];
    }
    int randNum = rand() % percentSum;
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += percent[i];
        if (randNum < sum) {
            return i;
        }
    }
    return -1;
}



void removeCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y) //���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API �Լ��Դϴ�. �̰� ���ʿ� �����
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}
// ȭ�� ������ ���ϴ� �������� �����Ѵ�.
void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}
// box �׸��� �Լ�, ch ���ڿ��� (x1,y1) ~ (x2,y2) box�� �׸���.
void draw_boxL(int x1, int y1, int x2, int y2)
{
	int x, y;
    gotoxy(x1, y1);
    printf("��");
    gotoxy(x2, y1);
    printf("��");
    gotoxy(x1, y2); 
    printf("��");
    gotoxy(x2, y2);
    printf("��");
    for (x = x1 + 2; x <= x2-1; x+=2) {
        gotoxy(x, y1);
        printf("��");
        gotoxy(x, y2);
        printf("��");
    }
    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        printf("��");
        gotoxy(x2, y);
        printf("��");
    }
}
void draw_boxB(int x1, int y1, int x2, int y2)
{
	int x, y;
    gotoxy(x1, y1);
    printf("��");
    gotoxy(x2, y1);
    printf("��");
    gotoxy(x1, y2); 
    printf("��");
    gotoxy(x2, y2);
    printf("��");
    for (x = x1 + 2; x <= x2-1; x+=2) {
        gotoxy(x, y1);
        printf("��");
        gotoxy(x, y2);
        printf("��");
    }
    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        printf("��");
        gotoxy(x2, y);
        printf("��");
    }
}