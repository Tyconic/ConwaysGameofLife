#include <iostream>
#include <Windows.h>
using namespace std;

const int n = 59;

void initializeArrayRandom(bool array[n/2][n]) { //Create a board of randomly placed cells
    for (int i = 0; i < n/2; i++) {
        for (int u = 0; u < n; u++) {
            array[i][u] = rand() % 2; //For every cell randomly assign a 1 or a 0
        }
    }
}

void initializeArrayGun(bool array[n/2][n]) { //Create a board with a glider gun
    for (int i = 0; i < n/2; i++) {
        for (int u = 0; u < n; u++) {
            array[i][u] = 0; //Set the whole board to 0
        }
    }
        array[0 + 3][24 + 3] = 1;
        array[1 + 3][22 + 3] = 1;
        array[1 + 3][24 + 3] = 1;
        array[2 + 3][12 + 3] = 1;
        array[2 + 3][13 + 3] = 1;
        array[2 + 3][20 + 3] = 1;
        array[2 + 3][21 + 3] = 1;
        array[2 + 3][34 + 3] = 1;
        array[2 + 3][35 + 3] = 1;
        array[3 + 3][11 + 3] = 1;
        array[3 + 3][15 + 3] = 1;
        array[3 + 3][20 + 3] = 1;
        array[3 + 3][21 + 3] = 1;
        array[3 + 3][34 + 3] = 1;
        array[3 + 3][35 + 3] = 1;
        array[4 + 3][0 + 3] = 1;
        array[4 + 3] [1 + 3] = 1;
        array[4 + 3] [10 + 3] = 1;
        array[4 + 3] [16 + 3] = 1;
        array[4 + 3] [20 + 3] = 1;
        array[4 + 3] [21 + 3] = 1;
        array[5 + 3] [0 + 3] = 1;
        array[5 + 3] [1 + 3] = 1;
        array[5 + 3] [10 + 3] = 1;
        array[5 + 3] [14 + 3] = 1;
        array[5 + 3] [16 + 3] = 1;
        array[5 + 3] [17 + 3] = 1;
        array[5 + 3] [22 + 3] = 1;
        array[5 + 3] [24 + 3] = 1;
        array[6 + 3] [10 + 3] = 1;
        array[6 + 3] [16 + 3] = 1;
        array[6 + 3] [24 + 3] = 1;
        array[7 + 3] [11 + 3] = 1;
        array[7 + 3] [15 + 3] = 1;
        array[8 + 3] [12 + 3] = 1;
        array[8 + 3] [13 + 3] = 1; //Set specific cells to 1 in the shape of a glider gun

}

void printArray(bool array[n/2][n]) { //Print the current board to the console
    for (int i = 0; i < n/2; i++) {
        for (int u = 0; u < n; u++) {
            if (array[i][u] == 1) cout << "O";
            else cout << " "; //Print cells with a value of 1 as alive and with 0 as dead
        }
        if(i != n/2) cout << endl;
    }
}

void iterateArray(bool array[n/2][n]) { //Apply Conway's rules to the current board / Evolve

    bool tmp[n/2][n]; //create a temporary array

    for (int i = 0; i < n / 2; i++) {
        for (int u = 0; u < n; u++) {
            int TL = array[i-1][u-1];
            int TM = array[i-1][u];
            int TR = array[i-1][u+1];
            int ML = array[i][u-1];
            int MM = array[i][u];
            int MR = array[i][u+1];
            int BL = array[i+1][u-1];
            int BM = array[i+1][u];
            int BR = array[i+1][u+1]; //save surrounding cells

            if (i == 0) {
                TL = array[n/2][u-1];
                TM = array[n/2][u];
                TR = array[n/2][u+1];
            }

            if (u == 0) {
                TL = array[i-1][0];
                ML = array[i][0];
                BL = array[i+1][0];
            }

            if (i == n/2) {
                BL = array[0][u-1];
                BM = array[0][u];
                BR = array[0][u+1];
            }

            if (u == n) {
                TR = array[i-1][n];
                MR = array[i][n];
                BR = array[i+1][n];
            }

            if (i == 0 && u == 0) {
                TL = array[n / 2][n];
            }

            if (i == 0 && u == n) {
                TR = array[n / 2][0];
            }

            if (i == n/2 && u == n) {
                BR = array[0][0];
            }

            if (i == n/2 && u == 0) { //Check for edge cases
                BL = array[0][n];
            } 

            int cellCount = TL + TM + TR + ML + MR + BL + BM + BR; //get the number of living cells surrounding a cell

            if (MM == 1) { 
                tmp[i][u] = 1;
                if (cellCount < 2) tmp[i][u] = 0; //If a cell has less than two live neighbors it dies
                if (cellCount > 3) tmp[i][u] = 0; //If a cell has more than three live neighbors it dies
            }
            if(MM == 0) {
                tmp[i][u] = 0;
                if (cellCount == 3) tmp[i][u] = 1; //If a cell has three neighbors it becomes alive
            }
        }
    }

    for (int i = 0; i < n/2; i++) {
        for (int u = 0; u < n; u++) {
            array[i][u] = tmp[i][u]; //Replace main board with temp
        }
    }
}

int main()
{
   while (1) { //Run Infinitly
       bool array[n / 2][n];
       bool gun;
       bool life = true;
       int waitTime = 50;

       HANDLE hStdOut = NULL;
       CONSOLE_CURSOR_INFO curInfo;

       cout << "Enter 0 for random, enter 1 for glider gun: ";
       cin >> gun;
       if (gun == true) initializeArrayGun(array);
       else initializeArrayRandom(array);

       hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
       GetConsoleCursorInfo(hStdOut, &curInfo);
       curInfo.bVisible = FALSE;
       SetConsoleCursorInfo(hStdOut, &curInfo); //Hide Cursor

       while (life) { //Game Loop
           system("cls"); //Clear the Console
           printArray(array);
           iterateArray(array);
           Sleep(waitTime); //Length of Evolution

           if (GetKeyState(VK_ESCAPE) & 0x8000)
           {
               life = false;
           }
       }
   }
}

