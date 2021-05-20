/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 body_maker_team.c
*/

#include "server.h"
#include "database.h"
#include "network/response_t.h"

static size_t get_list_size(team_t *team, bool is_list)
{
    size_t size = 0;

    if (!is_list) {
        return 1;
    } else {
        for (team_t *node = team; node; node = LIST_NEXT(node, entries))
            size++;
        return size;
    }
}

static void write_content(void *body, team_t *team, bool is_list)
{
    bin_team_t *packet = NULL;
    bin_team_t *ptr = NULL;

    ptr = (bin_team_t *)((char *)body + sizeof(body_header_t));
    for (team_t *node = team; node; node = LIST_NEXT(node, entries)) {
        packet = serializer_team_t(node);
        *ptr = *packet;
        free(packet);
        ptr++;
        if (!is_list)
            break;
    }
}

void *body_maker_team(team_t *team, bool is_list, const char *logger)
{
    size_t size = get_list_size(team, is_list);
    body_header_t *head;
    void *body = NULL;

    body = malloc(sizeof(body_header_t) + sizeof(bin_team_t) * size);
    if (!body)
        return NULL;
    head = body;
    *head = (body_header_t) {.elem_size = sizeof(bin_team_t),
        .list_size = size, .entity = "team", .logger = ""};
    strncpy(head->logger, logger, SIZE_NAME);
    write_content(body, team, is_list);
    return body;
}