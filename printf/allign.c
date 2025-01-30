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

void    allign_left(t_form mod, int num, int *sign, char *numstr)
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
