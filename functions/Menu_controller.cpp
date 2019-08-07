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

/* functions to control cursor */
void gotoxy(int x, int y); //sets cursor in position(x,y) into terminal
void hideCursor();
void showCursor();

/*  functions to animate the system  */
void initialAnimation();  // animation
void showLoadingBar();    // laoding bar
void userHelper();        // shows keys can be used for user (TUTORIAL)
void goodbyeMessage();    // exit message

/*  functions to control the position  */
void resetPosition(int &position);                      //resets cursor position to initial position
void changePosition(char key, int &position);           //changes arrows position from next position
void showNewPosition(int position);                     //prints arrows in current position
void removeLastPosition(int position);                  //removes the last position in which the arrow was

/*  functions to control the menu  */
void runPrincipalFunctions(char key, int &position, int &menu_selector, tPokemon rPokemon[], int &current_register_length);     //principal function for show second menu
void showPrincipalMenu(int menu_selector);                                                                                      //shows principal menu, names of functions
void showHeaderMenu(int menu_selector);                                                                                         //shows last menu for know where are you from

/*  functions to control the Pokedex information  */
void getInformationFromFile(tPokemon rPokemon[], int &current_register_length);                             //loads information from file
void ShowTemplateToEnterNameFromFile(char * name_file);                                                     //shows text to enter the name of file
void enterInformationIntoFile(tPokemon rPokemon[], int current_register_length);                            //enters information

void showMenuToEnterInformationFromUser(tPokemon rPokemon[], int &current_register_length);                 //gets information from user, asks them how many records they want to load
void showTemplateToEnterInformationFromUser(tPokemon rPokemon[], int current_register_length);              //assigns the information to the struct
void showHeaderQuantityRemainsToEnter(int current_quantity, int quantity_limit_pokemons);                   //shows remaining quantity to enter

/* functions to control Pokemons stats */
void computePokemonsGroupedByLevel(tPokemon rPokemon[], int current_register_length);                       //counts how many Pokemons are level 500 and how many are below or over that level
void showPokemonsGroupedByLevel(int level_higher, int level_lower, int lever_equal);                        //shows the number of Pokemons with level below 500, over 500 or equal to 500

void computeQuantityOfPokemonsGroupedByType(tPokemon rPokemon[], int current_register_length);                                          //counts how many Pokemons of each type were loaded in the system
void showQuantityOfPokemonsGroupedByType(int contador_tierra, int contador_fuego, int contador_agua, int contador_electrico);           //shows how many Pokemons belong to each type

void quantityOfPokemonsInThePokedex(tPokemon rPokemon[], int current_register_length, int &contador_tierra, int &contador_fuego, int &contador_agua, int &contador_electrico);      //counts the total number of Pokemons loaded in the system

void computeLevelAverageOfPokemonsGroupedByType(tPokemon rPokemon[], int current_register_length);                                          //takes every Pokemon of each type and calculates the average of their levels
void showLevelAverageOfPokemonsGroupedByType(int contador_tierra, int contador_fuego, int contador_agua, int contador_electrico);           //shows the average level in each type category

void computePokemonsWithHighestLevel(tPokemon rPokemon[], int current_register_length);                                                                             //looks at every Pokemon and returns the one with the highest level
void computePokemonsWithLowestLevel(tPokemon rPokemon[], int current_register_length);                                                                              //looks at every Pokemon and returns the one with the lowest level
void showPokemonsWithHighestAndLowestLevel(tPokemon rPokemon_temporal[], bool is_highest_or_lowest);

/*functions to validate data entry from user*/
bool isValidNumber(int number);                 //validates number
int isValidLetter(string letter);               //validates key
bool isValidName(string name);                  //validates pokemon name
void changeLetterToUppercase(string &word);     //changes letter to uppercase to validate pokemon type
void showEmptyPokedexMessage();                 //shows a message so the user is warned that there aren´t any Pokemons loaded in the Pokedex

