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
    bool    valid[2];

    valid[0] = true;
    valid[1] = false;
    va_start(args, fstring);
    //int a = va_arg(args, int);
    //pos = a;
    pos = 0;
    while (fstring[pos] != '\0')
    {
        if (fstring[pos] == '%')
        {
            valid[0] = true;
            fend = check_specifier((char *)&fstring[pos], valid);
            format_value((char *)&fstring[pos], fend, valid, args);
            pos += fend + 1;
            continue ;
        }
        write(1, &fstring[pos], 1);
        pos++;
    }
    va_end(args);
    return ((int)pos);
}

static size_t  check_specifier(char *start, bool *valid)
{
    size_t  offset;
    //size_t  offst;
    bool    val;

    //offst = 0;
    val = true;
    offset = find_ending(start, &val, &valid[1]);
    if (start[offset] == '\0')
        offset -= 1;
    if (val == true && valid[0] == true)
        return (offset);
    /*if (start[offset] == '%' && start[offset + 1] != '\0')
    {
        offst += check_specifier(&start[offset], &val);
        if (offst == 0)
            offset -= 1;
        else
            offset += offst;
    }*/
    if (val == true && valid[0] == false)
        return (0);
    valid[0] = false;
    return (offset);
}
