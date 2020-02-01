#include <fstream>
#include <string>
#include <iostream>
#include <cstring>

//PASTE YOUR CODE HERE, EXCEPT main() 
/*
 * main.cpp
 *
 *  Created on: Sep 19, 2019
 *      Author: kevinw
 */

#include <iostream>
#include <cstring>
using namespace std;

const int ARRAY_SIZE = 12;
const char POTION = 'o';
const char RIM = 'T';
const char WALL = '*';
const char EMPTY = ' ';

enum TASK {CLEANUP, WARMUP_FILL, SIMPLE_FILL, ADVANCED_FILL};
void print_array(const char array[][ARRAY_SIZE+1]) {
    cout << "  ";
    for (int j = 0; j < ARRAY_SIZE; j++)
	cout << j % 10;
    cout << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
	cout << i % 10 << " ";
	cout << array[i] << endl;
    }
}
//int count=0;

int cleanup(char array[ARRAY_SIZE][ARRAY_SIZE+1], int row = 0, int col = 0) {
// Don't forget to return!
//cout<<"("<<row<<","<<col<<")";
if(row==0 && col ==0){array[0][12]=0;}
if(row==12 && col ==0){
	int count= array[0][12];
	array[0][12]='\0';
	return count;}
if(array[row][col]==POTION){array[0][12]++;array[row][col]=EMPTY;}
if(col+1==ARRAY_SIZE){cleanup(array,row+1,0);}
else if(row+1<=ARRAY_SIZE && col+1!=ARRAY_SIZE){cleanup(array,row,col+1);}
}

int findTRfromleft(char array[][ARRAY_SIZE+1], int row=0, int col=0){
if(array[row][col]==RIM){return col;}
if(col+1==ARRAY_SIZE){findTRfromleft(array,row+1,0);}
else if(row+1<=ARRAY_SIZE && col+1!=ARRAY_SIZE){findTRfromleft(array,row,col+1);}}

int findTR(char array[][ARRAY_SIZE+1], int row=0, int col=0){
if(array[row][col]==RIM){return row;}
if(col+1==ARRAY_SIZE){findTR(array,row+1,0);}
else if(row+1<=ARRAY_SIZE && col+1!=ARRAY_SIZE){findTR(array,row,col+1);}}

int findTRfromright(char array[][ARRAY_SIZE+1], int row=0, int col=ARRAY_SIZE-1){
if(array[row][col]==RIM){return col;}
if(col-1<0){findTRfromright(array,row+1,ARRAY_SIZE-1);}
else if(row+1<=ARRAY_SIZE && col-1!=-1){findTRfromright(array,row,col-1);}}

void spillout(char array[][ARRAY_SIZE+1]){
	int z = findTR(array);
	int x = findTRfromleft(array);
	int y = findTRfromright(array);
	if(array[z][x-1]==POTION || array[z][y+1]==POTION ||array[11][0]==POTION||array[0][0]==POTION){cleanup(array,0,0);}
}


void warmup_fill(char array[][ARRAY_SIZE+1], int row, int col, int level) {

	if(((array[row][col]==EMPTY || array[row][col]==POTION)&& array[row+1][col]==EMPTY && row<ARRAY_SIZE))
  {
    warmup_fill(array,row+1,col,level);
  }

	if(row>=level && row<ARRAY_SIZE && row>=0 && col<ARRAY_SIZE && col>=0)array[row][col]=POTION;

	if((array[row][col]==POTION && array[row][col+1]==EMPTY && col<ARRAY_SIZE))
  {
    warmup_fill(array,row,col+1,level);
  }

	if((array[row][col]==POTION && array[row-1][col]==EMPTY && row>=0))
  {
    warmup_fill(array,row-1,col,level);
  }

	if((array[row][col]==POTION && array[row][col-1]==EMPTY && col>=0))
  {
    warmup_fill(array,row,col-1,level);
	}
}

