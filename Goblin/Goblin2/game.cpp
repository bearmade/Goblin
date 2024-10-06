// Goblin.cpp : Defines the entry point for the application.
//
#include <iostream>
#include "Goblin.h"

using namespace std;

void printDisplay();
void displayTitle();
string generateName();
void processTerrain();
void processShop();
void processSkillShop();
void processMerchant();
void processInventory();
void processBattle(string TYPE, string enemyType);
void generatePlayer(string object, string TILE);
void processInput();
void processMovement(int dx, int dy);
void generateWorldMap();
void generateDungeon();
int getRandom(int low, int high);
void printBoard();
void initBoard();
void cellularAutomataMaze(int iterations);
void cellularAutomata(int iterations);
void cellularAuto(int iterations);
int countNeighbors(int row, int column, string TYPE);
void randGen();
void cellularAutomataMiniMaze(int iterations);
void villageSpawn(int iterations);
void cellularAutomataBorder(int iterations);
void randomWalk(int iterations, string TYPE);
void runRuleTile(string TYPE, string vertTYPE, string horTYPE);
void destroyIslands(string TYPE);
void crossRiver(int iterations, string TYPE, string changeTYPE, string clearTYPE);
void changeTiles(string TYPE, string changeTYPE);


//gloabal colors
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";
const string BLACK = "\033[30m";
const string bgWHITE = "\033[47m";
const string bgRED = "\033[41m";
const string bgGREEN = "\033[42m";
const string bgYELLOW = "\033[43m";
const string bgBLUE = "\033[44m";
const string MAGENTA = "\033[35m";
const string bgMAGENTA = "\033[45m";
const string CYAN = "\033[36m";
const string bgCYAN = "\033[46m";
const string BLINK = "\033[5m";
const string REVERSED = "\033[7m";
//string GROUND = bgWHITE + BLUE + "/\\" +RESET;
//string gGROUND = bgGREEN + BLACK + ", " + RESET;
//string WATER = bgBLUE+ "  " +RESET;
//string GROUNDrand = bgWHITE + BLUE + "^ " + RESET;
//string gGROUNDrand = bgGREEN+ YELLOW+"~."+RESET;
//string WATERrand = bgBLUE + "~ " + RESET;


string GROUND = "/\\" + RESET;
string EXIT = "()" + RESET;
string BLOCKER = "##" + RESET;
string gGROUND = YELLOW + "^ " + RESET;
string WATER = YELLOW + "  " + RESET;
string GROUNDrand = GREEN + ". " + RESET;
string gGROUNDrand = MAGENTA + ", " + RESET;
string WATERrand = "  " + RESET;
string CASTLE = RED + "[]" + RESET;
string CASTLEwall = YELLOW + "==" + RESET;
string CASTLEwallUP = YELLOW + "||" + RESET;
string VILLA = "  ";
string SHORE = GREEN + ";:" + RESET;
string WALKER = BLUE + "~ " + RESET;
string crossWATER = bgCYAN + "~ " + RESET;

string tempTileA = "  ";
string tempTileB = "  ";
string tempTileC = "  ";
string currentTerrain = "  ";
string terrainMessage = " ";
string terrainMessageTemp = " ";

//global vars
int SIZE = 35;
int gridWidth = SIZE;
int gridHeight = SIZE;
int row = 0;
int column = 0;

vector<vector<string>> board(gridWidth, vector<string>(gridHeight, ""));
vector<vector<string>> boardTemp(gridWidth, vector<string>(gridHeight, ""));

//Player variables
string PLAYER = BLINK + "db" + RESET;
int playerX = 0;
int playerY = 0;
int playerPOS[2] = { playerX,playerY };

int tempPlayerX = 0;
int tempPlayerY = 0;
int tempPlayerPOS[2] = { tempPlayerX,tempPlayerY };

