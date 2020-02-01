//============================================================================
// Name        : pa1_skeleton.cpp
// Author      : liuhao
// Version     : PA1 COMP2011 Fall 2019
// Copyright   : COMP2011 teaching team
// Description : Ping-pong number
//============================================================================

#include <iostream>
using namespace std;

/**
 * Task 1
 * This function returns a boolean value indicating whether the input n is a ping-pong number
 * The input n is a non-negative integer
 * Single digits are ping-pong numbers
 */
bool is_pingpong(int n)
{
	// TODO: start your coding here
	if(n>=0	&&	n<=9){return true;}

	else if(n>9) {
		//counting the length of a number
		int i=n;
		int count=0;
		for(;i!=0;count++){i=i/10;}
		//initiate number of pair of digit
		int backup_count=count-1;
		//compare digit
		int pair=0;
		for(int j=1;count-1!=0;j=j*10,count--){
			int a =n/j%10;
			int b =n/(j*10)%10;
			if(a-b==1||a-b==-1){
				pair++;
			}
		}
		//if pair of 1/-1 equal the number of pair of digit,it is a ping pong number
		if(pair==backup_count){return true;}
	}
	return false;
}

/**
 * Task 2
 * This function prints all the ping-pong number in range [m, n] five in a row in ascending order
 * Inputs m and n are non-negative integers, and m < n
 * m and n are included in the range
 * Use cout for print
 * The numbers printed within a row is separated by a space (" ")
 * Additional spaces are allowed at the beginning or end of each row, but not allowed between numbers printed
 * Additional newlines are allowed at the beginning or end of all the output, but not allowed in the middle
 * Make sure nothing else is printed out
 */
void print_pingpong(int m, int n)
{
	// TODO: start your coding here
	for(int j=0;m<=n;m++){
		/*j is the number of counting how many m is pingpong number
        when j has no reminder when divided by 5, a new line is printed
		 */
		if(j%5!=0	&&	is_pingpong(m)==true){cout<<m<<" ";}

		else if (j%5==0	&&	is_pingpong(m)==true)
		{
			if(j==0){cout<<m<<" ";}
			else{cout<<endl<<m<<" ";}
		}
		if(is_pingpong(m)==true){j++;}
	}
}

/**
 * Task 3
 * This function prints the ping-pong number counting histogram in range [m, n]
 * Inputs m and n are non-negative integers, num_bins is a positive integer, m < n
 * First split the range [m, n] into (num_bins) bins
 * E.g. [0, 10002] into 5 bins: [0, 1999], [2000, 3999], [4000, 5999], [6000, 7999], [8000, 10002]
 * Except for the last bin, each bin contains floor((n - m + 1)/num_bins) numbers
 * Last bin must end at n, and it might have more elements
 * For each bin range, first count the number of ping-pong numbers, denoted by count
 * if count == 0, bin is empty, print a blank row
 * else print a row of ceiling(count / 10) bar_chars (e.g. '*')
 * After each print of a bin, a newline should be inserted
 * Additional newlines are allowed after the last bin
 */
void print_pingpong_histogram(int m, int n, int num_bins, char bar_char)
{
	// TODO: start your coding here
	int count = 0;
	int end ;
	int number_per_bin=(n-m+1)/num_bins;//how many number per interval
	for (int i = 0; i < num_bins; i++)
	{

		if(i<num_bins-1){
			end=m+number_per_bin-1;
			for (; m <= end; m++){if (is_pingpong(m) == true){count++;}}

			if (count>10	&&	count % 10 !=	0)
			{
				for (int i = 0; i < count / 10 + 1; i++){cout << bar_char;}
				cout<<endl;
			}
			else if (count>10	&&	count % 10 == 0)
			{
				for (int i = 0; i < count / 10; i++){cout << bar_char;}
				cout<<endl;
			}
			else if(count>0	&&	count<=10){cout << bar_char<<endl;}

			else if(count==0){cout<<endl;}
			count = 0;
			m = end + 1;
		}

		else if (i == num_bins-1)//special case when the last interval is arrived
		{
			count = 0;
			end = n;
			for (; m <= end; m++){if (is_pingpong(m) == true){count++;}}

			if (count>10	&&	count % 10 != 0)
			{
				for (int i = 0; i < count / 10 + 1; i++){cout << bar_char;}
				cout<<endl;
			}
			else if (count>10	&&	count % 10 == 0)
			{
				for (int i = 0; i < count / 10; i++){cout << bar_char;}
				cout<<endl;
			}
			else if(count>0	&&	count<=10){cout << bar_char<<endl;}

			else if(count==0){cout<<endl;}
		}
	}
}

/**
 * Task 4
 * This function returns k-th digit of a non-negative integer n from right
 * The rightmost digit has index 1
 * k can be any integer
 * Returns -1 if given index k is out of bound (i.e. k <= 0 or k is larger than the total number of digits of n)
 */
