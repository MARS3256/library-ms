// manageMembers.c - Manage Members menu page
#include <stdio.h>
#include "ui.h"

// forward declarations
void findMemberPage(void);
void listMembersPage(void);
void addMemberPage(void);
void removeMemberPage(void);
void editMemberPage(void);

void manageMembersPage(void) {
    int choice;
    
    while (1) {
        showTitle();
        printf("Manage Members\n");
        printf("--------------\n\n");
        printf("1. Find Member\n");
        printf("2. List All Members\n");
        printf("3. Add Member\n");
        printf("4. Remove Member\n");
        printf("5. Edit Member\n");
        printf("6. Back\n\n");
        
        choice = getIntInput("Choice: ");
        
        switch (choice) {
            case 1: findMemberPage(); break;
            case 2: listMembersPage(); break;
            case 3: addMemberPage(); break;
            case 4: removeMemberPage(); break;
            case 5: editMemberPage(); break;
            case 6: return;
            default:
                printf("Invalid option.\n");
                pressEnter();
        }
    }
}
