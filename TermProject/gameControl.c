#include "mapMake.h"
// 시야 영어로: 
int playerSight = 5;
int needSightRender = 0;
sightType playerViewSight;

void initPlayerMapSight() {
    int x0 = player.x;
    int y0 = player.y;
    float radius = playerSight;
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

void isAvailableMove(int x, int y) {
    if (player.x + x < 0 || player.x + x >= MAP_SIZE || player.y + y < 0 || player.y + y >= MAP_SIZE) {
        return;
    }
    if (map[player.x + x][player.y + y] != ROOM) {
        return;
    }
    if (zLayer[player.x + x][player.y + y].type != -1) {
        return;
    }
    moveSight(x, y);
}
int isObjectMoveValid(int x, int y) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) {
        return 0;
    }
    if(x == player.x && y == player.y) {
        return 2;
    }
    if(map[x][y] != ROOM) {
        return 0;
    }
    if (zLayer[x][y].type != -1) {
        return 0;
    }
    return 1;
}

void mobAttack(objectType* mob) {
    int atk = randint(mob->atk/3, mob->atk);
    player.nowHp -= atk;
    mob->mobDetail.hp -= randint(player.atk/3, player.atk) - randint(0, mob->def);

}

void moveMob(int zLayerX, int zLayerY, objectType* monsterObj) {
    int isMove = randint(0, monsterObj->objectTypeEnum + 1);
    if (isMove == 0) {
        // 만약 플레이어로부터 거리가 4보다 작으면 플레이어 쪽으로 이동
        if (sqrt(((zLayerX-player.x) * (zLayerX-player.x)) + ((zLayerY-player.y) * (zLayerY-player.y))) < 3) {
            if (player.x - zLayerX > 0) {
                switch(isObjectMoveValid(zLayerX + 1, zLayerY))
                {
                    case 1:
                        zLayer[zLayerX + 1][zLayerY].type = monsterObj->objectTypeEnum;
                        zLayer[zLayerX + 1][zLayerY].object = monsterObj;
                        zLayer[zLayerX][zLayerY].type = -1;
                        zLayer[zLayerX][zLayerY].object = NULL;
                        return;
                    case 2:
                        mobAttack(monsterObj);
                        if (mobAliveCheck(zLayer[zLayerX][zLayerY].object) == 0)
                        {
                            zLayer[zLayerX][zLayerY].object = NULL;
                            zLayer[zLayerX][zLayerY].type = -1;
                            
                        }
                        return;
                    default:
                        break;
                }
            }
            if (player.x - zLayerX < 0) {
                switch (isObjectMoveValid(zLayerX - 1, zLayerY))
                {
                    case 1:
                        zLayer[zLayerX - 1][zLayerY].type = monsterObj->objectTypeEnum;
                        zLayer[zLayerX - 1][zLayerY].object = monsterObj;
                        zLayer[zLayerX][zLayerY].type = -1;
                        zLayer[zLayerX][zLayerY].object = NULL;
                        return;
                    case 2:
                        mobAttack(monsterObj);
                        if (mobAliveCheck(zLayer[zLayerX][zLayerY].object) == 0)
                        {
                            zLayer[zLayerX][zLayerY].object = NULL;
                            zLayer[zLayerX][zLayerY].type = -1;
                        }
                        return;
                    default:
                        break;
                }
            }
            if (player.y - zLayerY > 0) {
                switch (isObjectMoveValid(zLayerX, zLayerY + 1))
                {
                    case 1:
                        zLayer[zLayerX][zLayerY + 1].type = monsterObj->objectTypeEnum;
                        zLayer[zLayerX][zLayerY + 1].object = monsterObj;
                        zLayer[zLayerX][zLayerY].type = -1;
                        zLayer[zLayerX][zLayerY].object = NULL;
                        return;
                    case 2:
                        mobAttack(monsterObj);
                        if (mobAliveCheck(zLayer[zLayerX][zLayerY].object) == 0)
                        {
                            zLayer[zLayerX][zLayerY].object = NULL;
                            zLayer[zLayerX][zLayerY].type = -1;
                        }
                        return;
                    default:
                        break;
                }
            }
            if (player.y - zLayerY < 0) {
                switch (isObjectMoveValid(zLayerX, zLayerY - 1))
                {
                    case 1:
                        zLayer[zLayerX][zLayerY - 1].type = monsterObj->objectTypeEnum;
                        zLayer[zLayerX][zLayerY - 1].object = monsterObj;
                        zLayer[zLayerX][zLayerY].type = -1;
                        zLayer[zLayerX][zLayerY].object = NULL;
                        return;
                    case 2:
                        mobAttack(monsterObj);
                        if (mobAliveCheck(zLayer[zLayerX][zLayerY].object) == 0)
                        {
                            zLayer[zLayerX][zLayerY].object = NULL;
                            zLayer[zLayerX][zLayerY].type = -1;
                        }
                        return;
                    default:
                        break;
                }
            }
        }
        else {
            int moveXY = randint(0, 1);
            int moveX = 0, moveY = 0; 
            if(moveXY == 0)
                moveX = randint(-1, 1);
            else 
                moveY = randint(-1, 1);
            if (isObjectMoveValid(zLayerX + moveX, zLayerY + moveY) == 1) {
                zLayer[zLayerX + moveX][zLayerY + moveY].type = monsterObj->objectTypeEnum;
                zLayer[zLayerX + moveX][zLayerY + moveY].object = monsterObj;
                zLayer[zLayerX][zLayerY].type = -1;
                zLayer[zLayerX][zLayerY].object = NULL;
                return;
            }
        }

    }
}

