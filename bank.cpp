#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Account{
private:
string AccountNo, Password;
int Balance;
public:
Account():AccountNo(""), Password(""),Balance(0){}

void setAccountNo(string id){
AccountNo = id;
}

void setPassword(string pw){
 Password = pw;
}

void setBalance(int balance){
 Balance = balance;
}

string getAccountNo(){
return AccountNo;
}

string getPassword(){
 return Password;
}

int getBalance(){
 return Balance;
}
};

void openAccount(Account user){
system("cls");
string id, pw;

cout<<"\tEnter Account No: ";
cin>>id;
user.setAccountNo(id);

 cout<<"\tEnter A Strong Password: ";
 cin>>pw;
 user.setPassword(pw);
 
 user.setBalance(0);
 
 ofstream outfile("accounts.txt", ios::app);
 if(!outfile){
cout<<"\tError: File Can't Open!"<<endl;
 }
 else{
outfile<<"\t"<<user.getAccountNo()<<" : "<<user.getPassword()<<" : "<<user.getBalance()<<endl<<endl;
cout<<"\tAccount Created Successfuly!"<<endl;
 }
 outfile.close();
Sleep(5000);
}

void addCash(){
system("cls");
string id;
cout<<"\tEnter Account No: ";
cin>>id;

ifstream infile("accounts.txt");
ofstream outfile("accounts_temp.txt");
if(!infile || !outfile){
cout<<"\tError: File Can't Open!"<<endl;
}

string line;
bool found = false;

while(getline(infile, line)){
stringstream ss;
ss<<line;
string userID, userPW;
int userBalance;
char delimiter;

ss>>userID>>delimiter>>userPW>>delimiter>>userBalance;
if(id == userID){
found = true;
int cash;
cout<<"\tEnter Cash: ";
cin>>cash;

int newBalance = userBalance + cash;
userBalance = newBalance;
outfile<<"\t"<<userID<<" : "<<userPW<<" : "<<userBalance<<endl;
cout<<"\tNew Balance Is: "<<userBalance<<endl;
}
else{
outfile<<line<<endl;
}
}
if(!found){
cout<<"\tEnter Valid Account No!"<<endl;
}
outfile.close();
infile.close();
remove("accounts.txt");
rename("accounts_temp.txt", "accounts.txt");
Sleep(5000);
}

void withdraw(){
string id, pw;
cout<<"\tEnter Account No: ";
cin>>id;

cout<<"\tEnter Password: ";
cin>>pw;
ifstream infile("accounts.txt");
ofstream outfile("accounts_temp.txt");
if(!infile || !outfile){
 cout<<"\tError: File Can't Open!"<<endl;
}

string line;
bool found = false;
while(getline(infile,line)){
stringstream ss;
ss<<line;
string userID, userPW;
int userBalance;
char delimiter;

ss>>userID>>delimiter>>userPW>>delimiter>>userBalance;

if(id==userID && pw == userPW){
found = true;
int cash;
cout<<"\tEnter Cash: ";
cin>>cash;
if(cash <= userBalance){
int newBalance = userBalance - cash;
userBalance = newBalance;
outfile<<"\t"<<userID<<" : "<<userPW<<" : "<<userBalance<<endl;	
cout<<"\tTransaction Was Successful!"<<endl;
cout<<"\tRemaining Balance: "<<userBalance<<endl;
}
else{
cout<<"\tLow Balance!"<<endl;
outfile<<"\t"<<userID<<" : "<<userPW<<" : "<<userBalance<<endl;	
}
}
else{
outfile<<line<<endl;
}
}
if(!found){
cout<<"\tInvalid Account No or Password!"<<endl;
}
outfile.close();
infile.close();
remove("accounts.txt");
rename("accounts_temp.txt", "accounts.txt");
Sleep(5000);
}

int main(int argc, char* argv[]) {
    Account user;

    if (argc > 1) {
        string action = argv[1];

        if (action == "create") {
            if (argc != 4) return 1;
            user.setAccountNo(argv[2]);
            user.setPassword(argv[3]);
            user.setBalance(0);
            ofstream outfile("accounts.txt", ios::app);
            if (!outfile) return 1;
            outfile << "\t" << user.getAccountNo() << " : " << user.getPassword() << " : " << user.getBalance() << endl << endl;
            outfile.close();
            return 0;
        }

        if (action == "deposit") {
            if (argc != 4) return 1;
            string id = argv[2];
            int cash = stoi(argv[3]);
            ifstream infile("accounts.txt");
            ofstream outfile("accounts_temp.txt");
            if (!infile || !outfile) return 1;
            string line;
            bool found = false;
            while (getline(infile, line)) {
                stringstream ss;
                ss << line;
                string userID, userPW;
                int userBalance;
                char delimiter;
                ss >> userID >> delimiter >> userPW >> delimiter >> userBalance;
                if (id == userID) {
                    found = true;
                    int newBalance = userBalance + cash;
                    userBalance = newBalance;
                    outfile << "\t" << userID << " : " << userPW << " : " << userBalance << endl;
                    cout << userBalance << endl;
                } else {
                    outfile << line << endl;
                }
            }
            outfile.close();
            infile.close();
            remove("accounts.txt");
            rename("accounts_temp.txt", "accounts.txt");
            if (!found) cout << "Invalid Account Number" << endl;
            return 0;
        }

        if (action == "withdraw") {
            if (argc != 5) return 1;
            string id = argv[2];
            string pw = argv[3];
            int cash = stoi(argv[4]);
            ifstream infile("accounts.txt");
            ofstream outfile("accounts_temp.txt");
            if (!infile || !outfile) return 1;
            string line;
            bool found = false;
            while (getline(infile, line)) {
                stringstream ss;
                ss << line;
                string userID, userPW;
                int userBalance;
                char delimiter;
                ss >> userID >> delimiter >> userPW >> delimiter >> userBalance;
                if (id == userID && pw == userPW) {
                    found = true;
                    if (cash <= userBalance) {
                        int newBalance = userBalance - cash;
                        userBalance = newBalance;
                        outfile << "\t" << userID << " : " << userPW << " : " << userBalance << endl;
                        cout << userBalance << endl;
                    } else {
                        cout << "Low Balance" << endl;
                        outfile << "\t" << userID << " : " << userPW << " : " << userBalance << endl;
                    }
                } else {
                    outfile << line << endl;
                }
            }
            outfile.close();
            infile.close();
            remove("accounts.txt");
            rename("accounts_temp.txt", "accounts.txt");
            if (!found) cout << "Invalid Account No or Password" << endl;
            return 0;
        }

        return 1;
    }

    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Bank Account Management System" << endl;
        cout << "\t*****************************************" << endl;
        cout << "\t1.Open New Account." << endl;
        cout << "\t2.Add Cash." << endl;
        cout << "\t3.Withdraw Cash." << endl;
        cout << "\t4.Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        if (val == 1) {
            openAccount(user);
        } else if (val == 2) {
            addCash();
        } else if (val == 3) {
            withdraw();
        } else if (val == 4) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(2000);
        }
        Sleep(3000);
    }
}
