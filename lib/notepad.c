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
#include <stdlib.h>
#include <ncurses/curses.h>
#include "notepad.h"
#include "errors.h"
#include "keys.h"
// Macro Hell
#define MAX_BUFFER_SIZE 2147483647 // Why would you have 2.1 billion characters in a diary? Use AWS for that.
#define null NULL
#define MEM_ALLOC_ERROR_MESSAGE "Failed to properly allocate memory D:\n"
// Function Declarations
void CaptureInput(struct Buffer *buffer, struct NotepadFlags *flags)
{
    char KeyBuffer = KEY_NULL;
    printw("Select mode to enter\n");
    printw("\t(1). Append Mode\n");
    printw("\t(2). uninitialized\n");
    printw("\t(3). uninitialized\n");
    printw("\t(4). uninitialized\n");
    printw("\t(5). uninitialized\n");
    printw("\t(6). uninitialized\n");
    printw("\t(7). uninitialized\n");
    printw("\t(8). uninitialized\n");
    printw("\t(9). uninitialized\n");
    printw("\t(0). uninitialized\n");
    if ((KeyBuffer = getch()) == KEY_1)
    {
        clear();
        refresh();
        EditText(buffer);
    }
}
enum CODE EditText(struct Buffer *buffer)
{
    // some mem heap bug here idk if i fixed it
    if (buffer->BufferSize < 10)
    {
        char* newBuffer = realloc(buffer->Buffer, 10);
        if (newBuffer == NULL)
        {
            fprintf(stderr, MEM_ALLOC_ERROR_MESSAGE);
            return MEM_ALLOC_ERROR; // I LOVE REPEATING CODE OMFG;
        }
        buffer->Buffer = newBuffer;
        buffer->BufferSize = 10;
    }
    printw("Begin typing.\n");
    CleanBuffer(buffer);
    char r;
    while ((r = getch()) != KEY_ESCP)
    {
        printf("printed: %#02x\n", (unsigned char)r);
        enum CODE result = BufferText(buffer, &r);
        // THE ISSUE WAS THAT I WAS FUCKING MOVING BUFFERSIZE INSTEAD OF BUFFER
        // END MY FUCKING LIFE
        if (result != SUCCESS) return result;
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
    if (buffer->BufferSize > MAX_BUFFER_SIZE)
    {
        printf("Buffer exceeded maximum buffer size.\n(What the fuck are you doing with %lu characters? Are you trying to write an OS in a diary application?)", MAX_BUFFER_SIZE);
        return EXCESSIVE_BUFFERING;
    }
    long size = strlen(buffer->Buffer) + strlen(key) + 1;
    if (size > buffer->BufferSize)
    {
        char* newBuffer = (char*)realloc(buffer->Buffer, size);
        if (newBuffer == NULL)
        {
            fprintf(stderr, "Failed to properly allocate memory D:\n");
            return MEM_ALLOC_ERROR;
        }
        buffer->Buffer = newBuffer;
        buffer->BufferSize = size;
    }
    Concatenate(buffer, key);
    *key = KEY_NULL; // reset key for next ncursesw char (chatgpt wants me to change this to \0 but fuck chatgpt)
    return SUCCESS;
}

void CleanBuffer(struct Buffer *buffer)
{
    for (int i = 0; i < buffer->BufferSize; i++)
    {
        buffer->Buffer[i] = 0x00;
    }
    buffer->Buffer[buffer->BufferSize - 1] = '\0';
    buffer->Position = 0;
}
void InitializeBuffer(struct Buffer *buffer, int bufferSize)
{
    buffer->BufferSize = bufferSize;
    buffer->Buffer = malloc(sizeof(char) * buffer->BufferSize);
    for (int i = 0; i < buffer->BufferSize; i++)
    {
        buffer->Buffer[i] = KEY_NULL;
    }
}
enum CODE Concatenate(struct Buffer *buffer, char *key)
{
    if (strlen(key) > 1) return INVALID_PARAMETER;
    buffer->Buffer[buffer->Position] = *key;
    buffer->Position++;
    return SUCCESS;
}
// EOF: Listening to inabakumori - An image in the making