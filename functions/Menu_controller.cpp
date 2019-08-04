//
// Created by sopderbeck on 5/6/2019.
//
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <regex>
#include <string>

using namespace std;

struct tPokemon {
    string type;
    int level;
    string name;
};

void gotoxy(int x, int y); //set cursor in position(x,y) into terminal

void hideCursor();
void showCursor();

/*  functions that animate the system  */
void showLoadingBar(); // laoding bar
void goodbyeMessage();    //exit message
void initialAnimation();  //animation

/*  functions that control the position  */
void resetPosition(int &position);                      //reset cursor position to initial position
void changePosition(char key, int &position);           //change arrows position from next position
void showNewPosition(int position);                     //prints arrows in current position
void removeLastPosition(int position);                  //removes the last position in which the arrow was

/*  functions that control the menu  */
void runPrincipalFunctions(char key, int &position, int &menu_selector,tPokemon rPokemon[], int &current_register_length);     //principal function for show second menu
void showPrincipalMenu(int menu_selector);                                   //show principal menu, names of functions
void showHeaderMenu(int menu_selector);                                      //show last menu for know where are you from

/*  functions that control the pokedex information  */
void getInformationFromFile(tPokemon rPokemon[], int &current_register_length);                            //function load information from file
void ShowTemplateToEnterNameFromFile(char * name_file);                                                                 // function that show text to enter the name of file
void enterInformationIntoFile(tPokemon rPokemon[], int current_register_length);                          //function that enter information
void showMenuToEnterInformationFromUser(tPokemon rPokemon[], int &current_register_length);               //function get information from user, ask how many records do you want to load
void showTemplateToEnterInformationFromUser(tPokemon rPokemon[], int current_register_length);  //function that assigns the information to the struct
void showHeaderQuantityRemainsToEnter(int current_quantity, int quantity_limit_pokemons); //header that show how quantity remains to enter

/* functios that control pokemons stats */
void showPokemonsGroupByType(); //function show all types of pokemons order by type

void showPokemonsGroupByMaxLevel();
void showPokemonsGroupByMinLevel();
void showPokemonsGroupByLevel();

void showPokemonsWithHighestLevel();
void showPokemonWithLessLevel();
void cantOfPokemonsPerType(tPokemon rPokemon[], int current_register_length); //Da la cantidad de pokemones por tipo
void showCantOfPokemonsPerType(int contador_tierra, int contador_fuego, int contador_agua, int contador_electrico); //muestra los contadores
void promLevelPerType(tPokemon rPokemon[], int current_register_length); //calcula el promedio de niveles por tipo
void showPromLevelPerType(int promedio_tierra, int promedio_fuego, int promedio_agua, int promedio_electrico); //muestra los promedios de niveles por tipo

/*functions that validate user data enter */
bool isValidNumber(int number); //function that validate number
int isValidLetter(string letter);       //function that validate key
bool isValidName (string name);      //function thar validate the name


int main() {
    system("color 07");//Black background Color and white Text Color
    showLoadingBar();
    int current_register_length = 0;
    tPokemon rPokemon[50];
    char key;
    int position = 1;
    int timer = 100;
    int menu_selector = 0;
    showPrincipalMenu(menu_selector);

    while (true){
        hideCursor();
        Sleep (15);
        showNewPosition(position);

        if (kbhit()){
            removeLastPosition(position);

            key = getch(); //key detector

            changePosition(key, position);

            runPrincipalFunctions(key, position, menu_selector, rPokemon, current_register_length);

            showNewPosition(position);
            timer = 100;
        }
        if (timer == 0){
            removeLastPosition(position);
            timer = 100;
            Sleep (500);
        }
        else timer -= 2;
    }
    return 0;
}
void initialAnimation() {
    gotoxy (15 , 5);
    cout << "   ::::::::          ::::::::::       :::        :::::::::::       :::::::::       :::::::::::  \n ";
    Sleep(100);
    gotoxy (15 , 6);
    cout << " :+:    :+:         :+:              :+:            :+:           :+:    :+:          :+: \n ";
    Sleep(100);
    gotoxy (15 , 7);
    cout << " +:+               +:+              +:+            +:+           +:+    +:+          +:+ \n ";
    Sleep(100);
    gotoxy (15 , 8);
    cout << " +#++:++#++       +#++:++#         +#+            +#+           +#++:++#+           +#+ \n ";
    Sleep(100);
    gotoxy (15 , 9);
    cout << "        +#+      +#+              +#+            +#+           +#+                 +#+  \n ";
    Sleep(100);
    gotoxy (15 , 10);
    cout << "#+#    #+#      #+#              #+#            #+#           #+#                 #+#   \n ";
    Sleep(100);
    gotoxy (15 , 11);
    cout << "########       ##########       ##########  ###########      ###              ###########    \n ";
}

