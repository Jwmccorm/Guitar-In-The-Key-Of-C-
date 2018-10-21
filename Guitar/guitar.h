#include<iostream>
#include<stdlib.h>
#include"stack.h"
#include"utils.h"
#include<Windows.h>
#include<thread>
#pragma comment(lib, "Winmm.lib")

typedef struct guitarStruct{
    STACKPTR e;
    STACKPTR B;
    STACKPTR G;
    STACKPTR D;
    STACKPTR A;
    STACKPTR E;

}GUITAR;
void printPirate();
typedef GUITAR* GUITARPTR;
int arraySize(string dataRef);
string noteMatch(char noteRef);
void notePush(GUITARPTR, int, char);
void playNotes(GUITARPTR stackRef);
string wavPlayFormat(STACKPTR stackRef);
void addNotes(GUITARPTR guitarRef, string dataRef[], int);

GUITARPTR createGuitar(){
    GUITARPTR newGuitar = (GUITARPTR)malloc(sizeof(GUITAR));
    newGuitar->e = createNotes('e');
    newGuitar->B = createNotes('B');
    newGuitar->G = createNotes('G');
    newGuitar->D = createNotes('D');
    newGuitar->A = createNotes('A');
    newGuitar->E = createNotes('E');
    return newGuitar;
}


//  TODO add one more level for each 6 segment. Function to check for spaces
//      Idea -> Check for count of '-' and determin if real line, otherwise skip
void addNotes(GUITARPTR guitarRef, string dataRef[], int length){
    int guitarStrings = 6;
    int counter = arraySize(dataRef[0]);
    string matcher = "";
    bool skiper = true;
    cout << "Made it";
    for (int i = 0 ; i < guitarStrings; i++){
        for (int j = counter ; j > 0  ; j--){
            matcher =noteMatch(dataRef[i][j]);
            if (dataRef[i][j] == '|'){
                skiper = true;
                continue;
            }
            if (matcher == "NOTE"){
                notePush(guitarRef, i,dataRef[i][j]);

                cout << dataRef[i][j];
                }else if (matcher == "STYLE" && !skiper){
                    notePush(guitarRef, i, '-');
                    cout << '-';
                }else if (skiper){
                    skiper = false;
                    //cout << "n";
                }

            }cout << endl;
        } cout << endl;
}




int arraySize(string dataRef){
    int counter = 0;
    while(dataRef[counter++] != '\0');
    //      count - 1 to catch the new line
    return counter - 1;
}

//  TODO make it do longer notes
//      Will have to change lots
string noteMatch(char noteRef){

    switch (noteRef){
    case('0'):
    case('1'):
    case('2'):
    case('3'):
    case('4'):
    case('5'):
    case('6'):
    case('7'):
    case('8'):
    case('9'):
        return "NOTE";
        break;
    case('-'):
    case('/'):
    case('h'):
    case('^'):
    case('p'):
    case('b'):
        return "STYLE";
        break;
    default:
    return "JUNK";
    }
}


void notePush(GUITARPTR guitarRef, int position, char note){

    switch (position){
    case(0):
        push(guitarRef->e, note);
        break;
    case(1):
        push(guitarRef->B, note);
        break;
    case(2):
        push(guitarRef->G, note);
        break;
    case(3):
        push(guitarRef->D, note);
        break;
    case(4):
        push(guitarRef->A, note);
        break;
    case(5):
        push(guitarRef->E, note);
        break;
    }
}

void printGuitar(GUITARPTR guitarRef){
    //      TODO Why does A have shortness?
    NODEPTR eRef = guitarRef->e->top;
    NODEPTR BRef = guitarRef->B->top;
    NODEPTR GRef = guitarRef->G->top;
    NODEPTR DRef = guitarRef->D->top;
    NODEPTR ARef = guitarRef->A->top;
    NODEPTR ERef = guitarRef->E->top;

    while(ERef != NULL ){
        cout << eRef->note;
        cout << BRef->note;
        cout << GRef->note;
        cout << DRef->note;
        cout << ARef->note;
        cout << ERef->note;
        eRef = eRef->next;
        BRef = BRef->next;
        GRef = GRef->next;
        DRef = DRef->next;
        ARef = ARef->next;
        ERef = ERef->next;
        cout << endl;
    }
}

void playGuitar(GUITARPTR guitarRef){
    NODEPTR eRef = guitarRef->e->top;
    NODEPTR BRef = guitarRef->B->top;
    NODEPTR GRef = guitarRef->G->top;
    NODEPTR DRef = guitarRef->D->top;
    NODEPTR ARef = guitarRef->A->top;
    NODEPTR ERef = guitarRef->E->top;
    while(eRef != NULL&&BRef != NULL &&GRef != NULL &&DRef != NULL &&ARef != NULL&&ERef != NULL ){
        playNotes(guitarRef);
        pop(guitarRef->e);
        pop(guitarRef->B);
        pop(guitarRef->G);
        pop(guitarRef->D);
        pop(guitarRef->A);
        pop(guitarRef->E);


        eRef = eRef->next;
        BRef = BRef->next;
        GRef = GRef->next;
        DRef = DRef->next;
        ARef = ARef->next;
        ERef = ERef->next;
    }
}

    int count = 0 ;