int pHealth = 30;
int pAttack = 1;
int pDefense = 5;
int pExp = 0;
int pLevel = 0;
int money = 0;
int steps = 0;
int goblinsKilled = 0;
//inventory variables
string itemNames[3] = { "skulls","bones","meat" };
int itemAmount[3] = { 0, 0, 0 };
int itemBasePrice[3] = { 4, 2, 1 };

//string GOBLINname = " ";
string playerAttackMessage[5] = { "You attack ","You swing at ","You strike in the general area of ","You throw a rock at ","You trip into " };


int main()
{
    char input;
    bool gameOver = false;
    displayTitle();
    system("pause");
    generateWorldMap();


    while (gameOver == false)
    {


        printBoard();
        printDisplay();
        processInput();
        processTerrain();
        if (pHealth < 1)
        {
            cout << "you have died\n";
            gameOver = true;


        }



    }




    return 0;
}

void displayTitle()
{

    cout << RED + "          " + "   ______      __    ___          \n";
    cout << RED + "          " + "  / ____/___  / /_  / (_)___      \n";
    cout << RED + "          " + " / / __/ __ \\/ __ \\/ / / __ \\     \n";
    cout << RED + "          " + "/ /_/ / /_/ / /_/ / / / / / /     \n";
    cout << RED + "          " + "\\____/\\____/_.___/_/_/_/ /_/      \n";
    cout << RESET;


}


void printDisplay()
{

    for (int x = 0; x < SIZE * 2; x++)
        cout << bgRED + BLACK + "=" + RESET;

    cout << endl;
    cout << "HP: " << pHealth << "   Level: " << pLevel << " Gold: " << money << "   Strength: " << pAttack << "  Steps: " << steps << " Goblins killed: " << goblinsKilled;
    cout << "\n" << terrainMessageTemp << "\n";
    cout << terrainMessage << "\n";
    terrainMessageTemp = terrainMessage;
    terrainMessage = " ";

}
string generateName()
{
    //string eTypeName[5] = { "","","","","" };

    string fname1[5] = { "Sn","Sk","Kr","Gr","B" };
    string fname2[5] = { "um","ar","ay","ee","oo" };
    string fname3[5] = { "po","py","bs","ble","gle" };
    string lname1[5] = { "Rub","Bum","Tum","Hum","Grum" };
    string lname2[5] = { "thum","bo","rum","tum","bum" };
    string lname3[5] = { "o","bles","gles","po","py" };
    string fNAME = fname1[getRandom(1, 5) - 1] + fname2[getRandom(1, 5) - 1] + fname3[getRandom(1, 5) - 1];
    string lNAME = lname1[getRandom(1, 5) - 1] + lname2[getRandom(1, 5) - 1] + lname3[getRandom(1, 5) - 1];
    string goblinNAME = (fNAME + " " + lNAME);

    return goblinNAME;


}

