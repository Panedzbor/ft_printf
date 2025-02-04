/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_fval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:37:02 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 14:37:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void extract_flags(char c, t_form *mod);
static void extract_numerics(char *str, char ending, va_list args, t_form *mod);
static void get_asterisk_val(va_list args, t_form *mod, bool *w);
static int get_number(char *str, t_form *mod, bool *w);

void    extract_format_val(char *str, size_t offset, va_list args, t_form *mod)
{
    int i;

    i = 1;
    while (i < offset)
    {
        if ((pf_isflagnum(str[i], 1) == 1 && str[i] != '0') || str[i] == '.')
        //{
          //printf("Yuhu\n");//test
          break ;
        //}
        extract_flags(str[i], mod);
        i++;
    }
    mod->end = str[offset];
    extract_numerics(&str[i], str[offset], args, mod);
}

static void extract_flags(char c, t_form *mod)
{
    if (c == '#')
        mod->flags[0] = '#';
    else if (c == '+')
        mod->flags[1] = '+';
    else if (c == ' ' && mod->flags[1] != '+')
        mod->flags[1] = ' ';
    else if (c == '-')
        mod->flags[2] = '-';
    else if (c == '0' && mod->flags[2] != '-')
        mod->flags[2] = '0';
}

static void extract_numerics(char *str, char ending, va_list args, t_form *mod)
{
    int i;
    int jump;
    bool    w;
    
    w = true;
    i = 0;
    while (str[i] != ending)
    {
        jump = 0;
        if (str[i] == '*')
            get_asterisk_val(args, mod, &w);
        else if (str[i] == '.')
        {
            w = false;
            mod->flags[3] = '.';
        }
        else if (ft_isdigit(str[i]) == 1)
            jump = get_number(&str[i], mod, &w) - 1;
        i += jump;
        i++;
    }
    if (mod->trunc == 0 && mod->flags[3] != '.')
        mod->trunc = mod->len;
}

static void get_asterisk_val(va_list args, t_form *mod, bool *w)
{
    if (*w)
    {
        mod->width = va_arg(args, int);
        *w = false;
    }
    else
        mod->precis = va_arg(args, int);
}

static int get_number(char *str, t_form *mod, bool *w)
{
    int i;
    int number;
    char *s;

    i = 0;
    while (ft_isdigit(str[i]) == 1)
        i++;
    s = ft_substr(str, 0, i);
    number = ft_atoi((const char *)s);
    free(s);
    if (*w)
    {
        mod->width = number;
        *w = false;
    }
    else
    {
        if (mod->end != 'c' && mod->end != 's')
            mod->precis = number;
        if (mod->end == 's')
            mod->trunc = number;
    }
    return (i);
}
