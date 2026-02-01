#include <iostream>
#include "fileio.h"
#include "menu.h"

using namespace std;

int main() {
    cout << "СПИСОК ДЕЛ\n";
    cout << "--------------------------\n";
    
    loadFromFile();
    showMenu();
    saveToFile();
    
    return 0;
}