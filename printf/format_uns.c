/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_uns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/31 18:33:04 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void write_rest(t_form mod, unsigned int num, char* numstr, int len);
static void fill_uns(t_form mod, unsigned int num, char *fill, int len);

void    format_u(char *str, size_t offset, va_list args)
{
    unsigned int num;
    char    *numstr;
    t_form  mod;
    int     len;

    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    num = va_arg(args, unsigned int);
    numstr = ft_utoa(num);
    len = (unsigned int)ft_strlen(numstr);
    write_rest(mod, num, numstr, len);
    free(numstr);
}

static void fill_uns(t_form mod, unsigned int num, char *fill, int len)
{
    int i;
    char    *numstr;
    
    numstr = ft_utoa(num); 
    if (mod.flags[2] == '0' && mod.flags[3] != '.')
        fill[0] = '0';
    else
        fill[0] = ' ';
    i = 0;
    while (i < mod.width - mod.precis && i < mod.width - len)
    {
        write(1, fill, 1);
        i++;
    }
    free(numstr);
}

static void    write_rest(t_form mod, unsigned int num, char* numstr, int len)
{
    char    fill[2];
    int     i;

    fill[1] = '\0';
    if (mod.flags[2] == '-')
        allign_left_u(mod, len, numstr);
    else
    {
        fill_uns(mod, num, fill, len);
        i = 0;
        while (i < mod.precis - len)
        {
            write(1, "0", 1);
            i++;
        }
        write(1, numstr, len); 
    }
}
