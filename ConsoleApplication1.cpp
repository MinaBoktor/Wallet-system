

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <regex>
#include <sodium.h>
#include <set>
#include <string>
#include <fstream>
#include <list>
#include "BSTree.h"
#include "User.cpp"
#include "Transaction.cpp"
#include "Request.cpp"
#include "Wallet.cpp"





using namespace std;

int welcome();
int get_int();
int login();
string get_string();
bool signUp();
int menu(User* user);
void admin();
bool user_auth();

Wallet wallet;

int main()
{
    wallet.load();

    int n = -1;
    int choice = 0;
    while (choice != 3) {

        choice = welcome();
        switch (choice) {
        case 1:
            n = login();
            if (n == 1) {
                User* user = wallet.find_user(wallet.currentUser);
                cout << "\nLogin success!\n" << endl;
                menu(user);
            }
            else if (n == 2) {
                admin();
            }
            else {
                cout << "\nInvalid Credentials!\n" << endl;
            }

            break;
        case 2:
            if (signUp()) {
                cout << "\nYou've Registered Successfully!" << endl;
                cout << "Login to start your Journey\n" << endl;
            }
            break;
        case 3:
            break;
        default:
            cout << "Please select 1, 2, or 3.\n\n";
        }
    }


    

    wallet.save();

    //wallet.add_user("mina", "124", true, 100, "01204242422");
    //wallet.add_user("sono", "1234", true, 10320, "01204242422");
    //wallet.add_user("del", "12334", true, 1320, "01204242422");
    //wallet.delete_user("del");
    //User* del = wallet.find_user("del");
    //if (del == nullptr) {
    //    cout << "Deleted successfully!";
    //}
    //wallet.create_request("mina", "sono", 320);
    //wallet.get_all_requests();
    //wallet.finalize_request(0);
    //wallet.get_all_requests();
    //wallet.get_all_trans();
    //wallet.make_trans("sono", "mina", 320);
    //wallet.display_user("mina");
    //wallet.display_user("sono");
    return 0;
    
}

int welcome() {
    int n;
    while (true) {
        cout << "Welcome to ASU Smart Wallet" << endl;
        cout << "1. Login" << endl;
        cout << "2. Sign up" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";

        n = get_int();
        return n;
    }
}

int login() {
    string username;
    string password;
    cout << "Enter your Username (case sensitive): ";
    username = get_string();
    cout << "Enter your Password: ";
    password = get_string();

    if (username == "admin" && password == "admin") {
        wallet.currentUser = "admin";
        return 2;
    }

    if (wallet.check_user(username, password)) {
        wallet.currentUser = username;
        return 1;
    }
    else
        return 0;
}

string get_string() {
    while (true) {
        try {
            string temp;
            cin >> temp;
            return temp;
        }
        catch (int err) {
            cout << "\nInvalid Input!\n" << endl;
        }
    }

}

int get_int() {
    int n = -1;
    cin >> n;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        n = -1;
    }
    return n;
}

bool signUp() {

    string username;
    string pass1;
    string pass2;
    string phone;
    

    while (true) {
        cout << "Enter Username (Should be unique): ";
        username = get_string();
        if (wallet.find_user(username) == nullptr) {
            break;
        }
    }

    while (true) {
        cout << "Password: ";
        pass1 = get_string();

        cout << "Enter again the password: ";
        pass2 = get_string();

        if (pass1 == pass2) {
            break;
        }
        else
            cout << "The password doesn't match" << endl;
    }

    int n;
    while (true) {
        cout << "Enter your phone number (Should consist only of numbers): ";
        try {
            n = get_int();
            if (n == -1) {
                continue;
            }
            phone = to_string(n);
            break;
        }
        catch (int err) {
            cout << "The phone number should contain only numbers" << endl;
        }
    }

    if (wallet.add_user(username, pass1, true, 0, phone))
        return true;
    else
        return false;

}

