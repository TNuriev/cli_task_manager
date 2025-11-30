#ifndef STRUCT_H
#define STRUCT_H
#include <string>
#include <vector>
#include <chrono>


struct Task
{
    std::string name;
    std::string status;
    int id;
    std::chrono::system_clock::time_point date_create;
    std::chrono::system_clock::time_point date_end;

    
};


std::vector<Task> load_json();
void write_json(std::vector<Task>);
#endif