bool countT(char array[][ARRAY_SIZE+1], int row, int col=0){
	if(col ==0){array[0][12]=0;}
if(col==ARRAY_SIZE){
	int count= array[0][12];
	array[0][12]='\0';
	if(count==2){return true;}
	else{return false;}
}
if(array[row][col]==RIM){array[0][12]++;}
if(col+1<=ARRAY_SIZE){countT(array,row,col+1);
}}
void simple_fill(char array[][ARRAY_SIZE+1], int row, int col) {

if(array[row][col-1]==EMPTY && array[row][col+1]==EMPTY){simple_fill(array,row+1,col);}
if(array[row][col-1]==RIM && array[row][col+1]==RIM && array[row][col]==EMPTY){
	warmup_fill(array,row,col,row);
	if(array[11][0]==POTION){spillout(array);}
	if(row<ARRAY_SIZE){simple_fill(array,row+1,col);}
	}

spillout(array);
/*if(array[row][col-1]==EMPTY && array[row][col+1]==EMPTY){simple_fill(array,row+1,col);}
if(array[row][col-1]==RIM && array[row][col+1]==RIM && array[row][col+2]==POTION){cleanup(array,0,0);}
*/
}


int advanced_fill(char array[][ARRAY_SIZE+1], int row, int col) {
// Don't forget to return!
//cout<<row<<col<<",";

if(array[row][col-1]==EMPTY && array[row][col+1]==EMPTY){advanced_fill(array,row+1,col);}
if((array[row][col-1]==RIM||array[row][col-2]==RIM||array[row][col-3]==RIM||array[row][col-4]==RIM||array[row][col-5]==RIM||array[row][col-6]==RIM||array[row][col-7]==RIM||array[row][col-8]==RIM||array[row][col-9]==RIM||array[row][col-10]==RIM) && (array[row][col+1]==RIM||array[row][col+2]==RIM||array[row][col+3]==RIM||array[row][col+4]==RIM||array[row][col+5]==RIM||array[row][col+6]==RIM||array[row][col+7]==RIM||array[row][col+8]==RIM||array[row][col+9]==RIM||array[row][col+10]==RIM) && array[row][col]==EMPTY){
	warmup_fill(array,row,col,row);
	if(array[11][0]==POTION){spillout(array);}
 if(row<ARRAY_SIZE){advanced_fill(array,row+1,col);}
}

spillout(array);
}


//////


#include "map.h"
using namespace std;
bool DEBUG = true;
bool check_value(const char array[][ARRAY_SIZE + 1], const char sol[][ARRAY_SIZE + 1]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
	for (int j = 0; j < ARRAY_SIZE; j++) 
	    if (array[i][j] != sol[i][j]) return false;
	if (array[i][ARRAY_SIZE] != '\0') return false;
    }
    return true;
}

void print_array_2(const char array[][ARRAY_SIZE+1]) {
    cout << "  ";
    for (int j = 0; j < ARRAY_SIZE; j++)
	cout << j % 10;
    cout << endl;
    for (int i = 0; i < ARRAY_SIZE + 2; i++) {
	cout << i % 10 << " ";
	if (i == 0 || i == ARRAY_SIZE + 1)
	   cout << array[i] << "  <-- out-of-bound array content, should not be changed" << endl;
	else
	   cout << array[i] << endl;
    }
}


void copy(char dst[][ARRAY_SIZE+1], const char src[][ARRAY_SIZE+1]) {
    for (int i = 0; i < ARRAY_SIZE; i++)
	for (int j = 0; j < ARRAY_SIZE + 1; j++)
	    dst[i][j] = src[i][j];
}
// cleanup
//
// There are few possible errors a cleanup can have
// 1. unfinished cleanup or over-clean (remove original WALL and RIM)
// 2. return wrong cleanup count
// 3. clean array[ARRAY_SIZE] or beyond
//
const int WRONG_ARRAY = 4;
const int WRONG_COUNT = 2;
const int WRONG_BOUND = 1;
const int CORRECT = 0;

