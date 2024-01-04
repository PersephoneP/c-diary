/******************************************************
 *
 * FILENAME: main.c
 * PROJECT NAME: Diary
 * LICENSE: TCI/C Unilicense (LICENSE)
 * Authors: Persephone Masalis Adonis
 *
 * Description:
 * diary
 *
 ******************************************************/


// Header imports
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time
#include <locale.h>
#include <string.h>
#include <ncurses/curses.h>
#include "date.h"
#include "notepad.h"
// #include <stdbool.h> // Commented out because I might not need it

// Macros
#define MAX_BUFFER_SIZE 2147483647

// Global variables


// Main function
int main(void)
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    struct Buffer buffer;
    struct NotepadFlags flags;
    InitializeBuffer(&buffer, 7);
    CleanBuffer(&buffer);
    // char r;
    // int k = 0;
    CaptureInput(&buffer, &flags);
    // EditText(&buffer);
    system("cls");
    puts(buffer.Buffer);
    return 0;
}
// EOF: listening to inabakumori - Copy and Pastime