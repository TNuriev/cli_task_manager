#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

string GetNumber(){
    ifstream in("tracker.json");
    int maxNumber = 0;
    string word;
    while (in >> word){
        stringstream ss(word);
        int num;
        if (ss >> num){
            if (num > maxNumber){
                maxNumber = num;
            }
        }
    }
    in.close();
    return to_string(maxNumber + 1);

}

void add(vector<string>& description){
    // ifstream in;  
    ofstream out("tracker.json", ios::app);
    out << GetNumber() << " : ";
    for (auto &p: description){
        out << p << " ";
    }
    out << "mark-in-progress" << "\n";
    out.close();
    // stringstream buffer;
    // buffer << file.rdbuff();
    // in.open("hello.txt"); 
    // // если файл открыт
    // if (in.is_open())
    // {
    //     cout << "ura" << endl;
    // }
    // cout << "bad" << endl;

}

void check (string& command, vector<string>& description){
    if (command == "add"){
        add(description);
    }
    else if (command == "update"){

    }
    else if (command == "delete"){

    }
    else if (command == "mark-in-progress"){

    }
    else if (command == "mark-done"){

    }
    else if (command == "list"){

    }
    else{
        cout << "Uncorrect command!";
    }
}
void parse(string& command){
    vector<string> words;
    size_t start = 0, end;
    while ((end = command.find(" ", start)) != std::string::npos){
        if (start != end){
            words.push_back(command.substr(start, end - start));
        }
        start = end + 1;
    }
    if (start < command.length()){
        words.push_back(command.substr(start));
    }
    check(words[0], words);

}



int main() {
    cout << "Hello, user! " << "What you want to do? " << endl;
    string com_f, com_sec;
    while (true) {
        cout << "Commands:" << endl;
        cout << "1) add " << endl;
        cout << "2) update (task number)   " << "delete (task number)   " << endl;
        cout << "3) mark-in-progress (task number)   " << " mark-done (task number)" << endl;
        cout << "4) list   ";
        cout << "list done   " << "list todo   " << "list in-progress" << endl;
        getline(cin, com_f);
        parse(com_f);

    }
    return 0;
}