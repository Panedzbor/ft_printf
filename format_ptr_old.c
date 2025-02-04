/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/01 18:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void     write_first_ch(t_form mod, uintptr_t num, int sign, int len);
static void write_rest(t_form mod, uintptr_t num, char* numstr, int sign);
static int fill_ptr(t_form mod, uintptr_t num, int sign, int len);

void    format_p(char *str, size_t offset, va_list args)
{
    uintptr_t   num;
    void        *ptr;
    char        *numstr;
    t_form      mod;
    int         sign;

    sign = 0;
    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    ptr = va_arg(args, void *);
    num = (uintptr_t)ptr;
    numstr = ft_ptoa(num);
    if (mod.flags[1] != '_') // mod.flags[1] == '+' || (mod.flags[1] == ' ' && mod.width <= ft_strlen(numstr) + 2) || < 0
        sign = 1;
    //write_first_ch(mod.flags[1], num, &sign);
    write_rest(mod, num, numstr, sign);
    free(numstr);
}

static void     write_first_ch(t_form mod, uintptr_t num, int sign, int len)
{
    if (mod.flags[1] == '+' && num >= 0)
    {
        write(1, "+", 1);
        
    }
    else if (mod.flags[1] == ' ' && sign == 1 && num >= 0)
    {
        write(1, " ", 1);
        
    }    
}

static void    write_rest(t_form mod, uintptr_t num, char* numstr, int sign)
{
    int     i;
    int     len;
    int     suf;

    len = ft_strlen(numstr) + sign;
    suf = 0;
    if (mod.flags[2] == '-')
        allign_left_p(mod, len, numstr, sign);
    else
    {
        suf = fill_ptr(mod, num, sign, len);
        write_first_ch(mod, num, sign, len);
        if (suf == 0) //mod.precis > len - sign
            {
                write(1, "0x", 2);
                suf = 1;
            }
        i = 0;
        while (i < mod.precis - len + sign)
        {
            write(1, "0", 1);
            i++;
        }
        if (mod.flags[2] != '0' && mod.precis <= len - sign && suf == 0)
            write(1, "0x", 2);
        write(1, numstr, len); 
    }
}

static int fill_ptr(t_form mod, uintptr_t num, int sign, int len)
{
    int i;
    int suf;
    char    *numstr;
    char    fill[2];
    
    suf = 0;
    fill[0] = ' ';
    fill[1] = '\0';
    numstr = ft_ptoa(num); 
    if (mod.flags[2] == '0' && mod.flags[3] != '.')
    {
        fill[0] = '0';
        if (sign == 0)
        {
            write(1, "0x", 2);
            suf = 1;
        }
    }
    i = 0;
    while (i < mod.width - mod.precis - 2 - sign && i < mod.width - len - 2)
    {
        write(1, fill, 1);
        i++;
    }
    free(numstr);
    return (suf);
}

