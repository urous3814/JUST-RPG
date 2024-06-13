#include <stdio.h>
#include "mapMake.h"

enum gameStatus { MAIN_MENU, ASK_NEW, SETTING, MAKE_MAP, MAKE_MAP_EXPLORE, MAKE_MAP_SEED, GAME_SETTING ,GAME_START, GAME_OVER, GAME_CLEAR };
typedef struct game {
    int gameStatus;
    int nowMenuIndx;
} gameType;

enum keyModeEnum keyMode = MOVE;
int turn = 0;
int killCount = 0;

gameType game = { MAIN_MENU, 0 };
gameType pGame = { MAIN_MENU, 0 };
gameType exGame = { MAIN_MENU, 0 };
int needSwitch = 0;
int customSeed = 0;

playerType player = { 100, 100, 50, 50, 10, 5, 0, 0, 1, 0, 0, {NULL, NULL, NULL} };

int main() {
    setup();
    scr_init();
    
    unsigned char ch;
    removeCursor(); 
    printStartPage(game.nowMenuIndx);
    scr_switch();


	while (1) {
        if (needBackCopy) {
            scr_copy();
            needBackCopy = 0;
        }
        if(pGame.gameStatus != game.gameStatus)
        {
            exGame = pGame;
            switch (game.gameStatus) {
            case MAIN_MENU:
                scr_clear();
                printStartPage(game.nowMenuIndx);
                break;
            case ASK_NEW:
                printAskModal(game.nowMenuIndx, 0);
                break;
            case SETTING:
                scr_clear();
                printSettingPage(game.nowMenuIndx);
                break;
            case MAKE_MAP:
                scr_clear();
                printMakeMapPage(game.nowMenuIndx);
                break;
            case MAKE_MAP_EXPLORE:
                printMapStr(game.nowMenuIndx);
                break;
            case GAME_SETTING:
                scr_clear();
                printAskModal(game.nowMenuIndx, 1);
                break;
            case GAME_START:
                scr_clear();
                setGame();
                printGamePage();
                printPlayerMapSight();
                printPlayerzLayerSight();
                break;
            case GAME_OVER:
                break;
            case GAME_CLEAR:
                break;
            default:
                break;
            }
            pGame = game;
            
        }
        // else if(pGame.nowMenuIndx != game.nowMenuIndx)
        // {
        //     switch (game.gameStatus) {
        //     case MAIN_MENU:
        //         break;
        //     case ASK_NEW:
        //         break;
        //     case SETTING:
                
        //         break;
        //     case GAME_START:
        //         break;
        //     case GAME_OVER:
        //         break;
        //     case GAME_CLEAR:
        //         break;
        //     default:
        //         break;
        //     }
        //     pGame = game;
        // }
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			//
			// ESC 누르면 프로그램 종료 추가
            if(game.gameStatus != GAME_START)
            {
                if (ch == ESC) {
                    break;
                }
                else if(ch == ENTER)
                {
                    if(game.gameStatus == MAIN_MENU)
                    {
                        switch (game.nowMenuIndx) {
                        case 0:
                            game.gameStatus = ASK_NEW;
                            break;
                        case 1:
                            game.gameStatus = GAME_START;
                            break;
                        case 2:
                            game.gameStatus = SETTING;
                            break;
                        default:
                            break;
                        }
                    }
                    else if(game.gameStatus == ASK_NEW)
                    {
                        switch (game.nowMenuIndx) {
                        case 0:
                            game.nowMenuIndx = 0;
                            game.gameStatus = MAKE_MAP;
                            break;
                        case 1:
                            eraseAskModal();
                            game.gameStatus = MAIN_MENU;
                            pGame.gameStatus = MAIN_MENU;
                            game.nowMenuIndx = 0;
                            break;
                        default:
                            break;
                        }
                    }
                    else if(game.gameStatus == MAKE_MAP)
                    {
                        switch (game.nowMenuIndx) {
                        case 0:
                            game.gameStatus = MAKE_MAP_EXPLORE;
                            game.nowMenuIndx = 0;
                            pGame = game;
                            break;
                        case 1:
                            gotoxy(98, 6);
                            printscr("    ");
                            gotoxy(98, 6);
                            showCursor();
                            scr_switch();
                            needSwitch = 0;
                            char seedChar[5];
                            int i = 0;
                            while(1)
                            {
                                scr_copy();
                                gotoxy(98+i, 6);
                                seedChar[i] = getch();
                                customSeed = customSeed * 10 + (seedChar[i] - '0');
                                if(seedChar[i] == BACKSPACE && i > 0)
                                {
                                    
                                    gotoxy(98+i-1, 6);
                                    printscr(" ");
                                    seedChar[i] = '0';
                                    customSeed = customSeed / 10;
                                    i -= 2;
                                    gotoxy(98 + i+1, 6);
                                }
                                else if(seedChar[i] == ENTER && i > 0)
                                {
                                    break;
                                }
                                else if(i<4){
                                    printscr("%c", seedChar[i]);
                                }
                                showCursor();
                                scr_switch();
                                if (i < 4) {
                                    i++;
                                }
                            }
                            removeAllCursor();
                            generateDungeon(customSeed);
                            printMapStr(0);
                            break;
                        case 2: //게임 세부설정.
                            game.nowMenuIndx = 0;
                            game.gameStatus = GAME_SETTING;
                            break;
                        case 3:
                            game.gameStatus = MAIN_MENU;
                            game.nowMenuIndx = 0;
                            break;
                        default:
                            break;
                        }
                    }
                    else if (game.gameStatus == MAKE_MAP_EXPLORE)
                    {
                        game.gameStatus = MAKE_MAP;
                        game.nowMenuIndx = 0;
                        pGame = game;
                    }
                    else if(game.gameStatus == GAME_SETTING)
                    {
                        difficulty = game.nowMenuIndx;
                        mapComplete();
                        game.gameStatus = GAME_START;
                    }
                }
                else if(ch == BACKSPACE)
                {
                    if(game.gameStatus == ASK_NEW)
                    {
                        eraseAskModal();
                        game.gameStatus = MAIN_MENU;
                        pGame.gameStatus = MAIN_MENU;
                        game.nowMenuIndx = 0;
                    }
                    else if(game.gameStatus == MAKE_MAP)
                    {
                        game.gameStatus = MAIN_MENU;
                        game.nowMenuIndx = 0;
                    }
                    else if(game.gameStatus == SETTING)
                    {
                        game.gameStatus = MAIN_MENU;
                        game.nowMenuIndx = 0;
                    }
                    else if (game.gameStatus == MAKE_MAP_EXPLORE)
                    {
                        game.gameStatus = MAKE_MAP;
                        game.nowMenuIndx = 0;
                        pGame = game;
                    }
                    
                } else if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                    // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                    ch = getch();
                    if(game.gameStatus == MAIN_MENU)
                    {
                        switch (ch) {
                        case UP:
                            if(game.nowMenuIndx > 0)
                                game.nowMenuIndx--;
                            break;
                        case DOWN:
                            if(game.nowMenuIndx < 2)
                                game.nowMenuIndx++;
                            break;
                        default:
                            break;
                        }
                        printFirstMenu(game.nowMenuIndx);
                    }
                    else if(game.gameStatus == ASK_NEW)
                    {
                        switch (ch) {
                        case LEFT:
                            if(game.nowMenuIndx > 0)
                                game.nowMenuIndx--;
                            break;
                        case RIGHT:
                            if(game.nowMenuIndx < 1)
                                game.nowMenuIndx++;
                            break;
                        default:
                            break;
                        }
                        printAskModalYN(game.nowMenuIndx, 0);
                    }
                    else if(game.gameStatus == MAKE_MAP_EXPLORE)
                    {
                        switch (ch) {
                        case UP:
                            if(game.nowMenuIndx > 0)
                            {
                                game.nowMenuIndx -= 5;
                                printMapStr(game.nowMenuIndx);
                            }
                            break;
                        case DOWN:
                            if(game.nowMenuIndx < 70)
                            {
                                game.nowMenuIndx += 5;
                                printMapStr(game.nowMenuIndx);
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    else if(game.gameStatus == MAKE_MAP)
                        switch (ch) {
                        case LEFT:
                            if(game.nowMenuIndx > 0)
                            {
                                game.nowMenuIndx -= 1;
                                printMapMakeMenu(game.nowMenuIndx);
                            }
                            break;
                        case RIGHT:
                            if(game.nowMenuIndx < 3)
                            {
                                game.nowMenuIndx += 1;
                                printMapMakeMenu(game.nowMenuIndx);
                            }
                            break;
                        default: // 방향키가 아니면 멈춘다
                            break;
                        }
                    else if(game.gameStatus == GAME_SETTING)
                    {
                        switch (ch) {
                        case LEFT:
                            if(game.nowMenuIndx > 0)
                                game.nowMenuIndx--;
                            break;
                        case RIGHT:
                            if(game.nowMenuIndx < 2)
                                game.nowMenuIndx++;
                            break;
                        default:
                            break;
                        }
                        printAskModalYN(game.nowMenuIndx, 1);
                    }
                    else if(game.gameStatus == GAME_START)
                    {
                        switch (ch) {
                        case UP:
                            isAvailableMove(0, -1);
                            break;
                        case DOWN:
                            isAvailableMove(0, 1);
                            break;
                        case LEFT:
                            isAvailableMove(-1, 0);
                            break;
                        case RIGHT:
                            isAvailableMove(1, 0);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            else 
            {
                if (ch == SPECIAL1 || ch == SPECIAL2) {
                    ch = getch();
                    if(keyMode == MOVE)
                    {
                        switch (ch) {
                        case UP:
                            isAvailableMove(0, -1);
                            break;
                        case DOWN:
                            isAvailableMove(0, 1);
                            needSightRender = 0;
                            printGameClear();
                            break;
                        case LEFT:
                            isAvailableMove(-1, 0);
                            break;
                        case RIGHT:
                            isAvailableMove(1, 0);
                            break;
                        default:
                            break;
                        }
                        playerHeal();
                        moveMobInSight();
                    }
                    else if(keyMode == ATTACK)
                    {
                        switch (ch) {
                        case UP:
                            attackDirection = Up;
                            break;
                        case DOWN:
                            attackDirection = Down;
                            break;
                        case LEFT:
                            attackDirection = Left;
                            break;
                        case RIGHT:
                            attackDirection = Right;
                            break;
                        default:
                            break;
                        }
                        markAttackArea();

                    }
                    
                }
                if(keyMode == MOVE)
                {
                    if(AttackCode(ch) == 1)
                    {
                        markAttackArea();
                        keyMode = ATTACK;
                    }
                    else if(AttackCode(ch) == 0)
                    {
                        keyMode = MOVE;
                    
                    }
                }
                else if(keyMode == ATTACK)
                {
                    if(ch == BACKSPACE)
                    {
                        keyMode = MOVE;
                        unmarkAttackArea();
                        textcolor(WHITE, BLACK);
                        empty_box(1, 25, 23, 35);
                        textcolor(BLACK, GRAY1);
                    }
                    else if(ch == SPACE){
                        confirmAttack();
                        keyMode = MOVE;
                        unmarkAttackArea();
                        textcolor(WHITE, BLACK);
                        empty_box(1, 25, 23, 35);
                        textcolor(BLACK, GRAY1);
                        moveMobInSight();
                    }
                }
                else if(keyMode == LEVELUP)
                {
                    if(ch == ENTER)
                    {
                        textcolor(BLACK, BLACK);
                        empty_box(42, 18, 78, 32);
                        textcolor(BLACK, GRAY1);
                        keyMode = MOVE;
                    }
                }
                else if(keyMode == GAMECLEAR)
                {
                    if(ch == ENTER)
                    {
                        return 0;
                    }
                
                }
            }
            if(needSightRender)
            {
                printPlayerMapSight();
                printPlayerzLayerSight();
                printPlayerStatus();
                playerLevelUp();
                needSightRender = 0;
            }
        }
        if(needSwitch)
        {
            scr_switch();
            needSwitch = 0;
        }
		Sleep(DELAY); // Delay를 줄이면 속도가 빨라진다.
	}
    return 0;
}