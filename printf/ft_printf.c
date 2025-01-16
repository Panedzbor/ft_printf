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

int ft_printf(const char *fstring, ...)
{
    va_list args;
    size_t  pos;
    size_t  fend;
    //size_t  j;
    bool    valid;

    va_start(args, fstring);
    //int a = va_arg(args, int);
    //pos = a;
    pos = 0;
    while (fstring[pos] != '\0')
    {
        if (fstring[pos] == '%')
        {
            valid = true;
            fend = check_specifier((char *)&fstring[pos], &valid);
            format_string((char *)&fstring[pos], fend, valid, args);
            pos += fend + 1;
            continue ;
        }
        write(1, &fstring[pos], 1);
        pos++;
    }
    printf("\n%s\n", valid == true ? "true" : "false");//test
    va_end(args);
    return ((int)pos);
}

static size_t  check_specifier(char *start, bool *valid)
{
    size_t  offset;
    size_t  offst;
    bool    val;

    offst = 0;
    val = true;
    offset = check_dependencies(start, &val);
    if (val == true && *valid == true)
        return (offset);
    if (start[offset] == '%' && start[offset + 1] != '\0')
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
