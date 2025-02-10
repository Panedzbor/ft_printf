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

static bool valid_chars(char *c, bool *flag, bool *dot, bool *flend);
static bool valid_dot(bool *flag, bool *dot);
static bool valid_asterisk(char *c, bool *flag);
static bool valid_digit(char *c, bool *flag);

size_t   find_ending(char *start, bool *val, bool *flend)
{
    size_t  i;
    size_t  e;
    bool    fl_dt[2];

    fl_dt[0] = true;
    fl_dt[1] = false;
    i = 1;
    while (start[i] != '\0')
    {
        e = 0;
        while (endings[e] != '\0')
        {
            if (endings[e] == start[i])
                return (i);
            e++;
        }
        if (!(fl_dt[0] && pf_isflag(start[i]) == 1))
        {
            if (!(valid_chars(&start[i], &fl_dt[0], &fl_dt[1], flend)))
                break ;
        }
        i++;
    }
    *val = false;
    return (i);
}

static bool valid_chars(char *c, bool *flag, bool *dot, bool *flend)
{
    *flend = true;
    if (pf_isflag(*c) == 1 && !*flag && *c != '0')
        return (false);
    if (*c == '.')
    {
        if (!(valid_dot(flag, dot)))
            return (false);
    }
    else if (*c == '*')
    {
        if (!(valid_asterisk(c, flag)))
            return (false);
    }
    else if (ft_isdigit(*c) == 1)    
    {
        if (!(valid_digit(c, flag)))
            return (false);
    }
    else
        return (false);
    *flend = false;
    return (true);
}

static bool valid_dot(bool *flag, bool *dot)
{
    if (*dot)
        return (false);
    *dot = true;
    *flag = false;
    return (true);
}

static bool valid_asterisk(char *c, bool *flag)
{
    if (c[-1] != '%' && c[-1] != '.' 
        && !(pf_isflag(c[-1]) == 1 && *flag))
    {
        *flag = false;
        return (false);
    }
    *flag = false;
    return (true);
}

static bool valid_digit(char *c, bool *flag)
{
    if (!(*c == '0' && *flag))
        *flag = false;
    if (c[-1] == '*')
        return (false);
    return (true);
}