int ta_cleanup(char [][ARRAY_SIZE + 1], int=0, int=0);
int compare_cleanup(const char a[][ARRAY_SIZE + 1]) {
    char x[ARRAY_SIZE][ARRAY_SIZE+1];
    char y[ARRAY_SIZE+2][ARRAY_SIZE+1] = {};
    copy(x, a);
    copy(&y[1], a);  // y[0] and y[ARRAY_SIZE + 1] is out-of-bound memory
    strcpy(y[ARRAY_SIZE + 1], "oooooooooooo");  //you should not touch this
    strcpy(y[0],              "oooooooooooo");   //you should not touch this

    int student = cleanup(&y[1]);
    int ta = ta_cleanup(x);

    int result = CORRECT;
    if (DEBUG) {
	cout << " Student Cleanup. return value=" << student << endl;
	print_array_2(y);
	cout << " Solution Cleanup. return value=" << ta << endl;
	print_array(x);
    }


    if (!check_value(x, &y[1])) result |= WRONG_ARRAY;
    if (ta != student) result |= WRONG_COUNT;
    for (int i = 0; i < ARRAY_SIZE; i++)
	if (y[ARRAY_SIZE+1][i] != 'o' || y[0][i] != 'o') 
	    result |= WRONG_BOUND;

    return result;

}


int test0() {    return compare_cleanup(f_bowl);    }
int test1() {    return compare_cleanup(f_cup);    }
int test2() {    return compare_cleanup(f_two_tubes);    }
int test3() {    return compare_cleanup(f_conical_flask);    }
int test4() {    return compare_cleanup(two_tubes);    }


//warmup_fill
//
//
void ta_warmup_fill(char [][ARRAY_SIZE + 1], int, int, int);
int compare_warmup(const char a[][ARRAY_SIZE+1], const int col, const int level) {
    char x[ARRAY_SIZE][ARRAY_SIZE+1];   
    char y[ARRAY_SIZE][ARRAY_SIZE+1];
    copy(x, a);
    copy(y, a);
    ta_warmup_fill(x, 0, col, level);
    warmup_fill(y, 0, col, level);

    int result = CORRECT;

    if (DEBUG) {
	cout << " Student warmup. " <<  endl << "drop here" << endl;
	for (int i = 0; i < col+2; i++)
	    cout << ' ';
	cout << 'D' << endl;
	print_array(x);

	cout << " Solution warmup. " << endl << "drop here" << endl;
	for (int i = 0; i < col+2; i++)
	    cout << ' ';
	cout << 'D' << endl;
	print_array(y);
    }


    if (!check_value(x, y)) result |= WRONG_ARRAY;
    return result;
}

int test5() {    return compare_warmup(two_tubes, 6, 1);}
int test6() {    return compare_warmup(test_tube, 6, 4);}
int test7() {    return compare_warmup(conical_flask, 6, 4);}
int test8() {    return compare_warmup(flask, 5, 1);}
int test9() {    return compare_warmup(up_and_down, 2, 4);}
int test10() {    return compare_warmup(trio, 6, 4);}
int test11() {    return compare_warmup(wu_tong, 6, 4);}
int test12() {    return compare_warmup(rocket, 6, 4);}

//simple_fill
//
//
void ta_simple_fill(char [][ARRAY_SIZE + 1], int, int);
int compare_simple(const char a[][ARRAY_SIZE+1], const int col) {
    char x[ARRAY_SIZE][ARRAY_SIZE+1];
    char y[ARRAY_SIZE][ARRAY_SIZE+1];
    copy(x, a);
    copy(y, a);
    ta_simple_fill(x, 0, col);
    simple_fill(y, 0, col);

    int result = CORRECT;

    if (DEBUG) {
	cout << " Student simple. " <<  endl << "drop here" << endl;
	for (int i = 0; i < col+2; i++)
	    cout << ' ';
	cout << 'D' << endl;
	print_array(x);

	cout << " Solution simple. " << endl << "drop here" << endl;
	for (int i = 0; i < col+2; i++)
	    cout << ' ';
	cout << 'D' << endl;
	print_array(y);
    }


    if (!check_value(x, y)) result |= WRONG_ARRAY;
    return result;
}

