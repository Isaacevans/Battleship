// Artificial Intelligence
// Battleship Game
// Authors: Isaac Evans, Stephen Maher

using namespace std;
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// check if spot has been previously shot
bool shotCheck(int computerBoard[10][10], int enemyBoard[10][10], int shot){
    int tempX = (shot-1)/10;
    int tempY = (shot-1)%10;
    if (computerBoard[tempX][tempY] == 110){
        enemyBoard[tempX][tempY] = 130;
        computerBoard[tempX][tempY] = 130;
        return true;
    }
    else{
        enemyBoard[tempX][tempY] = 120;
        computerBoard[tempX][tempY] = 120;
        return false;
    }
}

void hitSearch(int playerBoard[10][10], int shot2, int &newShot, int &function){
    int tempX = (shot2-1)/10;
    int tempY = (shot2-1)%10;

    if (playerBoard[tempX][tempY+1] < 115 && (function == 1 || function == 0) && tempY != 9){
        newShot = shot2+1;
        function = 1;
        return;
    }
    if (playerBoard[tempX][tempY-1] < 115 && (function == 2 || function == 0) && tempY != 0){
        newShot = shot2-1;
        function = 2;
        return;
    }
    if (playerBoard[tempX+1][tempY] < 115 && (function == 3 || function == 0) && tempX != 9){
        newShot = shot2 + 10;
        function = 3;
        return;
    }
    if (playerBoard[tempX-1][tempY] < 115 && (function == 4 || function == 0) && tempX != 0){
        newShot = shot2 - 10;
        function = 4;
        return;
    }
}

bool enemyShotCheck(int shot2, int playerBoard[10][10], int &computerHitCount){
    int tempX = (shot2-1)/10;
    int tempY = (shot2-1)%10;
    int newShot = 0;
    int function = 0;
    if (playerBoard[tempX][tempY] == 110){
        playerBoard[tempX][tempY] = 130;
        computerHitCount++;
        return true;
    }
    else if (playerBoard[tempX][tempY] == 120 || playerBoard[tempX][tempY] == 130){
        hitSearch( playerBoard, shot2 , newShot, function);
        enemyShotCheck(shot2+1, playerBoard, computerHitCount);
        return false;
    }
    else{
        playerBoard[tempX][tempY] = 120;
        return false;
    }
}

bool gameOver(int playerWin, int playerLoss, int computerHitCount){
    if (playerWin > 3){
        cout << "YOU WON! OH MY!" << endl;
        return true;
    }
    else if (playerLoss > 3 || computerHitCount > 13){
        cout << "\nOH NO! YOU LOST!" << endl;
        return true;
    }

    return false;
}

void playerShipArray(const int temp1, const int temp2, int &one, int &two, int &three, int &four, int &five){
    one = temp1;
    two = temp2;

    if (temp1%10 == temp2%10){
        if (temp1 > temp2){
            three = temp1 - 10;
            four = temp1 - 20;
            five = temp1 - 30;   
        }
        else{
            three = temp1 + 10;
            four = temp1 + 20;
            five = temp1 + 30;
        }
    }
    else{
        if (temp1 > temp2){
            three = temp1 - 1;
            four = temp1 - 2;
            five = temp1 - 3;
        }
        else{
            three = temp1 + 1;
            four = temp1 + 2;
            five = temp1 +3;
        }
    }
}

void shipPlacement(int playerBoard[10][10], int temp1, int temp2){

    int temp1X = (temp1-1)/10;
    int temp1Y = (temp1-1)%10;
    int temp2X = (temp2-1)/10;
    int temp2Y = (temp2-1)%10;
    int r = 1;

    playerBoard[temp1X][temp1Y] = 110;
    playerBoard[temp2X][temp2Y] = 110;
    if(temp1Y == temp2Y){
        if(temp1 > temp2){
           while(playerBoard[temp1X-r][temp1Y] != playerBoard[temp2X][temp2Y]){
                playerBoard[temp1X-r][temp1Y] = 110;
                ++r;
            }
        }
        else{ 
            while(playerBoard[temp1X+r][temp1Y] != playerBoard[temp2X][temp2Y]){
                playerBoard[temp1X+r][temp1Y] = 110;
                ++r;
            }
        }
    }
    else{
        if(temp1 > temp2){
            while(playerBoard[temp1X][temp1Y-r] != playerBoard[temp2X][temp2Y]){
                playerBoard[temp1X][temp1Y-r] = 110;
                ++r;
            }
        }
        else{
            while(playerBoard[temp1X][temp1Y+r] != playerBoard[temp2X][temp2Y]){
                playerBoard[temp1X][temp1Y+r] = 110;
                ++r;
            }
        }
    }
}

