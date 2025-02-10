/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/04 18:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int  define_prefix(t_form mod, int *sppl, int snum);
static int  define_sign(t_form mod, int snum);
static int  sum_val(int *values, t_form mod, int snum);

int get_sum(t_form mod, signed int snum)
{
    int sppl[4]; //sign prefix precision value_len
    int sum;
    int trunc;

    init_arr(sppl, 4);
    sppl[0] = define_sign(mod, snum);
    sppl[1] = define_prefix(mod, sppl, snum);
    if (mod.end == 'p' && mod.precis < 12 && snum > 0)
        sppl[2] = 12;
    else
    {
       // if (mod.end == 's')
         //   sppl[2] = -(mod.trunc - mod.len);
        //else
            sppl[2] = mod.precis;
    }
    //trunc = 0;
    //if (mod.len <= mod.trunc) //?? changed < to <=
    //    trunc = 0;
    //else
    //    trunc = mod.len - mod.trunc;
    /*if (mod.len > mod.trunc)
        mod.len = mod.trunc;*/
    //if (mod.end == 'p' && snum == 0)
    //    trunc = 0;
    sppl[3] = mod.len;// - trunc;
    sum = sum_val(sppl, mod, snum);
    return (sum);
}

static int sum_val(int *values, t_form mod, int snum)
{
    int i;
    int result;

    i = 0;
    result = 0;
    while (i < 4)
    {
        if (i == 2)
        {
            if (values[2] > values[3] && !(mod.end == 'p' && snum == 0))
                values[i] = values[2] - values[3];
            else
                values[i] = 0;
        }
        result += values[i];
        i++;
    }
    return (result);
}

static int define_sign(t_form mod, int snum)
{
    if (snum < 0)
        return (1);
    if (mod.flags[1] != '_' &&
        (mod.end == 'd' || mod.end == 'i' || (mod.end == 'p' && snum > 0)))
        return (1);
    return (0);
}

static int define_prefix(t_form mod, int *sppl, int snum)
{
    if (snum == 0)
        return (0);
    if (mod.end == 'p')
        return (2);
    if ((mod.end == 'x' || mod.end == 'X') && mod.flags[0] == '#')
        return (2);
    return (0);
}

