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

int menu (){
    system ("CLS");
    char tecla;
    int posicion = 1;
    int temporizador = 100;


    while (true){
        Sleep (15);
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
        if (kbhit()){
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
            tecla = getch();
            changePosition(tecla);

            else if (tecla == (int) 13){
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
                    //system ("CLS");
                    //return 0;
                }
            }
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
            else if (posicion == 0){
                gotoxy (58 , 20);
                cout << (char) 175;
            }
            temporizador = 100;
        }
        if (temporizador == 0){
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
            temporizador = 100;
            Sleep (500);
        }
        else {
            temporizador -= 2;
        }
    }
}

void segundo_menu(){

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

void changePosition(string tecla, int &posicion){
    if ((tecla == 'w') || (tecla == (int) 72) || (tecla == 'W')){
        if (posicion == 0) posicion = 5;
        else posicion --;
    }
    else if ((tecla == 's') || (tecla == (int) 80) || (tecla == 'S')){
        if (posicion == 5) posicion = 0;
        else posicion ++;
    }
}