int main() {
    system("color 07");     //Black background Color and white Text Color
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
    else if(menu_selector == 1){            //Set information for Pokedex (menu)
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
    else if(menu_selector == 2){             //Stats from Pokedex (menu)
        showHeaderMenu(menu_selector);
        Sleep(50);
        gotoxy (32 , 22);
        cout << "   MOSTRAR POKEMONES DIVIDIDOS POR TIPO  ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR CANTIDAD DE POKEMONES POR NIVEL ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "   MOSTRAR POKEMONES CON MAYOR/MENOR NIVEL    "; //Highest level and lowest level
    }
    else if(menu_selector == 21){             //Stats from Pokedex (menu)
        showHeaderMenu(menu_selector);
        Sleep(50);
        gotoxy (32 , 22);
        cout << "   MOSTRAR CANTIDAD DE POKEMONES DE CADA TIPO  ";
        Sleep(50);
        gotoxy (32 , 24);
        cout << "   MOSTRAR EL NIVEL PROMEDIO DE LOS POKEMONES   ";
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                    VOLVER                     ";
    }
    else if(menu_selector == 23){             //Stats from Pokedex ( sub menu from show pokemons group by type )
        showHeaderMenu(menu_selector);
        gotoxy (32 , 22);
        cout << "   MOSTRAR POKEMONES MAS PODEROSOS POR TIPO ";      // Highest level
        Sleep(50);
        gotoxy (32 , 24);
        cout << "    MOSTRAR POKEMONES MAS DEBILES POR TIPO   ";     // Lowest level
        Sleep(50);
        gotoxy (32 , 26);
        cout << "                  VOLVER                   ";      // back to stats menu
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
        gotoxy (63 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (63 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "INGRESAR INFORMACION AL POKEDEX MANUALMENTE";
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
    else if (menu_selector == 21){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (48 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (48 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "POKEMONES DIVIDIDOS POR TIPO";
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
        cout << "CANTIDAD DE POKEMONES POR NIVEL";
    }
    else if (menu_selector == 23){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (51 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (51 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "POKEMONES CON MAYOR/MENOR NIVEL";
    }
    else if (menu_selector == 211){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (54 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (54 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "CANTIDAD DE POKEMONES DE CADA TIPO";
    }
    else if (menu_selector == 212){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (50 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (50 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "NIVEL PROMEDIO EN CADA TIPO";
    }
    else if (menu_selector == 231){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (49 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (49 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "POKEMON MAS PODEROSO POR TIPO";
    }
    else if (menu_selector == 232){
        gotoxy (19 , 14);
        cout << (char) 201; //Upper left corner
        gotoxy (19 , 16);
        cout << (char) 200; //Lower left corner
        gotoxy (46 , 14);
        cout << (char) 187; //Upper right corner
        gotoxy (46 , 16);
        cout << (char) 188; //Lower right corner

        gotoxy (20 , 15);
        cout << "POKEMON MAS DEBIL POR TIPO";
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
            if (position == 1) {
                menu_selector = 21;
                showPrincipalMenu(menu_selector);                                                                       // shows menu Pokemons divided by type
            }
            else if (position == 2) computePokemonsGroupedByLevel(rPokemon, current_register_length);                   // shows Pokemons with level below 500, over 500 or equal to 500
            else if (position == 3){
                menu_selector = 23;
                showPrincipalMenu(menu_selector);                                                                       // shows menu Pokemons with highest or lowest level
            }
        }
        else if (menu_selector == 21){
            if (position == 1) computeQuantityOfPokemonsGroupedByType(rPokemon, current_register_length);               // shows how many Pokemons belong to each type
            else if (position == 2) computeLevelAverageOfPokemonsGroupedByType(rPokemon, current_register_length);      // shows the average level in each type category
            else if (position == 3){
                menu_selector = 2;
                showPrincipalMenu(menu_selector);                                                                       // back to menu --> show Pokemon statistics
            }
        }
        else if (menu_selector == 23){
            if (position == 1) computePokemonsWithHighestLevel(rPokemon, current_register_length);                      // shows the Pokemon with the highest level
            else if (position == 2) computePokemonsWithLowestLevel(rPokemon, current_register_length);                  // shows the Pokemon with the lowest level
            else if (position == 3){
                menu_selector = 2;
                showPrincipalMenu(menu_selector);                                                                       // back to menu --> show Pokemon statistics
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
        else if (menu_selector == 21 || menu_selector == 22 || menu_selector == 23){
            menu_selector = 2;
            showPrincipalMenu(menu_selector);
        }
        resetPosition(position);
    }
    if (key == (int) 75 || key == (int) 107){ // key = K
        userHelper();
        showPrincipalMenu(menu_selector);
    }

}

/*  FUNCTIONS TO CONTROL THE CURSOR   */
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

/*  FUNCTIONS TO CONTROL POKEDEX INFORMATION   */
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
    showHeaderMenu(11); // "INGRESAR INFORMACION MANUALMENTE"
    showCursor();
    int quantity_limit_pokemons;
    gotoxy (32 , 22);
    cout << "   CANTIDAD DE POKEMONES A INGRESAR: ";
    cin >> quantity_limit_pokemons;
    for (int current_quantity = 0; current_quantity < quantity_limit_pokemons; current_quantity++){
        showHeaderQuantityRemainsToEnter(current_quantity, quantity_limit_pokemons);
        showTemplateToEnterInformationFromUser(rPokemon, current_register_length);
        current_register_length ++;
    }
    system("CLS");
    showPrincipalMenu(1);
}

void showErrorMessage (int error) {
    if(error == 1){
        gotoxy(32 , 24);
        cout << "   TIPO INVALIDO    ";
        gotoxy (35 , 26);
        Sleep(1000);
        gotoxy(32 , 24);
        cout << "                    ";
        gotoxy(52 , 22);
        cout << "                    ";
    }
    else if (error == 2){
        gotoxy(32 , 26);
        cout << "   NIVEL INVALIDO   ";
        gotoxy (35 , 28);
        Sleep(1000);
        gotoxy(32 , 26);
        cout << "                    ";
        gotoxy(52 , 24);
        cout << "                    ";
    }
    else if (error == 3){
        gotoxy(32 , 28);
        cout << "   NOMBRE INVALIDO  ";
        gotoxy (32 , 30);
        Sleep(1000);
        gotoxy(32 , 28);
        cout << "                    ";
        gotoxy(52 , 26);
        cout << "                    ";
    }
}

void showTemplateToEnterInformationFromUser(tPokemon rPokemon[], int current_register_length) {
    gotoxy (32 , 22);
    cout << "   TIPO DE POKEMON: ";
    cin >> rPokemon[current_register_length].type;
    while (!isValidLetter(rPokemon[current_register_length].type)) {
        showErrorMessage(1);
        gotoxy(32 , 22);
        cout << "   TIPO DE POKEMON: ";
        cin >> rPokemon[current_register_length].type;
    }
    changeLetterToUppercase(rPokemon[current_register_length].type);

    gotoxy (32 , 24);
    cout << "   NIVEL DE POKEMON: ";
    cin >> rPokemon[current_register_length].level;
    while (!isValidNumber(rPokemon[current_register_length].level)) {
        showErrorMessage(2);
        gotoxy(32 , 24);
        cout << "   NIVEL DE POKEMON: ";
        cin >> rPokemon[current_register_length].level;
    }

    gotoxy (32 , 26);
    cout << "   NOMBRE DE POKEMON: ";
    cin >> rPokemon[current_register_length].name;
    while (!isValidName (rPokemon[current_register_length].name)){
        showErrorMessage(3);
        gotoxy(32 , 26);
        cout << "   NOMBRE DE POKEMON: ";
        cin >> rPokemon[current_register_length].name;
    }

    enterInformationIntoFile(rPokemon, current_register_length);
}

void showHeaderQuantityRemainsToEnter(int current_quantity, int quantity_limit_pokemons) {
    system("CLS");
    gotoxy (20 , 14);
    cout << (char) 201; //Upper left corner
    gotoxy (20 , 16);
    cout << (char) 200; //Lower left corner
    gotoxy (47 , 14);
    cout << (char) 187; //Upper right corner
    gotoxy (47 , 16);
    cout << (char) 188; //Lower right corner

    gotoxy (20 , 15);
    cout << " POKEMONES INGRESADOS " << current_quantity + 1 << " / " << quantity_limit_pokemons;
}

/*  FUNCTIONS TO COMPUTE AND SHOW POKEDEX STATISTICS    */
/*  FIRST FUNCTIONS OR FIRST MENU   */
void computeQuantityOfPokemonsGroupedByType(tPokemon rPokemon[], int current_register_length) {
    int counter_t = 0, counter_f = 0, counter_a = 0, counter_e = 0;
    quantityOfPokemonsInThePokedex(rPokemon, current_register_length, counter_t, counter_f, counter_a, counter_e);
    current_register_length ? showQuantityOfPokemonsGroupedByType(counter_t, counter_f, counter_a, counter_e) : showEmptyPokedexMessage();
    showPrincipalMenu(21);
}

void showQuantityOfPokemonsGroupedByType(int counter_t, int counter_f, int counter_a, int counter_e) {
    system("CLS");
    showHeaderMenu(211); // "CANTIDAD DE POKEMONES DE CADA TIPO"
    gotoxy (32 , 22);
    cout << " LA CANTIDAD DE POKEMONES DE TIERRA ES: " << counter_t;
    gotoxy (32 , 24);
    cout << " LA CANTIDAD DE POKEMONES DE FUEGO ES: " << counter_f;
    gotoxy (32 , 26);
    cout << " LA CANTIDAD DE POKEMONES DE AGUA ES: " << counter_a;
    gotoxy (32 , 28);
    cout << " LA CANTIDAD DE POKEMONES ELECTRICOS ES: " << counter_e;
    gotoxy (32 , 32);
    system("PAUSE");
}

void quantityOfPokemonsInThePokedex(tPokemon rPokemon[], int current_register_length, int &counter_t, int &counter_f, int &counter_a, int &counter_e) {
    for (int i = 0; i < current_register_length; i++){
        if (rPokemon[i].type == "T")
            counter_t ++;
        else if (rPokemon[i].type == "F")
            counter_f ++;
        else if (rPokemon[i].type == "A")
            counter_a ++;
        else
            counter_e ++;
    }
}

void computeLevelAverageOfPokemonsGroupedByType(tPokemon rPokemon[], int current_register_length) {
    int counter_t = 0, counter_f = 0, counter_a = 0, counter_e = 0, total_level_t = 0, total_level_f = 0, total_level_a = 0, total_level_e = 0;
    for (int i = 0; i < current_register_length; i++){
        if (rPokemon[i].type == "T")
            total_level_t += rPokemon[i].level;
        else if (rPokemon[i].type == "F")
            total_level_f += rPokemon[i].level;
        else if (rPokemon[i].type == "A")
            total_level_a += rPokemon[i].level;
        else
            total_level_e += rPokemon[i].level;
    }
    quantityOfPokemonsInThePokedex(rPokemon, current_register_length, counter_t, counter_f, counter_a, counter_e);

    int average_t = counter_t ? total_level_t / counter_t : 0;
    int average_f = counter_f ? total_level_f / counter_f : 0;
    int average_a = counter_a ? total_level_a / counter_a : 0;
    int average_e = counter_e ? total_level_e / counter_e : 0;
    current_register_length ? showLevelAverageOfPokemonsGroupedByType(average_t, average_f, average_a, average_e) : showEmptyPokedexMessage();
    showPrincipalMenu(21);
}

void showLevelAverageOfPokemonsGroupedByType(int average_t, int average_f, int average_a, int average_e) {
    system("CLS");
    showHeaderMenu(212); // "PROMEDIO DE NIVEL DE CADA TIPO"
    gotoxy (32 , 22);
    cout << " EL PROMEDIO DEL NIVEL DE LOS POKEMONES DE TIERRA ES: " << average_t;
    gotoxy (32 , 24);
    cout << " EL PROMEDIO DEL NIVEL DE LOS POKEMONES DE FUEGO ES: " << average_f;
    gotoxy (32 , 26);
    cout << " EL PROMEDIO DEL NIVEL DE LOS POKEMONES DE AGUA ES: " << average_a;
    gotoxy (32 , 28);
    cout << " EL PROMEDIO DEL NIVEL DE LOS POKEMONES ELECTRICOS ES: " << average_e;
    gotoxy (32 , 32);
    system("PAUSE");
}

/*  SECOND FUNCTIONS OR SECOND MENU   */
void computePokemonsGroupedByLevel(tPokemon rPokemon[], int current_register_length) {
    int level_higher = 0, level_lower = 0, level_equal = 0;
    for (int i = 0; i < current_register_length; i++){
        if (rPokemon [i].level > 500)
            level_higher++;
        else if (rPokemon [i].level < 500)
            level_lower++;
        else
            level_equal++;
    }
    current_register_length ? showPokemonsGroupedByLevel (level_higher, level_lower, level_equal) : showEmptyPokedexMessage();
    showPrincipalMenu(2);
}

void showPokemonsGroupedByLevel (int level_higher, int level_lower, int level_equal) {
    system ("CLS");
    showHeaderMenu(22); // "CANTIDAD DE POKEMONES POR NIVEL"
    gotoxy (32 , 22);
    cout << "LA CANTIDAD DE POKEMONES CON NIVEL MAYOR A 500 ES: " << level_higher;
    gotoxy (32 , 24);
    cout << "LA CANTIDAD DE POKEMONES CON NIVEL MENOR A 500 ES: " << level_lower;
    gotoxy (32 , 26);
    cout << "LA CANTIDAD DE POKEMONES CON NIVEL IGUAL A 500 ES: " << level_equal;
    gotoxy (32 , 30);
    system ("PAUSE");
}

/*  THIRD FUNCTIONS OR THIRD MENU   */
void computePokemonsWithHighestLevel(tPokemon rPokemon[], int current_register_length) {
    tPokemon rPokemon_temporal[4];
    rPokemon_temporal [0].level = 0; rPokemon_temporal [1].level = 0; rPokemon_temporal [2].level = 0; rPokemon_temporal [3].level = 0;
    //most powerful Pokemon earth type, most powerful Pokemon fire type, most powerful Pokemon water type, most powerful Pokemon electric type

    for (int i = 0; i < current_register_length; i++){
        if (rPokemon [i].type == "T"){
            if (rPokemon [i].level >= rPokemon_temporal[0].level)
                rPokemon_temporal [0] = rPokemon [i];
        }
        else if (rPokemon [i].type == "F"){
            if (rPokemon [i].level >= rPokemon_temporal[1].level)
                rPokemon_temporal [1] = rPokemon [i];
        }
        else if (rPokemon [i].type == "A"){
            if (rPokemon [i].level >= rPokemon_temporal[2].level)
                rPokemon_temporal [2] = rPokemon [i];
        }
        else if (rPokemon [i].type == "E"){
            if (rPokemon [i].level >= rPokemon_temporal[3].level)
                rPokemon_temporal [3] = rPokemon [i];
        }
    }
    current_register_length ? showPokemonsWithHighestAndLowestLevel(rPokemon_temporal, true) : showEmptyPokedexMessage();
    showPrincipalMenu(23);
}

void computePokemonsWithLowestLevel(tPokemon rPokemon[], int current_register_length) {
    tPokemon rPokemon_temporal[4];
    rPokemon_temporal [0].level = 1001; rPokemon_temporal [1].level = 1001; rPokemon_temporal [2].level = 1001; rPokemon_temporal [3].level = 1001;
    //less powerful Pokemon earth type, less powerful Pokemon fire type, less powerful Pokemon water type, less powerful Pokemon electric type

    for (int i = 0; i < current_register_length; i++){
        if (rPokemon [i].type == "T"){
            if (rPokemon [i].level <= rPokemon_temporal[0].level)
                rPokemon_temporal [0] = rPokemon [i];
        }
        else if (rPokemon [i].type == "F"){
            if (rPokemon [i].level <= rPokemon_temporal[1].level)
                rPokemon_temporal [1] = rPokemon [i];
        }
        else if (rPokemon [i].type == "A"){
            if (rPokemon [i].level <= rPokemon_temporal[2].level)
                rPokemon_temporal [2] = rPokemon [i];
        }
        else if (rPokemon [i].type == "E"){
            if (rPokemon [i].level <= rPokemon_temporal[3].level)
                rPokemon_temporal[3] = rPokemon [i];
        }
    }

    current_register_length ? showPokemonsWithHighestAndLowestLevel(rPokemon_temporal, false) : showEmptyPokedexMessage();
    showPrincipalMenu(23);
}

void showPokemonsWithHighestAndLowestLevel(tPokemon rPokemon_temporal[], bool is_highest_or_lowest) {
    system ("CLS");
    string power_measure = is_highest_or_lowest ? "MAS ALTO" : "MAS BAJO";
    is_highest_or_lowest ? showHeaderMenu(231) : showHeaderMenu(232);

    gotoxy (32 , 22);
    if (rPokemon_temporal[0].level != 0 && rPokemon_temporal[0].level != 1001)
        cout << "EL POKEMON DE TIERRA CON EL NIVEL " << power_measure << " ES: " << rPokemon_temporal[0].name << " CON UN NIVEL DE " << rPokemon_temporal[0].level;
    else
        cout << "NO HAY POKEMONES DE TIPO TIERRA INGRESADOS ";

    gotoxy (32 , 24);
    if (rPokemon_temporal[1].level != 0 && rPokemon_temporal[1].level != 1001)
        cout << "EL POKEMON DE FUEGO CON EL NIVEL " << power_measure << " ES: " << rPokemon_temporal[1].name << " CON UN NIVEL DE " << rPokemon_temporal[1].level;
    else
        cout << "NO HAY POKEMONES DE TIPO FUEGO INGRESADOS ";

    gotoxy (32 , 26);
    if (rPokemon_temporal[2].level != 0 && rPokemon_temporal[2].level != 1001)
        cout << "EL POKEMON DE AGUA CON EL NIVEL " << power_measure << " ES: " << rPokemon_temporal[2].name << " CON UN NIVEL DE " << rPokemon_temporal[2].level;
    else
        cout << "NO HAY POKEMONES DE TIPO AGUA INGRESADOS ";

    gotoxy (32 , 28);
    if (rPokemon_temporal[3].level != 0 && rPokemon_temporal[3].level != 1001)
        cout << "EL POKEMON ELECTRICO CON EL NIVEL " << power_measure << " ES: " << rPokemon_temporal[3].name << " CON UN NIVEL DE " << rPokemon_temporal[3].level;
    else
        cout << "NO HAY POKEMONES DE TIPO ELECTRICO INGRESADOS ";

    gotoxy (32 , 32);
    system ("PAUSE");
}

/*  FUNCTIONS TO VALIDATE THE INFORMATION ENTERED INTO THE POKEDEX  */
bool isValidNumber(int number) {
    return (number <= 1000 && number >= 1);
}

bool isValidName (string name) {
    return (name.size() <= 10);
}

int isValidLetter(string letter) {
    regex regex_letter_validation ("^[TtFfEeAa]{1}$");
    smatch match;
    return regex_search(letter, match, regex_letter_validation);
}

void changeLetterToUppercase(string &word) {
    //word[0] = ((int)word[0] > 96 && (int)word[0] < 123) ? (int)word[0] - 32 : word[0];
    word[0] = toupper(word[0]);
}

void showEmptyPokedexMessage() {
    gotoxy (12 , 30);
    cout << "   Todavia no se ingresaron Pokemones en el Pokedex ";
    system( "PAUSE");
}

/*  ANIMATION FUNCTIONS */
void showLoadingBar() {
    system("CLS");
    gotoxy (40 , 19);
    cout << " Loading... ";
    Sleep(150);

    gotoxy (38 , 20);
    for (int i = 0; i < 10; i++){
        cout << (char) 219;
        Sleep(150);
    }
    system("CLS");
}

void goodbyeMessage() {
    system("CLS");
    exit(0);
}

void userHelper() {
    Sleep(150);
    gotoxy (82 , 22);
    cout << (char) 186 << " < W > : MOVER HACIA ARRIBA " << (char) 186;
    Sleep(150);
    gotoxy (82 , 24);
    cout << (char) 186 << " < S > : MOVER HACIA ABAJO  " << (char) 186;
    Sleep(150);
    gotoxy (82 , 26);
    cout << (char) 186 << " < K > : AYUDA DE TECLAS    " << (char) 186;
    Sleep(150);
    gotoxy (82 , 28);
    cout << (char) 186 << " <ESC> : VOLVER | SALIR     " << (char) 186;
    Sleep(150);
    gotoxy (42 , 33);
    cout << "#######################################";
    gotoxy (42 , 32);
    system ("PAUSE");
    system("CLS");
}
