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
    /*
    setlocale(LC_ALL,"en_US.UTF-8");
    struct Date date;
    struct Settings settings;
    settings.FormatRegion = 2;
    settings.FormatDelimiter = 0;
    settings.Uses24Hour = 0;
    date.Time.Timezone = -500;
    InitializeDate(&date);
    VerifySettings(&settings);
    unsigned long result = time(NULL);
    printf("The current time is %s(%+'li seconds since the Epoch)\n", asctime(gmtime(&result)), result);
    printf("Seconds in a year: %i\n", 365 * 86400);
    printf("Days since the UNIX Epoch: %li\n", result / 86400);
    unsigned long seconds = result % 86400;
    printf("Hours since the UNIX Epoch: %li\n", seconds / 3600);
    printf("Minutes since the UNIX Epoch: %li\n", (seconds % 3600) / 60);
    printf("Seconds since the UNIX Epoch: %li\n\n\n\n", ((seconds % 3600) % 60));
    char* str = malloc(sizeof(char) * 8);
    if (date.Time.Timezone == 0) str = "UTC";
    else asprintf(&str, "UTC %+i:%02i", date.Time.Timezone / 100, ((date.Time.Timezone % 100) * 60 / 100));
    printf("The current time is %s\n(%li seconds since the Epoch)\n", DateToString(date, settings), date.Time.Epoch);
    printf("Days since the UNIX Epoch: %i\n", date.Day);
    printf("Months since the UNIX Epoch: %i\n", date.Month);
    printf("Years since the UNIX Epoch: %i\n\n", date.Year);
    printf("Hours since the UNIX Epoch: %i\n", date.Time.Hour);
    printf("Minutes since the UNIX Epoch: %i\n", date.Time.Minute);
    printf("Seconds since the UNIX Epoch: %i\n", date.Time.Second);
    //printf("Leap years since 1970: %'i\n", CalculateLeapYears(date.Day));
    */
    initscr();
    raw();
    keypad(stdscr, TRUE);
    char* ch = calloc(10000, sizeof(char));
    int r;
    int k = 0;
    while ((r = getch()) != 'q')
    {
        ch[k] = (char)r;
        printw("Key pressed: %#x\n", (unsigned int)ch[k]);
        refresh();
        k++;
    }
    system("cls");
    puts(ch);
    printf("Buffer exceeded maximum buffer size (What the fuck are you doing with %i characters?)\n", MAX_BUFFER_SIZE);
    return 0;
}
// EOF: listening to inabakumori - Copy and Pastime