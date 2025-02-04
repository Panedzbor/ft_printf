/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/31 18:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void write_rest(t_form mod, unsigned int num, char* numstr, char end);
static void fill_hex(t_form mod, unsigned int num, char end, int len);

void    format_x(char *str, size_t offset, va_list args)
{
    unsigned int num;
    char    *numstr;
    t_form  mod;
    int     len;

    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    num = va_arg(args, unsigned int);
    numstr = ft_xtoa(num);
    write_rest(mod, num, numstr, str[offset]);
    free(numstr);
}

static void fill_hex(t_form mod, unsigned int num, char end, int len)
{
    int i;
    int h;
    char    *numstr;
    char    fill[2];
    char    buf[3];
    
    init_buf(buf, end);
    h = 0;
    fill[0] = ' ';
    fill[1] = '\0';
    if (mod.flags[0] == '#')
        h = 2;
    numstr = ft_xtoa(num); 
    if (mod.flags[2] == '0' && mod.flags[3] != '.')
        fill[0] = '0';
    if (mod.flags[0] == '#' && mod.flags[2] == '0')
        write(1, buf, 2);
    i = 0;
    while (i < mod.width - mod.precis - h && i < mod.width - len - h)
    {
        write(1, fill, 1);
        i++;
    }
    free(numstr);
}

static void    write_rest(t_form mod, unsigned int num, char* numstr, char end)
{
    int     i;
    int     len;
    char    buf[3];
    
    init_buf(buf, end);
    len = (unsigned int)ft_strlen(numstr);
    if (mod.flags[2] == '-')
        allign_left_x(mod, len, numstr, end);
    else
    {
        fill_hex(mod, num, end, len);
        if (mod.flags[0] == '#' && mod.precis > len)
            write(1, buf, 2);
        i = 0;
        while (i < mod.precis - len)
        {
            write(1, "0", 1);
            i++;
        }
        if (mod.flags[0] == '#' && mod.flags[2] != '0' && mod.precis <= len)
            write(1, buf, 2);
        capitalize_hex(numstr, len, end); 
    }
}

void capitalize_hex(char *numstr, int len, char end)
{
    int i;
    char buf[2];

    buf[1] = '\0';
    i = 0;
    if(end == 'x')
        write(1, numstr, len);
    else
    {
        while (i < len)
        {
            buf[0] = ft_toupper(numstr[i]);
            write(1, buf, 1);
            i++;
        }
    }
}