void showPrincipalMenu(int menu_selector) {
    system ("CLS");
    if (menu_selector == 0){                //Principal Menu
        initialAnimation();
        gotoxy (32 , 22);
        cout << "   INGRESAR INFORMACION EN EL POKEDEX    ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "    MOSTRAR ESTADISTICAS DEL POKEDEX     ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                  SALIR                  ";
    }
    else if(menu_selector == 1){             //Set information for pokedex (menu)
        showHeaderMenu(menu_selector);
        Sleep(50);
        gotoxy (32 , 22);
        cout << "    INGRESAR INFORMACION MANUALMENTE     ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "    CARGAR INFORMACION DE UN ARCHIVO    ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                 VOLVER                  ";
    }
    else if(menu_selector == 2){             //Stats from pokedex (menu)
        showHeaderMenu(menu_selector);
        Sleep(50);
        gotoxy (32 , 22);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS POR TIPO  ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS POR NIVEL ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "   MOSTRAR POKEMONS DEVIDIDO POR NIVEL    "; //Higher level and lower level
    }
    else if(menu_selector == 22){             //Stats from pokedex ( sub menu from show pokemons group by level)
        showHeaderMenu(menu_selector);
        Sleep(50);
        gotoxy (32 , 22);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS CON NIVEL MAYOR A 500 ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS CON NIVEL MENOR A 500 ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "   MOSTRAR CANTIDAD DE POKEMONS CON NIVEL IGUAL A 500 "; //Higher level and lower level
    }
    else if(menu_selector == 23){             //Stats from pokedex ( sub menu from show pokemons group by type )
        showHeaderMenu(menu_selector);
        gotoxy (32 , 22);
        cout << "   MOSTRAR POKEMONS MAS PODEROSOS POR TIPO "; // Higher level
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR POKEMONS MAS DEBILES POR TIPO   ";   // lower level
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                  VOLVER                   "; // back to stats menu
    }
}

void resetPosition(int &position) {
    position = 1;
}

void changePosition(char key, int &position) {
    if (key == 'w' || key == (int) 72 || key == 'W') position = (position == 1) ? 3 : position - 1;
    else if (key == 's' || key == (int) 80 || key == 'S') position = (position == 3) ? 1 : position + 1;
}

void showNewPosition(int position) {
    if (position == 1) gotoxy (30 , 22);
    else if (position == 2) gotoxy (30 , 24);
    else if (position == 3) gotoxy (30 , 26);
    cout << (char) 175;
}

void removeLastPosition(int position) {
    if (position == 1) gotoxy (30 , 22);
    else if (position == 2) gotoxy (30 , 24);
    else if (position == 3) gotoxy (30 , 26);
    cout << " ";
}

