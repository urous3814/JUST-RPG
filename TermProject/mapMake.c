#include "mapMake.h"


int roomCount = 0;

void initializeDungeon() {
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            map[i][j] = EMPTY_SPACE;
        }
        map[i][MAP_SIZE] = '\0';
    }
    roomCount = 0;
}

void divideSpace(SpaceTree* node, int n) {
    if (n == MAX_NODE)
        return;
    node->left = (SpaceTree*)malloc(sizeof(SpaceTree));
    node->right = (SpaceTree*)malloc(sizeof(SpaceTree));
    if (node->space.width > node->space.height) {
        int divide = rand() % (int)(node->space.width * 0.4) + node->space.width * 0.4;

        node->left->space.x = node->space.x;
        node->right->space.x = node->space.x + divide;
        node->left->space.y = node->space.y;
        node->right->space.y = node->space.y;
        node->left->space.width = divide;
        node->right->space.width = node->space.width - divide;
        node->left->space.height = node->space.height;
        node->right->space.height = node->space.height;

    }
    else {
        int divide = rand() % (int)(node->space.height * 0.4) + node->space.height * 0.4;
        node->left->space.x = node->space.x;
        node->left->space.y = node->space.y;
        node->right->space.x = node->space.x;
        node->right->space.y = node->space.y + divide;
        node->left->space.height = divide;
        node->right->space.height = node->space.height - divide;
        node->left->space.width = node->space.width;
        node->right->space.width = node->space.width;
    }

    divideSpace(node->left, n + 1);
    divideSpace(node->right, n + 1);
}

const int roomPercent[6] = { 10, 50, 0, 5, 10, 20 };

void drawRoom(roomType room) {
    for (int i = room.x; i < room.x + room.width; i++) {
        for (int j = room.y; j < room.y + room.height; j++) {
            map[i][j] = ROOM;
        }
    }
}



objectType* makeMonsterObject(enum monEnum monType)
{   
    objectType* monster = (objectType*)malloc(sizeof(objectType));
    switch (monType)
    {
    case NormalM:
        monster->objectTypeEnum = objMONSTER;
        monster->level = randint(1, 3);
        monster->hp = randint(10, 15) * monster->level;
        monster->atk = randint(1, 2) * monster->level;
        monster->def = randint(1, 2) * monster->level;
        monster->gold = randint(1, 3) * monster->level;
        monster->exp = randint(1, 3) * monster->level;
        monster->item = NULL;
        break;
    case EliteM:
        monster->objectTypeEnum = objELITE;
        monster->level = randint(3, 5);
        monster->hp = randint(15, 20) * monster->level;
        monster->atk = randint(1, 2) * monster->level;
        monster->def = randint(1, 2) * monster->level;
        monster->gold = randint(1, 3) * monster->level;
        monster->exp = randint(1, 3) * monster->level;
        monster->item = NULL;
        break;
    case BossM:
        monster->objectTypeEnum = objBOSS;
        monster->level = randint(10, 15);
        monster->hp = randint(15, 20) * monster->level;
        monster->atk = randint(3, 5) * monster->level;
        monster->def = randint(3, 5) * monster->level;
        monster->gold = randint(3, 5) * monster->level;
        monster->exp = randint(10, 20) * monster->level;
        monster->item = NULL;
        break;

    default:
        break;
    }
    return monster;
}

void addMonsterObject(roomType room) {
    //난이도 가져오기
    int mobCount = randint(4, 4 + 3 * difficulty);
    for (int i = 0; i < mobCount; i++) {
        int x = randint(room.x, room.x + room.width);
        int y = randint(room.y, room.y + room.height);
        zLayer[x][y].type = objMONSTER;
        zLayer[x][y].object = makeMonsterObject(0);
    }
}

objectType* makeTreasureObject()
{
    objectType* treasure = (objectType*)malloc(sizeof(objectType));
    treasure->objectTypeEnum = objTREASURE;
    treasure->level = randint(1, 3);
    treasure->hp = 0;
    treasure->atk = 0;
    treasure->def = 0;
    treasure->gold = randint(5, 10) * treasure->level;
    treasure->exp = randint(5, 10) * treasure->level;
    treasure->item = NULL;
    return treasure;
}

