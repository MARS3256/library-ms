// findMember.c - Find Member (reusable for search & select)
#include <stdio.h>
#include <string.h>
#include "member.h"
#include "ui.h"

// search members, returns selected index or -1
// if selectMode=1: allows selection from results
// if selectMode=0: just displays results
int findMember(int selectMode) {
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Department\n\n");
    
    int choice = getIntInput("Choice: ");
    int results[MAX_MEMBERS];
    int count = 0;
    
    switch (choice) {
        case 1: {
            int id = getIntInput("Enter Member ID: ");
            int idx = findMemberIndexById(id);
            if (idx >= 0) {
                showTitle();
                printf("Member Found:\n\n");
                printMemberDetailed(idx);
                if (selectMode) return idx;
            } else {
                printf("Member with ID %d not found.\n", id);
            }
            return -1;
        }
        case 2: {
            char name[50];
            getStringInput("Enter Member Name: ", name, sizeof(name));
            count = findMembersByName(name, results, MAX_MEMBERS);
            break;
        }
        case 3: {
            char dept[4];
            getStringInput("Enter Department: ", dept, sizeof(dept));
            count = findMembersByDept(dept, results, MAX_MEMBERS);
            break;
        }
        default:
            printf("Invalid option.\n");
            return -1;
    }
    
    if (count == 0) {
        printf("No members found.\n");
        return -1;
    }
    
    // show results
    showTitle();
    printf("Found %d member(s):\n\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d. %s (ID: %d, Dept: %s)\n", i + 1,
            members[results[i]].name, members[results[i]].id,
            members[results[i]].dept);
    }
    
    if (!selectMode) return -1;
    
    // select from results
    int sel = getIntInput("\nSelect (0 to cancel): ");
    if (sel < 1 || sel > count) return -1;
    
    return results[sel - 1];
}

// page wrapper for menu
void findMemberPage(void) {
    showTitle();
    printf("Find Member\n");
    printf("-----------\n\n");
    
    findMember(0);  // display only mode
    pressEnter();
}
