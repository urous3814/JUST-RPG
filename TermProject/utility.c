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

//���� ���۸� 

int hidden_index; // Hidden ȭ�� ��ȣ 0 or 1
HANDLE scr_handle[2]; // ȭ�� ���� ����
long long frame_count = 0;

void removeCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�

    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void scr_init()
{
    int i;
    CONSOLE_CURSOR_INFO cci;

    cci.dwSize = 1;
    cci.bVisible = FALSE;
    // ȭ�� ���� 2���� �����.
    for (i = 0; i < 2; i++) {
        scr_handle[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        // Ŀ���� �����.
        SetConsoleCursorInfo(scr_handle[i], &cci);
    }
    // 0�� ȭ���� default
    SetConsoleActiveScreenBuffer(scr_handle[0]);
    hidden_index = 1; // 1�� ȭ���� Hidden Screen
}

void ChangeScreenSize(HANDLE hnd, COORD NewSize)
{
    //HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    GetConsoleScreenBufferInfo(hnd, &SBInfo);
    DisplayArea.Bottom = NewSize.Y;
    DisplayArea.Right = NewSize.X;
    SetConsoleWindowInfo(hnd, 1, &DisplayArea);
}

void ChangeBuffSize(HANDLE hnd, COORD NewSize)
{
    SetConsoleScreenBufferSize(hnd, NewSize);
}

void scr_switch()
{
    // hidden �� active �� �����Ѵ�.
    SetConsoleActiveScreenBuffer(scr_handle[hidden_index]);
    // active�� hidden���� �����Ѵ�.
    hidden_index = !hidden_index; // 0 <-> 1 toggle
}

void scr_clear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    // hidden screen�� clear�Ѵ�.
    // WIDTH*2 * HEIGHT ���� [�Ӽ�]���� ������ ���� ��Ȯ�� ���ƾ� �Ѵ�.
    // ��, ȭ�� �Ӽ����� �ʺ�(W)=80, ����(H)=25��� Ư�� ���ڴ� 2ĭ�� �̹Ƿ� WIDTH=40, HEIGHT=25�̴�.
    FillConsoleOutputCharacter(scr_handle[hidden_index], ' ', WIDTH*2 * HEIGHT, Coor, &dw);
}

void scr_release()
{
    CloseHandle(scr_handle[0]);
    CloseHandle(scr_handle[1]);
}

void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(scr_handle[hidden_index], fg_color | bg_color << 4);
}

// ȭ�� ������ ���ϴ� �������� �����Ѵ�.
void cls(int text_color, int bg_color)
{
    char cmd[100];
    system("cls");
    // ȭ�� ũ�� ������ �����Ѵ�.
    sprintf(cmd, "mode con: cols=%d lines=%d", WIDTH*2, HEIGHT);
    system(cmd);
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}

void gotoxy(int x, int y)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    // hidden screen�� gotoxy
    SetConsoleCursorPosition(scr_handle[hidden_index], CursorPosition);
}
void printscr(char* str)
{
    DWORD dw;
    // hidden screen�� gotoxy �Ǿ��ٰ� �����ϰ� print
    WriteFile(scr_handle[hidden_index], str, strlen(str), &dw, NULL);
}

 // �������� ó���� ���� ��� ���� �߰�

void printscr(char* format, ...)
{
    va_list args; // �������� ����� ������ ����
    char buffer[1024]; // ����� ���ڿ��� ������ ����

    va_start(args, format); // �������� ��� �ʱ�ȭ

    // format�� �������ڵ��� ���ۿ� ����ȭ�Ͽ� ����
    vsprintf(buffer, format, args);

    va_end(args); // �������� ó�� ����

    // hidden screen�� ���
    DWORD dw;
    WriteFile(scr_handle[hidden_index], buffer, strlen(buffer), &dw, NULL);
}
