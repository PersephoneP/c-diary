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
/******************************************************
 *
 * GOALS:
 * 
 * 1.   Divert keyboard presses to local functions
 * 2.   If a certain set of keys are pressed, use the
 *      proper function. 
 * 3.   yeah that's about it
 * 4.   it doesn't seem that hard lol
 * 
 * 
 * 
 * 
 ******************************************************/
// Header Imports
#include <string.h>
#include <stdio.h>
#include "notepad.h"
#include "errors.h"
// Macro Hell
#define MAX_BUFFER_SIZE 2147483647 // Why would you have 2.1 billion characters in a diary? Use AWS for that.
#define null NULL
// Function Declarations

void CaptureInput(void);
void CaptureKey(void);
void SetDisplaySettings(void);
void ReadFile(void);
void WriteFile(void);
void ModifyEntry(void);
void Newline(void);
void Tab(void);
void DisplayNewline(void);
void DisplayTab(void);
void CaptureCopy(void);
void CaptureCut(void);
void CapturePaste(void);
void CaptureFind(void);
enum CODE BufferText(struct Buffer *buffer, int *key)
{
    // Did you know that I have never read "The ANSI C Programming Language?"
    size_t size = strlen(buffer->Buffer) + strlen((char)key) + 1;
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
    *key = 0; // reset key for next ncursesw char
    return SUCCESS;
}

// EOF: Listening to inabakumori - An image in the making