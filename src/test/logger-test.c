
#include <stdio.h>
#include "../utils/logger.c"

int main()
{
    printf("Testing logger...\n");

    log_message("This is a test log message.");
    log_message("Another log message.");
    log_message(NULL);

    printf("Finished testing logging. Check the log file.\n");

    return 0;
}
