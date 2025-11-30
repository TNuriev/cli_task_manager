#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <format>
#include <sstream>
#include "../include/struct.h"

std::string get_name(size_t pos, std::string &content){
    size_t pos_op = content.find("[", pos);
    size_t pos_cl = content.find("]", pos);
    size_t it = content.find("\"name\"", pos_op);
    size_t it_2 = content.find("\"", it + 9);
    std::string name = content.substr(it + 9, it_2 - it - 9);
    return name;
}

std::string get_status(size_t pos, std::string &content){
    size_t pos_op = content.find("[", pos);
    size_t pos_cl = content.find("]", pos);
    size_t it = content.find("\"status\"", pos_op);
    size_t it_2 = content.find(",", it + 1);
    std::string name = content.substr(it + 11, it_2 - it - 12);
    return name;
}

int get_id(size_t pos, std::string &content){
    size_t pos_op = content.find("[", pos);
    size_t pos_cl = content.find("]", pos);
    size_t it = content.find("\"id\"", pos_op);
    size_t it_2 = content.find(",", it + 1);
    std::string name = content.substr(it + 6, it_2 - it - 6);
    return std::stoi(name);
}

std::string get_date_create(size_t pos, std::string &content){
    size_t pos_op = content.find("[", pos);
    size_t pos_cl = content.find("]", pos);
    size_t it = content.find("\"date_create\"", pos_op);
    size_t it_2 = content.find("\"", it + 16);
    std::string name = content.substr(it + 16, it_2 - it - 16);
    return name;
}

std::string get_date_end(size_t pos, std::string &content){
    size_t pos_op = content.find("[", pos);
    size_t pos_cl = content.find("]", pos);
    size_t it = content.find("\"date_end\"", pos_op);
    size_t it_2 = content.find("\"", it + 13);
    std::string name = content.substr(it + 13, it_2 - it - 13);
    return name;
}

std::chrono::system_clock::time_point from_iso(const std::string& s)
{
    std::chrono::system_clock::time_point tp;
    std::istringstream iss(s);
    iss >> std::chrono::parse("%Y-%m-%dT%H:%M:%SZ", tp);
    return tp;
}

std::string normal_date(const std::chrono::system_clock::time_point& t){
    
     auto t_sec = std::chrono::floor<std::chrono::seconds>(t);
    return std::format("{:%Y-%m-%dT%H:%M:%SZ}", t_sec);

}
std::vector<Task> load_json(){
    std::ifstream in("tracker.json");
    std::vector<Task> tasks;
     if (!in) {
        std::cerr << "File not found, create new.\n";
        return tasks;
    }
    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    size_t task = content.find("task_");
    int count = 0;
    while ( task != std::string::npos) {
        std::string task_name;
        Task example;
        example.name = get_name(task, content);
        example.status = get_status(task, content); 
        example.id = get_id(task, content); 
        example.date_create = from_iso(get_date_create(task, content));
        example.date_end = from_iso(get_date_end(task, content));
        tasks.push_back(example);
        task = content.find("task_", task + 1);
        
    }
    return tasks;
}

void write_json(std::vector<Task> tasks){
    std::ofstream out("tracker.json");
    out << "{";
    out << "\n";
    int count = 1;
    for (int i = 0; i < tasks.size(); i++){
        out << "  \"task_" << std::to_string(count) << "\"" << ": [" << "\n"; 
        out << "    {" << "\n";
        out <<  "      \"name\": \"" << tasks[i].name << "\"," << "\n";
        out <<  "      \"status\": \"" << tasks[i].status <<  "\"," << "\n";
        out <<  "      \"id\": " << tasks[i].id  << " ," << "\n";
        out <<  "      \"date_create\": \"" << normal_date(tasks[i].date_create)  << "\"," << "\n";
        out <<  "      \"date_end\": \"" << normal_date(tasks[i].date_end) << "\"" << "\n";
        out << "    }" << "\n";
        if (i < tasks.size() - 1){
            out << "  ]," << "\n";
        }
        else{
            out << "  ]" << "\n";
        }
        count++;
    }
     out << "}";

}