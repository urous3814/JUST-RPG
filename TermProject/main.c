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
		if (kbhit() == 1) {  // Ű���尡 ������ ������
			ch = getch(); // key ���� �д´�
            gotoxy(10, 10);
            printf("%h", ch);
			//
			// ESC ������ ���α׷� ���� �߰�
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
                    case 2: //���� ���μ���.
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
                
            } else if (ch == SPECIAL1 || ch == SPECIAL2) { // ���� Ư��Ű
				// ���� ��� UP key�� ��� 0xe0 0x48 �ΰ��� ���ڰ� ���´�.
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
                    default: // ����Ű�� �ƴϸ� �����
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
				// Ư�� ���ڰ� �ƴ����� AWSD�� ����Ű ��� ����ϴ� ��� ó��
			}
		}
		
		Sleep(DELAY); // Delay�� ���̸� �ӵ��� ��������.
	}
    return 0;
}