void admin() {
    int choice = -1;
    
    cout << "\nWelcome " << "Mr. Admin\n" << endl;
    while (choice != 4) {

        

        cout << "1. Show all users" << endl;
        cout << "2. View System Transactions" << endl;
        cout << "3. Edit User Account" << endl;

        cout << "4. Logout\n" << endl;

        cout << "choice: ";

        // case 1
        string letter;
        string pass1, pass2;
        float balance;
        int n = -1 , temp = -1;
        string username;
        User* user;
        choice = get_int();

        switch (choice) {
        case 1:
            wallet.get_all_users();
            break;
        case 2:
            wallet.get_all_trans();
            break;

        case 3:

            while (true) {
                cout << "Enter the Account's Username: ";
                username = get_string();
                user = wallet.find_user(username);
                if (user != nullptr) {
                    break;
                }

                cout << "Incorrect Username!" << endl;
                }

            while (n != 5) {

                wallet.display_user(username);

                cout << "1. Reset Password" << endl;
                cout << "2. Change Balance" << endl;
                cout << "3. Replace Phone Number" << endl;
                if (user->status) {
                    cout << "4. Suspend Account" << endl;
                }
                else {
                    cout << "4. Activate Account" << endl;
                }
                cout << "5. Back to Menu" << endl;


                cout << "Choice: ";
                n = get_int();

                switch (n) {
                    case 1:
                        while (true) {
                            cout << "Password: ";
                            pass1 = get_string();

                            cout << "Enter again the password: ";
                            pass2 = get_string();

                            if (pass1 == pass2) {
                                user->password = wallet.hash_password(pass1);
                                break;
                            }
                            else
                                cout << "The password doesn't match" << endl;
                        }
                        break;
                    case 2:
                        while (true) {
                            cout << "Enter Balance: ";
                            balance = get_int();
                            if (balance != -1) {
                                user->balance = balance;
                                cout << "Balance Updated Successfully!" << endl;
                                break;
                            }
                        }
                        break;

                    case 3:
                        while (true) {
                            cout << "Enter the phone number (Should consist only of numbers): ";
                            try {
                                temp = get_int();
                                if (temp == -1) {
                                    continue;
                                }
                                user->phone = to_string(temp);
                                break;
                            }
                            catch (int err) {
                                cout << "The phone number should contain only numbers" << endl;
                            }
                        }
                        break;
                    case 4:

                        if (!user->status) {
                            cout << "Are you sure you want to activate the account ? (y/n): ";
                        }
                        else {
                            cout << "Are you sure you want to suspend the account ? (y/n): ";
                        }

                        letter = get_string();
                        if (letter == "y" || letter == "Y" || letter == "yes" || letter == "Yes") {
                            user->status = !user->status;
                        }
                        break;

                    case 5:
                        wallet.currentUser = "";
                        break;
                    default:
                        cout << "Select a valid option!" << endl;
                }
                
            }






            break;

        default:
            cout << "Select a valid option!" << endl;
        }
    }
}

