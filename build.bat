@echo off
REM Compile Library Management System
REM Uses MinGW GCC

cd /d "%~dp0"

REM Try to find gcc
set GCC_PATH=C:\ProgramData\mingw64\mingw64\bin\gcc.exe
if not exist "%GCC_PATH%" set GCC_PATH=gcc

echo ===================================
echo  Library Management System Builder
echo ===================================
echo.
echo Choose build option:
echo 1. Single File (lms_single.c) - Quick compile
echo 2. Full Version (src folder)  - Modular code
echo.
set /p choice="Enter choice (1 or 2): "

if "%choice%"=="1" goto single
if "%choice%"=="2" goto full
echo Invalid choice!
goto end

:single
echo.
echo Compiling Single File Version...
"%GCC_PATH%" -o lms.exe lms_single.c
goto check

:full
echo.
echo Compiling Full Modular Version...
"%GCC_PATH%" -I./include -o lms.exe ^
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
    src/pages/data/saveLoadData.c 2>&1
goto check

:check
if exist lms.exe (
    echo.
    echo Build successful!
    echo Run: lms.exe
) else (
    echo.
    echo Build failed! Check errors above.
)

:end
pause

