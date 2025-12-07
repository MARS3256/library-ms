// addMember.c - Add Member page
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "member.h"
#include "ui.h"
#include "sync.h"

void addMemberPage(void) {
    showTitle();
    printf("Add New Member\n");
    printf("--------------\n\n");
    
    if (memberCount >= MAX_MEMBERS) {
        printf("Member list is full. Cannot add more.\n");
        pressEnter();
        return;
    }
    
    Member newMember;
    
    // get unique ID
    while (1) {
        newMember.id = getIntInput("Member ID: ");
        if (isMemberIdExists(newMember.id)) {
            printf("ID %d already exists. Try another.\n", newMember.id);
        } else {
            break;
        }
    }
    
    getStringInput("Member Name: ", newMember.name, sizeof(newMember.name));
    
    // get department (3 chars max)
    char dept[10];
    getStringInput("Department (3 chars, e.g. CSE): ", dept, sizeof(dept));
    strncpy(newMember.dept, dept, 3);
    newMember.dept[3] = '\0';
    
    // capitalize
    if (newMember.name[0]) newMember.name[0] = toupper(newMember.name[0]);
    for (int i = 0; i < 3 && newMember.dept[i]; i++) {
        newMember.dept[i] = toupper(newMember.dept[i]);
    }
    
    if (confirmAction("Add this member?")) {
        acquireLock();
        members[memberCount++] = newMember;
        releaseLock();
        printf("Member added successfully.\n");
    } else {
        printf("Cancelled.\n");
    }
    
    pressEnter();
}
