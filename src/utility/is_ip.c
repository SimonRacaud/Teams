/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 is_ip.c
*/

#include "utility.h"
#include <arpa/inet.h>

bool is_ip(const char *str)
{
    struct sockaddr_in addr;

    return inet_pton(AF_INET, str, &addr.sin_addr) != 0;
}
