// member.c - Core member data and functions
#include <stdio.h>
#include <string.h>
#include "member.h"

Member members[MAX_MEMBERS];
int memberCount = 0;

// find member index by ID, returns -1 if not found
int findMemberIndexById(int id) {
    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == id) return i;
    }
    return -1;
}

// find members by name, returns count of matches
int findMembersByName(const char *name, int *results, int maxResults) {
    int count = 0;
    for (int i = 0; i < memberCount && count < maxResults; i++) {
        if (strstr(members[i].name, name) != NULL) {
            results[count++] = i;
        }
    }
    return count;
}

// find members by department, returns count of matches
int findMembersByDept(const char *dept, int *results, int maxResults) {
    int count = 0;
    for (int i = 0; i < memberCount && count < maxResults; i++) {
        if (strstr(members[i].dept, dept) != NULL) {
            results[count++] = i;
        }
    }
    return count;
}

// check if member ID exists
int isMemberIdExists(int id) {
    return findMemberIndexById(id) != -1;
}

// print short member info
void printMemberShort(int index) {
    printf("Name: %s\n", members[index].name);
    printf("Dept: %s\n", members[index].dept);
}

// print detailed member info
void printMemberDetailed(int index) {
    printf("Name: %s\n", members[index].name);
    printf("ID: %d\n", members[index].id);
    printf("Department: %s\n", members[index].dept);
}