void printBoard(int board[10][10]){
    for (int x = 0; x < 10; ++x){
        cout << endl;
        for (int y = 0; y < 10; ++y){
            if (board[x][y] == 110)
                cout << "+\t";
            else if (board[x][y] == 120)
                cout << "@\t";
            else if (board[x][y] == 130)
                cout << "X\t";
            else
                cout << board[x][y] << "\t";

        }
    }
    cout << "\n\n";
}

void computerShipPlacement(int computerBoard[10][10], int aircraftCarrierComputer[5], 
    int battleshipComputer[4], int destroyerComputer[3], int patrolBoatComputer[2]){
    // Patrol Boat
    srand(time(NULL));
    int random = rand() %100 + 1;
    while (random%10 == 0)
        random = rand() %100 + 1;

    shipPlacement(computerBoard, random, random+1);
    patrolBoatComputer[0] = random;
    patrolBoatComputer[1] = random+1;

    // Destroyer
    random = rand() %100 + 1;
    while (random > 80)
        random = rand() %100 + 1;
    
    shipPlacement(computerBoard, random+20, random);
    destroyerComputer[0] = random +20;
    destroyerComputer[1] = random;
    destroyerComputer[2] = random + 10;

    // Battleship
    random = rand() %100 + 1;
    while (random%10 == 0 || random%10 > 7)
        random = rand() %100 + 1;
    
    shipPlacement(computerBoard, random, random+3);
    battleshipComputer[0] = random;
    battleshipComputer[1] = random +3;
    battleshipComputer[2] = random +2;
    battleshipComputer[3] = random +1;

    // Aircraft Carrier
    random = rand() %100 + 1;
    while (random > 60)
        random = rand() %100 + 1;

    shipPlacement(computerBoard, random+40, random);
    aircraftCarrierComputer[0] = random +40;
    aircraftCarrierComputer[1] = random;
    aircraftCarrierComputer[2] = random + 30;
    aircraftCarrierComputer[3] = random + 20;
    aircraftCarrierComputer[4] = random + 10;
}

int shipSunk(int shot, int aircraftCarrier[5],int battleship[4], int destroyer[3], int patrolBoat[2]){

    for(int i=0; i<5; i++){
        if(shot==aircraftCarrier[i]){
            aircraftCarrier[i] = 0;
        }
        if(i < 4 && shot==battleship[i]){
            battleship[i] = 0;
        }
        if(i < 3 && shot==destroyer[i]){
            destroyer[i] = 0;
        }
        if(i < 2 && shot== patrolBoat[i]){
            patrolBoat[i] = 0;
        }
    }

    int carrierCheck = 5;
    int battleshipCheck = 4;
    int destroyerCheck = 3;
    int patrolCheck = 2;

    int carrierCount=0;
    int battleshipCount=0;
    int patrolCount=0;
    int destroyerCount=0;

    for(int i=0; i<5; i++){
        if(aircraftCarrier[i] == 0){
            carrierCount++;
        }
        if(i < 4 && battleship[i] == 0){
            battleshipCount++;
        }
        if(i < 3 && destroyer[i] == 0){
            destroyerCount++;
        }
        if(i < 2 && patrolBoat[i] == 0){
            patrolCount++;
        }
    }
    if(carrierCheck == carrierCount){
        aircraftCarrier[0] = 150;
        return 4;
    }
    if(battleshipCheck == battleshipCount){
        battleship[0] = 150;
        return 3;
    }
    if(destroyerCheck == destroyerCount){
        destroyer[0] = 150;
        return 2;
    } 
    if(patrolCount == patrolCheck){
        patrolBoat[0] = 150;
        return 1;
    }

    return 0;
}


