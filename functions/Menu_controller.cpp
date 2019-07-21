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
void runPrincipalFunctions(char key, int &position, int &menu_selector, tPokemon rPokemon[], int &current_register_length);     //principal function for show second menu
void showPrincipalMenu(int menu_selector);                                   //show principal menu, names of functions
void showHeaderMenu(int menu_selector);                                      //show last menu for know where are you from

/*  functions that control the pokedex information  */
void getInformationFromFile();                          //function get information from file
void showMenuToEnterInformationFromUser();              //function get information from user, ask how many records do you want to load
void showTemplateToEnterInformationFromUser(int step);  //function that assigns the information to the struct
void showHeaderQuantityRemainsToEnter(int current_quantity, int quantity_limit_pokemons); //header that show how quantity remains to enter

/* functios that control pokemons stats */
void showPokemonsGroupByType(); //function show all types of pokemons order by type

void computePokemonsGroupByLevel(tPokemon rPokemon[], int current_register_length);
void showPokemonsGroupByLevel (int level_higher, int level_lower, int lever_equal);


void showPokemonsWithHighestLevel();
void showPokemonWithLessLevel();

/*functions that validate user data enter */
bool isValidNumber(int number); //function that validate number
int isValidLetter(string letter);       //function that validate key


int main() {
    system("color 07");//Black background Color and white Text Color
    showLoadingBar();

    int current_register_length = 0;
    tPokemon rPokemon[802];

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
        cout << "   INGRESAR INFORMACION DE UN ARCHIVO    ";
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
            if (position == 1) showMenuToEnterInformationFromUser();
            else if (position == 2) getInformationFromFile();
            else if (position == 3){
                menu_selector = 0;
                showPrincipalMenu(menu_selector); //back to principal menu
            }
        }
        else if (menu_selector == 2){
            if (position == 1) showPokemonsGroupByType();  // show Pokemons Group By Type
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
            if (position == 1) computePokemonsGroupByLevel(rPokemon, current_register_length);      // show Pokemons Group By Max level, more than 500
            else if (position == 2) computePokemonsGroupByLevel(rPokemon, current_register_length); // show Pokemons Group By Min level, less than 500
            else if (position == 3) computePokemonsGroupByLevel(rPokemon, current_register_length);    // show Pokemons Group By level equals to 500
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
    system("CLS");
    showHeaderMenu(11); //INGRESAR INFORMACION MANUALMENTE
    showCursor();
    int quantity_limit_pokemons;
    gotoxy (32 , 22);
    cout << "   CANTIDAD DE POKEMONS A INGRESAR: ";
    cin >> quantity_limit_pokemons;
    for (int current_quantity = 0; current_quantity < quantity_limit_pokemons; current_quantity++){
        showHeaderQuantityRemainsToEnter(current_quantity, quantity_limit_pokemons);
        for (int step = 1; step < 4; step++){
            showTemplateToEnterInformationFromUser(step);
        }
    }
}

void showTemplateToEnterInformationFromUser(int step) {
    string type, name;
    int level;
    if (step == 1){
        gotoxy (32 , 22);
        cout << "   TIPO DE POKEMON: ";
        cin >> type;
    }
    else if (step == 2){
        gotoxy (32 , 24);
        cout << "   NIVEL DE POKEMON: ";
        cin >> level;
    }
    else if (step == 3){
        gotoxy (32 , 26);
        cout << "   NOMBRE DE POKEMON: ";
        cin >> name;
    }
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
    cout << " POKEMONS INGRESADOS " << current_quantity << " / " << quantity_limit_pokemons;
}

void showPokemonsGroupByType() {

}

void computePokemonsGroupByLevel(tPokemon rPokemon[], int current_register_length) {
    int level_higher = 0;
    int level_lower = 0;
    int level_equal = 0;
    for (int i = 0; i < current_register_length; i++){
        if (rPokemon [i].level > 500){
            level_higher++;
        }
        else if (rPokemon [i].level < 500){
            level_lower++;
        }
        else {
            level_equal++;
        }
    }
    showPokemonsGroupByLevel (level_higher, level_lower, level_equal);
}
void showPokemonsGroupByLevel (int level_higher, int level_lower, int level_equal) {
    system ("CLS");
    gotoxy (32 , 22);
    cout << "LA CANTIDAD DE POKÉMONS CON NIVEL MAYOR A 500 ES:" << level_higher;
    gotoxy (32 , 24);
    cout << "LA CANTIDAD DE POKÉMONS CON NIVEL MENOR A 500 ES:" << level_lower;
    gotoxy (32 , 26);
    cout << "LA CANTIDAD DE POKÉMONS CON NIVEL IGUAL A 500 ES:" << level_equal;
    system ("PAUSE");
    showPrincipalMenu(2);
}


void showPokemonsWithHighestLevel() {

}

void showPokemonWithLessLevel() {

}

bool isValidNumber(int number) {
    return (number <= 1000 && number >= 1) ? true : false;
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



