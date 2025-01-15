/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:03:01 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 14:03:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t   valid_ending(char *str, bool *val);
static void valid_chars(char *str, size_t offset, bool *val);
static void valid_dots(char *str, size_t offset, bool *val);

size_t  check_dependencies(char *start, bool *val)
{
    size_t  offset;

    offset = valid_ending(start, val);
    if (*val == true)
        valid_chars(start, offset, val);
    if (*val == true)
        valid_dots(start, offset, val);
    if (*val == true)
        valid_numerics(start, offset, val);
    return (offset);
}

static size_t   valid_ending(char *str, bool *val)
{
    size_t  i;
    size_t  e;

    i = 1;
    while (str[i] != '\0')
    {
        e = 0;
        while (endings[e] != '\0')
        {
            if (endings[e] == str[i])
                return i;
            e++;
        }
        i++;
    }
    *val = false;
    return (i - 1);
}

static void valid_chars(char *str, size_t offset, bool *val)
{
    size_t  i;
    size_t  n;
    bool    invalid_char;

    invalid_char = false;
    i = 1;
    while (i < offset)
    {
        invalid_char = true;
        if (pf_isflagnum(str[i], 2) == 1)
            invalid_char = false;
        if (invalid_char == true)
        {    
            *val = false;
            return ;
        }
        i++;
    }
}

static void valid_dots(char *str, size_t offset, bool *val)
{
    size_t  i;
    size_t  n;

    i = 1;
    while (i < offset)
    {
        if (str[i++] != '.')
            continue ;
        while (i < offset)
        {
            if (pf_isflagnum(str[i], 1) == 0)
            {
                *val = false;
                return ;
            }
            i++;
        }
    }
}




