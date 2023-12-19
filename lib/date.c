/******************************************************
 *
 * FILENAME: date.c
 * PROJECT NAME: Diary
 * LICENSE: TCI/C Unilicense (LICENSE)
 * Authors: Persephone Masalis Adonis
 *
 * Description:
 * Datetime functions.
 ******************************************************/

// Header imports
#include "date.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Macro Hell
	// None of these are necessary but will be used for... readability
	// (totally not because I'm fucking retarded no trust me I'm a mentally sane person)
#define SECONDS_PER_DAY 86400
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60
#define HOURS_PER_DAY 24
#define DAYS_PER_YEAR 365
#define DAYS_PER_LEAP_YEAR 366
#define UNIX_EPOCH_YEAR 1970
	// make
	// make run
	// make clean

// Function declaration
int DayOfWeek(struct Date date)
{
	if (date.Year < 1753) return -1; // This formula does not work for years before 1753
	// EDIT: kinda unnecessary since an epoch time of 0xFFFF (assuming two's complement) is 20:45:52 on 13 January 1901
	int MonthKey[] = 
	{
		1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6
	};
	if (IsLeapYear(date.Year) == 1)
	{
		MonthKey[0] = 0;
		MonthKey[1] = 3;
	}
	int k = (date.Year % 100);
	k += (k / 4) + MonthKey[date.Month - 1] + date.Day;
	if (date.Year < 1900) k += 2;
	if (date.Year < 1800) k += 2; // 2 instead of 4 because 1800 is less than 1900 so the first 2 is already added.
	if (date.Year >= 2000 && date.Year < 2100) k--;
	return k % 7;
}
int IsLeapYear(int year)
{
	if (year % 400 == 0) return 1; // years divisible by 400 are leap years
	else return (year % 4 == 0 && year % 100 != 0) ? 1 : 0; // years divisible by 4 but not 100 are leap years
}
void InitializeDate(struct Date *date)
{
	date->Time.Epoch = time(NULL) + (date->Time.Timezone / 100) * SECONDS_PER_HOUR + ((date->Time.Timezone % 100) * MINUTES_PER_HOUR / 100) * MINUTES_PER_HOUR;
	// First, set up hours, minutes, and seconds
	date->Time.Hour = ((date->Time.Epoch % SECONDS_PER_DAY) / SECONDS_PER_HOUR);
	date->Time.Minute = (((date->Time.Epoch % SECONDS_PER_DAY) % SECONDS_PER_HOUR) / MINUTES_PER_HOUR);
	date->Time.Second = (((date->Time.Epoch % SECONDS_PER_DAY) % SECONDS_PER_HOUR) % SECONDS_PER_MINUTE);
	// Then days.
	date->Day = date->Time.Epoch / SECONDS_PER_DAY;
	// Then we can validate the date.
	ValidateDate(date);
}
void ValidateDate(struct Date *date)
{
	// Validate second
	while (date->Time.Second > 59)
	{
		date->Time.Second -= SECONDS_PER_MINUTE;
		date->Time.Minute++;
	}
	while (date->Time.Second < 0)
	{
		date->Time.Second += SECONDS_PER_MINUTE;
		date->Time.Minute--;
	}
	// Validate minute
	while (date->Time.Minute > 59)
	{
		date->Time.Minute -= MINUTES_PER_HOUR;
		date->Time.Hour++;
	}
	while (date->Time.Minute < 0)
	{
		date->Time.Minute += MINUTES_PER_HOUR;
		date->Time.Hour--;
	}
	// Validate hour
	while (date->Time.Hour > 23)
	{
		date->Time.Hour -= HOURS_PER_DAY;
		date->Day++;
	}
	while (date->Time.Hour < 0)
	{
		date->Time.Hour += HOURS_PER_DAY;
		date->Day--;
	}
	// Calculate day
	date->Day -= CalculateLeapYears(date->Day);
	date->Year = date->Day / DAYS_PER_YEAR + UNIX_EPOCH_YEAR;
	date->Month++;
	date->Day %= DAYS_PER_YEAR;

	int Months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (IsLeapYear(date->Year) == 1) Months[1]++;
	for (int i = 0; Months[i] < date->Day; i++)
	{
		date->Month++;
		date->Day -= Months[i];
	}
	date->Day++;
	date->DayOfWeek = GetDayOfWeek(DayOfWeek(*date));
}
int CalculateLeapYears(int endingDay)
{
	int yearType = DAYS_PER_YEAR;
	int leapYears = 0;
	// Assumes the starting day is 1 Jan 1970
	for (int i = UNIX_EPOCH_YEAR; endingDay > 0; i++)
	{
		if (IsLeapYear(i) == 1)
		{
			yearType = DAYS_PER_LEAP_YEAR;
			leapYears++;
			endingDay -= yearType;
			if (endingDay < 0) leapYears--;
		}
		else
		{
			yearType = DAYS_PER_YEAR;
			endingDay -= yearType;
		}
	}
	return leapYears;
}
enum Days GetDayOfWeek(int x)
{
  int r = x * ((x >= 0) ? 1 : -1); // if x is negative, make it positive
  return (enum Days)(r % 7); // make a guess, dumbass
}
char * DaysToString(enum Days days)
{
  switch (days)
  {
    case SATURDAY:
		return "Saturday";
    case SUNDAY:
    	return "Sunday";
    case MONDAY:
    	return "Monday";
    case TUESDAY:
    	return "Tuesday";
    case WEDNESDAY:
    	return "Wednesday";
    case THURSDAY:
    	return "Thursday";
    case FRIDAY:
    	return "Friday";
  }
  return "NULL";
}

