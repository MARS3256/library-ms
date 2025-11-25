/*
Library Management System
-------------------------
Made by: 
Muhammad As-Adur Rahman Sajid (233014037)

*/


#include <stdio.h>
#include <stdlib.h>

#include "book.h"
#include "ui.h"
#include "sync.h"
#include "fileio.h"
#include "scheduler.h"
#include "analytics.h"

// generate random requests for simulation
static void generateRequests(int n)
{
    for (int i = 0; i < n; i++) {
        Request r = {
            .userId = i + 1,
            .bookId = (rand() % 10) + 1,
            .action = (i % 2 == 0) ? 'B' : 'R',
            .priority = rand() % 5
        };
        addRequest(r);
    }
}

// run scheduling simulation submenu
static void runSimulation(void)
{
    showTitle();
    printf("Requests to simulate: ");
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) { clearInputBuffer(); return; }
    clearInputBuffer();

    printf("Scheduler:\n1. FCFS\n2. Round-Robin\n3. Priority\nChoice: ");
    int choice;
    if (scanf("%d", &choice) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    generateRequests(n);
    resetMetrics();

    switch (choice) {
        case 1: runFCFS(); break;
        case 2: runRoundRobin(10); break;
        case 3: runPriority(); break;
        default: printf("Invalid.\n"); return;
    }

    printMetrics();
    exportCSV("data/metrics.csv");
    proceed();
}

// save/load catalog submenu
static void catalogMenu(void)
{
    showTitle();
    printf("1. Save Catalog\n");
    printf("2. Load Catalog\n");
    printf("Choice: ");
    int choice;
    if (scanf("%d", &choice) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    switch (choice) {
        case 1:
            saveCatalog("data/catalog.txt");
            printf("Catalog saved.\n");
            break;
        case 2:
            loadCatalog("data/catalog.txt");
            printf("Catalog loaded.\n");
            break;
        default:
            printf("Invalid.\n");
            break;
    }
    proceed();
}

int main(void)
{
    initLocks();          // initialize mutexes/semaphores
    loadCatalog("data/catalog.txt"); // load saved catalog if exists

    while (1)
    {
        showTitle();
        printf("1. Add Books\n");
        printf("2. List All Books\n");
        printf("3. Find Book\n");
        printf("4. Save/Load Catalog\n");
        printf("5. Run Scheduling Simulation\n");
        printf("6. Exit\n");
        printf("Choice: ");
        int option;
        if (scanf("%d", &option) != 1)
        {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (option)
        {
        case 1:
            addBooks();
            break;
        case 2:
            listAllBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            catalogMenu();
            break;
        case 5:
            runSimulation();
            break;
        case 6:
            saveCatalog("data/catalog.txt");
            destroyLocks();
            return 0;
        default:
            printf("Invalid option.\n");
            proceed();
            break;
        }
    }
}