void processTerrain()
{
    //string name = generateName();

    if (currentTerrain == gGROUNDrand && getRandom(1, 100) > 75)
        processBattle(gGROUNDrand, generateName());
    if (currentTerrain == gGROUND && getRandom(1, 100) > 95)
        money = money + getRandom(0, 1) + pLevel;
    if (currentTerrain == CASTLE && getRandom(1, 100) > 95)
        processSkillShop();
    if (currentTerrain == CASTLE && getRandom(1, 100) > 75)
        processShop();
    if (currentTerrain == VILLA && getRandom(1, 100) > 75)
        processMerchant();
    if (currentTerrain == GROUND && getRandom(1, 100) > 75)
    {
        board[playerPOS[0]][playerPOS[1]] = BLOCKER;
        board[playerPOS[0]][playerPOS[1]] = boardTemp[playerPOS[0]][playerPOS[1]];
        boardTemp = board;
        tempPlayerX = playerPOS[0];
        tempPlayerY = playerPOS[1];
        pLevel = pLevel + 1;
        generateDungeon();
    }

    if (currentTerrain == EXIT)
    {
        board = boardTemp;
        playerX = tempPlayerX;
        playerY = tempPlayerY;

        printBoard();

    }


    //terrainMessages
    if (currentTerrain == gGROUNDrand)
        terrainMessage = RED + "this area is infested with goblins" + RESET;
    if (currentTerrain == VILLA)
        terrainMessage = GREEN + "there are merchants in the area" + RESET;
    if (currentTerrain == GROUND)
        terrainMessage = RED + "the ground is unstable" + RESET;
    if (currentTerrain == CASTLE)
        terrainMessage = GREEN + "this area is has services" + RESET;
    if (currentTerrain == gGROUND)
        terrainMessage = YELLOW + "gold is in the area" + RESET;

}
void processShop()
{
    bool shopOpen = true;
    char input = ' ';
    system("cls");
    printDisplay();
    cout << "\n\nWelcome to the Inn\n";
    while (shopOpen == true)
    {
        int randHP = getRandom(10, 25) * (pLevel + 1);
        int randGold = getRandom(10, 25) * (pLevel + 1);
        cout << "Purchase " << randHP << " HP for " << randGold << " gold ? (A) for YES/ (D) for NO ";
        input = _getch();
        input = toupper(input);
        if (input == 'A' && money >= randGold)
        {
            money = money - randGold;
            pHealth = pHealth + randHP;
            shopOpen = false;
            break;
        }
        else
        {
            shopOpen = false;
        }




    }

}

void processSkillShop()
{
    bool shopOpen = true;
    char input = ' ';
    system("cls");
    printDisplay();
    cout << "\n\nA Mentor approaches\n";
    while (shopOpen == true)
    {
        int randHP = getRandom(10, 25);
        int randGold = (getRandom(10, 25) * (pLevel + 1));
        cout << "Purchase strencth upgrade for " << randGold << " gold ? (A) for YES/ (D) for NO ";
        input = _getch();
        input = toupper(input);
        if (input == 'A' && money >= randGold)
        {
            money = money - randGold;
            pAttack = pAttack + 1;
            shopOpen = false;
            break;
        }
        else
        {
            shopOpen = false;
        }




    }

}

void processMerchant()
{
    bool shopOpen = true;
    char input = ' ';
    system("cls");
    printDisplay();
    cout << "\n\nA merchant approaches\n";
    while (shopOpen == true)
    {
        int randAmount = getRandom(10, 25);
        int randItem = getRandom(1, 3);
        int randGold = getRandom(10, 25);
        int itemPriceLow = (itemBasePrice[randItem - 1] * randAmount) / 2;
        int itemPriceHigh = (itemBasePrice[randItem - 1] * randAmount) * 2;
        int itemPrice = getRandom(itemPriceLow, itemPriceHigh);
        cout << "(A)Purchase / (S)Sell / (D)Exit \n\n";
        input = _getch();
        input = toupper(input);
        switch (input)
        {
        case 'A':

            cout << "Purchase " << randAmount << " " << itemNames[randItem - 1] << " for " << itemPrice << " gold ? (A) for YES / (D) for NO \n\n";
            input = _getch();
            input = toupper(input);
            if (input == 'A' && money > itemPrice)
            {
                money = money - itemPrice;
                itemAmount[randItem - 1] = itemAmount[randItem - 1] + randAmount;
                shopOpen = false;
                break;
            }
            else
            {
                shopOpen = false;
            }

            break;
        case 'S':
            if (itemAmount[randItem - 1] > 0)
            {
                cout << "Sell " << itemAmount[randItem - 1] << " " << itemNames[randItem - 1] << " for " << itemPrice << " gold ? (A) for YES / (D) for NO \n\n";
                input = _getch();
                input = toupper(input);
                if (input == 'A')
                {
                    money = money + itemPrice;
                    itemAmount[randItem - 1] = itemAmount[randItem - 1] - itemAmount[randItem - 1];
                    shopOpen = false;
                    break;
                }
                else
                {
                    shopOpen = false;
                }

            }
            else
            {
                cout << "They aren't buying.\n";
            }


            break;
        case 'D':
            shopOpen = false;
            break;
        }







    }

}

