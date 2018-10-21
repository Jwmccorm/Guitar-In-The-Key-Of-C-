#include <iostream>
#include<string>
#include"fileImport.h"
#include"guitar.h"
#pragma comment(lib, "Winmm.lib")
#include<Windows.h>
#include <cstdlib>

using namespace std;

int main(){
    int FS = fileSize();
    string openingImport[6];

    readFile(openingImport);
    for(int i = 0 ; i < 6; i++){
        cout << openingImport[i] << endl;
    }

    GUITARPTR newFender = createGuitar();
    addNotes(newFender, openingImport, FS);
    //printGuitar(newFender);
    playGuitar(newFender);


    getchar();


}
