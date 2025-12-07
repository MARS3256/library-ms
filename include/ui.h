#ifndef UI_H
#define UI_H

// common UI functions
void clearScreen(void);
void showTitle(void);
void clearInputBuffer(void);
void pressEnter(void);
int confirmAction(const char *message);
int getIntInput(const char *prompt);
void getStringInput(const char *prompt, char *buffer, int size);

#endif
