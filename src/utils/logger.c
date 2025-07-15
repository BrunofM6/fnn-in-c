#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define LOG_FILE "../../log/log.txt"
#define BUFFER_SIZE 64

void log_message(const char *message)
{
    if (message == NULL)
    {
        fprintf(stderr, "CRITICAL ERROR: Null message sent to logger.\n");
        return;
    }

    FILE *log_fp = NULL;
    log_fp = fopen(LOG_FILE, "a");

    if (log_fp == NULL)
    {
        fprintf(stderr, "CRITICAL ERROR: Could not open log file: %s.\n", strerror(errno));
        
        fprintf(stderr, "Original log message: %s.\n", message);
    } else 
    {
        time_t current_time = time(NULL);
        if (current_time == (time_t)-1)
        {
            fprintf(stderr, "CRITICAL ERROR: Current time is null.\n");
            fclose(log_fp);
            return;
        }

        struct tm *local_time_info = localtime(&current_time);
        if (local_time_info == NULL)
        {
            fprintf(stderr, "CRITICAL ERROR: Could not convert time to local time.\n");
            fclose(log_fp);
            return;
        }

        char date_buffer[BUFFER_SIZE];
        const char *format_string = "%Y-%m-%d %H:%M:%S";
        size_t bytes_written = strftime(date_buffer, BUFFER_SIZE, format_string, local_time_info);
        if (bytes_written == 0)
        {
            fprintf(stderr, "CRITICAL ERROR: Buffer too small or invalid format string for date/time.\n");
            fclose(log_fp);
            return;
        }

        fprintf(log_fp, "[%s] %s\n", date_buffer, message);
        
        fflush(log_fp);
        fclose(log_fp);
    }
}

void clear_logger()
{
    FILE *log_fp = NULL;
    log_fp = fopen(LOG_FILE, "w");

    if (log_fp == NULL)
    {
        fprintf(stderr, "CRITICAL ERROR: Couldn't open and clear log file.\n");
        return;
    }
    
    fclose(log_fp);
    return;
}
