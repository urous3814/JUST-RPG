#include "mapMake.h"

char* firstMenu[4] = { "  새     로     시     작  ", "  이     어     하     기  ", "  환     경     설     정  "};

int mobListLen = 0;

void colorLogo(char* str)
{
    int color = MAGENTA1;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] != ' ')
            textcolor(color, color);
        else
            textcolor(BLACK, BLACK);
        printscr("%c", str[i]);
    }
    textcolor(WHITE, BLACK);
}

void colorSkill(char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        
        if(str[i] == '#')
            textcolor(RED2, RED2);
        else if(str[i] == 'P')
            textcolor(CYAN1, CYAN1);
        else
            textcolor(GRAY2, GRAY2);
        printscr("%c", str[i]);
    }
    textcolor(BLACK, GRAY1);
}

void printDungeonScene(int x, int y)
{  
    gotoxy(x, y + 1);
    printscr("         /####/  . │RPG Game       ");
    gotoxy(x, y + 2);
    printscr("        @====@ .   │Based on       ");
    gotoxy(x, y + 3);
    printscr("     O  |   /|     │ROUGE.       ");
    gotoxy(x, y + 4);
    printscr("    /|\\ |  / |     │2371335      ");
    gotoxy(x, y + 5);
    printscr("  .  |  | /  |  .  │KIMJIHUN  ");
    gotoxy(x, y + 6);
    printscr("     ^  |/  .|    .│            ");
    gotoxy(x, y + 7);
    printscr("    | |   .        │        ");
    gotoxy(x, y + 8);
}

void printLogo(int x, int y)
{  
    gotoxy(x, y);
    colorLogo("   ####   ##  ##    #####   ######           ######   ######     ####   \n");
    gotoxy(x, y + 1);
    colorLogo("    ##    ##  ##   ### ##   # ## #            ##  ##   ##  ##   ##  ##  \n");
    gotoxy(x, y + 2);
    colorLogo("    ##    ##  ##   ###        ##              ##  ##   ##  ##   ##      \n");
    gotoxy(x, y + 3);
    colorLogo("    ##    ##  ##    ####      ##              #####    #####    ## ###  \n");
    gotoxy(x, y + 4);
    colorLogo(" ## ##    ##  ##      ###     ##              ## ##    ##       ##  ##  \n");
    gotoxy(x, y + 5);
    colorLogo(" ## ##    ##  ##   ## ###     ##              ## ##    ##       ##  ##  \n");
    gotoxy(x, y + 6);
    colorLogo("  ###      ####    #####     ####            ### ###  ####       ####   \n");
    gotoxy(x, y + 7);
    colorLogo("                                                                         \n");
    printDungeonScene(85, 22);
}

void printStartPage(int nowIndx){
    printLogo(25, 10);
    draw_boxL(0, 0, 120, 46);
    draw_boxL(80, 30, 116, 42);
    gotoxy(80 + 12*2, 30);
    printscr("┴");
    gotoxy(5, 44);
    printscr("github.com/urous3814/JUST-RPG");
    printFirstMenu(nowIndx);
}

void printSettingPage(int nowIndx){
    printLogo(25, 10);
    draw_boxB(18, 19, 102, 43);
    draw_boxL(20, 20, 100, 24);
    gotoxy(54, 22);
    printscr("  환 경 설 정 ");
    draw_boxL(20, 25, 60, 42);
    draw_boxL(60, 25, 100, 42);
    gotoxy(60, 25);
    printscr("┬");
    gotoxy(60, 42);
    printscr("┴");
    //환경설정 창에는 각각 사운드 크기, 사운드 on/off, 효과음 크기, 효과음 on/off, 뒤로가기, 자동저장 턴수 옵션 조정 가능
}



