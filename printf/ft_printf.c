/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:14:25 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/10 13:14:29 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t   check_specifier(char *start, bool *valid);
size_t   valid_all(char *start, bool *val); //header!

int ft_printf(const char *fstring, ...)
{
    va_list args;
    size_t  pos;
    size_t  fend;
    size_t  j;
    bool    valid;

    va_start(args, fstring);
    pos = 0;
    while (fstring[pos] != '\0')
    {
        if (fstring[pos] == '%')
        {
            valid = true;
            fend = check_specifier(&fstring[pos], &valid);
            format_string(&fstring[pos], fend, valid);
            /* int d = va_arg(args, int);
            char *numtext;
            numtext = ft_itoa(d);
            j = 0;
            while (numtext[j] != '\0')
            {
                write(1, &numtext[j], 1);
                j++;
            }
            i += j + 1;
            continue ; */
            pos += fend + 1;
            continue ;
        }
        write(1, &fstring[pos], 1);
        pos++;
    }
    va_end(args);
    return ((int*)pos);
}



static size_t  check_specifier(char *start, bool *valid)
{
    size_t  offset;
    size_t  offst;
    bool    val;

    offst = 0;
    val = true;
    offset = valid_all(start, &val);
    if (val == true && *valid == true)
        return (offset);
    if (start[offset] == '%')
    {
        offst += check_specifier(&start[offset], &val);
        if (offst == 0)
            offset -= 1;
        else
            offset += offst;
    }
    if (val == true && *valid == false)
        return (0);
    *valid = false;
    return (offset);
}


//file 2
size_t  valid_all(char *start, bool *val)
{
    size_t  offset;

    offset = valid_ending(start, val);
    if (*val == true)
        valid_chars(start, offset, val);
    if (*val == true)
        valid_dots(start, offset, val);
    if (*val == true)
        valid_numeric(start, offset, val);
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
    return (i);
}

static void valid_chars(char *str, size_t offset, bool *val)
{
    size_t  i;
    size_t  n;
    bool    no_match;

    i = 1;
    while (i < offset)
    {
        no_match = true;
        n = 0;
        while (flags_numerics[n] != '\0')
        {
            if (str[i] == flags_numerics[n])
            {
                no_match = false;
                break ;
            }
            n++;
        }
        i++;
    }
    if (no_match == true)
        *val = false;
}
//file 3