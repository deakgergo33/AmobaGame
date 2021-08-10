#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>

FILE* stream;

struct elozmeny
{
    int min;
    int hour;
    int day;
    char month[4];
    int year;
};

void elozmenyiras(char *winner, char *loser)
{
    time_t result = time(NULL);

    struct tm time;
    localtime_s(&time, &result);

    struct elozmeny history;

    history.min = time.tm_min;
    history.hour = time.tm_hour;
    history.day = time.tm_mday;
    strftime(history.month, sizeof history.month, "%b", &time);
    history.year = time.tm_year + 1900;

    errno_t err = fopen_s(&stream, "history.txt", "a");
    if (!err && stream)
    {
        fprintf_s(stream, "WIN %s vs. %s LOSE\t\t", winner, loser);
        fprintf_s(stream, "%d %s %d %d:%d\n", history.year, history.month, history.day, history.hour, history.min );
        fclose(stream);
    }

    return;
}

void elozmenyolvasas()
{
    system("cls");

    int i = 0;
    char beolvas[400] = {0};

    errno_t err = fopen_s(&stream, "history.txt", "r");
    if (!err && stream)
    {
        while ((beolvas[i] = fgetc(stream)) != EOF) 
        {
            i++;
        }
        
        fclose(stream);
    }

    printf("Press Enter to return\n\n%s", beolvas);

    while (1)
    {
        if (_getch() == '\r') { return; }
    }
}