void printSkill(int height, int index) {
    gotoxy(3, 2+height);
    colorSkill(skill[index].Hit[0]);
    gotoxy(7, 2+height);
    printscr("%s   (%c)", skill[index].name, skill[index].key);
    gotoxy(3, 3+height);
    colorSkill(skill[index].Hit[1]);
    gotoxy(7, 3+height);
    printscr("마나소모 %d", skill[index].mana);
    gotoxy(3, 4+height);
    colorSkill(skill[index].Hit[2]);
    gotoxy(7, 4+height);
    printscr("공격력 %d-%d", skill[index].damage[0], skill[index].damage[1]);
    gotoxy(3, 5+height);
    if(height != 24)
        printscr("    %s", magicName[skill[index].magic]);
    else
        printscr("        ");
}

void printPlayerInfo() {

}

void printMobStatus(int indx, objectType* mobObj) {
    mobListLen = indx+1;
    gotoxy(104, 2 + 4*indx);
    printscr("                 ");
    gotoxy(104, 2 + 4*indx);
    printscr("[ %s %2d ]\n", mobNameKor[mobObj->mobDetail.mobType], mobObj->mobDetail.mobIndx);
    gotoxy(104, 3 + 4*indx);
    printscr("                 ");
    gotoxy(104, 3 + 4*indx);
    printscr("LV%2d HP%3d/%d\n", mobObj->level, mobObj->mobDetail.hp, mobObj->maxHp);
    gotoxy(104, 4 + 4*indx);
    printscr("                 ");
    gotoxy(104, 4 + 4*indx);
    if(mobObj->mobDetail.magicLen > 0)
        printscr("STATUS %s[%d]\n", statusName[mobObj->mobDetail.magic], mobObj->mobDetail.magicLen);
    else
        printscr("STATUS 정상\n");

    int hpBarSize = 17 * mobObj->mobDetail.hp / mobObj->maxHp;
    gotoxy(104, 5 + 4*indx);
    textcolor(BLACK, BLACK);
    printscr("#################");
    gotoxy(104, 5 + 4*indx);
    textcolor(RED1, RED1);
    printscr("%.*s", hpBarSize, "=================");
    textcolor(BLACK, GRAY1);
}

void eraseMobStatus()
{
    textcolor(BLACK, GRAY1);
    for(int i = 0; i < mobListLen; i++)
    {
        gotoxy(104, 2 + 4*i);
        printscr("                  ");
        gotoxy(104, 3 + 4*i);
        printscr("                  ");
        gotoxy(104, 4 + 4*i);
        printscr("                  ");
        gotoxy(104, 5 + 4*i);
        printscr("                  ");
    }
    mobListLen = 0;
}

void printMobList() {
    eraseMobStatus();
    int indx = 0;
    for (int i = 0; i < bossArraySize; i++) {
        printMobStatus(indx++, bossArray[i]);
    }
    for (int i = 0; i < eliteArraySize; i++) {
        printMobStatus(indx++, eliteArray[i]);
    }
    for (int i = 0; i < monsterArraySize; i++) {
        printMobStatus(indx++, monsterArray[i]);
    }
}



void printNowAction(int manaAvailable) {
    textcolor(BLACK, GRAY1);
    empty_box(1, 25, 21, 34);
    draw_boxL(1, 25, 21, 27);
    gotoxy(8, 26);
    printscr("현재액션");
    draw_boxL(1, 27, 21, 34);
    gotoxy(1, 27);
    printscr("├");
    gotoxy(21, 27);
    printscr("┤");
    printSkill(26, nowSkillIndx);
    if(manaAvailable == 0)
    {
        gotoxy(3, 32);
        printscr("마나 부족");
    }
    else
    {
        gotoxy(3, 32);
        printscr("확인( S P A C E )");
        gotoxy(3, 33);
        printscr("취소( BACKSPACE )");
    }
    textcolor(WHITE, BLACK);
}
void printBar(int x, int barSize, int amount, int full)
{
    int colorFg = WHITE, colorBg = BLACK;
    char bar[30];
    if(x == 0)
        sprintf(bar, "#HP#%d/%d#############", amount, full);
    else
        sprintf(bar, "#MP#%d/%d#############", amount, full);

    gotoxy(22 + x, 41);
    for(int i = 0; i < 20; i++)
    {
        if(bar[i]=='#')
            colorFg = BLACK;
        else
            colorFg = WHITE;

        if(i<barSize){
            if(x == 0)
                colorBg = RED1;
            else
                colorBg = BLUE1;
            if(colorFg == BLACK)
                textcolor(colorBg, colorBg);
            else
                textcolor(colorFg, colorBg);
        }
        else{
            if(bar[i]=='#')
                colorFg = BLACK;
            else
                colorFg = WHITE;
            textcolor(colorFg, BLACK);
        }
        printscr("%c", bar[i]);

    }
    textcolor(BLACK, GRAY1);
}

