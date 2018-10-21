#include<iostream>
#include<stdlib.h>
#include <fstream>
#include<string>
#include<sstream>
#include<stdio.h>
#include<iterator>

using namespace std;


//      Takes in array and alters it based on the data in the file
void readFile(string data[]){
    ifstream file("data.txt");
    int counter = 0;
    string tempStr = "";
    while (file >> tempStr){
        data[counter++ % 6] += tempStr;
    };
}


//      File size is a function so the program can scale to any size file.
int fileSize(){
    ifstream myfile("data.txt");
    int counter = 0;
    string lineTracker;
    //      More focused on getting the line count on this function the returning that.
    while (getline(myfile, lineTracker)){counter++;};
    return counter;
}