int magicMobLen = 0;
int newMagicMobLen = 0;
objectType* magicedMob[15] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

void magicApply() {
    newMagicMobLen = 0;
    for(int i = 0; i < magicMobLen; i++)
    {
        if(magicedMob[i]==NULL || magicedMob[i]->mobDetail.magicLen <= 0 || magicedMob[i]->mobDetail.magic == None)
        {
            continue;
        }
        else
        {
            if(magicedMob[i]->mobDetail.magicLen == 0)
            {
                magicedMob[i]->mobDetail.magic = None;
            }
            else
            {
                switch (magicedMob[i]->mobDetail.magic)
                {
                case Ice:
                    magicedMob[i]->mobDetail.hp -= randint(1, 3);
                    break;
                default:
                    break;
                }
                magicedMob[newMagicMobLen++] = magicedMob[i];
            }
            magicedMob[i]->mobDetail.magicLen--;
        }
    }
    magicMobLen = newMagicMobLen;
}

void moveMobInSight() {
    turn++;
    needSightRender = 1;
    magicApply();
    for (int i = 0; i < 11; i++) {
        int x = playerViewSight.mapSight[i][0];
        int y = playerViewSight.mapSight[i][1];
        for(int j = 0; j < playerViewSight.size[i]; j++) {
            if(x+j < 0 || x + j >= MAP_SIZE || y< 0 || y>= MAP_SIZE) {
                continue;
            }
            if(zLayer[x + j][y].type <= objELITE && zLayer[x + j][y].type != -1) {
                if (mobAliveCheck(zLayer[x + j][y].object) == 0)
                {
                    zLayer[x + j][y].object = NULL;
                    zLayer[x + j][y].type = -1;
                    continue;
                }
                if(zLayer[x + j][y].object->isMoved == 0)
                {
                    zLayer[x + j][y].object->isMoved = 1;
                    moveMob(x + j, y, zLayer[x + j][y].object);
                }
            }
        }
    }
}

char* magicName[4] = {"얼음", "공포", "마비", "능력 없음"};
char* statusName[4] = {"빙결", "공포", "마비", "정상"};

skillType skill[3] = {
    {"빙결", {"###", "   ", " P "}, 10, {3, 5}, 'H', Ice},
    {"참격", {" # ", " # ", " P "}, 5, {4, 9}, 'J', Mabi},
    {"광격", {"###", "###", "#P#"}, 25, {0, 20}, 'K', Mabi}
};