void printExpBar(int barSize, int amount, int full)
{
    int colorFg = WHITE, colorBg = BLACK;
    char bar[50];
    sprintf(bar, "EXP#%d/%d#################################", amount, full);
    gotoxy(22, 40);
    for(int i = 0; i < 40; i++)
    {
        if(bar[i]=='#')
            colorFg = BLACK;
        else
            colorFg = WHITE;

        if(i<barSize){
            colorBg = YELLOW1;
            if(colorFg == BLACK)
                textcolor(colorBg, colorBg);
            else
                textcolor(colorFg, colorBg);
        }
        else{
            if(bar[i]=='#')
                colorFg = WHITE;
            else
                colorFg = BLACK;
            textcolor(colorFg, WHITE);
        }
        printscr("%c", bar[i]);
    }
    textcolor(BLACK, GRAY1);
}

void printPlayerStatus() {
    textcolor(BLACK, GRAY1);
    empty_box(20, 38, 98, 46);
    draw_boxL(20, 38, 98, 46);
    gotoxy(22, 39);
    printscr("UROUS  LV. %d TURN: %d\n", player.level, turn);

    int expBarSize = 42 * player.exp / (player.level*30);
    printExpBar(expBarSize, player.exp, player.level*30);
    int hpBarSize = 20 * player.nowHp / player.hp;
    int mpBarSize = 20 * player.nowMp / player.mp;
    printBar(0, hpBarSize, player.nowHp, player.hp);
    printBar(20, mpBarSize, player.nowMp, player.mp);
    gotoxy(22, 42);
    printscr("ATK: %d  DEF: %d 골드: %d  킬 카운트: %d\n", player.atk, player.def, player.gold, killCount);

}

void printGamePage() {
    // 좌측 상단 스킬 상자
    textcolor(BLACK, GRAY1);
    empty_box(1, 1, 21, 18);
    draw_boxL(1, 1, 21, 3);
    gotoxy(10, 2);
    printscr("스킬");
    draw_boxL(1, 3, 21, 18);
    gotoxy(1, 3);
    printscr("├");
    gotoxy(21, 3);
    printscr("┤");
    printSkill(2, 0);
    printSkill(7, 1);
    printSkill(12, 2);

    // 좌측 하단 라이프 베슬
    empty_box(1, 20, 21, 23);
    draw_boxL(1, 20, 21, 23);
    gotoxy(3, 20);
    printscr("라이프 베슬\n");
    gotoxy(3, 21);
    printscr("10-50%%의 hp로 소생\n");
    gotoxy(3, 22);
    printscr("5-40%%의 EXP 손실\n");

    


    // 중앙 상단 시야 표시
    //(100+22)/2=61 61 + 3*5 + 2 = 78     2 * 11 = 22
    // 61-4*5-1 = 40 
    // draw_boxL(40, 10, 82, 32);

    // 우측 상단 몬스터 정보
    empty_box(102, 1, 122, 34);
    draw_boxL(102, 1, 122, 34);
    // gotoxy(104, 2);
    // printscr("[ 고블린 ]\n");
    // gotoxy(104, 3);
    // printscr("LV 1 HP 3\n");
    // gotoxy(104, 4);
    // printscr("STATUS 약화[2]\n");
    // gotoxy(104, 6);
    // printscr("[ 고블린 ]\n");
    // gotoxy(104, 7);
    // printscr("LV 1 HP 10\n");
    // gotoxy(104, 8);
    // printscr("STATUS 정상\n");
    // gotoxy(104, 10);
    // printscr("[ 구울 ]\n");
    // gotoxy(104, 11);
    // printscr("LV 7 HP 95\n");
    // gotoxy(104, 12);
    // printscr("STATUS 광폭[4]\n");

    // 하단 중앙 플레이어 상태
    printPlayerStatus();

    // 우측 하단 메뉴
    empty_box(102, 36, 122, 46);
    draw_boxL(102, 36, 122, 46);
    gotoxy(104, 37);
    printscr("인벤토리 (I)\n");
    gotoxy(104, 39);
    printscr("장비 (O)\n");
    gotoxy(104, 41);
    printscr("메뉴 (ESC)\n");
    textcolor(WHITE, BLACK);
    
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
        printscr("게임을 새로 시작하시겠습니까?");
        gotoxy(48, 24);
        printscr("기존 데이터는 삭제됩니다.");
    }
    else if (nowStatus == 1)
    {
        gotoxy(46, 22);
        printscr("게임의 난이도를 선택해주세요.");
        
    }
    draw_boxL(45, 26, 75, 28);
    printAskModalYN(nowIndx, nowStatus);
}