void processInventory()
{

    system("cls");
    printDisplay();
    cout << "\n\n";
    int size = *(&itemNames + 1) - itemNames;
    for (int i = 0; i < size; i++)
    {
        cout << itemNames[i] << "     " << itemAmount[i] << "\n";

    }
    system("pause");
}

void processBattle(string TYPE, string enemyType)
{
    char input = ' ';
    bool battleOver = false;
    int eHealth = (getRandom(10, 20) * (pLevel + 1));

    system("cls");


    while (battleOver == false)
    {
        string randPlayerAttackMessage = playerAttackMessage[getRandom(1, 5) - 1];
        system("cls");
        printDisplay();
        int attack = (pAttack + getRandom(1, 5)) * (pLevel + 1);
        int eAttackLow = (getRandom(1, 3) * (pLevel + 1));
        int eAttackHigh = (getRandom(3, 7) * (pLevel + 1));
        int eAttack = getRandom(eAttackLow, eAttackHigh);
        cout << " Goblin Encounter \n\n" + enemyType + " HP: " << eHealth << "\n\n";
        cout << "(A)attack, (D)run away\n";
        input = _getch();
        input = toupper(input);
        if (input == 'A')
        {
            cout << randPlayerAttackMessage + enemyType + " for " << attack << " damage.\n";
            eHealth = eHealth - attack;
            if (eHealth < 1)
            {
                int gold = (getRandom(1, 10) * (pLevel + 1));
                int dropChance = getRandom(1, 10);
                int dropItem = getRandom(1, 3);
                int dropAmount = getRandom(1, 3) * (pLevel + 1);
                cout << "you killed the pitiful " + enemyType + ".\n";
                cout << "you found " << gold << " gold.\n";
                money = money + gold;
                goblinsKilled = goblinsKilled + 1;
                if (dropChance > 7)
                {
                    cout << "you found " << dropAmount << " " << itemNames[dropItem - 1] << ".\n";
                    itemAmount[dropItem - 1] = dropAmount;
                }



                battleOver = true;
                break;
            }
        }
        if (input == 'D')
        {
            int gold = (getRandom(1, 5) * (pLevel + 1));
            if (money < (money - gold))
            {
                cout << "you run away.\n";
                battleOver = true;
                break;
            }
            cout << "you run away and drop " << gold << " gold.\n";
            money = money - gold;
            if (money < 1)
                money = 0;
            battleOver = true;
            break;
        }


        system("pause");
        system("cls");
        printDisplay();
        cout << enemyType + " attacks you for " << eAttack << " damage.\n";
        pHealth = pHealth - eAttack;
        if (pHealth < 1)
        {
            cout << "you have fallen to the mighty " + enemyType + ".\n";
            battleOver = true;
            break;

        }
        system("pause");

    }



    system("pause");
}

void generatePlayer(string object, string TILE)
{
    bool playerPlaced = false;
    int randomChance = getRandom(1, 10000);
    while (playerPlaced == false) {
        for (int i = 3; i < gridWidth - 3; i++) {
            for (int j = 3; j < gridHeight - 3; j++) {
                if (board[i][j] == TILE && (getRandom(1, 10000) > 9990) && playerPlaced == false)
                {
                    board[i][j] = object;
                    if (object == PLAYER)
                    {
                        playerPOS[0] = i;
                        playerPOS[1] = j;
                    }

                    playerPlaced = true;
                }




            }
        }
    }


}

