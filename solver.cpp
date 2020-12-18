#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;


int size = 9;
int puzzle[9][9];


/**
 * Gets the puzzle input from the .txt file
**/
void getInput(){
    int rowSize = 0;
    int colSize = 0;
    ifstream file("input.txt");
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            string num;
            for(int i = 0; i < 9; i++){
                num = line.substr(i, 1);
                puzzle[rowSize][colSize] = stoi(num);
                colSize++;
            }
            colSize = 0;
            rowSize++;
        }
    }
}

/**
 * Prints out the board in a 3x3 grid
**/
void printGrid(){
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            if(col == 3 || col == 6){
                cout << "| ";
            } 
            cout << puzzle[row][col] << " ";
        }
        if(row == 2 || row == 5){
            cout << endl;
            for(int i = 0; i < 7; i++){
                cout << "---";
            }
        }
        cout << endl;
    }
}

/**
 * 
 * @param find    the number that you are looking to find
 * @param col     the column you are looking at
 * @returns bool  returns true if the number is present in the col
**/
bool isPresentInCol(int find, int col){
    for(int row = 0; row < size; row++){
        if(puzzle[row][col] == find){
            return true;
        }
    }
    return false;
}

/**
 *
 * @param find    the number that you are looking to find
 * @param row     the row you are looking at
 * @returns bool  returns true if the number is present in the row 
**/
bool isPresentInRow(int find, int row){
    for(int col = 0; col < size; col++){
        if(puzzle[row][col] == find){
            return true;
        }
    }
    return false;
}

/**
 *
 * @param find       the number that you are looking to find
 * @param rowStart   the row you are looking at
 * @param colStart   the col you are looking at
 * @returns bool     returns true if the number is present in the 3x3 grid space 
**/
bool isPresentIn3x3(int find, int rowStart, int colStart){
    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            if(puzzle[row+rowStart][col+colStart] == find){
                return true;
            }
        }
    }
    return false;
}

/**
 *
 * @param find   the number that you are looking to find
 * @param row    the row you are looking at
 * @param col    the col you are looking at
 * @return bool  returns true if the number can be put in the grid space
**/
bool isValid(int find, int row, int col){
    if(!isPresentInRow(find, row) && 
       !isPresentInCol(find, col) &&
       !isPresentIn3x3(find, row - row%3, col - col%3)){
       return true; 
    }
    return false;
}

/**
 *
 * @param row    passed by reference to update the newest location of an empty row
 * @param col    passed by reference to update the newest location of an empty col
 * @return bool  returns true if the grid space is empty
**/
bool isEmpty(int &row, int &col){
    for(int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            if(puzzle[row][col] == 0){
                return true;
            }
        }
    }
    return false;
}

bool solve(){
    int row;
    int col;
    if(!isEmpty(row, col)){
        return true;
    }
    for(int find = 1; find <= 9; find++){
        if(isValid(find, row, col)){
            puzzle[row][col] = find;
            if(solve()){
                return true;
            }
            puzzle[row][col] = 0;
        }
    }
    return false;
}




int main(){
    getInput();
    cout << "Before solving:" << endl;
    printGrid();
    if(solve() == true){
        cout << endl << "After" << endl;
        printGrid();
    }
    else{
        cout << endl << "No solution exists";
    }
    return 0;
}