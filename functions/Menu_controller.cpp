int menu (){

    char tecla;
    int posicion = 1;
    int temporizador = 100;

    segundo_menu ();


    while (true){
        ocultar_cursor ();
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
        else if (posicion == 6){
            gotoxy (58 , 32);
            cout << (char) 175;
        }
        if (hay_partida == true){
            if (posicion == 0){
                gotoxy (58 , 20);
                cout << (char) 175;
            }
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
            else if (posicion == 6){
                gotoxy (58 , 32);
                cout << " ";
            }
            if (hay_partida == true){
                if (posicion == 0){
                    gotoxy (58 , 20);
                    cout << " ";
                }
            }
            tecla = getch();
            if ((tecla == 'w') || (tecla == (int) 72) || (tecla == 'W')){
                if (hay_partida == true){
                    if (posicion == 0){
                        posicion = 6;
                    }
                    else {
                        posicion --;
                    }
                }
                else if (posicion == 1){
                    posicion = 6;
                }
                else {
                    posicion --;
                }
            }
            else if ((tecla == 's') || (tecla == (int) 80) || (tecla == 'S')){
                if (hay_partida == true){
                    if (posicion == 6){
                        posicion = 0;
                    }
                    else {
                        posicion ++;
                    }
                }
                else if (posicion == 6){
                    posicion = 1;
                }
                else {
                    posicion ++;
                }
            }
            else if (tecla == (int) 13){
                if (posicion == 1){
                    crear_partida (lenguaje , mis_limites , mi_salud , mi_nave , mi_matriz, puntaje , mi_Partida);
                }
                else if (posicion == 2){
                    hay_partida = true;
                    abrir_partida (lenguaje ,mis_limites ,mi_salud ,mi_nave ,mi_matriz , puntaje, mi_Partida , hay_partida );
                }
                else if (posicion == 3){
                    guardar_Partida (mi_Partida , lenguaje , mi_salud , mi_nave , mi_matriz, puntaje);
                }
                else if (posicion == 4){
                    informacion_basica (lenguaje , hay_partida);
                }
                else if (posicion == 5){
                    partidas (lenguaje , mis_limites , mi_salud , mi_nave , mi_matriz , puntaje , mi_Partida , hay_partida);
                }
                else if (posicion == 6){
                    tutorial (lenguaje , mis_limites , mi_salud , mi_nave , mi_matriz, puntaje , mi_Partida);
                }
                else if (posicion == 0){
                    system ("CLS");
                    return 0;
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
            else if (posicion == 6){
                gotoxy (58 , 32);
                cout << (char) 175;
            }
            if (hay_partida == true){
                if (posicion == 0){
                    gotoxy (58 , 20);
                    cout << (char) 175;
                }
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
            else if (posicion == 6){
                gotoxy (58 , 32);
                cout << " ";
            }
            if (hay_partida == true){
                if (posicion == 0){
                    gotoxy (58 , 20);
                    cout << " ";
                }
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
        cout << "   CREAR PARTIDA";
        Sleep(50);
        gotoxy (60 , 24);
        cout << "   ABRIR PARTIDA";
        Sleep(50);
        gotoxy (60 , 26);
        cout << "  GUARDAR PARTIDA";
        Sleep(50);
        gotoxy (60 , 28);
        cout << " INFORMACION BASICA";
        Sleep(50);
        gotoxy (60 , 30);
        cout << " PARTIDAS GUARDADAS";
        Sleep(50);
        gotoxy (60 , 32);
        cout << "     TUTORIAL";

}