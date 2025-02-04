/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:15:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/30 18:36:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void    allign_left_d(t_form mod, int num, int *sign, char *numstr)
{
    int i;
    int len;

    len = get_len_d(num, sign, numstr);
    if (num < 0)
        write(1, "-", 1);
    i = 0;
    while (i < mod.precis - len)
    {
        write(1, "0", 1);
        i++;
    }
    if (num < 0)
        write(1, &numstr[1], len);
    else
        write(1, numstr, len);
    i = 0;
    while (i < mod.width - mod.precis - *sign && i < mod.width - len - *sign)
    {
        write(1, " ", 1);
        i++;
    }   
}

void    allign_left_u(t_form mod, int len, char *numstr)
{
    int i;

    i = 0;
    while (i < mod.precis - len)
    {
        write(1, "0", 1);
        i++;
    }
    write(1, numstr, len);
    i = 0;
    while (i < mod.width - mod.precis && i < mod.width - len)
    {
        write(1, " ", 1);
        i++;
    }   
}

void    allign_left_x(t_form mod, int len, char *numstr, char end)
{
    int i;
    int h;
    char buf[3];

    init_buf(buf, end);
    h = 0;
    if (mod.flags[0] == '#')
    {
        h = 2;
        write(1, buf, 2);
    }
    i = 0;
    while (i < mod.precis - len)
    {
        write(1, "0", 1);
        i++;
    }
    capitalize_hex(numstr, len, end);
    i = 0;
    while (i < mod.width - mod.precis - h && i < mod.width - len - h)
    {
        write(1, " ", 1);
        i++;
    }   
}

void    allign_left_p(t_form mod, int len, char *numstr, int sign)
{
    int i;

    write(1, "0x", 2);
    i = 0;
    while (i < mod.precis - len + sign)
    {
        write(1, "0", 1);
        i++;
    }
    write(1, numstr, len - sign);
    i = 0;
    while (i < mod.width - mod.precis - 2 - sign && i < mod.width - len - 2)
    {
        write(1, " ", 1);
        i++;
    }   
}