int main(){

    /**********************************************************************/
    // Initial Values setting
    int aircraftCarrierPlayer[5];
    int battleshipPlayer[4];
    int destroyerPlayer[3];
    int patrolBoatPlayer[2];

    int aircraftCarrierComputer[5];
    int battleshipComputer[4];
    int destroyerComputer[3];
    int patrolBoatComputer[2];

    int playerBoard[10][10];
    int computerBoard[10][10];
    int enemyBoard[10][10];

    int shot;
    int shot2;
    int playerWin = 0;
    int playerLoss = 0;
    int computerHitCount = 0;

    int one, two, three, four, five;
    bool enemyHit = false;
    int newShot;
    int function = 0;

    srand(time(NULL));

    int i = 1;
    while (i < 101){
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < 10; ++y){
                playerBoard[x][y]= i;
                computerBoard[x][y]= i;
                enemyBoard[x][y]= i;
                ++i;
            }
        }
    }

    int temp1, temp2;

    int temp1X;
    int temp1Y;

    int temp2X;
    int temp2Y;
    /**********************************************************************/

    /**********************************************************************/
    // Initial Game State
    computerShipPlacement(computerBoard, aircraftCarrierComputer, battleshipComputer, 
        destroyerComputer, patrolBoatComputer);

    cout << "\nWelcome to Battleship!!! Don't lose." << endl;
    cout << "To begin, you will need to place all four battleships.";
    cout << "\n" << "Here is your sea space to place your fleet: " << endl;
    printBoard(playerBoard);
    cout << endl;
    cout << "Starting with your Patrol Boat (2 spaces), enter the beginning number for the placement: " << endl;
    cin >> temp1;
    cout << "Now enter the ending number for the placement of your Patrol Boat (2 spaces): " << endl;
    cin >> temp2;
    playerShipArray(temp1, temp2, one, two, three, four, five);
    patrolBoatPlayer[0] = one;
    patrolBoatPlayer[1] = two;
    shipPlacement(playerBoard, temp1, temp2);
    cout << "Now this is what your fleet looks like:" << endl;
    printBoard(playerBoard);

    cout << "Starting with your Destroyer (3 spaces), enter the beginning number for the placement: " << endl;
    cin >> temp1;
    cout << "Now enter the ending number for the placement of your Destroyer (3 spaces): " << endl;
    cin >> temp2;
    playerShipArray(temp1, temp2, one, two, three, four, five);
    destroyerPlayer[0] = one;
    destroyerPlayer[1] = two;
    destroyerPlayer[2] = three;
    shipPlacement(playerBoard, temp1, temp2);

    cout << "Now this is what your fleet looks like:" << endl;
    printBoard(playerBoard);

    cout << "Starting with your Battleship (4 spaces), enter the beginning number for the placement: " << endl;
    cin >> temp1;
    cout << "Now enter the ending number for the placement of your Battleship (4 spaces): " << endl;
    cin >> temp2;
    playerShipArray(temp1, temp2, one, two, three, four, five);
    battleshipPlayer[0] = one;
    battleshipPlayer[1] = two;
    battleshipPlayer[2] = three;
    battleshipPlayer[3] = four;

    shipPlacement(playerBoard, temp1, temp2);

    cout << "Now this is what your fleet looks like:" << endl;
    printBoard(playerBoard);

    cout << "Starting with your Aircraft Carrier (5 spaces), enter the beginning number for the placement: " << endl;
    cin >> temp1;
    cout << "Now enter the ending number for the placement of your Aircraft Carrier (5 spaces): " << endl;
    cin >> temp2;
    playerShipArray(temp1, temp2, one, two, three, four, five);
    aircraftCarrierPlayer[0] = one;
    aircraftCarrierPlayer[1] = two;
    aircraftCarrierPlayer[2] = three;
    aircraftCarrierPlayer[3] = four;
    aircraftCarrierPlayer[4] = five;
    shipPlacement(playerBoard, temp1, temp2);

    cout << "\n" << "Your view of the Enemy Fleet:";
    printBoard(enemyBoard);

    cout << "\n" << "Your Fleet:";
    printBoard(playerBoard);
    /**********************************************************************/

    /**********************************************************************/
    // Start The Game

    cout << "You have now set up all your ships. The game will now begin. It's your turn first!\n" << endl;

    int deadShip = 0;

    while (!gameOver(playerWin, playerLoss, computerHitCount)){
        // Player Turn
        cout << "Enter a number to take a shot!" << endl;
        cin >> shot;
        cout << "----------------" << endl;
        if (shotCheck(computerBoard, enemyBoard, shot)){
            cout << "YOU HIT!" << endl;
            deadShip = shipSunk(shot, aircraftCarrierComputer, battleshipComputer, destroyerComputer, patrolBoatComputer);
            if(deadShip == 4){
                cout << "You sunk their Aircraft Carrier! YAY!" << endl;
                ++playerWin;
            }
            else if (deadShip == 3){
                cout << "You sunk their Battleship! Good job!" << endl;
                ++playerWin;
            }
            else if (deadShip == 2){
                cout << "You sunk their Destroyer! Well done!" << endl;
                ++playerWin;
            }
            else if (deadShip == 1){
                cout << "You sunk their Patrol Boat! GG!" << endl;
                ++playerWin;
            }
        }
        else cout << "YOU MISS!" << endl;

        // Computer Turn
        if (enemyHit == false){
            shot2 = rand() %100 + 1;
            if(enemyShotCheck(shot2, playerBoard, computerHitCount)){
                cout << "COMPUTER HIT!" << endl;
                //computerHitCount++;
                enemyHit = true;
                deadShip = shipSunk(shot2, aircraftCarrierPlayer, battleshipPlayer, destroyerPlayer, patrolBoatPlayer);
                if(deadShip == 4){
                    cout << "They sunk your Aircraft Carrier! NOOOOO!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                }
                else if (deadShip == 3){
                    cout << "They sunk your Battleship! Well drat!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                }
                else if (deadShip == 2){
                    cout << "They sunk your Destroyer! This day sucks!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                }
                else if (deadShip == 1){
                    cout << "They sunk your Patrol Boat! OH MY!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                }
            }
            else{
                cout << "Computer Miss!" << endl;
                enemyHit = false;
            }
        }
        else{
            hitSearch(playerBoard, shot2, newShot, function);
            if(enemyShotCheck(newShot, playerBoard, computerHitCount)){
                cout << "COMPUTER HIT!" << endl;
                enemyHit = true;
                //computerHitCount++;
                deadShip = shipSunk(newShot, aircraftCarrierPlayer, battleshipPlayer, destroyerPlayer, patrolBoatPlayer);
                if(deadShip == 4){
                    cout << "They sunk your Aircraft Carrier! NOOOOO!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                    newShot = 0;
                }
                else if (deadShip == 3){
                    cout << "They sunk your Battleship! Well drat!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                    newShot = 0;
                }
                else if (deadShip == 2){
                    cout << "They sunk your Destroyer! This day sucks!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                    newShot = 0;
                }
                else if (deadShip == 1){
                    cout << "They sunk your Patrol Boat! OH MY!" << endl;
                    ++playerLoss;
                    enemyHit = false;
                    newShot = 0;
                }
                hitSearch(playerBoard, newShot, newShot, function);
            }

            else{
                cout << "Computer Miss!" << endl;
                function = 0;
                hitSearch(playerBoard, shot2, newShot, function);
            }
        }
        cout << "----------------" << endl;

        cout << "\n" << "Your view of the Enemy Fleet:";
        printBoard(enemyBoard);

        cout << "\n" << "Your Fleet:" << endl;
        printBoard(playerBoard);

        cout << "******************************************" << endl;
        // Used for testing:: cout << "playerLoss: " << playerLoss << "// playerWin: " << playerWin << endl;
        // Used for testing:: cout << "Computer Hit Count: " << computerHitCount << endl;
        cout << "******************************************" << endl;
    }

    return 0;
}