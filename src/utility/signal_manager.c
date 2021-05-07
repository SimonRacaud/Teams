/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 signal_manager.c
*/

#include "utility.h"
#include <signal.h>

static void activator_switch(bool *activator_ptr)
{
    static bool *ptr = NULL;

    if (activator_ptr != NULL) {
        ptr = activator_ptr;
        *ptr = true;
    } else if (ptr != NULL) {
        *ptr = false;
    }
}

static void handler(__attribute__((unused)) int signum)
{
    activator_switch(NULL);
}

int signal_manager(int signum, bool *activator_ptr)
{
    activator_switch(activator_ptr);
    if (signal(signum, &handler) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}