skillType* nowSkill = NULL;
nowSkillIndx = -1;
enum Direction attackDirection = Up;
enum Direction exAttackDirection = Up;
int isMarked = 0;


int AttackCode(char ch) {
    for(int i = 0; i < 3; i++)
    {
        if(ch == tolower(skill[i].key))
        {
            nowSkill = &skill[i];
            nowSkillIndx = i;
            if(player.nowMp < nowSkill->mana)
            {
                printNowAction(0);
                return 0;
            }
            printNowAction(1);
            return 1;
        }
    }
    return 0;
}

void unmarkAttackArea() {
    needSightRender = 1;
    isMarked = 0;
    if(exAttackDirection == Up)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.y - 2 + i < 0 || player.x - 1 + j < 0 || player.x - 1 + j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x - 1 + j][player.y - 2 + i].isAttackArea = 0;
                }
            }
        }
    }
    else if(exAttackDirection == Down)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.y + 2 - i >= MAP_SIZE || player.x + 1 - j < 0 || player.x + 1 - j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x + 1 - j][player.y + 2 - i].isAttackArea = 0;
                }
            }
        }
    }
    else if(exAttackDirection == Left)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.x - 2 + i < 0 || player.y + 1 - j < 0 || player.y + 1 - j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x - 2 + i][player.y + 1 - j].isAttackArea = 0;
                }
            }
        }
    }
    else if(exAttackDirection == Right)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.x + 2 - i >= MAP_SIZE || player.y - 1 + j < 0 || player.y - 1 + j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x + 2 - i][player.y - 1 + j].isAttackArea = 0;
                }
            }
        }
    }
    exAttackDirection = attackDirection;
    
}



void markAttackArea()
{
    needSightRender = 1;
    if(isMarked == 1)
    {
        unmarkAttackArea();
    }
    isMarked = 1;
    if(attackDirection == Up)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(nowSkill->Hit[i][j] == '#')
                {
                    if(player.y - 2 + i < 0 || player.x - 1 + j < 0 || player.x - 1 + j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x - 1 + j][player.y - 2 + i].isAttackArea = 1;
                }
            }
        }
    }
    else if(attackDirection == Down)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(nowSkill->Hit[i][j] == '#')
                {
                    if(player.y + 2 - i >= MAP_SIZE || player.x + 1 - j < 0 || player.x + 1 - j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x + 1 - j][player.y + 2 - i].isAttackArea = 1;
                }
            }
        }
    }
    else if(attackDirection == Left)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(nowSkill->Hit[i][j] == '#')
                {
                    if(player.x - 2 + i < 0 || player.y + 1 - j < 0 || player.y + 1 - j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x - 2 + i][player.y + 1 - j].isAttackArea = 1;
                }
            }
        }
    }
    else if(attackDirection == Right)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(nowSkill->Hit[i][j] == '#')
                {
                    if(player.x + 2 - i >= MAP_SIZE || player.y - 1 + j < 0 || player.y - 1 + j >= MAP_SIZE)
                    {
                        continue;
                    }
                    zLayer[player.x + 2 - i][player.y - 1 + j].isAttackArea = 1;
                }
            }
        }
    }

}

