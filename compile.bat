@echo off
cd /d "%~dp0"
set GCC=C:\ProgramData\mingw64\mingw64\bin\gcc.exe

echo Compiling...
"%GCC%" -I./include -o lms.exe ^
    src/main.c ^
    src/ui.c ^
    src/book.c ^
    src/member.c ^
    src/fileio.c ^
    src/sync.c ^
    src/simulation/generator.c ^
    src/simulation/action.c ^
    src/simulation/simulator.c ^
    src/pages/runSimulation.c ^
    src/pages/books/manageBooks.c ^
    src/pages/books/findBook.c ^
    src/pages/books/listBooks.c ^
    src/pages/books/addBook.c ^
    src/pages/books/removeBook.c ^
    src/pages/books/editBook.c ^
    src/pages/members/manageMembers.c ^
    src/pages/members/findMember.c ^
    src/pages/members/listMembers.c ^
    src/pages/members/addMember.c ^
    src/pages/members/removeMember.c ^
    src/pages/members/editMember.c ^
    src/pages/issue/issueBooks.c ^
    src/pages/issue/approveRequests.c ^
    src/pages/issue/returnBook.c ^
    src/pages/issue/directIssue.c ^
    src/pages/data/saveLoadData.c

if exist lms.exe (
    echo Build SUCCESS
) else (
    echo Build FAILED
)

pause
