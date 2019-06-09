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

void changePosition(char tecla, int &posicion); //change arrows position from next position
void showNewPosition(int posicion); //prints arrows in current position
void removeLastPosition(int posicion); //removes the last position in which the arrow was
void runFunction(char tecla, int posicion); //execute function
void showPrincipalMenu(); //show principal menu, names of functions

int menu (){
    system ("CLS");
    char tecla;
    int posicion = 1;
    int temporizador = 100;


    while (true){
        Sleep (15);
        showPosition(posicion);

        if (kbhit()){
            removeLastPosition(posicion);

            tecla = getch(); //key detector
            changePosition(tecla, posicion);

            runFunction(tecla, posicion);

            showPosition(posicion);
            temporizador = 100;
        }
        if (temporizador == 0){
            removeLastPosition(posicion);
            temporizador = 100;
            Sleep (500);
        }
        else temporizador -= 2;
    }
}

void showPrincipalMenu()(){

    gotoxy (0 , 5);
    cout << "\n\n\t          ::::::::       ::::::::::       :::            ::::::::::       :::::::::       :::::::::           :::  \n";
    Sleep(50);
    cout << "\t        :+:    :+:      :+:              :+:            :+:                   :+:             :+:          :+: :+: \n";
    Sleep(50);
    cout << "\t       +:+             +:+              +:+            +:+                  +:+             +:+          +:+   +:+ \n";
    Sleep(50);
    cout << "\t      +#++:++#++      +#++:++#         +#+            +#++:++#            +#+             +#+          +#++:++#++: \n";
    Sleep(50);
    cout << "\t            +#+      +#+              +#+            +#+                +#+             +#+           +#+     +#+  \n";
    Sleep(50);
    cout << "\t    #+#    #+#      #+#              #+#            #+#               #+#             #+#            #+#     #+#   \n";
    Sleep(50);
    cout << "\t    ########       ##########       ##########     ##########       #########       #########       ###     ###    \n";

    gotoxy (60 , 22);
    cout << "   Nombre de funcion ";
    Sleep(50);
    gotoxy (60 , 24);
    cout << "   Nombre de funcion ";
    Sleep(50);
    gotoxy (60 , 26);
    cout << "  Nombre de funcion";
    Sleep(50);
    gotoxy (60 , 28);
    cout << " Nombre de funcion";
    Sleep(50);
    gotoxy (60 , 30);
    cout << " Nombre de funcion";
    Sleep(50);

}

void changePosition(char tecla, int &posicion){
    if ((tecla == 'w') || (tecla == (int) 72) || (tecla == 'W')){
        if (posicion == 0) posicion = 5;
        else posicion --;
    }
    else if ((tecla == 's') || (tecla == (int) 80) || (tecla == 'S')){
        if (posicion == 5) posicion = 0;
        else posicion ++;
    }
}

void showPosition(int posicion){
    if (posicion == 1){
        gotoxy (58 , 22);
        cout << (char) 175;
    }
    else if (posicion == 2){
        gotoxy (58 , 24);
        cout << (char) 175;
    }
    else if (posicion == 3){
        gotoxy (58 , 26);
        cout << (char) 175;
    }
    else if (posicion == 4){
        gotoxy (58 , 28);
        cout << (char) 175;
    }
    else if (posicion == 5){
        gotoxy (58 , 30);
        cout << (char) 175;
    }
    if (posicion == 0){
        gotoxy (58 , 20);
        cout << (char) 175;
    }
}

void removeLastPosition(int posicion){
    if (posicion == 1){
        gotoxy (58 , 22);
        cout << " ";
    }
    else if (posicion == 2){
        gotoxy (58 , 24);
        cout << " ";
    }
    else if (posicion == 3){
        gotoxy (58 , 26);
        cout << " ";
    }
    else if (posicion == 4){
        gotoxy (58 , 28);
        cout << " ";
    }
    else if (posicion == 5){
        gotoxy (58 , 30);
        cout << " ";
    }
    if (posicion == 0){
        gotoxy (58 , 20);
        cout << " ";
    }
}

void runFunction(char tecla, int posicion){
    if (tecla == (int) 13){
        if (posicion == 1){
        //funcion 1
        }
        else if (posicion == 2){
        //funcion 2
        }
        else if (posicion == 3){
        //funcion 3
        }
        else if (posicion == 4){
        //funcion 4
        }
        else if (posicion == 5){
        //funcion 5
        }
        else if (posicion == 0){
        //funcion 0
        }
    }
}
