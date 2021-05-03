/*
** EPITECH PROJECT, 2021
** HUB_my_troyan
** File description:
** 01/05/2021 select_t.h
*/

#ifndef SELECT_T_H
#define SELECT_T_H

typedef struct select {
    fd_set read_fds;
    int status;
} select_t;

#endif // SELECT_T_H
