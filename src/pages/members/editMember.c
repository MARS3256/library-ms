// editMember.c - Edit Member page
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "member.h"
#include "ui.h"
#include "sync.h"
#include "fileio.h"

void editMemberPage(void) {
    showTitle();
    printf("Edit Member\n");
    printf("-----------\n\n");
    
    if (memberCount == 0) {
        printf("No members to edit.\n");
        pressEnter();
        return;
    }
    
    int idx = findMember(1);
    
    if (idx < 0) {
        printf("No member selected.\n");
        pressEnter();
        return;
    }
    
    showTitle();
    showTitle();
    printf("Editing Member (ID: %d)\n", members[idx].id);
    
    char input[50];
    
    // edit name
    printf("Current Name: %s\n", members[idx].name);
    getStringInput("New Name: ", input, sizeof(input));
    if (strlen(input) > 0 && strcmp(input, "0") != 0) {
        acquireLock();
        strcpy(members[idx].name, input);
        if (members[idx].name[0]) {
            members[idx].name[0] = toupper(members[idx].name[0]);
        }
        releaseLock();
    }
    
    // edit department
    printf("\nCurrent Department: %s\n", members[idx].dept);
    getStringInput("New Department (3 chars, 0 to skip): ", input, sizeof(input));
    if (strlen(input) > 0 && strcmp(input, "0") != 0) {
        acquireLock();
        strncpy(members[idx].dept, input, 3);
        members[idx].dept[3] = '\0';
        for (int i = 0; i < 3 && members[idx].dept[i]; i++) {
            members[idx].dept[i] = toupper(members[idx].dept[i]);
        }
        releaseLock();
    }
    
    saveMembersOnly();
    printf("\nMember updated successfully.\n");
    pressEnter();
}
