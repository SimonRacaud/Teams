/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 format_t.h
*/

#ifndef FORMAT_T_H
#define FORMAT_T_H

/**
 * "([prefix])[pattern's body][suffix]"
 * prefix   : pattern of the prefix (optional)
 * suffix   : pattern of the suffix
 * suffix_chars : list of chars => suffix
 * exclude  : excluded characters of the pattern's body
 * is_alpha : pattern's body character must be alphabetic
 * is_num   : pattern's body character must be numeric
 */

typedef struct format_s {
    char *prefix;
    char *suffix_chars;
    char *suffix;
    bool accept_null_suffix;
    char *exclude;
    bool is_alpha;
    bool is_num;
    bool no_body;
} format_t;

#endif // FORMAT_T_H
