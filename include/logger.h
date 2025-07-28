#ifndef LOGGER_H
#define LOGGER_H

#define LOG_FILE "../../log/log.txt"
#define BUFFER_SIZE 64

void log_message(const char *message);

void clear_logger(void);

#endif
