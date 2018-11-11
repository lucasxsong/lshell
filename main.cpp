#include <iostream>
#include <string>

using namespace std;

bool runShell = true;

void runInput() {
    string userInput;
    cout << "$ ";
    getline(cin, userInput);

    if (userInput == "exit" ||userInput == "Exit") { 
        runShell = false;
    }

    //parseInput(userInput);

}


int main () {
    while (runShell) {
        runInput();
    }

    return 0;
}


