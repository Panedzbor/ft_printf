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
    int i;
    int num = 0;
    int num2[2];
    bool num21[2];
    num21[0] = false; num21[1] = false;
    char *numstr;
    t_form  mod;
    bool dig = false;
    int ext[2][2];
    ext[0][0] = -1;
    ext[0][1] = -1;
    ext[1][0] = -1;
    ext[1][1] = -1;
    char *maxnum = "2147483647";
    num2[0] = 0;
    num2[1] = 0;
    long numb[2];
    numb[0] = -1;
    numb[1] = -1;

    i = 0;
    if (str[i] == '%')
    {    
        if (offset == 0)
            return ;
    }
    init_struct(&mod);
    mod.len = offset;
    if ((pf_isflagnum(str[offset], 2) == 1) && !flend && str[offset + 1] == '\0')
        mod.len += 1;
    extract_format_val(str, mod.len, args, &mod);/*printf("%c %c %c %c %d %d %d %c %d\n", mod.flags[0], mod.flags[1], mod.flags[2], mod.flags[3], mod.width, mod.precis, mod.trunc, mod.end, mod.len);*/
    while (i <= offset)
    {
        if (ft_isdigit(str[i]) == 1 && str[i] != '0' && i < offset)
            dig = true;
        if (ft_isdigit(str[i]) == 0)
            dig = false;
        if (dig)
        {
            if (ext[0][0] == -1)
                ext[0][0] = i;
            else if (ext[0][1] > -1 && ext[1][0] == -1)
                ext[1][0] = i;
        }
        else
        {
            if (ext[0][0] > -1 && ext[1][0] == -1)
                ext[0][1] = i - 1;
            else if (ext[1][0] > -1 && ext[1][1] == -1)
                ext[1][1] = i - 1;
        }
        i++;
    }
    if (ext[0][0] > -1 && ext[0][1] > -1)
    {
        numstr = ft_substr((const char *)str, ext[0][0], ext[0][1] - ext[0][0] + 1);
        if (!numstr)
            return;
        if (ft_strlen(numstr) < 10)
            num = ft_atoi(numstr);
        else if (ft_strlen(numstr) == 10)
        {
            i = 0;
            while (i < 11)
            {
                if (numstr[i] > maxnum[i])
                    break ;
                i++;
            }
            if (i == 11)
                num = ft_atoi(numstr);
            else
                num = -1;
        }
        else
            num = -1;
        free(numstr);
    }
    if (num == -1)
        return ;
    if (ext[1][0] > -1 && ext[1][1] > -1)
    {
        numstr = ft_substr((const char *)str, ext[1][0], ext[1][1] - ext[1][0] + 1);
        if (!numstr)
            return;
        if (ft_strlen(numstr) < 10)
            num = ft_atoi(numstr);
        else if (ft_strlen(numstr) == 10)
        {
            i = 0;
            while (i < 11)
            {
                if (numstr[i] < maxnum[i])
                    break ;
                i++;
            }
            if (i == 11)
                num = ft_atoi(numstr);
            else
                num = -1;
        }
        else
            num = -1;
        free(numstr);
    }
    if (num == -1)
        return ;
    i = 0;
    while (i < offset)
    {
        if (str[i] == '*' && !num21[0])
        {
            num2[0] = mod.width;
            num21[0] = true;
        }
        if (str[i] == '*' && num21[0] && !num21[1])
        {
            num2[1] = mod.precis;
            num21[1] = true;
        }
        i++;
    }
    if ((mod.end == 'q' || mod.end == 't' || mod.end == 'h'
        || mod.end == 'j' || mod.end == 'l' || mod.end == 'z') && str[offset + 1] == '\0')
        return ;
    if (mod.end != '\0')
        write(1, "%", 1);
    i = 0;
        
    while (i < 3 && mod.end != '\0')
    {
        if (i == 2 && mod.flags[i] != '-' && num2[0] < 0)
        {    
            write(1, "-", 1);
            
        }
        if (mod.flags[i] != '_')
        {    
            write(1, &mod.flags[i], 1);
            
        }
        i++;
    }
    i = 0;
    bool f = false;
    while (i < offset && mod.end != '\0')
    {
        if (pf_isflag(str[i]) == 0 && str[i] != '%' && str[i] != '.' && str[i] != '*')
        {
            write(1, &str[i], 1);
            f = true;
        }
        if (f && str[i] == '0')
            write(1, "0", 1);
        if (str[i] == '.' && i < offset && num2[1] >= 0)
        {
            write(1, ".", 1);
            if (ft_isdigit(str[i + 1]) == 0 && str[i + 1] != '*')
                write(1, "0", 1);
            f = true;
        }
        if (str[i] == '*')
        {
            f = true;
            int x;
            if (str[i - 1] == '.')
                x = 1;
            else
                x = 0;
            numb[x] = num2[x];
            if (num2[0] < 0)
                numb[0] = -(long)num2[0];
            if (num2[1] < 0 && x == 1)
            {
                write(1, &str[offset], 1);
                return ;
            }
            char *num_u = ft_utoa((unsigned int)numb[x]);
            if (!num_u)
                return ;
            int y = 0;
            while (num_u[y] != '\0')
            {
                if (x == 0 && (num2[0] == 0 || num2[0] == -2147483648))
                {
                    if (num2[0] == -2147483648)
                        write(1, "18446744071562067968", 20);
                    break ;
                }
                write(1, &num_u[y], 1);
                y++;
            }
            free(num_u);
        }
        i++;
    }
    if (mod.end != '\0' && mod.end != 'q' && mod.end != 't' && mod.end != 'h'
        && mod.end != 'j' && mod.end != 'l' && mod.end != 'z')
        write(1, &str[i], 1);
}
