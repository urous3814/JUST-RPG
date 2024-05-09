#include <stdio.h>
#include "mapMake.h"

enum gameStatus { MAIN_MENU, ASK_NEW, SETTING, MAKE_MAP, GAME_START, GAME_OVER, GAME_CLEAR };
typedef struct game {
    int gameStatus;
    int nowMenuIndx;
} gameType;

gameType game = { MAIN_MENU, 0 };
gameType pGame = { MAIN_MENU, 0 };

int main() {

    setup();
    unsigned char ch;
    removeCursor();
    if(game.gameStatus == MAIN_MENU)
    {   
        printStartPage(game.nowMenuIndx);
    }
    //generateDungeon();


	while (1) {
        if(pGame.gameStatus != game.gameStatus)
        {
            switch (game.gameStatus) {
            case MAIN_MENU:
                printStartPage(game.nowMenuIndx);
                break;
            case ASK_NEW:
                printAskModal(game.nowMenuIndx);
                break;
            case SETTING:
                printSettingPage(game.nowMenuIndx);
                break;
            case MAKE_MAP:
                printMakeMapPage();
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
            }
			//
			if (ch == SPECIAL1 || ch == SPECIAL2) { // ���� Ư��Ű
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
                    printAskModalYN(game.nowMenuIndx);
                }
                else if(game.gameStatus == MAKE_MAP)
                {
                    switch (ch) {
                    case UP:
                        if(game.nowMenuIndx > 0)
                            game.nowMenuIndx-=5;
                        break;
                    case DOWN:
                        if(game.nowMenuIndx < 70)
                            game.nowMenuIndx+=5;
                        break;
                    default:
                        break;
                    }
                    printMapStr(game.nowMenuIndx);
                }
				switch (ch) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					break;
				default: // ����Ű�� �ƴϸ� �����
					break;
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
