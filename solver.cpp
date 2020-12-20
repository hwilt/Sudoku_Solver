#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#define N 9
using namespace std;



int grid[N][N];

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
                grid[rowSize][colSize] = stoi(num);
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
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col++){
            if(col == 3 || col == 6){
                cout << "| ";
            } 
            cout << grid[row][col] << " ";
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


bool isPresentInCol(int col, int num){
   for (int row = 0; row < N; row++)
      if (grid[row][col] == num)
         return true;
   return false;
}


bool isPresentInRow(int row, int num){
   for (int col = 0; col < N; col++)
      if (grid[row][col] == num)
         return true;
   return false;
}


bool isPresentInBox(int boxStartRow, int boxStartCol, int num){
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (grid[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}


bool findEmptyPlace(int &row, int &col){ 
   for (row = 0; row < N; row++)
      for (col = 0; col < N; col++)
         if (grid[row][col] == 0) 
            return true;
   return false;
}


bool isValidPlace(int row, int col, int num){
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,col - col%3, num);
}


bool solveSudoku(){
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; 
   for (int num = 1; num <= 9; num++){ 
      if (isValidPlace(row, col, num)){ 
         grid[row][col] = num;
         if (solveSudoku()) 
            return true;
         grid[row][col] = 0;
      }
   }
   return false;
}

int main(){
    getInput();
    cout << "Before solving:" << endl;
    printGrid();
    if(solveSudoku() == true){
        cout << endl << "After" << endl;
        printGrid();
    }
    else{
        cout << endl << "No solution exists";
    }
    return 0;
}