int menu(User* user) {
    cout << "\nWelcome " << user->username << endl;

    int choice = -1;

    while (choice != 6) {

        cout << "\nCurrent Balance: " << user->balance << "\n" << endl;
        cout << "\nAccount Activation State: " << user->status << "\n" << endl;

        cout << "1. Send Money" << endl;
        cout << "2. Request Money" << endl;
        cout << "3. Review Pending Requests" << endl;
        cout << "4. Change Profile Details" << endl;
        cout << "5. Display Transactions" << endl;
        cout << "6. Logout\n" << endl;

        cout << "choice: ";
        choice = get_int();

        // Case 1 variables
        string username;
        float amount;

        // Case 2 variables
        int id;
        string letter;
        int n = 0;
        Request* req;

        // case 4 variables
        string pass1;
        string pass2;
        int temp;


        switch (choice) {
        case 1:
            if (user_auth()) {
                if (user->status && user->balance > 0) {

                    while (true) {
                        cout << "Enter the recipient Username: ";
                        username = get_string();

                        if (wallet.find_user(username) != nullptr) {
                            if (!(wallet.find_user(username)->status)) {
                                cout << "The username account you entered is currently suspended" << endl;
                                continue;
                            }
                            if (username == user->username) {
                                cout << "You can't send money to your account!" << endl;
                                continue;
                            }
                            break;
                        }

                        cout << "Incorrect Username!" << endl;
                    }

                    while (true) {
                        cout << "Enter the amount you want to send: ";
                        amount = get_int();
                        if (user->balance >= amount) {
                            break;
                        }
                        cout << "Insufficient funds!" << endl;
                    }

                    if (wallet.make_trans(user->username, username, amount)) {
                        cout << amount << " USD sent to " << username << " Successfully!" << endl;
                    }

                    else
                        cout << "Failed to send the money" << endl;
                }
                else
                    cout << "Make sure you have money at your wallet and your account is active!" << endl;
            }
            else
                cout << "Authentication Failed!" << endl;
            break;

        case 2:
            if (user->status) {
                username = "";
                amount = 0;
                User* sender;
                while (true) {
                    cout << "Enter the Sender Username (Who will send the money): ";
                    username = get_string();
                    sender = wallet.find_user(username);
                    if (sender != nullptr) {
                        if (!(wallet.find_user(username)->status)) {
                            cout << "The username account you entered is currently suspended" << endl;
                            continue;
                        }
                        if (username == user->username) {
                            cout << "You can't request money from your account!" << endl;
                            continue;
                        }
                        break;
                    }
                    cout << "Incorrect Username!" << endl;
                }

                while (true) {
                    cout << "Enter the amount you want the sender to send: ";
                    amount = get_int();

                    if (sender->balance >= amount) {
                        break;
                    }
                    cout << "The Sender doesn't have sufficient funds!" << endl;
                }

                wallet.create_request(user->username, sender->username, amount);
                cout << "Request to get " << amount << " USD from " << sender->username << " was sent successfully!" << endl;
                break;

            }
            else
                cout << "Your account isn't activated!" << endl;
            break;
        case 3:
            n = 0;
            wallet.get_all_requests(user->username);
            while (n != 3 && wallet.n_requests(user->username) > 0) {

                if (!user->status) {
                    cout << "You can't accept or delete any requests until your account is activated!";
                    break;
                }

                id = 0;
                req = nullptr;
                letter = "";


                cout << "1. Accept a request" << endl;
                cout << "2. Delete a request" << endl;
                cout << "3. Back to menu" << endl;

                cout << "Choice: ";
                n = get_int();
                switch (n) {
                case 1:
                    if (user_auth()) {
                        cout << "Enter Request ID: ";
                        id = get_int();
                        req = wallet.find_requests(id);
                        if (req == nullptr) {
                            cout << "Invalid Request ID!" << endl;
                            break;
                        }

                        if (req->sender != user->username) {
                            cout << "Invalid Request ID!" << endl;
                            break;
                        }

                        cout << "You are going to transfer " << req->amount << " USD to " << req->requester << " now\nConfirm? (y\\n): ";
                        letter = get_string();
                        if (letter == "y" || letter == "Y" || letter == "yes" || letter == "Yes") {
                            if (wallet.finalize_request(id)) {
                                cout << "Request with ID number " << id << " has been finalized successfully\n" << endl;
                            }

                        }
                    }
                    break;
                case 2:
                    if (user_auth()) {
                        cout << "Enter Request ID: ";
                        id = get_int();
                        req = wallet.find_requests(id);
                        if (req == nullptr) {
                            cout << "Invalid Request ID!" << endl;
                            break;
                        }

                        if (req->sender != user->username) {
                            cout << "Invalid Request ID!" << endl;
                            break;
                        }

                        cout << "You are going to delete a request from " << req->requester << " now\nConfirm? (y\\n): ";
                        letter = get_string();
                        if (letter == "y" || letter == "Y" || letter == "yes" || letter == "Yes") {
                            if (wallet.delete_request(id)) {
                                cout << "Request with ID number " << id << " has been deleted successfully\n" << endl;
                            }
                        }
                    }
                    break;
                case 3:
                    break;
                default:
                    cout << "Select a valid option!" << endl;
                    continue;
                }
            }
            break;
        case 4:
            n = 0;
            while (n != 3) {
                wallet.display_user(user->username);

                cout << "1. Reset Password" << endl;
                cout << "2. Change phone number" << endl;
                cout << "3. Back to menu" << endl;
                cout << "choice: ";
                n = get_int();

                switch (n) {
                case 1:
                    if (user_auth()) {
                        while (true) {
                            cout << "Password: ";
                            pass1 = get_string();

                            cout << "Enter again the password: ";
                            pass2 = get_string();

                            if (pass1 == pass2) {
                                user->password = wallet.hash_password(pass1);
                                break;
                            }
                            else
                                cout << "The password doesn't match" << endl;
                        }


                    }
                    else
                        cout << "Incorrect Password!" << endl;
                    break;
                case 2:
                    if (user_auth()) {
                        while (true) {
                            cout << "Enter your phone number (Should consist only of numbers): ";
                            try {
                                temp = get_int();
                                if (temp == -1) {
                                    continue;
                                }
                                user->phone = to_string(temp);
                                break;
                            }
                            catch (int err) {
                                cout << "The phone number should contain only numbers" << endl;
                            }
                        }
                    }
                    else
                        cout << "Incorrect Password!" << endl;
                    break;
                case 3:
                    break;
                default:
                    cout << "Select a valid option!" << endl;
                    continue;
                }
            }
                    break;
                case 5:
                    wallet.get_all_trans(user->username);
                    break;
                case 6:
                    wallet.currentUser = "";
                    break;

                default:
                    cout << "Select a valid option!" << endl;
            }
        }
        

    return 0;
}

bool user_auth() {
    string pass;
    cout << "Enter your password: ";
    pass = get_string();
    if (wallet.check_user(wallet.currentUser, pass))
        return true;
    else
        return false;
}
