/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:33:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 14:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void    format_d(char *str, size_t offset, va_list args);
static void    format_u(char *str, size_t offset, va_list args);
static void    format_x(char *str, size_t offset, va_list args);
static void    format_p(char *str, size_t offset, va_list args);

void    format_number(char *str, size_t offset, char end, va_list args)
{
    if (end == 'd' || end == 'i')
        format_d(str, offset, args);
     else if (end == 'u')
        format_u(str, offset, args);
     else if (end == 'x' || end == 'X')
        format_x(str, offset, args);
    else if (end == 'p')
        format_p(str, offset, args); 
}

static void    format_d(char *str, size_t offset, va_list args)
{
    int num;
    char    *numstr;
    t_form  mod;

    init_struct(&mod);
    num = va_arg(args, int);
    numstr = ft_itoa(num);
    mod.len = ft_strlen(numstr);
    extract_format_val(str, offset, args, &mod);
    if (num < 0)
        mod.len -= 1;
    if (mod.flags[2] == '-')
        allign_left(mod, num, numstr);
    else
        allign_right(mod, num, numstr);
    free(numstr);
}

static void    format_u(char *str, size_t offset, va_list args)
{
    unsigned int num;
    char    *numstr;
    t_form  mod;

    init_struct(&mod);
    num = va_arg(args, unsigned int);
    numstr = ft_utoa(num);
    mod.len = ft_strlen(numstr);
    extract_format_val(str, offset, args, &mod);
    if (mod.flags[2] == '-')
        allign_left(mod, 0, numstr);
    else
        allign_right(mod, 0, numstr);
    free(numstr);
}

static void    format_x(char *str, size_t offset, va_list args)
{
    uintptr_t   num;
    char        *numstr;
    t_form      mod;

    init_struct(&mod);
    num = va_arg(args, uintptr_t);
    numstr = ft_xtoa((unsigned int)num);
    mod.len = ft_strlen(numstr);
    extract_format_val(str, offset, args, &mod);
    if (mod.flags[2] == '-')
        allign_left(mod, 0, numstr);
    else
        allign_right(mod, 0, numstr);
    free(numstr);
}

static void    format_p(char *str, size_t offset, va_list args)
{
    uintptr_t   num;
    void        *ptr;
    char        *numstr;
    t_form      mod;

    init_struct(&mod);
    ptr = va_arg(args, void *);
    num = (uintptr_t)ptr;
    numstr = ft_ptoa(num);
    mod.len = ft_strlen(numstr);
    extract_format_val(str, offset, args, &mod);
    if (mod.flags[2] == '-')
        allign_left(mod, 0, numstr);
    else
        allign_right(mod, 0, numstr);
    free(numstr);
}