int kth_digit_from_right(int n, int k)
{
	// TODO: start your coding here
	int a = n;
	int i=1;
	int count = 0;
	int require_digit;
	//find length of a number
	if(a==0){count=1;}
	for (; a != 0; count++){a = a / 10;}
	

	//return -1 if out of boundary
	if (k > count || k <= 0){return -1;}

	else// the required digit
	{
		for (int j = 1; i <= k; j = j * 10, i++)
		{
			int b = n / j % 10;
			if (i == k)
			{
				require_digit=b;
			}
		}
	}
	return require_digit;
}

/**
 * Task 5
 * Check whether n is a generalized ping-pong number with given step and digit-diff
 * n >= 0, diff >= 0, and step > 0
 */
bool is_generalized_pingpong(int n, int step, int diff)
{
	// TODO: start your coding here

	int i=n;
	int count=0;
	int a=0,b=0;
	//int y =1;
	//counting length of a number
	for(;i!=0;count++){i=i/10;}
	//a number less than 10 is always ping pong number
	//cout<<count<<step;
	if((n>=0&&n<9)||step>count-1){return true;}

	//theoretical arrow
	//int y=count-step;
	/*for(int p =2;y+step<count;y++,p++)
	{if(y+step*p<count){y++;}}
	cout<<y;*/
	//from right to left
	for(int i=1;i+step<=count;i++){
		if(kth_digit_from_right(n,i)-kth_digit_from_right(n,i+step)==diff||kth_digit_from_right(n,i)-kth_digit_from_right(n,i+step)==-diff)
		{a++;}}
		//cout<< a;
	/*// from left to right
	for(int i=count;i-step>0;i--){
		if(kth_digit_from_right(n,i)-kth_digit_from_right(n,i-step)==diff||kth_digit_from_right(n,i)-kth_digit_from_right(n,i-step)==-diff)
		{b++;}}
		cout<< b;*/
		
		if(a==count-step){return true;}
	return false;
}
int main()
{
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Welcome to the Main program of Assignment 1" << endl;
	cout << "You can check whether your code works properly with our below examples" << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << boolalpha;
	cout << endl;
	cout << "1. Check whether a given number is a ping-pong number" << endl;
	cout << "Is 3 a ping-pong number: " << is_pingpong(3) << endl;
	cout << "Is 10 a ping-pong number: " << is_pingpong(10) << endl;
	cout << "Is 14 a ping-pong number: " << is_pingpong(14) << endl;
	cout << "Is 100 a ping-pong number: " << is_pingpong(100) << endl;
	cout << "Is 101 a ping-pong number: " << is_pingpong(101) << endl;
	cout << "Is 656787 a ping-pong number: " << is_pingpong(656787) << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "2. Print all the ping-pong numbers from 0 to 100" << endl;
	print_pingpong(0, 100);
	cout << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "3.1 Print the ping-pong histogram from 0 to 10000 with 5 bins" << endl;
	print_pingpong_histogram(0, 10000, 5, '*');
	cout << endl;
	cout << "3.2 Print the ping-pong histogram from 20 to 52 with 6 bins" << endl;
	print_pingpong_histogram(20, 52, 6, '#');
	cout << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "4. Find the k-th digit" << endl;
	cout << "The first digit of 76: " << kth_digit_from_right(76, 1) << endl;
	cout << "The 4-th digit of 654321: " << kth_digit_from_right(654321, 4) << endl;
	cout << "The 8-th digit of 30283: " << kth_digit_from_right(30283, 8) << endl;
	cout << "The (-2)-th digit of 30283: " << kth_digit_from_right(30283, -2) << endl;
	cout << "The (1)-th digit of 0: " << kth_digit_from_right(0, 1) << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "5. Check whether a given number is a (step, diff)-ping-pong number" << endl;
	cout << boolalpha;
	cout << "Is 3 a (2, 2)-ping-pong number: " << is_generalized_pingpong(3, 2, 2) << endl;
	cout << "Is 4455463 a (2, 1)-ping-pong number: " << is_generalized_pingpong(4455463, 2, 1) << endl;
	cout << "Is 4061806 a (2, 2)-ping-pong number: " << is_generalized_pingpong(4061806, 2, 2) << endl; 
	cout << "Is 79 a (1, 2)-ping-pong number: " << is_generalized_pingpong(79, 1, 2) << endl;
	cout << "Is 79 a (1, 3)-ping-pong number: " << is_generalized_pingpong(79, 1, 3) << endl;
	cout << "Is 100 a (1, 4)-ping-pong number: " << is_generalized_pingpong(100, 1, 4) << endl;
	cout << "Is 10101010 a (1, 1)-ping-pong number: " << is_generalized_pingpong(10101010, 1, 1) << endl;
	cout << "Is 10101010 a (2, 2)-ping-pong number: " << is_generalized_pingpong(10101010, 2, 3) << endl;
	cout << "Is 5544453 a (3, 1)-ping-pong number: " << is_generalized_pingpong(5544453, 3, 1) << endl;
	cout << "Is 79 a (2, 2)-ping-pong number: " << is_generalized_pingpong(79, 1, 3) << endl;
	cout << 
	"----------------------------------------------------------------------" << endl;

}
