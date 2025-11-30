# Task Tracker

Sample solution for the [task-tracker](https://roadmap.sh/projects/task-tracker) challenge from [roadmap.sh](https://roadmap.sh/).

## How to run

Clone the repository and run the following command:

```bash
git clone https://github.com/TNuriev/cli_task_manager.git
cd cli_task_manager
```

Run the following command to build the project:

```bash
mkdir build
cd build
cmake ..
cmake --build .
cd ../Debug

# To add a task
./TaskManager add "Buy groceries"

# To update a task
./TaskManager update 1 "Buy groceries and cook dinner"

# To delete a task
./TaskManager delete 1

# To mark a task as in progress/done/todo
./TaskManager mark-in-progress 1
./TaskManager mark-done 1
./TaskManager mark-todo 1

# To list all tasks
./TaskManager list
./TaskManager list done
./TaskManager list todo
./TaskManager list in-progress
```
