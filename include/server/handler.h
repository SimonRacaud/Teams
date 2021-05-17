/*
** EPITECH PROJECT, 2021
** handler.h
** File description:
** handler
*/

#ifndef HANDLER_H
#define HANDLER_H

#include "server.h"

/*
**
** HANDLER
**
*/

int handler_help(server_t *srv, request_t *request);

/*
**
** HANDLER TOOLS
**
*/

uint get_tab_len(const char **tab);
char *add_crlf(char *tram, size_t len);

#endif