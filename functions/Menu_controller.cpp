//
// Created by sopderbeck on 5/6/2019.
//
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

void gotoxy(int x,int y); //set cursor in position(x,y) into terminal

void hideCursor();

void goodbyeMessage(); //exit message

/*  functions that control the position  */
void changePosition(char key, int &position);           //change arrows position from next position
void showNewPosition(int position);                     //prints arrows in current position
void removeLastPosition(int position);                  //removes the last position in which the arrow was

/*  functions that control the menu  */
void runPrincipalFunctions(char key, int position, int &principal_secondary_menu);     //principal function for show second menu
void showPrincipalMenu(int principal_secondary_menu);                                 //show principal menu, names of functions
void showHeaderMenu(int principal_secondary_menu);                                    //show last menu for know where are you from

/*  functions that control the pokedex information  */
void getInformationFromFile();                  //function get information from file
void showMenuToEnterInformationFromUser();      //function get information from user, ask how many records do you want to load

/* functios that control pokemons stats */
void showPokemonsGroupByType(); //function show all types of pokemons order by type

void showPokemonsGroupByMaxLevel();
void showPokemonsGroupByMinLevel();
void showPokemonsGroupByLevel();

void showPokemonsWithHighestLevel();
void showPokemonWithLessLevel();

int main() {
    system ("CLS");
    system("color 07");
    char key;
    int position = 1;
    int timer = 100;
    int principal_secondary_menu = 0;
    showPrincipalMenu(principal_secondary_menu);

    while (true) {
        hideCursor();
        Sleep (15);
        showNewPosition(position);

        if (kbhit()) {
            removeLastPosition(position);

            key = getch(); //key detector

            changePosition(key, position);

            runPrincipalFunctions(key, position, principal_secondary_menu);

            showNewPosition(position);
            timer = 100;
        }
        if (timer == 0) {
            removeLastPosition(position);
            timer = 100;
            Sleep (500);
        }
        else timer -= 2;
    }
    return 0;
}


void showPrincipalMenu(int principal_secondary_menu) {
    system ("CLS");
    if (principal_secondary_menu == 0) {                //Principal Menu
        gotoxy (30 , 5);
        cout << "   ::::::::          ::::::::::       :::        :::::::::::       :::::::::           :::  \n ";
        Sleep(50);
        gotoxy (30 , 6);
        cout << " :+:    :+:         :+:              :+:            :+:           :+:    :+:        :+: :+: \n ";
        Sleep(50);
        gotoxy (30 , 7);
        cout << " +:+               +:+              +:+            +:+           +:+    +:+       +:+   +:+ \n ";
        Sleep(50);
        gotoxy (30 , 8);
        cout << " +#++:++#++       +#++:++#         +#+            +#+           +#++:++#+       +#++:++#++: \n ";
        Sleep(50);
        gotoxy (30 , 9);
        cout << "        +#+      +#+              +#+            +#+           +#+             +#+     +#+  \n ";
        Sleep(50);
        gotoxy (30 , 10);
        cout << "#+#    #+#      #+#              #+#            #+#           #+#             #+#     #+#   \n ";
        Sleep(50);
        gotoxy (30 , 11);
        cout << "########       ##########       ########## ###########       ###             ###     ###    \n ";

        gotoxy (32 , 22);
        cout << "   INGRESAR INFORMACION EN EL POKEDEX    ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "    MOSTRAR ESTADISTICAS DEL POKEDEX     ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                  SALIR                  ";
    }
    else if(principal_secondary_menu == 1){             //Set information for pokedex (menu)
        showHeaderMenu(principal_secondary_menu);
        gotoxy (32 , 22);
        cout << "    INGRESAR INFORMACION MANUALMENTE     ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   INGRESAR INFORMACION DE UN ARCHIVO    ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                 VOLVER                  ";
    }
    else if(principal_secondary_menu == 2){             //Stats from pokedex (menu)
        showHeaderMenu(principal_secondary_menu);
        gotoxy (32 , 22);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS POR TIPO  ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS POR NIVEL ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "   MOSTRAR POKEMONS DEVIDIDO POR NIVEL    "; //Higher level and lower level
    }
    else if(principal_secondary_menu == 22){             //Stats from pokedex ( sub menu from show pokemons group by level)
        showHeaderMenu(principal_secondary_menu);
        gotoxy (32 , 22);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS CON NIVEL MAYOR A 500 ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS CON NIVEL MENOR A 500 ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS CON NIVEL IGUAL A 500  "; //Higher level and lower level
    }
    else if(principal_secondary_menu == 23){             //Stats from pokedex ( sub menu from show pokemons group by type )
        showHeaderMenu(principal_secondary_menu);
        gotoxy (32 , 22);
        cout << "   MOSTRAR POKEMONS CON MAYOR NIVEL POR TIPO "; // Higher level
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR POKEMONS CON MENOR NIVEL POR TIPO "; // lower level
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                   VOLVER                    "; // back to stats menu
    }
}

