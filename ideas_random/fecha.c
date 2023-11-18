#include <stdio.h>
#include <time.h>
int main()
{
    time_t seconds=time(NULL);
    struct tm* current_time=localtime(&seconds); 
    
    printf("Current year = %d\n",(current_time->tm_year + 1900));
    printf("Current month = %d\n",(current_time->tm_mon));
    return 0;
}
