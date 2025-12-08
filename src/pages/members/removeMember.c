// removeMember.c - Remove Member page
#include <stdio.h>
#include "member.h"
#include "ui.h"
#include "sync.h"
#include "fileio.h"

void removeMemberPage(void) {
    showTitle();
    printf("Remove Member\n");
    printf("-------------\n\n");
    
    if (memberCount == 0) {
        printf("No members to remove.\n");
        pressEnter();
        return;
    }
    
    int idx = findMember(1);
    
    if (idx < 0) {
        printf("No member selected.\n");
        pressEnter();
        return;
    }
    
    // show member details
    showTitle();
    printf("Member to remove:\n\n");
    printMemberDetailed(idx);
    printf("\n");
    
    if (confirmAction("Remove this member?")) {
        acquireLock();
        for (int i = idx; i < memberCount - 1; i++) {
            members[i] = members[i + 1];
        }
        memberCount--;
        releaseLock();
        saveMembersOnly();
        printf("Member removed successfully.\n");
    } else {
        printf("Cancelled.\n");
    }
    
    pressEnter();
}
