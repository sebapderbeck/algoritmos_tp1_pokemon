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

void changePosition(char key, int &position); //change arrows position from next position
void showNewPosition(int position); //prints arrows in current position
void removeLastPosition(int position); //removes the last position in which the arrow was
void runFunction(char key, int position); //execute function
void showPrincipalMenu(); //show principal menu, names of functions
void showPokedexInformationMenu(); //show second menu for load data in pokedex

int menu (){
    system ("CLS");
    char key;
    int position = 1;
    int timer = 100;


    while (true){
        Sleep (15);
        showPosition(position);

        if (kbhit()){
            removeLastPosition(position);

            key = getch(); //key detector
            changePosition(key, position);

            runFunction(key, position);

            showPosition(position);
            timer = 100;
        }
        if (timer == 0){
            removeLastPosition(position);
            timer = 100;
            Sleep (500);
        }
        else timer -= 2;
    }
}
void showPokedexInformationMenu (){
    system ("CLS");
    gotoxy (60 , 22);
    cout << "   INGRESAR INFORMACION MANUALMENTE      ";
    Sleep(50);
    gotoxy (60 , 24);
    cout << "   INGRESAR INFORMACION DE UN ARCHIVO    ";
    Sleep(50);
    gotoxy (60 , 26);
    cout << "                  SALIR                  ";
}




void showPrincipalMenu (){
    system ("CLS");
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
    //Sleep(50);
    //gotoxy (60 , 28);
    //cout << "             ";
    //Sleep(50);
    //gotoxy (60 , 30);
    //cout << "             ";
    //Sleep(50);

}

void changePosition (char key, int &position){
    if ((key == 'w') || (key == (int) 72) || (key == 'W')){
        if (position == 0) position = 5;
        else position --;
    }
    else if ((key == 's') || (key == (int) 80) || (key == 'S')){
        if (position == 5) position = 0;
        else position ++;
    }
}

void showPosition (int position){
    if (position == 1){
        gotoxy (58 , 22);
        cout << (char) 175;
    }
    else if (position == 2){
        gotoxy (58 , 24);
        cout << (char) 175;
    }
    else if (position == 3){
        gotoxy (58 , 26);
        cout << (char) 175;
    }
    else if (position == 4){
        gotoxy (58 , 28);
        cout << (char) 175;
    }
    else if (position == 5){
        gotoxy (58 , 30);
        cout << (char) 175;
    }
    if (position == 0){
        gotoxy (58 , 20);
        cout << (char) 175;
    }
}

void removeLastPosition (int position){
    if (position == 1){
        gotoxy (58 , 22);
        cout << " ";
    }
    else if (position == 2){
        gotoxy (58 , 24);
        cout << " ";
    }
    else if (position == 3){
        gotoxy (58 , 26);
        cout << " ";
    }
    else if (position == 4){
        gotoxy (58 , 28);
        cout << " ";
    }
    else if (position == 5){
        gotoxy (58 , 30);
        cout << " ";
    }
    if (position == 0){
        gotoxy (58 , 20);
        cout << " ";
    }
}

void runFunction (char key, int position){
    if (key == (int) 13){
        if (position == 1) ShowPokedexInformationMenu();

        else if (position == 2){
        //funcion 2
        }
        else if (position == 3){
        //funcion 3
        }
        else if (position == 4){
        //funcion 4
        }
        else if (position == 5){
        //funcion 5
        }
        else if (position == 0){
        //funcion 0
        }
    }
}
