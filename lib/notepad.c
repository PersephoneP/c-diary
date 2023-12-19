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


// Macro Hell


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

// EOF