void printLevelUp() {
    textcolor(BLACK, WHITE);
    empty_box(42, 18, 78, 32);
    draw_boxB(42, 18, 78, 32);
    gotoxy(50, 20);
    printscr("레벨업을 축하합니다!");
    gotoxy(48, 23);
    printscr("HP: %3d->%3d  MP: %3d->%3d",  exPlayer.hp, player.hp, exPlayer.mp, player.mp);
    gotoxy(48, 24);
    printscr("ATK: %2d->%2d  DEF: %2d->%2d", exPlayer.atk, player.atk, exPlayer.def, player.def);
    gotoxy(49, 27);
    printscr("<ENTER>를 눌러 재개하기.");
    textcolor(BLACK, GRAY1);
    keyMode = LEVELUP;

}

void printGameClear() {
    textcolor(BLACK, WHITE);
    empty_box(42, 18, 78, 32);
    draw_boxB(42, 18, 78, 32);
    gotoxy(50, 20);
    printscr("게임을 클리어했습니다!");
    gotoxy(48, 23);
    printscr("TURN: %d  KillCount: %d", turn, killCount);
    gotoxy(48, 24);
    printscr("GOLD: %d LEVEL: %d", player.gold, player.level);
    gotoxy(49, 27);
    printscr("<ENTER>를 눌러 종료하기.");
    textcolor(BLACK, GRAY1);
    keyMode = GAMECLEAR;

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

char* mapMakeMenu[4] = { "   둘러보기   ", "   시드변경   ", "   맵  확정   ", "   뒤로가기   "};
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
    printscr("맵 생 성");
    draw_boxL(90, 5, 110, 7);
    gotoxy(92, 6);
    srand(time(NULL));
    int seed = rand() % 10000;
    printscr("시드: %d", seed);
    draw_boxL(8, 9, 112, 40);
    draw_boxL(8, 41, 112, 43);
    printMapMakeMenu(nowIndx);
    generateDungeon(seed);
    printMapStr(0);
    //112 - 8 = 104 / 4 = 26
    //맵 둘러보기 | 시드 변경 | 맵 확정 | 뒤로가기
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
//여기에서부터 게임 본편

void printPlayerMapSight() {
    int startX;
    int size;
    int color1, color2;
    float transparency; // 투명도 변수 추가
    for (int i = 0; i < 11; i++) {
        startX = playerViewSight.startX[i];
        size = playerViewSight.size[i];
        if (playerViewSight.mapSight[i][1] < 0 || playerViewSight.mapSight[i][1] >= MAP_SIZE) {
            for (int l = 0; l < size; l++)
                printMapBlock(startX + l, i, 0, BLACK, GRAY2); // 시야 밖의 블록은 완전 투명하게 설정
        } else {
            for (int j = 0; j < size; j++) {
                if (playerViewSight.mapSight[i][0] + j < 0) {
                    for (int l = 0; l < -playerViewSight.mapSight[i][0]; l++)
                        printMapBlock(startX + l, i, 0, BLACK, GRAY2); // 시야 밖의 블록은 완전 투명하게 설정
                    j -= playerViewSight.mapSight[i][0];
                } else if (playerViewSight.mapSight[i][0] + j > MAP_SIZE) {
                    for (int l = j; l < size; l++)
                        printMapBlock(startX + l, i, 0, BLACK, GRAY2); // 시야 밖의 블록은 완전 투명하게 설정
                    break;
                }
                // 거리에 따른 투명도 계산
                //중앙은 (i = 5,j = 0)에 있음
                //중앙과의 거리를 계산
                switch (map[playerViewSight.mapSight[i][0] + j][playerViewSight.mapSight[i][1]]) {
                    case EMPTY_SPACE:
                        color1 = BLACK;
                        color2 = GRAY2;
                        break;
                    case ROOM:
                        if(zLayer[playerViewSight.mapSight[i][0] + j][playerViewSight.mapSight[i][1]].isAttackArea == 1)
                        {
                            color1 = MAGENTA2;
                            color2 = MAGENTA2;
                        }
                        else
                        {
                            color2 = GRAY1;
                            color1 = GRAY1;
                        }
                        
                        
                        break;
                    default:
                        color1 = BLACK;
                        color2 = GRAY2;
                }
                printMapBlock(startX + j, i, 0, color1, color2); // 투명도를 적용하여 블록 출력
            }
        }
    }
}

objectType* bossArray[10];
int bossArraySize = 0;
objectType* eliteArray[20];
int eliteArraySize = 0;
objectType* monsterArray[100];
int monsterArraySize = 0;

void printPlayerzLayerSight() {
    bossArraySize = 0;
    eliteArraySize = 0;
    monsterArraySize = 0;
    int startX;
    int size;
    int color;
    int addX, addY;
    int mapSightX, mapSightY;
    mobDetailType* mobDetail;
    
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
            if(mapSightX + j < 0)
            {
                j -= mapSightX;
            }
            else if(mapSightX + j > MAP_SIZE)
            {
                break;
            }
            if(zLayer[mapSightX + j][mapSightY].type != -1)
            {
                switch (zLayer[mapSightX + j][mapSightY].type)
                {
                case objMONSTER:
                    if (zLayer[mapSightX + j][mapSightY].object == NULL)
                        continue;
                    zLayer[mapSightX + j][mapSightY].object->isMoved = 0;
                    monsterArray[monsterArraySize++] = zLayer[mapSightX + j][mapSightY].object;
                    mobDetail = &zLayer[mapSightX + j][mapSightY].object->mobDetail;
                    if(zLayer[mapSightX + j][mapSightY].isAttackArea == 1)
                        color = MAGENTA1;
                    else
                        color = RED2;
                    break;
                case objBOSS:
                    zLayer[mapSightX + j][mapSightY].object->isMoved = 0;
                    bossArray[bossArraySize++] = zLayer[mapSightX + j][mapSightY].object;
                    mobDetail = &zLayer[mapSightX + j][mapSightY].object->mobDetail;
                    if(zLayer[mapSightX + j][mapSightY].isAttackArea == 1)
                        color = MAGENTA1;
                    else
                        color = RED1;
                    break;
                case objELITE:
                    zLayer[mapSightX + j][mapSightY].object->isMoved = 0;
                    eliteArray[eliteArraySize++] = zLayer[mapSightX + j][mapSightY].object;
                    mobDetail = &zLayer[mapSightX + j][mapSightY].object->mobDetail;
                    if(zLayer[mapSightX + j][mapSightY].isAttackArea == 1)
                        color = MAGENTA1;
                    else
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
                    color = GRAY2;
                    break;
                }
                if(zLayer[mapSightX + j][mapSightY].type <= objELITE)
                {
                    printObjBlock(startX + j, i, &mobDetail->mobName, mobDetail->mobIndx, color, WHITE);
                }
                else
                {
                    printMapBlock(startX + j, i, 0, color, WHITE);
                }
            }
        }
    }
    printMapBlock(0, 5, 1, CYAN1, WHITE);
    printMobList();
}