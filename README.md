# Library Management System

A simple console-based library management system in C with OS concepts.

## Features

### Book Management
- Add, edit, remove books
- Search by ID, name, author, year
- List all books

### Member Management
- Add, edit, remove members
- Search by ID, name, department
- List all members

### Book Issuing
- Direct issue (AVAILABLE → BORROWED)
- New request (AVAILABLE → REQUESTED)
- Approve/deny requests (REQUESTED → BORROWED)
- Return book (BORROWED → AVAILABLE)

### Data Persistence
- Save/load books and members to files
- Auto-save on exit

### FCFS Simulation
- Generate random actions with arrival times
- Process actions using FCFS queue
- Semaphore lock for critical sections
- Calculate waiting time and burst time

## How to Compile

### Windows
```bat
compile.bat
```

### Linux
```bash
chmod +x compile.sh
./compile.sh
```

## How to Run

### Windows
```bat
lms.exe
```

### Linux
```bash
./lms
```



## OS Concepts Used

- **Semaphore**: Binary semaphore for critical section lock
- **FCFS Scheduling**: First-Come-First-Serve queue for actions
- **File I/O**: Buffered read/write with lock protection
