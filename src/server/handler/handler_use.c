/*
** EPITECH PROJECT, 2021
** handler_use.c
** File description:
** handler_use function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

static int selector_verification(
    size_t args_size, selected_entity_t *selector, database_t *db)
{
    void *(*verif[]) (const database_t *db, uuid_selector_t *params) = {
        (void *(*) (const database_t *, uuid_selector_t *) ) get_team,
        (void *(*) (const database_t *, uuid_selector_t *) ) get_channel,
        (void *(*) (const database_t *, uuid_selector_t *) ) get_thread,
    };
    const rcode_e err_tab[] = {
        ERR_UNKNOWN_TEAM, ERR_UNKNOWN_CHANNEL, ERR_UNKNOWN_THREAD};
    void *result = NULL;
    uuid_selector_t params = {0};

    uuid_copy(params.uuid_team, selector->team);
    uuid_copy(params.uuid_channel, selector->channel);
    uuid_copy(params.uuid_thread, selector->thread);
    for (size_t i = 0; i < args_size; i++) {
        result = verif[i](db, &params);
        if (!result)
            return err_tab[i];
    }
    return SUCCESS;
}

int handler_use(server_t *srv, request_t *request, client_t *client)
{
    size_t i = 0;
    selected_entity_t selector = {0};
    selected_entity_t *move_ptr = NULL;
    const rcode_e err_tab[] = {
        ERR_UNKNOWN_TEAM, ERR_UNKNOWN_CHANNEL, ERR_UNKNOWN_THREAD};
    int return_value = SUCCESS;

    memcpy(&selector, &client->selector, sizeof(selected_entity_t));
    for (; request->args[i]; i++, move_ptr += sizeof(uuid_t)) {
        if (uuid_parse(request->args[i], (unsigned char *) move_ptr) == -1) {
            memcpy(&client->selector, &selector, sizeof(selected_entity_t));
            return reply_str(err_tab[i], request, "Invalid argument");
        }
    }
    return_value = selector_verification(i, &client->selector, &srv->database);
    if (return_value != SUCCESS) {
        memcpy(&client->selector, &selector, sizeof(selected_entity_t));
        return reply_str(return_value, request, "Argument not found");
    }
    return reply_str(SUCCESS, request, "Use correctly executed");
}