void showHeaderMenu(int menu_selector) {
    system("CLS");
    if (menu_selector == 1){
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
    else if (menu_selector == 11){
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
    else if (menu_selector == 12){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (52 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (52 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "CARGAR INFORMACION DE UN ARCHIVO";
    }
    else if (menu_selector == 2){
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
    else if (menu_selector == 22){
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
    else if (menu_selector == 23){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (47 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (47 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "POKEMONS DIVIDIDO POR NIVEL";
    }
}

void runPrincipalFunctions(char key, int &position, int &menu_selector, tPokemon rPokemon[], int &current_register_length) {
    if (key == (int) 13){  //enter key
        if (menu_selector == 0){
            if (position == 1){
                menu_selector = 1;
                showPrincipalMenu(menu_selector);
            }
            else if (position == 2){
                menu_selector = 2;
                showPrincipalMenu(menu_selector);
            }
            else if (position == 3) goodbyeMessage();  //close program
        }
        else if (menu_selector == 1){
            if (position == 1) showMenuToEnterInformationFromUser(rPokemon, current_register_length);
            else if (position == 2) getInformationFromFile(rPokemon, current_register_length);
            else if (position == 3){
                menu_selector = 0;
                showPrincipalMenu(menu_selector); //back to principal menu
            }
        }
        else if (menu_selector == 2){
            if (position == 1) cantOfPokemonsPerType(rPokemon, current_register_length);  // show Pokemons Group By Type
            else if (position == 2){
                menu_selector = 22;
                showPrincipalMenu(menu_selector); // show Pokemons Group By Level
            }
            else if (position == 3){
                menu_selector = 23;
                showPrincipalMenu(menu_selector); // show Pokemons divided by level
            }
        }
        else if (menu_selector == 22){
            if (position == 1) showPokemonsGroupByMaxLevel();      // show Pokemons Group By Max level, more than 500
            else if (position == 2) showPokemonsGroupByMinLevel(); // show Pokemons Group By Min level, less than 500
            else if (position == 3) showPokemonsGroupByLevel();    // show Pokemons Group By level equals to 500
            else if (position == 4){
                menu_selector = 2;
                showPrincipalMenu(menu_selector);
            }
        }
        else if (menu_selector == 23){
            if (position == 1) showPokemonsWithHighestLevel();  // Show pokemon with the highest level
            else if (position == 2) showPokemonWithLessLevel(); // Show the pokemon with less level
            else if (position == 3){
                menu_selector = 2;
                showPrincipalMenu(menu_selector);
            }
        }
        resetPosition(position);
    }
    if (key == (int) 27){ // escape key
        if (menu_selector == 0) goodbyeMessage();
        else if (menu_selector == 1 || menu_selector == 2){
            menu_selector = 0;
            showPrincipalMenu(menu_selector);
        }
        else if (menu_selector == 22 || menu_selector == 23){
            menu_selector = 2;
            showPrincipalMenu(menu_selector);
        }
        resetPosition(position);
    }

}

void gotoxy(int x,int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon , dwPos);
}

void hideCursor() {
    HANDLE hCon;
    hCon = GetStdHandle (STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = false;
    SetConsoleCursorInfo(hCon , &cci);
}

void showCursor() {
    HANDLE hCon;
    hCon = GetStdHandle (STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = true;
    SetConsoleCursorInfo (hCon , &cci);
}

void goodbyeMessage() {
    system("CLS");
    exit(0);
}

void ShowTemplateToEnterNameFromFile(char * name_file) {
    system("CLS");
    showCursor();
    showHeaderMenu(12);
    char * extension = ".dat";

    gotoxy (32 , 22);
    cout << "INGRESAR EL NOMBRE DEL ARCHIVO: ";
    cin >> name_file;

    strcat(name_file, extension);
    hideCursor();
}

void getInformationFromFile(tPokemon rPokemon[], int &current_register_length) {
    FILE * filePokedex; //create file
    tPokemon rTemporalPokemon;
    char * name_file;
    ShowTemplateToEnterNameFromFile(name_file);
    filePokedex = fopen (name_file, "rb"); //open file in mode read
    if (filePokedex != NULL){
        fread (&rTemporalPokemon, sizeof(rTemporalPokemon), 1, filePokedex);
        while (!feof(filePokedex)){
            rPokemon[current_register_length].type  = rTemporalPokemon.type;
            rPokemon[current_register_length].level = rTemporalPokemon.level;
            rPokemon[current_register_length].name  = rTemporalPokemon.name;
            current_register_length ++;
            fread (&rTemporalPokemon, sizeof(rTemporalPokemon), 1, filePokedex);
        }
    }
    fclose (filePokedex); //close file
}

void enterInformationIntoFile(tPokemon rPokemon[], int current_register_length) {
    FILE *filePokedex; //create file
    filePokedex = fopen ("pokedex.dat","wb"); //open file in mode write
    tPokemon rTemporalPokemon = rPokemon[current_register_length];
    fwrite (&rTemporalPokemon, sizeof(rTemporalPokemon), 1, filePokedex); //write one line into file
    fclose (filePokedex); //close file
}

void showMenuToEnterInformationFromUser(tPokemon rPokemon[], int &current_register_length) {
    system("CLS");
    showHeaderMenu(11); //INGRESAR INFORMACION MANUALMENTE
    showCursor();
    int quantity_limit_pokemons;
    gotoxy (32 , 22);
    cout << "   CANTIDAD DE POKEMONS A INGRESAR: ";
    cin >> quantity_limit_pokemons;
    for (int current_quantity = 0; current_quantity < quantity_limit_pokemons; current_quantity++){
        showHeaderQuantityRemainsToEnter(current_quantity, quantity_limit_pokemons);
        showTemplateToEnterInformationFromUser(rPokemon, current_register_length);
        current_register_length ++;
    }
    system("CLS");
    showPrincipalMenu(1);
}

void showTemplateToEnterInformationFromUser(tPokemon rPokemon[], int current_register_length) {
    gotoxy (32 , 22);
    cout << "   TIPO DE POKEMON: ";
    cin >> rPokemon[current_register_length].type;
    while (!isValidLetter(rPokemon[current_register_length].type)) {
        gotoxy(32 , 24);
        cout << "  TIPO INVALIDO, por favor ingresar t, f, a, e.  ";
        gotoxy (32 , 26);
        system ("PAUSE");
        system ("CLS");
        gotoxy(32 , 22);
        cout << "   TIPO DE POKEMON: ";
        cin >> rPokemon[current_register_length].type;
    }
    gotoxy (32 , 24);
    cout << "   NIVEL DE POKEMON: ";
    cin >> rPokemon[current_register_length].level;
    while (!isValidNumber(rPokemon[current_register_length].level)) {
        gotoxy(32 , 26);
        cout << "  NIVEL INVALIDO, por favor ingresar un valor entre 1 y 1000  ";
        gotoxy (32 , 28);
        system ("PAUSE");
        system ("CLS");
        gotoxy(32 , 24);
        cout << "   NIVEL DE POKEMON: ";
        cin >> rPokemon[current_register_length].level;
    }
    gotoxy (32 , 26);
    cout << "   NOMBRE DE POKEMON: ";
    cin >> rPokemon[current_register_length].name;
    while (!isValidName (rPokemon[current_register_length].name)){
        gotoxy(32 , 28);
        cout << "  NOMBRE INVALIDO, por favor ingresar un nombre con menos de 10 caracteres  ";
        gotoxy (32 , 30);
        system ("PAUSE");
        system ("CLS");
        gotoxy(32 , 26);
        cout << "   NOMBRE DE POKEMON: ";
        cin >> rPokemon[current_register_length].name
    }

    enterInformationIntoFile(rPokemon, current_register_length);
}
void showHeaderQuantityRemainsToEnter(int current_quantity, int quantity_limit_pokemons){
    system("CLS");
    gotoxy (20 , 14);
    cout << (char) 201; //Upper left corner
    gotoxy (20 , 16);
    cout << (char) 200; //Lower left corner
    gotoxy (46 , 14);
    cout << (char) 187; //Upper right corner
    gotoxy (46 , 16);
    cout << (char) 188; //Lower right corner

    gotoxy (20 , 15);
    cout << " POKEMONS INGRESADOS " << current_quantity + 1 << " / " << quantity_limit_pokemons;
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

bool isValidNumber(int number) {
    return (number <= 1000 && number >= 1);
}
bool isValidName (string name) {
     return (name.size() <= 10);
}

int isValidLetter(string letter) {
    regex regex_letter_validation ("[^TtFfEeAa]");
    smatch match;
    return !regex_search(letter, match, regex_letter_validation);
}

void showLoadingBar() {
    system("CLS");
    gotoxy (40 , 19);
    cout << " Please Wait... ";
    Sleep(150);

    gotoxy (38 , 20);
    for (int i = 0; i < 15; i++){
        cout << (char) 219;
        Sleep(150);
    }
    system("CLS");
}

int getLimitPokemonInArray(){
    int n;
    cout << " ingrese la cantidad máxima de pokemones: ";
    cin >> n;
    return n;
}

void cantOfPokemonsPerType(tPokemon rPokemon[], int current_register_length){
    int contador_tierra = 0, contador_fuego = 0, contador_agua = 0, contador_electrico = 0;
    for (int i = 0; i < current_register_length; i++){
        if (rPokemon[i].type == "t"){
            contador_tierra++;
        } else if (rPokemon[i].type == "f"){
            contador_fuego++;
        } else if (rPokemon[i].type == "a"){
            contador_agua++;
        } else {
            contador_electrico++;
        }
    }
    showCantOfPokemonsPerType(contador_tierra, contador_fuego, contador_agua, contador_electrico);
}

void showCantOfPokemonsPerType(int contador_tierra, int contador_fuego, int contador_agua, int contador_electrico){
    system("CLS");
    gotoxy (32 , 22);
    cout << " LA CANTIDAD DE POKEMONES TIPO TIERRA ES: " << contador_tierra;
    gotoxy (32 , 24);
    cout << " LA CANTIDAD DE POKEMONES TIPO FUEGO ES: " << contador_fuego;
    gotoxy (32 , 26);
    cout << " LA CANTIDAD DE POKEMONES TIPO AGUA ES: " << contador_agua;
    gotoxy (32 , 28);
    cout << " LA CANTIDAD DE POKEMONES TIPO ELECTRICO ES: " << contador_electrico;
    gotoxy (32 , 32);
    system("PAUSE");
    showPrincipalMenu(2);
}

void promLevelPerType(tPokemon rPokemon[], int current_register_length){
    int contador_tierra = 0, contador_fuego = 0, contador_agua = 0, contador_electrico = 0, total_nivel_tierra = 0, total_nivel_fuego = 0, total_nivel_agua = 0, total_nivel_electrico = 0;
    for (int i = 0; i < current_register_length; i++){
        if (rPokemon[i].type == "t"){
            contador_tierra++;
            total_nivel_tierra += rPokemon[i].level;
        } else if (rPokemon[i].type == "f"){
            contador_fuego++;
            total_nivel_fuego += rPokemon[i].level;
        } else if (rPokemon[i].type == "a"){
            contador_agua++;
            total_nivel_agua += rPokemon[i].level;
        } else {
            contador_electrico++;
            total_nivel_electrico += rPokemon[i].level;
        }
    }
    int promedio_tierra = total_nivel_tierra / contador_tierra;
    int promedio_fuego = total_nivel_fuego / contador_fuego;
    int promedio_agua= total_nivel_agua / contador_agua;
    int promedio_electrico = total_nivel_electrico / contador_electrico;
    showPromLevelPerType(promedio_tierra, promedio_fuego, promedio_agua, promedio_electrico);

}

void showPromLevelPerType(int promedio_tierra, int promedio_fuego, int promedio_agua, int promedio_electrico){
    system("CLS");
    gotoxy (32 , 22);
    cout << " EL PROMEDIO DE NIVELES DE POKEMONES TIPO TIERRA ES: " << promedio_tierra;
    gotoxy (32 , 24);
    cout << " EL PROMEDIO DE NIVELES DE POKEMONES TIPO FUEGO ES: " << promedio_fuego;
    gotoxy (32 , 26);
    cout << " EL PROMEDIO DE NIVELES DE POKEMONES TIPO AGUA ES: " << promedio_agua;
    gotoxy (32 , 28);
    cout << " EL PROMEDIO DE NIVELES DE POKEMONES TIPO ELECTRICO ES: " << promedio_electrico;
    gotoxy (32 , 32);
    system("PAUSE");
    showPrincipalMenu(2);

}

