#include <iostream>
#include <string>

using namespace std;


int CheckUserPermissionAccess() {
    string username;
    string password;
    string pass = "123";
    //This is not a secure way to have passwords
    //A database with usernames and passwords should be applied

    do {
        cout << "Enter your username: " << endl;
        cin >> username;

        cout << "Enter your password: " << endl;
        cin >> password;
        if (password != pass) {
            cout << "Invalid Password. Please try again" << endl;
            return 2;
        }
    } while (password != pass);
    //there shouldn't be infinite tries, should lock after 3 or so incorrect entries
    //also would be ideal to have alternate ways to verify identity

    return 1;
}

void DisplayInfo(int& num1, int& num2, int& num3, int& num4, int& num5) {

    cout << endl
        << "   Clients Name      Service Selected (1 = Brokerage, 2 = Retirement)" << endl
        << "1. Bob Jones selected option " << num1 << endl
        << "2. Sarah Davis selected option " << num2 << endl
        << "3. Amy Friendly selected option " << num3 << endl
        << "4. Johnny Smith selected option " << num4 << endl
        << "5. Carol Spears selected option " << num5 << endl;

    //Data would be better stored in a table, would make the data more secure

    return;
}

void ChangeCustomerChoice(int& num1, int& num2, int& num3, int& num4, int& num5) {
    int input;
    int clientNum;

    cout << endl;
    cout << "Enter the number of the client that you wish to change " << endl;
    cin >> input;
    //using the clients number is to easy to mess up, it should be the clients entire name
    cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement) " << endl;
    cin >> clientNum;

    if (input == 1) {
        num1 = clientNum;
    }
    if (input == 2) {
        num2 = clientNum;
    }
    if (input == 3) {
        num3 = clientNum;
    }
    if (input == 4) {
        num4 = clientNum;
    }
    if (input == 5) {
        num5 = clientNum;
    }

    return;
}

int main() {

    int userInput = 0;
    int num1 = 1, num2 = 2, num3 = 1, num4 = 1, num5 = 2;
    int loginTotal = 0;
    int ans;

    cout << "This was created by Noah Caruthers" << endl;

    do {
        if (loginTotal > 3) {
            cout << "Max login attempts reached" << endl;
            return 0;
        }
        ans = CheckUserPermissionAccess();
        if (ans == 1) {
            break;
        }
        else {
            loginTotal++;
        }
    } while (ans != 1);

    do {
        cout << endl
            << "What would you like to do?" << endl
            << "DISPLAY the client list (enter 1)" << endl
            << "CHANGE a client's choice (enter 2)" << endl
            << "Exit the program.. (enter 3)" << endl; // i prefer the exit number to be unique from the others, I would prefer 9 for example

        cin >> userInput;

        if (userInput == 1) {
            cout << "You chose 1" << endl;
            DisplayInfo(num1, num2, num3, num4, num5);
        }
        if (userInput == 2) {
            cout << "You chose 2" << endl;
            DisplayInfo(num1, num2, num3, num4, num5);
            ChangeCustomerChoice(num1, num2, num3, num4, num5);
        }
    } while (userInput != 3);
}