void changePosition(char key, int &position) {
    if (key == 'w' || key == (int) 72 || key == 'W') {
        if (position == 1) position = 3;
        else position --;
    }
    else if (key == 's' || key == (int) 80 || key == 'S') {
        if (position == 3) position = 1;
        else position++;
    }
}

void showNewPosition(int position) {
    if (position == 1) gotoxy (30 , 22);
    else if (position == 2) gotoxy (30 , 24);
    else if (position == 3) gotoxy (30 , 26);
    else if (position == 4) gotoxy (30 , 28);
    cout << (char) 175;
}

void removeLastPosition(int position) {
    if (position == 1) gotoxy (30 , 22);
    else if (position == 2) gotoxy (30 , 24);
    else if (position == 3) gotoxy (30 , 26);
    else if (position == 4) gotoxy (30 , 28);
    cout << " ";
}

void showHeaderMenu(int principal_secondary_menu) {
    if (principal_secondary_menu == 1){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (45 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (45 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "INFORMACION EN EL POKEDEX";
    }
    else if (principal_secondary_menu == 11){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (64 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (64 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "INGRESAR INFORMACION DEL POKEDEX MANUALMENTE";
    }
    else if (principal_secondary_menu == 2){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (44 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (44 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "ESTADISTICAS DEL POKEDEX";
    }
    else if (principal_secondary_menu == 22){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (50 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (50 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "CANTIDAD DE POKEMONS POR NIVEL";
    }
    else if (principal_secondary_menu == 23){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (50 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (50 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "POKEMONS DEVIDIDO POR NIVEL";
    }
}

void runPrincipalFunctions(char key, int position, int &principal_secondary_menu) {
    if (key == (int) 13) { //enter key
        if (principal_secondary_menu == 0) {
            if (position == 1) showPrincipalMenu(position);
            else if (position == 2) showPrincipalMenu(position);
            else if (position == 3) goodbyeMessage();  //close program
        }
        else if (principal_secondary_menu == 1) {
            if (position == 1) showMenuToEnterInformationFromUser();
            else if (position == 2) getInformationFromFile();
            else if (position == 3) showPrincipalMenu(0);   //back to principal menu
        }
        else if (principal_secondary_menu == 2) {
            if (position == 1) showPokemonsGroupByType();  // show Pokemons Group By Type
            else if (position == 2) showPrincipalMenu(22); // show Pokemons Group By Level
            else if (position == 3) showPrincipalMenu(23); // show Pokemons divided by level
        }
        else if (principal_secondary_menu == 22) {
            if (position == 1) showPokemonsGroupByMaxLevel();      // show Pokemons Group By Max level, more than 500
            else if (position == 2) showPokemonsGroupByMinLevel(); // show Pokemons Group By Min level, less than 500
            else if (position == 3) showPokemonsGroupByLevel();    // show Pokemons Group By level equals to 500
            else if (position == 4) showPrincipalMenu(2);
        }
        else if (principal_secondary_menu == 23) {
            if (position == 1) showPokemonsWithHighestLevel();  // Show pokemon with the highest level
            else if (position == 2) showPokemonWithLessLevel(); // Show the pokemon with less level
            else if (position == 3) showPrincipalMenu(2);
        }
    }
    else if (key == (int) 27) { //escape key}
        if (principal_secondary_menu == 1) goodbyeMessage();
        else if (principal_secondary_menu == 1 || principal_secondary_menu == 2) showPrincipalMenu(0);
        else if (principal_secondary_menu == 22 || principal_secondary_menu == 23) showPrincipalMenu(2);
    }
}

void gotoxy(int x,int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void hideCursor() {
    HANDLE hCon;
    hCon = GetStdHandle (STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = false;
    SetConsoleCursorInfo (hCon , &cci);
}

void goodbyeMessage() {
    system("CLS");
    gotoxy(30,5);
    cout << "CHAU PONEME UN 10";
    exit(0);
}

void getInformationFromFile() {
    ifstream filePokedex; //created object filePokedex of type ifstream
    int lenght = 500;     //file size
    char * buffer = new char [lenght]; //variable temporal
    filePokedex.open("pokedex.dat", ios::in | ios::binary); //open file

    while(!filePokedex.eof()) {
        filePokedex.read(buffer, lenght);
    }
    filePokedex.close();
}

void showMenuToEnterInformationFromUser() {

}

void showPokemonsGroupByType() {

}
void showPokemonsGroupByMaxLevel() {

}

void showPokemonsGroupByMinLevel() {
}

void showPokemonsGroupByLevel() {
}

void showPokemonsWithHighestLevel() {
}

void showPokemonWithLessLevel() {
}
