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

static void    f_decimal(char *str, size_t offset, va_list args);
/* static void    f_unsigned(va_list args); */

//void    format_number(char fs, va_list args)
void    format_number(char *str, size_t offset, char end, va_list args)
{
    if (end == 'd' || end == 'i')
        f_decimal(str, offset, args);
/*     else if (end == 'u') */
//        f_unsigned(str, offset, args);
      /*   f_unsigned(args); */
/*     else if (end == 'x' || end == 'X')
        f_hexadecimal(str, offset, args);
    else if (end == 'p')
        f_pointer(str, offset, args); */
}

/* static void    f_decimal(va_list args) */
static void    f_decimal(char *str, size_t offset, va_list args)
{
    int num;
    int i;
    int len;
    char    *numstr;
    int    sign;
    char    fill[2];
    t_form  mod;

    sign = 0;
    fill[1] = '\0';
    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    num = va_arg(args, int);
    numstr = ft_itoa(num);
    if (num < 0)
    {
        len = ft_strlen(numstr) - 1;
        sign = 1;
    }
    else
        len = ft_strlen(numstr);
    if (mod.flags[1] == '+' && num >= 0)
    {
        write(1, "+", 1);
        sign = 1;
    }
    else if (mod.flags[1] == ' ' && num >= 0)
        write(1, " ", 1);
    if (mod.flags[2] == '-')
    {
        if (num < 0)
            write(1, "-", 1);
        i = 0;
        while (i < mod.precis - len)
        {
            write(1, "0", 1);
            i++;
        }
        if (num < 0)
            write(1, &numstr[1], len);
        else
            write(1, numstr, len);
        i = 0;
        while (i < mod.width - mod.precis - sign && i < mod.width - len - sign)
        {
            write(1, " ", 1);
            i++;
        }   
    }
    else
    {
        if (mod.flags[2] == '0' && mod.flags[3] != '.')
            fill[0] = '0';
        else
            fill[0] = ' ';
        i = 0;
        while (i < mod.width - mod.precis - sign && i < mod.width - len - sign)
        {
            write(1, fill, 1);
            i++;
        }
        i = 0;
        if (num < 0)
            write(1, "-", 1);
        while (i < mod.precis - len)
        {
            write(1, "0", 1);
            i++;
        }
        if (num < 0)
            write(1, &numstr[1], len);
        else
            write(1, numstr, len); 
    }
    free(numstr);
}


/* //void    f_unsigned(char *str, size_t offset, va_list args)
static void    f_unsigned(va_list args)
{
    unsigned int num;

    num = va_arg(args, unsigned int);
    printf("%u\n", num);//test
} */
