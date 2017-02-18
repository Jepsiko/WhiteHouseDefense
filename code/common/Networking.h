#ifndef PROJET_NETWORKING_H
#define PROJET_NETWORKING_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>


ssize_t receive_data(int socket_fd, void *message, int length);
char *get_data_from_socket(int socket_fd, char *buffer, int size);
int get_message_length(int socket_fd);
void ensure_buffer_is_big_enough(char *buffer, int length);
int receive_message(int socket_fd, char *buffer);
bool receive_message_with_timeout(int socket_fd, char *buffer, int timeout);

void send_data(int socket_fd, char *buffer, int length);
void send_message(int socket_fd, const char *message);

#endif //PROJET_NETWORKING_H