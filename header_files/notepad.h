#pragma once

// Imports? In my header file?
#include "errors.h"
// Enumerations


// Structures
struct ExperimentalSettings // dw ;)
{
    int CompileCharacters; // 0: Use tab/enter; 1: Use escape characters
    int UseNewlines;
    int UseTabs;
    int EnableExperimentalSettings; // Enable copy-paste 
};
struct Buffer
{
    char *Buffer;
    size_t BufferSize;
};

// Function Prototypes
enum CODE BufferText(struct Buffer *, int *);

/* EOF: Did you know that I like inabakumori? You did? H-how?
 *      Well, did you know that I don't understand Japanese?
 *      O-oh... you... inferred that...
 *      ...f-fuck you then.
 */