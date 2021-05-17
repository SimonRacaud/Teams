/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 strdup_format.c
*/

#include "utility.h"

static char *jump_pattern(char *str, const char *pattern)
{
    size_t len = strlen(pattern);

    if (strncmp(str, pattern, len) != 0) {
        return NULL;
    }
    return (str + len);
}

static char *jump_char(char *str, const char *characters, bool accept_null)
{
    if (accept_null && str[0] == '\0') {
        return (str + 1);
    }
    if (str[0] == '\0' || strchr(characters, str[0]) == NULL) {
        return NULL;
    }
    return (str + 1);
}

static char *browse_body(char *str, const format_t *ft)
{
    bool stop = false;

    if ((ft->suffix && jump_pattern(str, ft->suffix))
        || (ft->suffix_chars
            && jump_char(str, ft->suffix_chars, ft->accept_null_suffix))) {
        stop = true;
    }
    if (stop)
        return str;
    if (str[0] == '\0' || ft->no_body == true)
        return NULL;
    if (ft->exclude && strchr(ft->exclude, str[0]) != NULL)
        return NULL;
    if (ft->is_alpha && ft->is_num && !isalnum(str[0]))
        return NULL;
    if (ft->is_alpha && !ft->is_num && !isalpha(str[0]))
        return NULL;
    if (ft->is_num && !ft->is_alpha && !isdigit(str[0]))
        return NULL;
    return browse_body(str + 1, ft);
}

char *strdup_format(char *str, const format_t *ft, char **end_ptr)
{
    char *post_prefix_ptr = str;
    char *ptr = NULL;

    if (ft->prefix) {
        post_prefix_ptr = jump_pattern(str, ft->prefix);
        if (!post_prefix_ptr)
            return NULL;
    }
    ptr = browse_body(post_prefix_ptr, ft);
    if (!ptr || ptr == str)
        return NULL;
    *end_ptr = NULL;
    if (ft->suffix_chars) {
        *end_ptr = jump_char(ptr, ft->suffix_chars, ft->accept_null_suffix);
    }
    if (!(*end_ptr))
        *end_ptr = ptr;
    return strndup(post_prefix_ptr, (ptr - post_prefix_ptr));
}

bool cmp_format(char *str, const format_t *ft)
{
    char *ptr = str;

    if (ft->prefix) {
        ptr = jump_pattern(str, ft->prefix);
        if (!ptr)
            return false;
    }
    ptr = browse_body(ptr, ft);
    if (!ptr)
        return false;
    return true;
}