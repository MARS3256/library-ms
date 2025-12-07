// listMembers.c - List All Members page
#include <stdio.h>
#include "member.h"
#include "ui.h"

void listMembersPage(void) {
    showTitle();
    printf("All Members\n");
    printf("-----------\n\n");
    printf("Total Members: %d\n\n", memberCount);
    
    if (memberCount == 0) {
        printf("No members registered.\n");
    } else {
        for (int i = 0; i < memberCount; i++) {
            printf("%d. %s\n", i + 1, members[i].name);
            printf("   ID: %d | Department: %s\n\n", 
                members[i].id, members[i].dept);
        }
    }
    
    pressEnter();
}
