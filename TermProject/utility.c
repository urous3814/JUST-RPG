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

void empty_box(int x1, int y1, int x2, int y2)
{
    int x, y;
    for (x = x1; x <= x2; x++) {
        for (y = y1; y <= y2; y++) {
            gotoxy(x, y);
            printscr(" ");
        }
    }
}

// box �׸��� �Լ�, ch ���ڿ��� (x1,y1) ~ (x2,y2) box�� �׸���.
void draw_boxL(int x1, int y1, int x2, int y2)
{
	int x, y;
    gotoxy(x1, y1);
    printscr("��");
    gotoxy(x2, y1);
    printscr("��");
    gotoxy(x1, y2); 
    printscr("��");
    gotoxy(x2, y2);
    printscr("��");
    for (x = x1 + 2; x < x2-1; x+=2) {
        gotoxy(x, y1);
        printscr("��");
        gotoxy(x, y2);
        printscr("��");
    }
    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        printscr("��");
        gotoxy(x2, y);
        printscr("��");
    }
}
void draw_boxB(int x1, int y1, int x2, int y2)
{
	int x, y;
    gotoxy(x1, y1);
    printscr("��");
    gotoxy(x2, y1);
    printscr("��");
    gotoxy(x1, y2); 
    printscr("��");
    gotoxy(x2, y2);
    printscr("��");
    for (x = x1 + 2; x <= x2-1; x+=2) {
        gotoxy(x, y1);
        printscr("��");
        gotoxy(x, y2);
        printscr("��");
    }
    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        printscr("��");
        gotoxy(x2, y);
        printscr("��");
    }
}
//���� ���۸� 

int hidden_index; // Hidden ȭ�� ��ȣ 0 or 1
HANDLE scr_handle[2]; // ȭ�� ���� ����
long long frame_count = 0;
int needBackCopy = 1;

void removeCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�

    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void removeAllCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(scr_handle[0], &cci);
    SetConsoleCursorInfo(scr_handle[1], &cci);
}



void showCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1; // Ŀ�� ũ��
    curInfo.bVisible = TRUE; // Ŀ�� ���̱� ����

    // Hidden screen���� Ŀ�� ���¸� �����մϴ�.
    SetConsoleCursorInfo(scr_handle[hidden_index], &curInfo);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


void scr_init()
{
    int i;
    CONSOLE_CURSOR_INFO cci;
    needSwitch = 0;

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
    needBackCopy = 1;
    // active�� hidden���� �����Ѵ�.
    hidden_index = !hidden_index; // 0 <-> 1 toggle
}

void scr_clear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    needBackCopy = 0;
    // ���� �ܼ� ȭ�� ������ �Ӽ��� �����ɴϴ�.
    GetConsoleScreenBufferInfo(scr_handle[hidden_index], &csbiInfo);
    // hidden screen�� clear�Ѵ�.
    // WIDTH*2 * HEIGHT ���� [�Ӽ�]���� ������ ���� ��Ȯ�� ���ƾ� �Ѵ�.
    // ��, ȭ�� �Ӽ����� �ʺ�(W)=80, ����(H)=25��� Ư�� ���ڴ� 2ĭ�� �̹Ƿ� WIDTH=40, HEIGHT=25�̴�.
    FillConsoleOutputCharacter(scr_handle[hidden_index], ' ', (WIDTH + 1) * (HEIGHT + 1), Coor, &dw);

    FillConsoleOutputAttribute(scr_handle[hidden_index], csbiInfo.wAttributes, (WIDTH + 1) * (HEIGHT + 1), Coor, &dw);

    needBackCopy = 0;
    needSwitch = 1;
    //�� �ʱ�ȭ
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
    sprintf(cmd, "mode con: cols=%d lines=%d", WIDTH, HEIGHT);
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
 // �������� ó���� ���� ��� ���� �߰�

void printscr(char* format, ...)
{
    if (needSwitch == 0)
    {
        needSwitch = 1;
    }
        
    
    va_list args; // �������� ����� ������ ����
    char buffer[8192]; // ����� ���ڿ��� ������ ����

    va_start(args, format); // �������� ��� �ʱ�ȭ

    // format�� �������ڵ��� ���ۿ� ����ȭ�Ͽ� ����
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args); // �������� ó�� ����

    // hidden screen�� ���
    DWORD dw;
    WriteFile(scr_handle[hidden_index], buffer, strlen(buffer), &dw, NULL);
}
CHAR_INFO cpBuffer[(WIDTH + 1) * (HEIGHT + 1)];
void scr_copy() {
    
    COORD bufferSize = {WIDTH+1, HEIGHT+1};
    COORD bufferCoord = {0, 0};
    SMALL_RECT readRegion = {0, 0, WIDTH+1, HEIGHT+1};

    // 0�� ȭ�� ���ۿ��� ������ �о�ɴϴ�.
    if (!ReadConsoleOutput(scr_handle[!hidden_index], cpBuffer, bufferSize, bufferCoord, &readRegion)) {
        fprintf(stderr, "ReadConsoleOutput ����\n");
        return;
    }
    
    // 1�� ȭ�� ���ۿ� ������ ���ϴ�.
    if (!WriteConsoleOutput(scr_handle[hidden_index], cpBuffer, bufferSize, bufferCoord, &readRegion)) {
        fprintf(stderr, "WriteConsoleOutput ����\n");
        return;
    }
}

void gotoxyScr(int x, int y) //���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API �Լ��Դϴ�. �̰� ���ʿ� �����
}

void printMapBlock(int x, int y, char ch, int bgcolor, int fgcolor) {
    textcolor(fgcolor, bgcolor);
    for(int i = 0; i < 2; i++)
    { 
        gotoxy(60 + x*4, 10 + y*2 + i);
        printscr("�Ƣ�");
    }
    textcolor(WHITE, BLACK);
}

void printObjBlock(int x, int y, char* ch, int indx, int bgcolor, int fgcolor, int pointColor) {
    textcolor(fgcolor, bgcolor);
    gotoxy(60 + x*4, 10 + y*2);
    printscr("%s%2i", ch, indx);
    gotoxy(60 + x*4, 10 + y*2 + 1);
    printscr("�Ƣ�");
    textcolor(WHITE, BLACK);
}