objectType* makeMimicObject()
{
    objectType* treasure = (objectType*)malloc(sizeof(objectType));
    treasure->objectTypeEnum = objTREASURE;
    treasure->level = randint(1, 3);
    treasure->hp = 0;
    treasure->atk = randint(3, 6) * treasure->level;
    treasure->def = 0;
    treasure->gold = 0;
    treasure->exp = 0;
    treasure->item = NULL;
    return treasure;
}


//방에 있는 요소들을 추가한다
void addRoomObject(roomType room) {
    //몹 추가하기
    addMonsterObject(room);

    //유형별 특별 오브젝트 추가하기
    switch (room.type)
    {
    case PlayerSpawn:
        //initPlayer(room.x + room.width / 2, room.y + room.height / 2);
        initPlayer(1, 1);
        break;
    case Treasure:
        zLayer[room.x + room.width / 2][room.y + room.height / 2].type = objTREASURE;
        zLayer[room.x + room.width / 2][room.y + room.height / 2].object = makeTreasureObject();
        break;
    case Mimic:
        zLayer[room.x + room.width / 2][room.y + room.height / 2].type = objTREASURE;
        zLayer[room.x + room.width / 2][room.y + room.height / 2].object = makeTreasureObject();
        break;
    case Boss:
        zLayer[room.x + room.width / 2][room.y + room.height / 2].type = objBOSS;
        zLayer[room.x + room.width / 2][room.y + room.height / 2].object = makeMonsterObject(2);
        break;
    case Elite:
        zLayer[room.x + room.width / 2][room.y + room.height / 2].type = objELITE;
        zLayer[room.x + room.width / 2][room.y + room.height / 2].object = makeMonsterObject(1);
        break;
    default:
        break;
    }
}

void mapComplete()
{
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            zLayer[i][j].type = -1;
        }
    }
    //1단계 플레이어 배치
    int spawnIndex = randint(0, MAX_ROOM - 1);
    rooms[spawnIndex].type = PlayerSpawn;
    //2단계 오브젝트 배치
    for (int i = 0; i < MAX_ROOM; i++)
    {
        addRoomObject(rooms[i]);
    }
}


void createRoom(SpaceTree* node, int n) {
    if (n == MAX_NODE) {
        int width = randint(node->space.width / 3 * 2, node->space.width - 2);
        int height = randint(node->space.height / 3 * 2, node->space.height - 2);
        int x = randint(node->space.x + 1, node->space.x + node->space.width - width - 1);
        int y = randint(node->space.y + 1, node->space.y + node->space.height - height - 1);
        rooms[roomCount].x = x;
        rooms[roomCount].y = y;
        rooms[roomCount].width = width;
        rooms[roomCount].height = height;
        rooms[roomCount].type = randint(Store, Elite);
        rooms[roomCount].roomIndx = roomCount;
        node->room = &rooms[roomCount];
        drawRoom(rooms[roomCount]);
        roomCount++;
    }
    else {
        createRoom(node->left, n + 1);
        createRoom(node->right, n + 1);
    }
}

void drawMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printscr("%c", map[i][j]);
        }
        printscr("\n");
    }
}

void generateRoad(SpaceTree* node, int n)
{
    if (n == MAX_NODE) return;
    int x1 = node->left->space.x + node->left->space.width / 2;
    int y1 = node->left->space.y + node->left->space.height / 2;
    int x2 = node->right->space.x + node->right->space.width / 2;
    int y2 = node->right->space.y + node->right->space.height / 2;
    for (int x = MIN(x1, x2); x <= MAX(x1, x2); x++)
    {
        if(map[x][y1] == EMPTY_SPACE)
            map[x][y1] = PASSAGEWAY;
    }
    for (int y = MIN(y1, y2); y <= MAX(y1, y2); y++)
    {  
        if (map[x2][y] == EMPTY_SPACE)
            map[x2][y] = PASSAGEWAY;
    }
    generateRoad(node->left, n + 1);
    generateRoad(node->right, n + 1);
}

void generateDungeon(int seed) {
    SpaceTree* root = (SpaceTree*)malloc(sizeof(SpaceTree));
    spaceType* space = (spaceType*)malloc(sizeof(spaceType));
    space->x = 0;
    space->y = 0;
    space->width = MAP_SIZE;
    space->height = MAP_SIZE;
    root->space = *space;
    srand(seed);
    initializeDungeon();
    divideSpace(root, 0);
    createRoom(root, 0);
    generateRoad(root, 0);
}