void processInput()
{
    char input = _getch();
    input = toupper(input);

    switch (input)
    {
    case 'W':
        if ((playerPOS[0] != 0) && (board[playerPOS[0] - 1][playerPOS[1]] != BLOCKER))
        {
            tempTileA = board[playerPOS[0] - 1][playerPOS[1]];
            tempTileC = tempTileB;
            board[playerPOS[0] - 1][playerPOS[1]] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;

            playerPOS[0] = playerPOS[0] - 1;
            steps++;
        }

        break;
    case 'A':
        if (playerPOS[1] != 0 && board[playerPOS[0]][playerPOS[1] - 1] != BLOCKER)
        {
            tempTileA = board[playerPOS[0]][playerPOS[1] - 1];
            tempTileC = tempTileB;
            board[playerPOS[0]][playerPOS[1] - 1] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;
            playerPOS[1] = playerPOS[1] - 1;
            steps++;
        }

        break;
    case 'S':
        if (playerPOS[0] != SIZE - 1 && board[playerPOS[0] + 1][playerPOS[1]] != BLOCKER)
        {
            tempTileA = board[playerPOS[0] + 1][playerPOS[1]];
            tempTileC = tempTileB;
            board[playerPOS[0] + 1][playerPOS[1]] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;
            playerPOS[0] = playerPOS[0] + 1;
            steps++;
        }

        break;
    case 'D':
        if (playerPOS[1] != SIZE - 1 && board[playerPOS[0]][playerPOS[1] + 1] != BLOCKER)
        {
            tempTileA = board[playerPOS[0]][playerPOS[1] + 1];
            tempTileC = tempTileB;
            board[playerPOS[0]][playerPOS[1] + 1] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;
            playerPOS[1] = playerPOS[1] + 1;
            steps++;
        }

        break;
    case 'I':
        processInventory();

        break;

    }
    currentTerrain = tempTileA;
}
void processMovement(int dx, int dy)
{
    tempTileA = board[playerPOS[0] + dx][playerPOS[1] + dy];
    tempTileC = tempTileB;
    board[playerPOS[0] + dx][playerPOS[1] + dy] = PLAYER;
    board[playerPOS[0]][playerPOS[1]] = tempTileC;
    tempTileB = tempTileA;
    playerPOS[1] = playerPOS[1] + 1;
}

void generateWorldMap()
{
    initBoard();
    cellularAutomataMaze(4);
    cellularAutomata(2);
    cellularAuto(1);
    randGen();
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    cellularAutomataMiniMaze(7);
    cellularAutomataMiniMaze(5);
    cellularAutomataMiniMaze(3);
    cellularAutomataMiniMaze(2);
    cellularAutomataMiniMaze(2);
    runRuleTile(CASTLE, CASTLEwallUP, CASTLEwall);
    cellularAutomataBorder(5);
    destroyIslands(WALKER);
    crossRiver(4, WALKER, crossWATER, WATERrand);
    generatePlayer(PLAYER, WATERrand);
    //randomWalk(30, WALKER);
    printBoard();
}

void generateDungeon()
{


    system("cls");
    initBoard();
    cellularAutomataMaze(4);

    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    changeTiles(GROUND, BLOCKER);
    //changeTiles(WALKER, WATER);
    generatePlayer(PLAYER, WALKER);
    tempTileB = WALKER;
    generatePlayer(EXIT, WATER);
    changeTiles(WALKER, gGROUNDrand);
    printBoard();

}

int getRandom(int low, int high)
{
    // Set up a random device to seed the random number generator
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> distribution(low, high);
    int randomInteger = distribution(engine);

    return randomInteger;
}

void printBoard()
{
    system("cls");
    // print game board
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            //cout << board[i][j];
            printf("%s", board[i][j].c_str());
        }
        //cout << endl;
        printf("%s\n");
    }
    //this_thread::sleep_for(chrono::milliseconds(10));
}

void initBoard()
{
    int randChance = 0;
    //initialize grid
    for (int x = 0;x < gridWidth;x++) {
        for (int y = 0;y < gridHeight;y++) {
            randChance = getRandom(1, 10);
            if (randChance > 5)
                board[x][y] = GROUND;
            else
                board[x][y] = WATER;
        }
    }
}

