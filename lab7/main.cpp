/*
 * File Created: Wednesday, 16th October 2019 1:46:18 pm
 * Code Skeleton
 * Author: 
 */

#include <iostream>
#include <cstring>
#include "lab7_functions.hpp"

using namespace std;
int main()
{
    char img_path[32]; //e.g. img1.txt
    cout << "Enter the input filename: "; cin >> img_path;
    ASCIIImage img;

    // read the image
    if(!read_image(img, img_path))
    {
        cerr << "Error: Reading image failed!"<<endl;
        return -1;
    }
    // print the image
    plot(img);

    int choice;
    do {
        char out_path[32]={0};
        cout << "1. Rotate clockwise\n" <<
                "2. Flip horizontally\n" <<
                "3. Exit" << endl;
        cout << "Which operation would you like to perform: ";
        cin >> choice;
        switch(choice)
        {
        case 1:
            rotate_clockwise(img);
            plot(img);
            strncpy(out_path, img_path, strlen(img_path)-4); //prefix
            strcat(out_path, "_rot");
            strcat(out_path, img_path + strlen(img_path)-4); //suffix
            write_image(img, out_path);
            cout << "Rotated image is saved in: " << out_path << endl;
            break;
        case 2:
            flip_horizontally(img);
            plot(img);
            strncpy(out_path, img_path, strlen(img_path)-4); //prefix
            strcat(out_path, "_flip");
            strcat(out_path, img_path + strlen(img_path)-4); //surfix
            write_image(img, out_path);
            cout << "Flipped image is saved in: " << out_path << endl;
        }
    }while(choice!=3);

    return 0;
}