void playNotes(GUITARPTR guitarRef){

    string stackRefsArray[6] = {
        wavPlayFormat(guitarRef->e),
        wavPlayFormat(guitarRef->B),
        wavPlayFormat(guitarRef->G),
        wavPlayFormat(guitarRef->D),
        wavPlayFormat(guitarRef->A),
        wavPlayFormat(guitarRef->E)};
    STACKPTR stringNotesRef[6] = {
        guitarRef->e,
        guitarRef->B,
        guitarRef->G,
        guitarRef->D,
        guitarRef->A,
        guitarRef->E};
    string combo;
    string opening = "open ";
    string typeSet = " type mpegvideo alias mp";
    for (int i = 0; i<6; i++){
       if (stringNotesRef[i]->top->note != '-'){
            string closeRef = "close mp";
            closeRef += i + '0';
            mciSendString(&closeRef[0], NULL, 0, NULL);
            cout <<"test";
            Sleep(300);
        }
    }


    for (int i = 0; i<6 ; i++){

        combo = opening;
        combo +=stackRefsArray[i];
        combo += typeSet;
        combo += '0' + i;
        char* inter = &combo[0];
        mciSendString(inter, NULL, 0, NULL);
        //cout << combo << endl;
        //cout << stackRefsArray[i] << endl;
    }

    mciSendString("play mp0", NULL, 0, NULL);
    mciSendString("play mp1", NULL, 0, NULL);
    mciSendString("play mp2", NULL, 0, NULL);
    mciSendString("play mp3", NULL, 0, NULL);
    mciSendString("play mp4", NULL, 0, NULL);
    mciSendString("play mp5", NULL, 0, NULL);
    cout <<"test";
    Sleep(300);



}


string wavPlayFormat(STACKPTR stackRef){
    string noteLocation = "Wav\\";
    char noteRef = stackRef->top->note;
    char positionRef = stackRef->position;
    string fileType = ".wav";
    stringstream C1, C2;

    noteLocation += positionRef;
    if (positionRef == 'E'){
        noteLocation += noteRef;
        noteLocation += "-2";

    }else{
        noteLocation += noteRef;

    }
    noteLocation += fileType;

    char* finalLocation = &noteLocation[0];
    return noteLocation;
}

void printPirate(){

    cout << "                                                                       " << endl;
    cout << "                            .xm*f``??T?@hc.				" << endl;
    cout << "                          z@`` `~((!!!!!!!?*m.				" << endl;
    cout << "                        z$$$K   ~~(/!!!!!!!!!Mh			" << endl;
    cout << "                      .f` `#$k``~~\!!!!!!!!!!!MMc			" << endl;
    cout << "                     :`     f*! ~:~(!!!!!!!!!!XHMk			" << endl;
    cout << "                     f      ` %n:~(!!!!!!!!!!!HMMM.			" << endl;
    cout << "                    d          X~!~(!!!!!!!X!X!SMMR			" << endl;
    cout << "                    M :   x::  :~~!>!!!!!!MNWXMMM@R			" << endl;
    cout << " n                  E ` *  ueeeeiu(!!XUWWWWWXMRHMMM>                :. " << endl;
    cout << " E%                 E  8 .$$$$$$$$K!!$$$$$$$$&M$RMM>               :`5 " << endl;
    cout << "z  %                3  $ 4$$$$$$$$!~!*$$$$$$$$!$MM$               :` ` " << endl;
    cout << "K   `:              ?> # `#$$$$$#~!!!!TR$$$$$R?@MME              z   R " << endl;
    cout << "?     %.             5     ^```~~~:XW!!!!T?T!XSMMM~            :^    J " << endl;
    cout << " `.    ^s             ?.       ~~d$X$NX!!!!!!M!MM             f     :~ " << endl;
    cout << "  `+.    #L            *c:.    .~`?!??!!!!!XX@M@~           z`    .*	" << endl;
    cout << "    `+     %L           #c``!+~~~!/!!!!!!@*TM8M           z`    .~	" << endl;
    cout << "      `:    `%.         `C*X  .!~!~!!!!!X!!!@RF         .#     +	" << endl;
    cout << "        `:    ^%.        9-MX!X!!X~H!!M!N!X$MM        .#`    +`	" << endl;
    cout << "          #:    `n       `L`!~M~)H!M!XX!$!XMXF      .+`   .z`		" << endl;
    cout << "            #:    `:      R *H$@@$H$*@$@$@$%M~     z`    +`		" << endl;
    cout << "              %:   `*L    `k` M!~M~X!!$!@H!tF    z`    z`		" << endl;
    cout << "                *:   ^*L   `k ~~~!~!!!!!M!X*   z*   .+`		" << endl;
    cout << "                  `s   ^*L  `%:.~~~:!!!!XH`  z#   .*`			" << endl;
    cout << "                    #s   ^%L  ^`#4@UU@##`  z#   .*`			" << endl;
    cout << "                      #s   ^%L           z#   .r`			" << endl;
    cout << "                        #s   ^%.       u#   .r`			" << endl;
    cout << "                          #i   `%.   u#   .@`				" << endl;
    cout << "                            #s   ^%u#   .@`				" << endl;
    cout << "                              #s x#   .*`				" << endl;
    cout << "                               x#`  .@%.				" << endl;
    cout << "                             x#`  .d`  `%.				" << endl;
    cout << "                           xf~  .r` #s   `%.				" << endl;
    cout << "                     u   x*`  .r`     #s   `%.  x.			" << endl;
    cout << "                     %Mu*`  x*`         #m.  `%zX`			" << endl;
    cout << "                     :R(h x*              `h..*dN.			" << endl;
    cout << "                   u@NM5e#>                 7?dMRMh.			" << endl;
    cout << "                 z$@M@$#`#`                 *``*@MM$hL			" << endl;
    cout << "               u@@MM8*                          `*$M@Mh.		" << endl;
    cout << "             z$RRM8F`                             `N8@M$bL		" << endl;
    cout << "            5`RM$#                                  `R88f)R		" << endl;
    cout << "            `h.$`                                     #$x*		" << endl;



}
