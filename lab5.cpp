/* 
 * File: lab5_skeleton.cpp
 *
 * Lab 5: Recursion - Same or Assimilation
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/* SIZE of the board */
const int BOARD_SIZE = 10;

// FUNCTION 1
/**
   TODO: Define the function, initialize_symbols(), with appropriate header and body
   1st parameter: the game board array
   2nd parameter: the number of symbols

   The function should initialize all array elements by randomly assigning a symbol from
   a set of characters. E.g. if 2nd parameter's value is 3, the 3 characters are 'A', 'B', 'C'.
**/
// Add the function header and body here
void initialize_symbols(char symbol_array[][BOARD_SIZE],int num_of_symbol){
  srand(time(0));
  for(int i=0;i<BOARD_SIZE;i++){
    for(int j=0;j<BOARD_SIZE;j++){
      char alphabet = rand() % num_of_symbol + 65;
      symbol_array[i][j]=alphabet;
}
    }
  }

// FUNCTION 2
/**
   TODO: Define the function, print_game_board(), with appropriate header and body
   1st parameter: the game board array

   The function should print the board (i.e. symbol_array). 
**/
// Add the function header and body here
void print_game_board(char symbol_array[][BOARD_SIZE]){
  for(int i=0;i<BOARD_SIZE;i++){
    if(i==0){cout<<" --- --- --- --- --- --- --- --- --- ---"<<endl;}
    for(int j=0;j<BOARD_SIZE;j++){
      if(j<BOARD_SIZE-1){cout<<"| "<<symbol_array[i][j]<<" ";}
      else if(j==BOARD_SIZE-1){cout<<"| "<<symbol_array[i][j]<<" |"<<endl;}
}
    if(i==BOARD_SIZE-1){cout<<" --- --- --- --- --- --- --- --- --- ---"<<endl;}
    }
}

// FUNCTION 3
/**
   TODO: Define the function, update_symbol_array_recursive(), with appropriate header and body
   1st parameter: the array symbol_array
   2nd parameter: the old symbol to be replaced 
   3rd parameter: the new symbol to be filled
   4th parameter: row index of the position to start the replacement
   5th parameter: col index of the position to start the replacement

   The function MUST update the game board with new symbol using RECURSION.
   It starts with a given position (4th & 5th parameters). 
   - If its symbol is not the same as the old symbol, do nothing. 
   - Otherwise, if the symbol is the same as the old symbol, it is replaced by the new symbol, 
     and then recursively update the symbols of all array elements which are connected with it (i.e. the 4 elements 
     which are north, south, west and east of it). 

**/
// Add the function header and body here
/*asuume 0,0 is an A,user input B 
first the program replaces the A by B, then search for the pair BA
down,right,up,left
*/
void update_symbol_array_recursive(char symbol_array[][BOARD_SIZE],char sym_to_replace,char new_sym,int row_index,int col_index){

if(row_index>=0 && col_index>=0 && row_index<BOARD_SIZE && col_index<BOARD_SIZE)
  {
   cout<<sym_to_replace<<"("<<row_index<<","<<col_index<<")-";
   symbol_array[row_index][col_index]=new_sym;
  }

   if(symbol_array[row_index+1][col_index]==sym_to_replace && symbol_array[row_index][col_index]==new_sym)
   update_symbol_array_recursive(symbol_array, sym_to_replace, new_sym, row_index+1, col_index);
   if(symbol_array[row_index][col_index+1]==sym_to_replace && symbol_array[row_index][col_index]==new_sym)
   update_symbol_array_recursive(symbol_array, sym_to_replace, new_sym, row_index, col_index+1);
   if(symbol_array[row_index-1][col_index]==sym_to_replace && symbol_array[row_index][col_index]==new_sym)
   update_symbol_array_recursive(symbol_array, sym_to_replace, new_sym, row_index-1, col_index);
   if(symbol_array[row_index][col_index-1]==sym_to_replace && symbol_array[row_index][col_index]==new_sym)
   update_symbol_array_recursive(symbol_array, sym_to_replace, new_sym, row_index, col_index-1);

   }

      
   
