#include <stdio.h>
#include "mapMake.h"

enum gameStatus { MAIN_MENU, ASK_NEW, SETTING, MAKE_MAP, MAKE_MAP_EXPLORE, MAKE_MAP_SEED, GAME_SETTING ,GAME_START, GAME_OVER, GAME_CLEAR };
typedef struct game {
    int gameStatus;
    int nowMenuIndx;
} gameType;

gameType game = { MAIN_MENU, 0 };
gameType pGame = { MAIN_MENU, 0 };
gameType exGame = { MAIN_MENU, 0 };
int customSeed = 0;

int main() {
    
    setup();
    
    unsigned char ch;
    removeCursor();
    printStartPage(game.nowMenuIndx);
    Sleep(1000);


	while (1) {
        if(pGame.gameStatus != game.gameStatus)
        {
            exGame = pGame;
            switch (game.gameStatus) {
            case MAIN_MENU:
                printStartPage(game.nowMenuIndx);
                break;
            case ASK_NEW:
                printAskModal(game.nowMenuIndx, 0);
                break;
            case SETTING:
                printSettingPage(game.nowMenuIndx);
                break;
            case MAKE_MAP:
                printMakeMapPage(game.nowMenuIndx);
                break;
            case MAKE_MAP_EXPLORE:
                printMapStr(game.nowMenuIndx);
                break;
            case GAME_SETTING:
                printAskModal(game.nowMenuIndx, 1);
                break;
            case GAME_START:
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
        else if(pGame.nowMenuIndx != game.nowMenuIndx)
        {
            switch (game.gameStatus) {
            case MAIN_MENU:
                break;
            case ASK_NEW:
                break;
            case SETTING:
                
                break;
            case GAME_START:
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
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
            gotoxy(10, 10);
            printf("%h", ch);
			//
			// ESC 누르면 프로그램 종료 추가
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
                        printf("    ");
                        gotoxy(98, 6);
                        showCursor();
                        scanf("%d", &customSeed); 
                        removeCursor();
                        generateDungeon(customSeed);
                        printMapStr(0);
                        break;
                    case 2: //게임 세부설정.
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
			}
			else {
				// 특수 문자가 아니지만 AWSD를 방향키 대신 사용하는 경우 처리
			}
		}
		
		Sleep(DELAY); // Delay를 줄이면 속도가 빨라진다.
	}
    return 0;
}
