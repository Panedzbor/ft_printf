/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/30 18:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int         get_len_d(int num, int *sign, char *numstr);
static void write_first_ch(char plus_or_space, int num, int *sign);
static void write_rest(t_form mod, int num, int *sign, char* numstr);
static void fill_dec(t_form mod, int num, int sign, char *fill);

void    format_d(char *str, size_t offset, va_list args)
{
    int num;
    char    *numstr;
    int    sign;
    t_form  mod;

    sign = 0;
    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    num = va_arg(args, int);
    numstr = ft_itoa(num);
    write_first_ch(mod.flags[1], num, &sign);
    write_rest(mod, num, &sign, numstr);
    free(numstr);
}

int   get_len_d(int num, int *sign, char *numstr)
{
    if (num < 0)
    {
        *sign = 1;
        return ((int)ft_strlen(numstr) - 1);
    }
    else
        return ((int)ft_strlen(numstr));
}

static void     write_first_ch(char plus_or_space, int num, int *sign)
{
    if (plus_or_space == '+' && num >= 0)
    {
        write(1, "+", 1);
        *sign = 1;
    }
    else if (plus_or_space == ' ' && num >= 0)
        write(1, " ", 1);
}



static void fill_dec(t_form mod, int num, int sign, char *fill)
{
    int i;
    int len;
    char    *numstr;
    
    numstr = ft_itoa(num); 
    len = get_len_d(num, &sign, numstr);
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
    free(numstr);
}

static void    write_rest(t_form mod, int num, int *sign, char* numstr)
{
    char    fill[2];
    int     i;
    int     len;

    fill[1] = '\0';
    len = get_len_d(num, sign, numstr);
    if (mod.flags[2] == '-')
        allign_left_d(mod, num, sign, numstr);
    else
    {
        fill_dec(mod, num, *sign, fill);
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
    }
}
