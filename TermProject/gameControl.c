#include "mapMake.h"
// 시야 영어로: 
int playerSight = 5;
int needSightRender = 0;
sightType playerViewSight;

void initPlayerMapSight() {
    int x0 = player.x;
    int y0 = player.y;
    float radius = playerSight+0.5;
    int index = 0;
    int mapX;
    int mapY;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                mapX = x0 + x;
                mapY = y0 + y;
                playerViewSight.mapSight[index][0] = mapX;
                playerViewSight.mapSight[index][1] = mapY;
                playerViewSight.size[index] = -x*2+1;
                playerViewSight.startX[index++] = x;
                break;
            }
        }
    }
}

void initPlayer(int x, int y) {
    player.hp = 100;
    player.atk = 10;
    player.def = 10;
    player.gold = 0;
    player.exp = 0;
    player.level = 1;
    player.x = x;
    player.y = y;
    for (int i = 0; i < 3; i++) {
        player.item[i] = NULL;
    }

}

void setGame() {
    initPlayerMapSight();
}

void moveSight(int x, int y) {
    needSightRender = 1;
    if(x!=0)
    {
        player.x += x;
        for(int i = 0; i < 11; i++) {
            playerViewSight.mapSight[i][0] += x;
        }
    }
    else if(y!=0)
    {
        player.y += y;
        for(int i = 0; i < 11; i++) {
            playerViewSight.mapSight[i][1] += y;   
        }
    }
    
}