/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:28:30 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 14:28:32 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void valid_format(char *str, size_t offset, va_list args);
static void invalid_format(char *str, size_t offset, va_list args);

void    format_value(char *str, size_t offset, bool valid, va_list args)
{
    if (valid == true)
        valid_format(str, offset, args);
    else
        invalid_format(str, offset, args);
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

static void invalid_format(char *str, size_t offset, va_list args)
{
    int i;
    t_form  mod;

    i = 0;
    if (offset == 0 && str[i] == '%')
        return ;
    init_struct(&mod);
    mod.len = offset;
    if (pf_isflag(str[offset]) == 1)
        mod.len += 1;//thats why
    extract_format_val(str, mod.len, args, &mod);/*printf("%c %c %c %c %d %d %d %c %d\n", mod.flags[0], mod.flags[1], mod.flags[2], mod.flags[3], mod.width, mod.precis, mod.trunc, mod.end, mod.len);*/
    if (mod.end != '\0')
        write(1, "%", 1);
    while (i < 3 && mod.end != '\0')
    {
        if (mod.flags[i] != '_')
            write(1, &mod.flags[i], 1);
        i++;
    }
    i = 0;
    while (i <= offset && mod.end != '\0')
    {
        if (pf_isflag(str[i]) == 0 && str[i] != '%' && str[i] != '.')
            write(1, &str[i], 1);
        if (str[i] == '.' && i < offset)
        {
            write(1, ".", 1);
            if (ft_isdigit(str[i + 1]) == 0)
                write(1, "0", 1);
        }

        i++;
    }
}