int test13() { return compare_simple(two_tubes, 6); }
int test14() {    return compare_simple(test_tube, 6);}
int test15() {    return compare_simple(conical_flask, 6);}
int test16() {    return compare_simple(flask, 5);}
int test17() {    return compare_simple(up_and_down, 2);}
int test18() {    return compare_simple(trio, 6);}
int test19() {    return compare_simple(wu_tong, 6);}
int test20() {    return compare_simple(rocket, 6);}


//advanced_fill
//
int ta_advanced_fill(char [][ARRAY_SIZE + 1], int, int);
int compare_adv(const char a[][ARRAY_SIZE+1], const int col) {
    char x[ARRAY_SIZE][ARRAY_SIZE+1];
    char y[ARRAY_SIZE+2][ARRAY_SIZE+1] = {};
    copy(x, a);
    copy(&y[1], a);
    strcpy(y[ARRAY_SIZE + 1], "************");  //you should not touch this
    strcpy(y[0],              "TTTTTTTTTTTT");   //you should not touch this
    ta_advanced_fill(x, 0, col);
    advanced_fill(&y[1], 0, col);

    int result = CORRECT;

    if (DEBUG) {
	
	cout << " Student advanced. " <<  endl << "drop here" << endl;
	for (int i = 0; i < col+2; i++)
	    cout << ' ';
	cout << 'D' << endl;
	print_array_2(y);

	cout << " Solution advanced. " << endl << "drop here" << endl;
	for (int i = 0; i < col+2; i++)
	    cout << ' ';
	cout << 'D' << endl;
	print_array(x);
    }


    if (!check_value(x, &y[1])) result |= WRONG_ARRAY;
    for (int i = 0; i < ARRAY_SIZE; i++)
	if (y[ARRAY_SIZE+1][i] != '*' || y[0][i] != 'T') 
	    result |= WRONG_BOUND;

    return result;
}

int test21() { return compare_adv(test_tube, 6); }
int test22() { return compare_adv(test_tube, 1); }
int test23() { return compare_adv(beaker, 3); }
int test24() { return compare_adv(beaker, 6); }
int test25() { return compare_adv(broken_flask, 6); }
int test26() { return compare_adv(broken_u_flask, 5); }
int test27() { return compare_adv(broken_u_flask, 10); }
int test28() { return compare_adv(up_and_down, 2); }
int test29() { return compare_adv(side_broken, 1); }
int test30() { return compare_adv(conical_flask, 5); } 
int test31() { return compare_adv(ripple, 2); } 
int test32() { return compare_adv(ripple, 5); }
int test33() { return compare_adv(blank, 1); }
int test34() { return compare_adv(timer, 3); }
int test35() { return compare_adv(flask, 7); }
int test36() { return compare_adv(flask, 6); }
int main(int argc, char* argv[]) {
    int  (*f[])() = {
	test0, test1, test2, test3, test4,
	test5, test6, test7, test8, test9, test10, test11, test12,
	test13,test14,test15,test16,test17,test18,test19,test20,
	test21,test22,test23,test24,test25,test26,test27,test28,test29,test30,test31,test32,test33,test34,test35,test36

    }; 
    const int TOTAL_CASES = sizeof(f)/sizeof(f[0]);
    if (argc == 2) { 
	int test_case = atoi(argv[1]);
	DEBUG = false;
	if (test_case >= TOTAL_CASES || test_case < 0) 
	    cout << "No such test case" << endl;
	else {
	    ofstream ofs(string(argv[1]) + ".log");
	    ofs << f[test_case]() << endl;
	    ofs.close();
	}
    } else {
	cout << "Please enter the number of test cases you want to test" << endl;
	cout << "[0-" << TOTAL_CASES - 1 << "]" << endl;
	int test_case;
	cin >> test_case;
	if (test_case >= TOTAL_CASES || test_case < 0) 
	    cout << "No such test case" << endl;
	else {
	    int result = f[test_case]();
	    cout << endl << "Test Result (non zero = incorrect):" << result << endl;
	}
    }

    return 0;
}




