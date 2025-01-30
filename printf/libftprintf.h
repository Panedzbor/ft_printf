/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/01/10 14:23:51 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>

typedef struct s_formatting
{
    char    flags[5];
    int     width;
    int     precis;
} t_form;

static const char *endings = "cspdiuxX%";
//static const char *flags = "-0.# +";
static const char *numerics = "0123456789*";
//static const char *digits = "0123456789";
static const char *flags_numerics = "-0.# +123456789*";



int     ft_printf(const char *, ...);
size_t  check_dependencies(char *start, bool *val);
void    valid_numerics(char *str, size_t offset, bool *val);
void    format_string(char *str, size_t offset, bool valid, va_list args);
void    format_number(char *str, size_t offset, char fs, va_list args);
void    format_d(char *str, size_t offset, va_list args);
int     pf_isflagnum(char c, int mode);
void    init_struct(t_form *mod);
void    extract_format_val(char *str, size_t offset, va_list args, t_form *mod);
int     get_len_d(int num, int *sign, char *numstr);
void    allign_left(t_form mod, int num, int *sign, char *numstr);

#endif
