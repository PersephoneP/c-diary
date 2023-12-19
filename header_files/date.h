#pragma once

// Enumerations
enum Days
{
	SATURDAY,
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY
}; // go to hell Persephone

// Structures
struct Time
{
	unsigned long Epoch; // Internally used to store the time in seconds. The rest are solely for display purposes.
	int Timezone; // in 100ths of an hour. E.g. -450 for -4:30.
	int Hour;
	int Minute;
	int Second;
};
struct Date
{
	enum Days DayOfWeek;
	int Year;
	int Month;
	int Day;
	struct Time Time;
};
struct Settings
{
	int Uses24Hour; // Whether the time is in 24-hour format.
	int FormatRegion; // Formats: DDMMYYYY, YYYYMMDD, MMDDYYYY
	int FormatDelimiter; // Format Delimiter: DD/MM/YYYY, DD.MM.YYYY, DD-MM-YYYY, DD MM YYYY
};

// Function Prototypes
int DayOfWeek(struct Date);
int IsLeapYear(int);
void InitializeDate(struct Date *);
void ValidateDate(struct Date *);
enum Days GetDayOfWeek(int);
char* DaysToString(enum Days);
int CalculateLeapYears(int);
char* DateToString(struct Date, struct Settings);
void VerifySettings(struct Settings *);
// EOF: date.h