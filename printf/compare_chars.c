/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:07:33 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 16:07:35 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int  pf_isflagnum(char c, int mode)
{
    int n;

    n = 0;
    if (mode == 1)
    {
        while (numerics[n] != '\0')
        {
            if (c == numerics[n])
                return (1);
            n++;
        }
    }
    else if (mode == 2)
    {
        while (flags_numerics[n] != '\0')
        {
            if (c == flags_numerics[n])
                return (1);
            n++;
        }
    }
    return (0);
}
