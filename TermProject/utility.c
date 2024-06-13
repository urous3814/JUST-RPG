#include "mapMake.h"


void setup()
{
    COORD coord;
    coord.X = 123; // 가로 길이
    coord.Y = 47;  // 세로 길이
    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 47;
    Rect.Right = 123;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들

    // 글꼴 크기 설정
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 8; // 가로 글꼴 크기
    fontInfo.dwFontSize.Y = 16; // 세로 글꼴 크기
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy(fontInfo.FaceName, L"Terminal"); // 레스터 글꼴 이름
    SetCurrentConsoleFontEx(Handle, FALSE, &fontInfo);


    SetConsoleWindowInfo(Handle, TRUE, &Rect);       // 창 크기 설정
    SetConsoleScreenBufferSize(Handle, coord);        // 버퍼 크기 설정

    // 콘솔 제목 설정
    char* euc_kr_title = "JUST RPG";

    // EUC-KR 문자열 길이
    int euc_kr_len = strlen(euc_kr_title);

    // Unicode 버퍼 크기 계산
    int unicode_len = MultiByteToWideChar(CP_ACP, 0, euc_kr_title, euc_kr_len, NULL, 0);

    // Unicode 버퍼 동적 할당
    wchar_t* unicode_title = (wchar_t*)malloc((unicode_len + 1) * sizeof(wchar_t));

    // EUC-KR 문자열을 Unicode로 변환
    MultiByteToWideChar(CP_ACP, 0, euc_kr_title, euc_kr_len, unicode_title, unicode_len);
    unicode_title[unicode_len] = L'\0'; // Null 종결 문자 추가

    // 콘솔 제목 설정
    SetConsoleTitle(unicode_title);

    // 메모리 해제
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

// box 그리기 함수, ch 문자열로 (x1,y1) ~ (x2,y2) box를 그린다.
void draw_boxL(int x1, int y1, int x2, int y2)
{
	int x, y;
    gotoxy(x1, y1);
    printscr("┌");
    gotoxy(x2, y1);
    printscr("┐");
    gotoxy(x1, y2); 
    printscr("└");
    gotoxy(x2, y2);
    printscr("┘");
    for (x = x1 + 2; x < x2-1; x+=2) {
        gotoxy(x, y1);
        printscr("─");
        gotoxy(x, y2);
        printscr("─");
    }
    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        printscr("│");
        gotoxy(x2, y);
        printscr("│");
    }
}
void draw_boxB(int x1, int y1, int x2, int y2)
{
	int x, y;
    gotoxy(x1, y1);
    printscr("┏");
    gotoxy(x2, y1);
    printscr("┓");
    gotoxy(x1, y2); 
    printscr("┗");
    gotoxy(x2, y2);
    printscr("┛");
    for (x = x1 + 2; x <= x2-1; x+=2) {
        gotoxy(x, y1);
        printscr("━");
        gotoxy(x, y2);
        printscr("━");
    }
    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        printscr("┃");
        gotoxy(x2, y);
        printscr("┃");
    }
}
//더블 버퍼링 

int hidden_index; // Hidden 화면 번호 0 or 1
HANDLE scr_handle[2]; // 화면 버퍼 변수
long long frame_count = 0;
int needBackCopy = 1;

