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

static void    f_decimal(va_list args);
static void    f_unsigned(va_list args);

//void    format_number(char *str, size_t offset, char fs, va_list args)
void    format_number(char fs, va_list args)
{
    if (fs == 'd' || fs == 'i')
//        f_decimal(str, offset, args);
        f_decimal(args);
    else if (fs == 'u')
//        f_unsigned(str, offset, args);
        f_unsigned(args);
/*     else if (fs == 'x' || fs == 'X')
        f_hexadecimal(str, offset, args);
    else if (fs == 'p')
        f_pointer(str, offset, args); */
}

static void    f_decimal(char *str, size_t offset, va_list args)
/* static void    f_decimal(va_list args) */
{
    int num;
    t_form  mod;

    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    num = va_arg(args, int);
    //                                                              continue here
}

//void    f_unsigned(char *str, size_t offset, va_list args)
static void    f_unsigned(va_list args)
{
    unsigned int num;

    num = va_arg(args, unsigned int);
    printf("%u\n", num);//test
}
