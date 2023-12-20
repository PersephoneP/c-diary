#pragma once

// Imports? In my header file?
#include "errors.h"
#include <corecrt.h>
// Enumerations


// Structures
struct ExperimentalSettings // dw ;)
{
    int CompileCharacters; // 0: Use tab/enter; 1: Use escape characters
    // If CompileCharacters is 0,
    int Stream; // this actively displays the current buffer. Otherwise, the bufer is silently compiled.
    int UseNewlines; // this allows for ENTER to translate to \n\r
    int UseTabs; // this allows for TAB to translate to \t
    int EnableExperimentalSettings; // Enable copy-paste 
};
struct Buffer
{
    char *Buffer;
    size_t BufferSize;
};
struct NotepadSettings
{
    int Editing; // 0: Not editing; 1: Editing
};

// Function Prototypes
enum CODE BufferText(struct Buffer *, char *);
enum CODE EditText(struct Buffer *);

/* EOF: Did you know that I like inabakumori? You did? H-how?
 *      Well, did you know that I don't understand Japanese?
 *      O-oh... you... inferred that...
 *      ...f-fuck you then.
 */