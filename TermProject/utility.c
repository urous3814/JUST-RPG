#include "mapMake.h"

void setup()
{
    COORD coord;
    coord.X = 123; // ���� ����
    coord.Y = 47;  // ���� ����
    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 47;
    Rect.Right = 123;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ�

    // �۲� ũ�� ����
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 8; // ���� �۲� ũ��
    fontInfo.dwFontSize.Y = 16; // ���� �۲� ũ��
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy(fontInfo.FaceName, L"Terminal"); // ������ �۲� �̸�
    SetCurrentConsoleFontEx(Handle, FALSE, &fontInfo);


    SetConsoleWindowInfo(Handle, TRUE, &Rect);       // â ũ�� ����
    SetConsoleScreenBufferSize(Handle, coord);        // ���� ũ�� ����

    // �ܼ� ���� ����
    char* euc_kr_title = "JUST RPG";

    // EUC-KR ���ڿ� ����
    int euc_kr_len = strlen(euc_kr_title);

    // Unicode ���� ũ�� ���
    int unicode_len = MultiByteToWideChar(CP_ACP, 0, euc_kr_title, euc_kr_len, NULL, 0);

    // Unicode ���� ���� �Ҵ�
    wchar_t* unicode_title = (wchar_t*)malloc((unicode_len + 1) * sizeof(wchar_t));

    // EUC-KR ���ڿ��� Unicode�� ��ȯ
    MultiByteToWideChar(CP_ACP, 0, euc_kr_title, euc_kr_len, unicode_title, unicode_len);
    unicode_title[unicode_len] = L'\0'; // Null ���� ���� �߰�

    // �ܼ� ���� ����
    SetConsoleTitle(unicode_title);

    // �޸� ����
    free(unicode_title);
}

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

void showCursor(void){ // Ŀ���� �Ⱥ��̰� �Ѵ�

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible=1;
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
    for (x = x1 + 2; x < x2-1; x+=2) {
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