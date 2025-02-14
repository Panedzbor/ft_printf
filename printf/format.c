/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:28:30 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/14 14:28:32 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void valid_format(char *str, size_t offset, va_list args);
static void invalid_format(char *str, size_t offset, va_list args, bool flend);

void    format_value(char *str, size_t offset, bool *valid, va_list args)
{
    if (valid[0] == true)
        valid_format(str, offset, args);
    else
        invalid_format(str, offset, args, valid[1]);
}

static void valid_format(char *str, size_t offset, va_list args)
{
    char    end;

    end = str[offset];
    if (end == 'c' || end == 's' || end == '%')
        format_text(str, offset, end, args);
    else
        format_number(str, offset, end, args);
}

static void invalid_format(char *str, size_t offset, va_list args, bool flend)
{
    int     i;
    t_form  mod;
    t_arrs  arrs;
    bool    dig;

    if (offset == 0)
        return ;
    init_struct(&mod);
    mod.len = (int)offset;
    if ((isflagnum_pf(str[offset])) && !flend && !str[offset + 1])
        mod.len += 1;
    extract_format_val(str, mod.len, args, &mod);
    init_strarr(&arrs);
    dig = false;
    i = 0;
    while ((size_t)i <= offset)
    {
        def_dig(str, (size_t)i, offset, &dig);
        def_extpts(&dig, arrs.ext, i);
        i++;
    }
    if (!write_str(&arrs, str, offset, mod))
        return ;
    check_exend(mod.end, str, i - 1);
}
