/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 parser.h
*/

#ifndef PARSER_H
#define PARSER_H

#include "network/request_t.h"

request_t *request_create(char *command);
int request_write(request_t *request);
void request_destroy(request_t *request);
request_t *request_parse(char *input);

#endif // PARSER_H
