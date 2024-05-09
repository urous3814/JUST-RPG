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
    switch (room.type)
    {
    case Store:
        map[room.x + room.width / 2][room.y + room.height / 2] = STORE;
        break;
    case Treasure:
        map[room.x + room.width / 2][room.y + room.height / 2] = TREASURE;
        break;
    case Mimic:
        map[room.x + room.width / 2][room.y + room.height / 2] = MIMIC;
        break;
    case Boss:
        map[room.x + room.width / 2][room.y + room.height / 2] = BOSS;
        break;
    case Elite:
        map[room.x + room.width / 2][room.y + room.height / 2] = ELITE;
        break;
    default:
        break;
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
            printf("%c", map[i][j]);
        }
        printf("\n");
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