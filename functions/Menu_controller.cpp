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

void goodbyeMessage() //exit message

/*  functions that control the position  */
void changePosition(char key, int &position);           //change arrows position from next position
void showNewPosition(int position);                     //prints arrows in current position
void removeLastPosition(int position);                  //removes the last position in which the arrow was

/*  functions that control the menu  */
void runPrincipalFunctions(char key, int position);     //principal function for show second menu
void showPrincipalMenu(int principal_secondary_menu);   //show principal menu, names of functions

/*  functions that control the pokedex information  */
void getInformationFromFile();                  //non-created function
void getInformationFromUser();                  //non-created function

int menu() {
    system ("CLS");
    char key;
    int position = 1;
    int timer = 100;
    int principal_secondary_menu = 0;

    showPrincipalMenu(principal_secondary_menu);
    while (true) {
        Sleep (15);
        showPosition(position);

        if (kbhit()) {
            removeLastPosition(position);

            key = getch(); //key detector
            changePosition(key, position);

            runFunction(key, position, principal_secondary_menu);

            showPosition(position);
            timer = 100;
        }
        if (timer == 0) {
            removeLastPosition(position);
            timer = 100;
            Sleep (500);
        }
        else timer -= 2;
    }
}


void showPrincipalMenu(int principal_secondary_menu) {
    system ("CLS");
    if (principal_secondary_menu == 0) {                //Principal Menu
        gotoxy (0 , 5);
        cout << "   ::::::::          ::::::::::       :::        :::::::::::       :::::::::           :::  \n ";
        Sleep(50);
        cout << " :+:    :+:         :+:              :+:            :+:           :+:    :+:        :+: :+: \n ";
        Sleep(50);
        cout << " +:+               +:+              +:+            +:+           +:+    +:+       +:+   +:+ \n ";
        Sleep(50);
        cout << " +#++:++#++       +#++:++#         +#+            +#+           +#++:++#+       +#++:++#++: \n ";
        Sleep(50);
        cout << "        +#+      +#+              +#+            +#+           +#+             +#+     +#+  \n ";
        Sleep(50);
        cout << "#+#    #+#      #+#              #+#            #+#           #+#             #+#     #+#   \n ";
        Sleep(50);
        cout << "########       ##########       ########## ###########       ###             ###     ###    \n ";

        gotoxy (60 , 22);
        cout << "   INGRESAR INFORMACION EN EL POKEDEX    ";
        Sleep(50);
        gotoxy (60 , 24);
        cout << "   MOSTRAR ESTADISTICAS DEL POKEDEX      ";
        Sleep(50);
        gotoxy (60 , 26);
        cout << "                  SALIR                  ";
    }
    else if(principal_secondary_menu == 1){             //Set information for pokedex (menu)
        gotoxy (60 , 22);
        cout << "   INGRESAR INFORMACION MANUALMENTE      ";
        Sleep(50);
        gotoxy (60 , 24);
        cout << "   INGRESAR INFORMACION DE UN ARCHIVO    ";
        Sleep(50);
        gotoxy (60 , 26);
        cout << "                 VOLVER                  ";
    }
    else if(principal_secondary_menu == 2){             //Stats from pokedex (menu)
        gotoxy (60 , 22);
        cout << "   MOSTRAR POKEMONS MAS FUERTES            ";
        Sleep(50);
        gotoxy (60 , 24);
        cout << "   MOSTRAR POKEMONS MAS DEBILES            ";
        Sleep(50);
        gotoxy (60 , 26);
        cout << "   MOSTRAR POKEMONS CON MAYOR NIVEL A 500  ";
    }
}

void changePosition(char key, int &position) {
    if (key == 'w' || key == (int) 72 || key == 'W') {
        if (position == 1) position = 3;
        else position --;
    }
    else if (key == 's' || key == (int) 80 || key == 'S') {
        if (position == 3) position = 1;
        else position ++;
    }
}

void showPosition(int position) {
    if (position == 1) {
        gotoxy (58 , 22);
        cout << (char) 175;
    }
    else if (position == 2) {
        gotoxy (58 , 24);
        cout << (char) 175;
    }
    else {
        gotoxy (58 , 26);
        cout << (char) 175;
    }
}

void removeLastPosition(int position) {
    if (position == 1)  {
        gotoxy (58 , 22);
        cout << " ";
    }
    else if (position == 2) {
        gotoxy (58 , 24);
        cout << " ";
    }
    else {
        gotoxy (58 , 26);
        cout << " ";
    }
}

void runPrincipalFunctions(char key, int position, int principal_secondary_menu) {
    if (key == (int) 13) {
        if (principal_secondary_menu == 0) {
            if (position == 1) showPrincipalMenu(principal_secondary_menu);
            else if (position == 2) showPokedexStatisticsMenu();
            else (position == 3) goodbyeMessage();
        }
        else if (principal_secondary_menu == 1) {
            if (position == 1) getInformationFromUser();
            else if (position == 2) getInformationFromFile();
            else (position == 3) showPrincipalMenu(0);
        }

    }
}

void goodbyeMessage(){
    cout << "CHAU PONEME UN 10";
}