char* DateToString(struct Date date, struct Settings settings)
{
	// I am mentally ill. There's an easier way to do this but my ego won't stoop so low as to use a predefined structure.
	// Maybe after this I'll make my own time.h file.
	// And then after that I'll create my own C compiler.
	// And then after that I'll create my own computer using sand harvested from Yalong Bay.
	char separator;
	char* Date;
	char* Time;
	char AMPM[3] = "AM";
	char* Result;
	char* UTC;
	unsigned int UTC_M = 0xFFFFFFFF - (unsigned int)(date.Time.Timezone % 100) + 1; // woke up thinking it'd be a good day and now I've done this and I'm tired despite being up three hours.
	switch (settings.FormatDelimiter)
	{
		case 0:
			separator = '/';
			break;
		case 1:
			separator = '.';
			break;
		case 2:
			separator = '-';
			break;
		case 3:
			separator = ' ';
			break;
	}
	switch (settings.FormatRegion)
	{
		case 0:
			asprintf(&Date, "%.3s %02i%c%02i%c%04i", DaysToString(date.DayOfWeek), date.Day, separator, date.Month, separator, date.Year);
			break;
		case 1:
			asprintf(&Date, "%.3s %02i%c%02i%c%04i", DaysToString(date.DayOfWeek), date.Year, separator, date.Month, separator, date.Day);
			break;
		case 2:
			asprintf(&Date, "%.3s %02i%c%02i%c%04i", DaysToString(date.DayOfWeek), date.Month, separator, date.Day, separator, date.Year);
			break;
	}
	if (settings.Uses24Hour == 1)
	{
		asprintf(&Time, "%02i:%02i:%02i", date.Time.Hour, date.Time.Minute, date.Time.Second);
	}
	else
	{
		if (date.Time.Hour > 11) AMPM[0] = 'P';
		asprintf(&Time, "%02i:%02i:%02i %s", ((date.Time.Hour % 12) != 0 ? date.Time.Hour % 12 : 12), date.Time.Minute, date.Time.Second, AMPM);
	}
	if (date.Time.Timezone == 0) asprintf(&UTC, "UTC");
	else asprintf(&UTC, "UTC %+i:%02u", date.Time.Timezone / 100, (UTC_M * MINUTES_PER_HOUR / 100));
	asprintf(&Result, "%s %s %s", Date, Time, UTC);
	free(Date); // HOLY FUCKING SHIT I FINALLY FUCKING MANAGED TO FREE MEMORY LIKE THIS HOLY SHIT
	free(Time); // I hate my life.
	free(UTC);
	return Result;
}

void VerifySettings(struct Settings *settings)
{
	if (settings->Uses24Hour < 0 || settings->Uses24Hour > 1) settings->Uses24Hour = 1; // 24-hour is most commonly used..
	if (settings->FormatRegion < 0 || settings->FormatRegion > 2) settings->FormatRegion = 0; // DDMMYYYY is most commonly used.
	if (settings->FormatDelimiter < 0 || settings->FormatDelimiter > 3) settings->FormatDelimiter = 0; // DD/MM/YYYY is aestheticly pleasing.
}

// EOF: I finished this at 7:31 AM on Saturday, 16 December 2023.