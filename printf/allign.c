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

void    allign_left(t_form mod, signed int snum, char *numstr)
{
    if (mod.except)
        return ;
    write_sign(mod, snum);
    write_space(mod, snum);
    write_prefix(mod, snum);
    precis_fill(mod, snum);
    write_arg(numstr, mod.end, mod.len);
    field_fill_num(mod, snum, ' ');
}

void    allign_right(t_form mod, signed int snum, char *numstr)
{
    if (mod.except)
        return ;
    if (mod.flags[2] != '0' || mod.flags[3] == '.')
    {
        write_space(mod, snum);
        field_fill_num(mod, snum, ' ');
        write_sign(mod, snum);
        write_prefix(mod, snum);
        precis_fill(mod, snum);
        write_arg(numstr, mod.end, mod.len);
    }
    else
    {
        write_sign(mod, snum);
        write_space(mod, snum);
        write_prefix(mod, snum);
        field_fill_num(mod, snum, '0');
        write_arg(numstr, mod.end, mod.len);
    }
}
