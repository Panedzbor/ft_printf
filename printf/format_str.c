/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:33:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/14 14:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void format_c(char *str, size_t offset, va_list args);
static void format_s(char *str, size_t offset, va_list args);
static void get_modvals(t_form *mod, const char *string, const char *null);

void    format_text(char *str, size_t offset, char end, va_list args)
{
    if (end == 'c')
        format_c(str, offset, args);
    else if (end == 's')
        format_s(str, offset, args);
    else if (end == '%')
        write(1, "%", 1);
}

static void    format_c(char *str, size_t offset, va_list args)
{
    char    c;
    char    val[2];
    t_form  mod;

    init_struct(&mod);
    mod.len = 1;
    extract_format_val(str, offset, args, &mod);
    c = va_arg(args, int);
    if (mod.trunc >= 0 && mod.trunc < mod.len)
        mod.len = mod.trunc;
    val[0] = c;
    val[1] = '\0';
    if (mod.flags[2] == '-' || mod.width < 0)
        allign_left(mod, 0, val);
    else
        allign_right(mod, 0, val);
}

static void    format_s(char *str, size_t offset, va_list args)
{
    const char    *string;
    const char     *null;
    t_form  mod;

    null = NULL;
    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    string = (const char *)va_arg(args, char *);
    if (!string)
        string = "(null)";
    else
        null = string;
    get_modvals(&mod, string, null);
    if (mod.flags[2] == '-' || mod.width < 0)
        allign_left(mod, 0, (char *)string);
    else
        allign_right(mod, 0, (char *)string);
}

static void get_modvals(t_form *mod, const char *string, const char *null)
{
    mod->len = ft_strlen((char *)string);
    if (mod->trunc == -1 && mod->flags[3] == '.')
        mod->trunc = 0;
    if (null == NULL && mod->trunc < mod->len && mod->trunc >= 0)
    {
        string = "";
        mod->len = 0;
    }
    if (mod->trunc >= 0 && mod->trunc < mod->len)
        mod->len = mod->trunc;
}
