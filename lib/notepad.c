/******************************************************
 *
 * FILENAME: notepad.c
 * PROJECT NAME: Diary
 * LICENSE: TCI/C Unilicense (LICENSE)
 * Authors: Persephone Masalis Adonis
 *
 * Description:
 * The whole diary thing.
 *
 ******************************************************/

/******************************************************
 *
 * FUNCTIONS TO ADD:
 *
 * Capture Entry (fucking obviously idiot)
 * Capture Display Settings
 * Read-Write to CSV
 * Newlines and tabs
 * Ctrl-C, Ctrl-X and Ctrl-V Capture
 * Find (Ctrl-F)
 * filler
 * filler
 * filler
 * lorem ipsum dolor sit amet, consectetur adipiscing
 * elit, sed do eiusmod tempor incididunt ut
 *
 ******************************************************/
// Header Imports
#include <string.h>
#include <stdio.h>
#include <ncurses/curses.h>
#include "notepad.h"
#include "errors.h"
// Macro Hell
#define MAX_BUFFER_SIZE 2147483647 // Why would you have 2.1 billion characters in a diary? Use AWS for that.
#define null NULL
#define MEM_ALLOC_ERROR_MESSAGE "Failed to properly allocate memory D:\n"
// Function Declarations

void CaptureInput(struct Buffer *buffer, struct NotepadSettings *notepadSettings)
{
    
}
enum CODE EditText(struct Buffer *buffer)
{
    if (buffer->BufferSize < 10)
    {
        char * newBuffer = (char *)realloc(buffer, 10);
        if (newBuffer = NULL)
        {
            fprintf(stderr, MEM_ALLOC_ERROR_MESSAGE);
            return MEM_ALLOC_ERROR; // I LOVE REPEATING CODE OMFG;
        }
        buffer->Buffer = newBuffer;
        buffer->BufferSize = 10;
    }
    char r;
    int k = 0;
    while ((r = getch()) != 0x1B)
    {
        enum CODE result = BufferText(buffer, &r);
        // THE ISSUE WAS THAT I WAS FUCKING MOVING BUFFERSIZE INSTEAD OF BUFFER
        // END MY FUCKING LIFE
        //if (result != SUCCESS) return result;
        k++;
    }
    return SUCCESS;
}
void CaptureKey(void);
void SetDisplaySettings(void);
void ReadFile(void);
void WriteFile(void);
void ModifyEntry(void);
void Newline(void);
void Tab(void);
void DisplayNewline(void);
void DisplayTab(void);
void Find(void);
/*
void CaptureCopy(void);
void CaptureCut(void);
void CapturePaste(void);
void CaptureFind(void);
*/
enum CODE BufferText(struct Buffer *buffer, char *key)
{
    // Did you know that I have never read "The ANSI C Programming Language?"
    long size = strlen(buffer->Buffer) + strlen(key) + 1;
    ///*
    if (size > MAX_BUFFER_SIZE)
    {
        printf("Buffer exceeded maximum buffer size.\n(What the fuck are you doing with %lu characters? Are you trying to write an OS in a diary application?)", MAX_BUFFER_SIZE);
        return EXCESSIVE_BUFFERING;
    }
    if (size > buffer->BufferSize)
    {
        char *newBuffer = realloc(buffer->Buffer, size);
        // buffer->Buffer = realloc(buffer->Buffer, size);
        if (newBuffer == NULL)
        {
            fprintf(stderr, "Failed to properly allocate memory D:\n");
            return MEM_ALLOC_ERROR;
        }
        buffer->Buffer = newBuffer;
        buffer->BufferSize = size;
    }
    strcat(buffer->Buffer, key);
    *key = 0; // reset key for next ncursesw char (chatgpt wants me to change this to \0 but fuck chatgpt)
    //*/
    return SUCCESS;
}

// EOF: Listening to inabakumori - An image in the making