void removeCursor(void) { // 커서를 안보이게 한다

    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void removeAllCursor(void) { // 커서를 안보이게 한다
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(scr_handle[0], &cci);
    SetConsoleCursorInfo(scr_handle[1], &cci);
}



void showCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1; // 커서 크기
    curInfo.bVisible = TRUE; // 커서 보이기 여부

    // Hidden screen에서 커서 상태를 설정합니다.
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
    // 화면 버퍼 2개를 만든다.
    for (i = 0; i < 2; i++) {
        scr_handle[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        // 커서를 숨긴다.
        SetConsoleCursorInfo(scr_handle[i], &cci);
    }
    // 0번 화면이 default
    SetConsoleActiveScreenBuffer(scr_handle[0]);
    hidden_index = 1; // 1번 화면이 Hidden Screen
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
    // hidden 을 active 로 변경한다.
    SetConsoleActiveScreenBuffer(scr_handle[hidden_index]);
    needBackCopy = 1;
    // active를 hidden으로 변경한다.
    hidden_index = !hidden_index; // 0 <-> 1 toggle
}

void scr_clear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    needBackCopy = 0;
    // 현재 콘솔 화면 버퍼의 속성을 가져옵니다.
    GetConsoleScreenBufferInfo(scr_handle[hidden_index], &csbiInfo);
    // hidden screen를 clear한다.
    // WIDTH*2 * HEIGHT 값은 [속성]에서 설정한 값과 정확히 같아야 한다.
    // 즉, 화면 속성에서 너비(W)=80, 높이(H)=25라면 특수 문자는 2칸씩 이므로 WIDTH=40, HEIGHT=25이다.
    FillConsoleOutputCharacter(scr_handle[hidden_index], ' ', (WIDTH + 1) * (HEIGHT + 1), Coor, &dw);

    FillConsoleOutputAttribute(scr_handle[hidden_index], csbiInfo.wAttributes, (WIDTH + 1) * (HEIGHT + 1), Coor, &dw);

    needBackCopy = 0;
    needSwitch = 1;
    //색 초기화
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

// 화면 지우기고 원하는 배경색으로 설정한다.
void cls(int text_color, int bg_color)
{
    char cmd[100];
    system("cls");
    // 화면 크기 강제로 조정한다.
    sprintf(cmd, "mode con: cols=%d lines=%d", WIDTH, HEIGHT);
    system(cmd);
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}


void gotoxy(int x, int y)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    // hidden screen에 gotoxy
    SetConsoleCursorPosition(scr_handle[hidden_index], CursorPosition);
}
 // 가변인자 처리를 위한 헤더 파일 추가

void printscr(char* format, ...)
{
    if (needSwitch == 0)
    {
        needSwitch = 1;
    }
        
    
    va_list args; // 가변인자 목록을 저장할 변수
    char buffer[8192]; // 출력할 문자열을 저장할 버퍼

    va_start(args, format); // 가변인자 목록 초기화

    // format과 가변인자들을 버퍼에 형식화하여 저장
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args); // 가변인자 처리 종료

    // hidden screen에 출력
    DWORD dw;
    WriteFile(scr_handle[hidden_index], buffer, strlen(buffer), &dw, NULL);
}
CHAR_INFO cpBuffer[(WIDTH + 1) * (HEIGHT + 1)];
void scr_copy() {
    
    COORD bufferSize = {WIDTH+1, HEIGHT+1};
    COORD bufferCoord = {0, 0};
    SMALL_RECT readRegion = {0, 0, WIDTH+1, HEIGHT+1};

    // 0번 화면 버퍼에서 내용을 읽어옵니다.
    if (!ReadConsoleOutput(scr_handle[!hidden_index], cpBuffer, bufferSize, bufferCoord, &readRegion)) {
        fprintf(stderr, "ReadConsoleOutput 실패\n");
        return;
    }
    
    // 1번 화면 버퍼에 내용을 씁니다.
    if (!WriteConsoleOutput(scr_handle[hidden_index], cpBuffer, bufferSize, bufferCoord, &readRegion)) {
        fprintf(stderr, "WriteConsoleOutput 실패\n");
        return;
    }
}

void gotoxyScr(int x, int y) //내가 원하는 위치로 커서 이동
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void printMapBlock(int x, int y, char ch, int bgcolor, int fgcolor) {
    textcolor(fgcolor, bgcolor);
    for(int i = 0; i < 2; i++)
    { 
        gotoxy(60 + x*4, 10 + y*2 + i);
        printscr("▒▒");
    }
    textcolor(WHITE, BLACK);
}

void printObjBlock(int x, int y, char* ch, int indx, int bgcolor, int fgcolor, int pointColor) {
    textcolor(fgcolor, bgcolor);
    gotoxy(60 + x*4, 10 + y*2);
    printscr("%s%2i", ch, indx);
    gotoxy(60 + x*4, 10 + y*2 + 1);
    printscr("▒▒");
    textcolor(WHITE, BLACK);
}