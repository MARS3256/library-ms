# Library Management System
build

`gcc -std=c11 -Wall -Wextra -Werror -Iinclude src/main.c src/book.c src/ui.c -o lms`

A simple console-based library management system written in C and organized into modular components.

## Project layout

- `include/book.h` / `src/book.c` – data model, in-memory storage, and CRUD/search routines for books.
- `include/ui.h` / `src/ui.c` – console input/output helpers and the search menu workflow.
- `src/main.c` – top-level menu loop that wires UI actions to the book module.

## Folder & file structure

```
oslab/
├── include/
│   ├── book.h    // Book struct + shared declarations
│   └── ui.h      // UI helper declarations
├── src/
│   ├── main.c    // menu loop that calls into book/ui modules
│   ├── book.c    // book storage + CRUD/search logic
│   └── ui.c      // screen, input, and search menu helpers
├── lms           // compiled binary (after build)
└── README.md     // build/run notes and OS extensions
```

Keep each module small: `main.c` orchestrates, `book.*` owns data, and `ui.*` handles presentation so future OS features can drop into focused files.

## Build

```bash
gcc -std=c11 -Wall -Wextra -Werror -Iinclude src/main.c src/book.c src/ui.c -o lms
```

## Run

```bash
./lms
```

The program manages up to 100 books in memory, allowing users to add, list, and search by ID, name, author, or year.

## Proposed OS additions (minimal code, short comments)

### Updated folder & file structure

```
oslab/
├── include/
│   ├── book.h         // Book struct + shared declarations
│   ├── ui.h           // UI helper declarations
│   ├── scheduler.h    // Scheduling algorithms (FCFS, RR, Priority)
│   ├── sync.h         // Mutex/semaphore wrappers
│   ├── fileio.h       // Catalog save/load (buffered vs unbuffered)
│   └── analytics.h    // Metrics tracking (wait time, throughput)
├── src/
│   ├── main.c         // menu loop + OS feature orchestration
│   ├── book.c         // book storage + CRUD/search logic
│   ├── ui.c           // screen, input, and search menu helpers
│   ├── scheduler.c    // request queue + FCFS/RR/Priority handlers
│   ├── sync.c         // mutex init/lock/unlock helpers
│   ├── fileio.c       // catalog persistence + buffered/unbuffered I/O
│   └── analytics.c    // timestamp collection + CSV export
├── data/
│   ├── catalog.dat    // binary catalog dump
│   ├── transactions.log // text log of borrow/return events
│   └── metrics.csv    // exported scheduling metrics
├── lms                // compiled binary
└── README.md
```

### Feature breakdown

#### 1. Processes & Scheduling (`scheduler.h/c`)
- **What**: Simulate multiple users (processes/threads) borrowing/returning books concurrently.
- **How**:
  - Define a `Request` struct: `{int userId; int bookId; char action; time_t arrivalTime;}`.
  - Maintain a global request queue (array or linked list).
  - Implement three schedulers:
    - `fcfs_schedule()` – process requests in arrival order.
    - `rr_schedule(int quantum)` – round-robin with time slice.
    - `priority_schedule()` – sort by user priority field.
  - Fork/pthread_create workers; each pops a request, processes it, logs timestamp.
- **Files**: `include/scheduler.h`, `src/scheduler.c`.

#### 2. Synchronization (`sync.h/c`)
- **What**: Protect shared catalog and logs from race conditions.
- **How**:
  - Declare `pthread_mutex_t catalog_lock;` and `sem_t log_sem;`.
  - Wrap every `books[]` read/write in `pthread_mutex_lock/unlock`.
  - Wrap file appends in semaphore wait/post.
  - Simple helpers: `init_locks()`, `acquire_catalog()`, `release_catalog()`.
- **Files**: `include/sync.h`, `src/sync.c`.

#### 3. File I/O (`fileio.h/c`)
- **What**: Persist catalog to disk; compare buffered vs unbuffered I/O.
- **How**:
  - `save_catalog_buffered()` – use `fopen/fwrite/fclose`.
  - `save_catalog_unbuffered()` – use `open/write/close`.
  - `load_catalog()` – read `data/catalog.dat` into `books[]` array.
  - `log_transaction(Request r)` – append to `data/transactions.log`.
  - Measure time with `clock_gettime()` and print comparison.
- **Files**: `include/fileio.h`, `src/fileio.c`.


#### 5. Analysis (`analytics.h/c`)
- **What**: Measure and visualize scheduling performance.
- **How**:
  - Track per-request: `arrivalTime`, `startTime`, `completionTime`.
  - Compute: `waitTime = startTime - arrivalTime`, `turnaroundTime = completionTime - arrivalTime`.
  - Export CSV: `scheduler,avgWaitTime,avgTurnaround,throughput`.
  - Python script reads CSV and plots bar charts (matplotlib).
- **Files**: `include/analytics.h`, `src/analytics.c`, `scripts/plot.py`.

### Build command (updated)

```bash
gcc -std=gnu11 -Wall -Wextra -Werror -pthread -Iinclude \
  src/main.c src/book.c src/ui.c src/scheduler.c src/sync.c \
  src/fileio.c src/analytics.c -o lms
```

### Minimal code style
- Keep functions under 30 lines.
- Use single-line comments: `// acquire lock before modifying books[]`.
- Avoid nested ifs; use early returns.
- Name variables clearly: `avgWaitTime` not `awt`.
