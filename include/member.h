#ifndef MEMBER_H
#define MEMBER_H

#define MAX_MEMBERS 100

typedef struct Member {
    int id;
    char name[50];
    char dept[4];   // 3 chars + null terminator
} Member;

extern Member members[MAX_MEMBERS];
extern int memberCount;

// core member functions (member.c)
int findMemberIndexById(int id);
int findMembersByName(const char *name, int *results, int maxResults);
int findMembersByDept(const char *dept, int *results, int maxResults);
int isMemberIdExists(int id);
void printMemberShort(int index);
void printMemberDetailed(int index);

// find member functions (findMember.c)
int findMember(int selectMode);   // selectMode=1 for selection, 0 for display

#endif
