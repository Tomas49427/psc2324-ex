#include <string.h>
#include <stdlib.h>

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday; int tm_yday; int tm_isdst;
};
int string_to_time(const char *string, struct tm *tm){
    char * next_token = strdup(string);
    int day;
    int month;
    int year;
    int hour;
    int min;
    int sec;
    int date_or_hour = 0;
    for(char * token = strsep(&next_token,"- :"); token != NULL; token = strsep(&next_token,"- :")){
        switch(date_or_hour){
            case 0: {
                if(strlen(token) != 2){
                    return 0;
                }
                if(token[0] == '0'){
                    day = atoi(&token[1]);
                } else {
                    day = atoi(token);
                }
                break;
            }
            case 1: {
                if(strlen(token) != 2){
                    return 0;
                }
                if(token[0] == '0'){
                    month = atoi(&token[1]) - 1;
                } else {
                    month = atoi(token) - 1;
                }
                break;
            }
            case 2: {
                if(strlen(token) != 4){
                    return 0;
                }
                year = atoi(token) - 1900;
                break;
            }
            case 3: {
                if(strlen(token) != 2){
                    return 0;
                }
                if(token[0] == '0'){
                    hour = atoi(&token[1]);
                } else {
                    hour = atoi(token);
                }
                break;
            }
            case 4: {
                if(strlen(token) != 2){
                    return 0;
                }
                if(token[0] == '0'){
                    min = atoi(&token[1]);
                } else {
                    min = atoi(token);
                }
                break;
            }
            case 5: {
                if(strlen(token) != 2){
                    return 0;
                }
                if(token[0] == '0'){
                    sec = atoi(&token[1]);
                } else {
                    sec = atoi(token);
                }
                break;
            }
            default: {
                return 0;
            }
        }
        date_or_hour++;
    }
    if(date_or_hour < 6){
        return 0;
    }
    tm->tm_hour = hour;
    tm->tm_min = min;
    tm->tm_sec = sec;
    tm->tm_mday = day;
    tm->tm_mon = month;
    tm->tm_year = year;
    tm->tm_wday = 0;
    tm->tm_yday = 0;
    tm->tm_isdst = 0;
    return 1;
}