void cellularAutomataMaze(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 2)
                    board[i][j] = WATER;
                if (board[i][j] == WATER && neighbors < 2)
                    board[i][j] = GROUND;
            }
        }
    }
}

void cellularAutomata(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 3)
                    board[i][j] = WATER;
            }
        }
    }
}

void cellularAuto(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 1)
                    board[i][j] = gGROUND;
                if (board[i][j] == GROUND && neighbors < 3)
                    board[i][j] = gGROUND;
                if (board[i][j] == gGROUND && neighbors > 1)
                    board[i][j] = gGROUND;
            }
        }
    }
}

int countNeighbors(int row, int column, string TYPE)
{
    int dx = 0;
    int dy = 0;
    int neighborCount = 0;

    if ((row != 0) && (column != 0) && (row != gridWidth - 1) && (column != gridHeight - 1)) {
        int xPlus = (row + 1);
        int xMinus = (row - 1);
        int yPlus = (column + 1);
        int yMinus = (column - 1);

        if (board[xPlus][column] == TYPE)
            neighborCount++;
        if (board[row][yPlus] == TYPE)
            neighborCount++;
        if (board[xPlus][yPlus] == TYPE)
            neighborCount++;
        if (board[xMinus][column] == TYPE)
            neighborCount++;
        if (board[row][yMinus] == TYPE)
            neighborCount++;
        if (board[xMinus][yMinus] == TYPE)
            neighborCount++;
        if (board[xPlus][yMinus] == TYPE)
            neighborCount++;
        if (board[xMinus][yPlus] == TYPE)
            neighborCount++;

    }
    return neighborCount;
}

void randGen()
{
    int randChance = 0;
    //initialize grid
    for (int x = 0;x < gridWidth;x++) {
        for (int y = 0;y < gridHeight;y++) {
            //randChance = getRandom(1, 10);
            if ((getRandom(1, 10) > 6) && (board[x][y] == gGROUND))
                board[x][y] = gGROUNDrand;
            if ((getRandom(1, 10) > 4) && (board[x][y] == GROUND))
                board[x][y] = GROUNDrand;
            if ((getRandom(1, 10) > 6) && (board[x][y] == WATER))
                board[x][y] = WATERrand;
        }
    }
}

void cellularAutomataMiniMaze(int iterations)
{
    int randStartX = getRandom(2, gridWidth - 8);
    int randStartY = getRandom(2, gridHeight - 8);
    int randWidth = getRandom(3, 8);
    int randHeight = getRandom(2, SIZE / 10);
    int randEndX = randStartX + randWidth;
    int randEndY = randStartY + randHeight;
    int neighbors = 0;

    int randChance = 0;
    //initialize grid
    for (int x = randStartX;x < randEndX;x++) {
        for (int y = randStartY;y < randEndY;y++) {
            randChance = getRandom(1, 10);
            if ((randChance > 5) && (row != 0) && (column != 0) && (row != gridWidth - 1) && (column != gridHeight - 1))

                board[x][y] = GROUND;
            else
                board[x][y] = WATER;
        }
    }

    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 2)
                    board[i][j] = WATER;
                if (board[i][j] == WATER && neighbors < 2)
                    board[i][j] = GROUND;
            }
        }
    }

    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                if (board[i][j] == GROUND)
                    board[i][j] = CASTLE;
                if (board[i][j] == WATER)
                    board[i][j] = VILLA;
            }
        }
    }
}

