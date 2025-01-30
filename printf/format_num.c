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

/* static void    f_unsigned(va_list args); */

//void    format_number(char fs, va_list args)
void    format_number(char *str, size_t offset, char end, va_list args)
{
    if (end == 'd' || end == 'i')
        format_d(str, offset, args);
/*     else if (end == 'u') */
//        f_unsigned(str, offset, args);
      /*   f_unsigned(args); */
/*     else if (end == 'x' || end == 'X')
        f_hexadecimal(str, offset, args);
    else if (end == 'p')
        f_pointer(str, offset, args); */
}




/* //void    f_unsigned(char *str, size_t offset, va_list args)
static void    f_unsigned(va_list args)
{
    unsigned int num;

    num = va_arg(args, unsigned int);
    printf("%u\n", num);//test
} */
