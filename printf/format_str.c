/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:33:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 14:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void    format_c(char *str, size_t offset, va_list args);
static void    format_s(char *str, size_t offset, va_list args);

void    format_text(char *str, size_t offset, char end, va_list args)
{
    if (end == 'c')
        format_c(str, offset, args);
     else if (end == 's')
        format_s(str, offset, args);
}

static void    format_c(char *str, size_t offset, va_list args)
{
    char    c;
    char    val[2];
    t_form  mod;

    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    c = va_arg(args, int);
    val[0] = c;
    val[1] = '\0';
    mod.len = 1;
    if (mod.flags[2] == '-')
        allign_left(mod, 0, val);
    else
        allign_right(mod, 0, val);
}

static void    format_s(char *str, size_t offset, va_list args)
{
    char    *string;
    t_form  mod;

    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    string = va_arg(args, char *);
    printf("got this from va_arg: %s\n", string);
    mod.len = ft_strlen(string);
    printf("len = %d\n", mod.len);
    if (mod.flags[2] == '-')
        allign_left(mod, 0, string);
    else
        allign_right(mod, 0, string);
}