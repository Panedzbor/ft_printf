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
# include <stdint.h>

typedef struct s_formatting
{
    char    flags[5];
    int     width;
    int     precis;
    int     trunc;
    int     len;
    char    end;
} t_form;

static const char *endings = "cspdiuxX%";
//static const char *flags = "-0.# +";
static const char *numerics = "0123456789*";
//static const char *digits = "0123456789";
static const char *flags_numerics = "-0.# +123456789*";



int     ft_printf(const char *, ...);
size_t  check_dependencies(char *start, bool *val);
void    valid_numerics(char *str, size_t offset, bool *val);
void    format_value(char *str, size_t offset, bool valid, va_list args);
void    format_number(char *str, size_t offset, char fs, va_list args);
void    format_text(char *str, size_t offset, char end, va_list args);
//void    format_d(char *str, size_t offset, va_list args);
//void    format_u(char *str, size_t offset, va_list args);
//void    format_x(char *str, size_t offset, va_list args);
//void    format_p(char *str, size_t offset, va_list args);
int     pf_isflagnum(char c, int mode);
void    init_struct(t_form *mod);
void    init_buf(char buf[3], char end);
void    init_arr(int *arr, int dim);
void    extract_format_val(char *str, size_t offset, va_list args, t_form *mod);
int     get_len_d(int num, int *sign, char *numstr);
//void    allign_left_d(t_form mod, int num, int *sign, char *numstr);
//void    allign_left_u(t_form mod, int len, char *numstr);
//void    allign_left_x(t_form mod, int len, char *numstr, char end);
//void    allign_left_p(t_form mod, int len, char *numstr, int sign);
void    allign_left(t_form mod, signed int snum, char *numstr);
void    allign_right(t_form mod, signed int snum, char *numstr);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned int n);
char	*ft_ptoa(uintptr_t n);
void    field_fill_num(t_form mod, signed int snum, char fill);
void    write_sign(t_form mod, signed int num);
void    write_prefix(t_form mod);
void    write_arg(char *numstr, char end, int trunc);
void    precis_fill(t_form mod);
void    write_space(t_form mod, signed int num);
int     get_sum(t_form mod, signed int snum);
void    capitalize_hex(char c);

#endif
