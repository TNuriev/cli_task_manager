#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "../include/struct.h"

using namespace std;


struct CommandLineArgs {
    string command;
    vector<string> args;
};


CommandLineArgs ParseCommandLineArgs(int argc, char* argv[]){
    CommandLineArgs args;
    if (argc > 1){
        args.command = argv[1];
        for (int i = 2; i < argc; i++){
            args.args.push_back(argv[i]);
        }
    }
    return args;
}

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

void add(string name){
    Task p;
    p.name = name;
    p.status = "todo";
    p.id = stoi(GetNumber());
    p.date_create = chrono::system_clock::now();
    p.date_end = chrono::system_clock::now();
    vector<Task> tasks = load_json();
    tasks.push_back(p);
    write_json(tasks);

    cout << "Task added successfully (ID: " << p.id << ")" << "\n";
}

void remove (int id){
    vector<Task> tasks = load_json();
    tasks.erase(tasks.begin() + id - 1);
    write_json(tasks);
}


void update(int id, string new_name){
    vector<Task> tasks = load_json();
    tasks[id - 1].name = new_name;
    tasks[id - 1].date_end = chrono::system_clock::now();
    write_json(tasks);
}

void markInProgress(int id){
    vector<Task> tasks = load_json();
    tasks[id - 1].status = "in-progress";
    tasks[id - 1].date_end = chrono::system_clock::now();
    write_json(tasks);
}

void markDone(int id){
    vector<Task> tasks = load_json();
    tasks[id - 1].status = "done";
    tasks[id - 1].date_end = chrono::system_clock::now();
    write_json(tasks);
}

void list(){
    vector<Task> tasks = load_json();
    for (auto &task: tasks){
        cout << "name: " << task.name << endl;
        cout << "status: " << task.status << endl;
        cout << "id: " << task.id << endl; 
        cout << "date-create: " << task.date_create << endl;
        cout << "date-end: " << task.date_end << endl;
        cout << endl;
    }
}

void list(string status){
    vector<Task> tasks = load_json();
    for (auto &task: tasks){
        if (task.status != status) continue;
        cout << "name: " << task.name << endl;
        cout << "status: " << task.status << endl;
        cout << "id: " << task.id << endl; 
        cout << "date-create: " << task.date_create << endl;
        cout << "date-end: " << task.date_end << endl;
        cout << endl;
    }
}

int main(int argc, char* argv[]) {

    CommandLineArgs args = ParseCommandLineArgs(argc, argv);
    if (args.command.empty()){
        cout << "Error: uncorrect input" << endl;
    }
    else{
        if (args.command == "add") {add(args.args[0]);}
        else if (args.command == "delete") {remove(stoi(args.args[0]));}
        else if (args.command == "update") {update(stoi(args.args[0]), args.args[1]);}
        else if (args.command == "mark-in-progress") {markInProgress(stoi(args.args[0]));}
        else if (args.command == "mark-done") {markDone(stoi(args.args[0]));}
        else if (args.command == "list" && argc == 2) {list();}
        else if (args.command == "list") {list(args.args[0]);}
    }

    return 0;
}