void villageSpawn(int iterations)
{
    int randStartX = getRandom(2, gridWidth);
    int randStartY = getRandom(2, gridHeight);
    int randEndX = getRandom(randStartX, gridWidth);
    int randEndY = getRandom(randStartY, gridHeight);
    int neighbors = 0;
    int randChance = 0;
    //initialize grid
    for (int x = randStartX;x < randEndX;x++) {
        for (int y = randStartY;y < randEndY;y++) {
            randChance = getRandom(1, 10);
            if (randChance > 5)
                board[x][y] = GROUND;
            else
                board[x][y] = WATER;
        }
    }




    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 2)
                    board[i][j] = WATER;
                if (board[i][j] == WATER && neighbors < 2)
                    board[i][j] = GROUND;
            }
        }
    }

    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                if (board[i][j] == GROUND)
                    board[i][j] = CASTLE;
                if (board[i][j] == WATER)
                    board[i][j] = VILLA;
            }
        }
    }
}

void cellularAutomataBorder(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, gGROUND);
                if (board[i][j] == WATER && neighbors > 1)
                    board[i][j] = SHORE;
                neighbors = countNeighbors(i, j, gGROUNDrand);
                if (board[i][j] == WATER && neighbors > 1)
                    board[i][j] = SHORE;
                neighbors = countNeighbors(i, j, gGROUND);
                if (board[i][j] == WATERrand && neighbors > 1)
                    board[i][j] = SHORE;
                neighbors = countNeighbors(i, j, gGROUNDrand);
                if (board[i][j] == WATERrand && neighbors > 1)
                    board[i][j] = SHORE;
            }
        }
    }
}

void randomWalk(int iterations, string TYPE)
{
    int midPoint = SIZE / 2;
    int quarterPoint = midPoint / 2;
    int randStartX = getRandom(quarterPoint, midPoint);
    int randStartY = getRandom(quarterPoint, midPoint);
    int randEndX = getRandom(randStartX, midPoint + quarterPoint);
    int randEndY = getRandom(randStartY, midPoint + quarterPoint);
    int neighbors = 0;
    int randDir = getRandom(1, 4);

    for (int x = 0; x < iterations; x++) {
        board[randStartX][randStartY] = TYPE;

        for (int y = 0; y < iterations; y++) {
            int randDir = getRandom(1, 4);
            if (randDir == 1 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX + 1][randStartY] = TYPE;
                randStartX = randStartX + 1;
            }
            if (randDir == 2 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX - 1][randStartY] = TYPE;
                randStartX = randStartX - 1;
            }
            if (randDir == 3 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX][randStartY + 1] = TYPE;
                randStartY = randStartY + 1;
            }
            if (randDir == 4 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX][randStartY - 1] = TYPE;
                randStartY = randStartY - 1;
            }
        }
    }
}

void runRuleTile(string TYPE, string vertTYPE, string horTYPE)
{
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            if ((i != 0) && (j != 0) && (i != gridWidth - 1) && (j != gridHeight - 1))
            {
                if ((board[i][j] == TYPE) && (board[i + 1][j] == TYPE) && (board[i - 1][j] == TYPE))
                    board[i][j] = vertTYPE;
                if ((board[i][j] == TYPE) && (board[i][j + 1] == TYPE) && (board[i][j - 1] == TYPE))
                    board[i][j] = horTYPE;
            }

        }
    }
}

void destroyIslands(string TYPE)
{

    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            if (board[i][j] != TYPE && countNeighbors(i, j, TYPE) > 6)
                board[i][j] = TYPE;

        }
    }
}

void crossRiver(int iterations, string TYPE, string changeTYPE, string clearTYPE)
{
    for (int x = 0; x < iterations; x++) {
        for (int i = 0; i < gridWidth; i++) {
            for (int j = 0; j < gridHeight; j++) {
                if (board[i][j] == TYPE && countNeighbors(i, j, TYPE) < 4)
                    board[i][j] = changeTYPE;
                if (board[i][j] == changeTYPE && countNeighbors(i, j, changeTYPE) > 2)
                    board[i][j] = changeTYPE;
                if (board[i][j] == changeTYPE)
                    board[i][j] = clearTYPE;

            }
        }
    }

}

void changeTiles(string TYPE, string changeTYPE)
{
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            if (board[i][j] == TYPE)
                board[i][j] = changeTYPE;


        }
    }
}
