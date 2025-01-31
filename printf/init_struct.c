/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:27:34 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 17:27:36 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void    init_struct(t_form *mod)
{
    int i;
    
    i = 0;
    while (i < 4)
    {
        mod->flags[i] = '_';
        i++;
    }
    mod->flags[5] = '\0';
    mod->precis = 0;
    mod->width = 0;
}
