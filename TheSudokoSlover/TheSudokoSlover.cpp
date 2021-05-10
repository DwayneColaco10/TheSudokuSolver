#include <iostream>
#include <vector>

using namespace std;



void printBoard(int arr[9][9]) {
    //this function is to print the board on the screen
    cout << "-----------------\n";

    for (int i = 0; i < 9; i++) {//loops through the rows
        for (int j = 0; j < 9; j++) {//nested loop that loops through the columns
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "-----------------\n";
}

bool placeavailable(int arr[9][9], int row, int column, int num) {

    if (arr[row][column] != 0) {
        return false;
    }
    bool state = true;

    int findgridX = (column / 3) * 3;//finds the x coordinate of the first position in the grid currently at depending on the column
    int findgridY = (row / 3) * 3;//finds the y coordinate of the first position in the grid currently at depending on the row

    for (int i = 0; i < 9; i++) {

        if (arr[row][i] == num) { state = false; break; }
        if (arr[i][column] == num) { state = false; break; }

        if (arr[findgridY + i / 3][findgridX + i % 3] == num) { state = false; break; }

    }

    return state;
}

vector<int> findplace(int arr[9][9], int row, int column) {

    vector<int> canplacehere = {};

    for (int i = 1; i <= 9; i++) //this for loop checks if the number can be placed into a slot
    {
        if (placeavailable(arr, row, column, i)) {

            canplacehere.push_back(i);//push the value of i into the vector canplacehere

        }
    }
    return canplacehere;
}

void copyarr(int arr[9][9], int duplicatearr[9][9]) {

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            duplicatearr[i][j] = arr[i][j];//duplicates arr into duplicatearr
        }
    }
}

void nextempty(int arr[9][9], int row, int column, int& nextrow, int& nextcolumn) {

    int index = 81;

    for (int i = row * 9 + column + 1; i < 81; i++)
    {
        if (arr[i / 9][i % 9] == 0) {//checks to see if current position is empty
            index = i; break;//sets the index to the value where the row and column are empty
        }
    }
    nextrow = index / 9;// divide the index by the width to find next position of row
    nextcolumn = index % 9;// divide the index by the length to find next position of column
}

bool solvesudo(int arr[9][9], int row, int column) {

    if (row > 8) { return true; }//if row greater then 8 that means all the cells in the row have been solved

    //this if statements finds the position thet is empty and when it does the if statement breaks
    if (arr[row][column] != 0) {
        int nextrow, nextcolumn;
        nextempty(arr, row, column, nextrow, nextcolumn);
        return solvesudo(arr, nextrow, nextcolumn);
    }

    vector<int> placeables = findplace(arr, row, column);

    if (placeables.size() == 0) { return false; }//if there is no placeables left at that space then returns false

    bool state = false;

    for (int i = 0; i < placeables.size(); i++)
    {
        int n = placeables[i];
        int arrcopy[9][9];
        copyarr(arr, arrcopy);
        arrcopy[row][column] = n;

        int nextrow, nextcolumn;
        nextempty(arrcopy, row, column, nextrow, nextcolumn);

        //this if statements calls solvesudo recurrsively untill all the cells have be explored
        if (solvesudo(arrcopy, nextrow, nextcolumn)) {
            copyarr(arrcopy, arr);//copies the solved ans into arr from arrcopy
            state = true; break;
        }
    }

    return state;
}

bool checkifcanplace(int arr[9][9], int row, int column, int num) {

    bool state = true;

    int findgridX = (column / 3) * 3;//finds the x coordinate of the first position in the grid currently at depending on the column
    int findgridY = (row / 3) * 3;//finds the y coordinate of the first position in the grid currently at depending on the row


    for (int i = 0; i < 9; i++) {

        if (num == 0) { state = true; break; }

        if (arr[row][i] == num) { state = false; break; }//checks and breaks if number entered is already in that row
        if (arr[i][column] == num) { state = false; break; }//checks and breaks if number entered is already in that row

        if (arr[findgridY + i / 3][findgridX + i % 3] == num) { state = false; break; }// checks if the number the user has entered already exists in the grid

    }

    return state;
}

void createboard(int arr[9][9]) {

    cout << "please enter the values into the sudoko one number at a time.\n";

    cout << "-----------------\n";

    for (int i = 0; i < 9; i++) {//loops through the rows
        for (int j = 0; j < 9; j++) {//nested loop that loops through the columns


            int enternum;
            cout << "enter your number\n";
           // cin >> enternum;

            //this while loop sanitizes the input so that the code doesnt crash
            while (!(cin >> enternum)) {//recieve the user input
                cout << "Error: enter a number \n";//explain the error

                cin.clear();//clear the previos input

                cin.ignore(1150, '\n');//dicard previos input
            }

            //the while loop checks if the number cannot be placed in this position and if the user has to re-enter a diffrent number
            while (!checkifcanplace(arr, i, j, enternum)) {
                cout << "this num cannot be placed here pick a different number\n";
                cout << "enter your number again\n";
                cin >> enternum;
            }
            arr[i][j] = enternum;
            printBoard(arr);
        }
        cout << "\n";
    }

    cout << "-----------------\n";

   
}


int main()
{

    int sudoboard[9][9] = {
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    };

    createboard(sudoboard);

    cout << "the sudoko will now be solved\n";
    solvesudo(sudoboard, 0, 0);
    printBoard(sudoboard);

}