void confirmAttack() {
    int atk = randint(nowSkill->damage[0], nowSkill->damage[1]);
    player.nowMp -= nowSkill->mana;
    if(exAttackDirection == Up)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.y - 2 + i < 0 || player.x - 1 + j < 0 || player.x - 1 + j >= MAP_SIZE)
                    {
                        continue;
                    }
                    if(zLayer[player.x - 1 + j][player.y - 2 + i].type <= objELITE && zLayer[player.x - 1 + j][player.y - 2 + i].type != -1 && zLayer[player.x - 1 + j][player.y - 2 + i].object != NULL)
                    {
                        zLayer[player.x - 1 + j][player.y - 2 + i].isAttackArea = 0;
                        AttackFunc(zLayer[player.x - 1 + j][player.y - 2 + i].object, atk);
                    }
                }
            }
        }
    }
    else if(exAttackDirection == Down)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.y + 2 - i >= MAP_SIZE || player.x + 1 - j < 0 || player.x + 1 - j >= MAP_SIZE)
                    {
                        continue;
                    }
                    if(zLayer[player.x + 1 - j][player.y + 2 - i].type <= objELITE && zLayer[player.x + 1 - j][player.y + 2 - i].type != -1)
                    {
                        if(zLayer[player.x + 1 - j][player.y + 2 - i].object != NULL)
                        {zLayer[player.x + 1 - j][player.y + 2 - i].isAttackArea = 0;
                        AttackFunc(zLayer[player.x + 1 - j][player.y + 2 - i].object, atk);}
                    }
                    
                }
            }
        }
    }
    else if(exAttackDirection == Left)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.x - 2 + i < 0 || player.y + 1 - j < 0 || player.y + 1 - j >= MAP_SIZE)
                    {
                        continue;
                    }
                    if(zLayer[player.x - 2 + i][player.y + 1 - j].type <= objELITE && zLayer[player.x - 2 + i][player.y + 1 - j].type != -1 && zLayer[player.x - 2 + i][player.y + 1 - j].object != NULL)
                    {
                        zLayer[player.x - 2 + i][player.y + 1 - j].isAttackArea = 0;
                        AttackFunc(zLayer[player.x - 2 + i][player.y + 1 - j].object, atk);
                    }
                }
            }
        }
    }
    else if(exAttackDirection == Right)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                {
                    if(player.x + 2 - i >= MAP_SIZE || player.y - 1 + j < 0 || player.y - 1 + j >= MAP_SIZE)
                    {
                        continue;
                    }
                    if(zLayer[player.x + 2 - i][player.y - 1 + j].type <= objELITE && zLayer[player.x + 2 - i][player.y - 1 + j].type != -1 && zLayer[player.x + 2 - i][player.y - 1 + j].object != NULL)
                    {
                        zLayer[player.x + 2 - i][player.y - 1 + j].isAttackArea = 0;
                        AttackFunc(zLayer[player.x + 2 - i][player.y - 1 + j].object, atk);
                    }
                }
            }
        }
    }
}


void AttackFunc(objectType* atkMob, int atk) {
    int def = atkMob->def;
    if(def < atk)
        atkMob->mobDetail.hp -= atk - randint(0, def);
    int magicOK = randint(0, 10);
    if(magicOK < 3)
    {
        int magicLen = randint(0, 3);
        atkMob->mobDetail.magic = nowSkill->magic;
        atkMob->mobDetail.magicLen = magicLen;
        magicedMob[(magicMobLen++)%15] = atkMob;
    }
}


int mobAliveCheck(objectType* mob) {
    if(mob == NULL)
    {
        return 0;
    }
    if(mob->mobDetail.hp <= 0)
        {
            if(mob->objectTypeEnum == objBOSS)
            {
                printGameClear();
                return 0;
            }
            player.gold += mob->gold;
            player.exp += mob->exp;
            free(mob);
            killCount++;
            return 0;
        }
    return 1;
}

playerType exPlayer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {NULL, NULL, NULL}};

int playerLevelUp() {
    if(player.exp >= player.level * 30)
    {
        exPlayer = player;
        player.exp -= player.level * 30;
        player.level++;
        player.atk += randint(1, 3);
        player.def += randint(1, 3);
        player.hp += randint(10, 20);
        player.mp += randint(10, 20);
        player.nowMp = player.mp;
        player.nowHp = player.hp;
        printLevelUp();
        return 1;
    }
    return 0;
}

void playerHeal() {
    if(player.nowMp < player.mp)
    {
        player.nowMp += randint(5, 10);
        if(player.nowMp > player.mp)
        {
            player.nowMp = player.mp;
        }
    }
}