// FUNCTION 4
/**
   TODO: Define the function, check_win(), with appropriate header and body
   1st parameter: the game board array

   The function returns true if the user wins the game, i.e. all elements are of the same symbol.
   Otherwise, returns false.
**/
// Add the function header and body here
bool check_win(char symbol_array[][BOARD_SIZE]){
  for(int i=0;i<BOARD_SIZE;i++){
    for(int j=1;j<BOARD_SIZE;j++){
      if(symbol_array[i][0]!=symbol_array[i][j]){return false;}
    }
}
return true;}

/**
   Given: the funtion, input_validation(), will check whether the new symbol is 
   a valid symbol, i.e. among the set of num_of_symbols characters.
   1st parameter: the game board array
   2nd parameter: the new sybmol
   3rd parameter: the number of symbols
**/
bool input_validation(const char sym[][BOARD_SIZE], char new_symbol, int num_of_symbols)
{
   if(new_symbol == sym[0][0])
   {
      cout << "Please input a different symbol..." << endl;
      return false; 
   }

   if(!(new_symbol - 'A' < num_of_symbols && new_symbol >= 'A'))
   {
      cout << "Please input a correct symbol..." << endl;
      return false; 
   }

   return true; 
}

/** 
   Given: the main() function
**/
int main()
{
   char symbol_array[BOARD_SIZE][BOARD_SIZE]; // a two-dimension array to store the symbols
   int num_of_symbols; // number of different symbols
   int max_step_num; // number of maximum steps for winning game

   cout << "*************************" << endl << "Same or Assimilation Game" << endl
        << "*************************" << endl << endl;
   cout << "Please input the number of symbols: "; 
   cin >> num_of_symbols;
   cout << "Please input the maximum number of steps for winning the game: "; 
   cin >> max_step_num;

  
   // CALLING FUNCTION 1
   /* The function initializes all array elements by randomly assigning a symbol from
        a set of max_step_num characters. E.g. if max_step_num is 3, the 3 characters are 'A', 'B', 'C'.
    */
   initialize_symbols(symbol_array, num_of_symbols);

   // CALLING FUNCTION 2
   /* The function prints the board (i.e. symbol_array). 
    */
   print_game_board(symbol_array);
   
   // GAME STARTS
   cout << endl << "GAME STARTS..." << endl << "Input new symbol to expand your territory!" << endl << endl;
   
   bool winning_flag = false;

   for(int step = 0; step < max_step_num && !winning_flag; ++step) 
   {
      cout << "\n\nSTEPS LEFT: " << max_step_num - step << endl; 

      // input the new symbol
      cout << "Input the new symbol to unleash your \"symbol army\" from the top-left: "; 
      char new_symbol;
      cin >> new_symbol;
      cout << endl;

      /* input validation:
         make sure the new input is different from the top-left symbol and are not out of the range.
       */
      if(!input_validation(symbol_array, new_symbol, num_of_symbols))
      {
         cout << "Please re-input..." << endl;
         continue;
      }
      
      // CALLING FUNCTION 3
      /* The function updates the game board with new symbol using recursion.
         It starts with the top-left array element, and changes all array elements which are connected with it and 
         sharing the same symbol with it to the new symbol.
         1st parameter: the array symbol_array
         2nd parameter: the old symbol to be replaced 
         3rd parameter: the new symbol to be filled
         4th parameter: row index of the position to start the replacement
         5th parameter: col index of the position to start the replacement
      */
      update_symbol_array_recursive(symbol_array, symbol_array[0][0], new_symbol, 0, 0);
      cout<<endl;
      // print the updated game board
      print_game_board(symbol_array);

      // CALLING FUNCTION 4
      /* The function returns true if the user wins the game, i.e. all elements are of the same symbol.
         Otherwise, returns false.
       */
      winning_flag = check_win(symbol_array);
   }
   
   if(winning_flag)
      cout << "\nCongratuations! You win the game!" << endl;
   else
      cout << "\nSo close! You lose the game!" << endl;

   return 0;
}
