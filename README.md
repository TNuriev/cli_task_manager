1) *Clone the repository:*

git clone https://github.com/TNuriev/cli_task_manager.git
cd cli_task_manager

2) *Build project:*
mkdir build
cd build
cmake --build .

3) *Run project:*
cd ../Debug
.\TaskManager add "New Task"

4) Adding a new task
.\TaskManager add "Buy groceries"
Output: Task added successfully (ID: 1)

Updating and deleting tasks
.\TaskManager  update 1 "Buy groceries and cook dinner"
.\TaskManager  delete 1

Marking a task as in progress or done
.\TaskManager  mark-in-progress 1
.\TaskManager  mark-done 1

Listing all tasks
.\TaskManager  list

Listing tasks by status
.\TaskManager  list done
.\TaskManager  list todo
.\TaskManager  list in-progress
