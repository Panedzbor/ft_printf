/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:28:30 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/15 14:28:32 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void valid_format(char *str, size_t offset, va_list args);
/* static void invalid_format(char *str, size_t offset); */

void    format_string(char *str, size_t offset, bool valid, va_list args)
{
    if (valid == true)
        valid_format(str, offset, args);
    /* else
        invalid_format(str, offset); */
}

static void valid_format(char *str, size_t offset, va_list args)
{
    char    end;

    end = str[offset];
    /* if (end == 'c' || end == 's' || end == '%') */
//        format_text(str, offset, end, args);
        /* format_text(end, args); */
    /* else */
//        format_number(str, offset, end, args);
        format_number(str, offset, end, args);
}