/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/12 14:23:51 by earutiun         ###   ########.fr       */
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
    bool    except;
} t_form;

static const char   *endings = "cspdiuxX%";
static const char   *flags = "-0# +";
static const char   *numerics = "0123456789*";
static const char   *flags_numerics = "-0.# +123456789*";

typedef struct s_arrays
{
    int     ext[2][2];
    int     astn[2];
    bool    astnumb[2];
    long    lnum[2];
} t_arrs;

int     ft_printf(const char *, ...);
size_t  find_ending(char *start, bool *val, bool *flend);
void    format_value(char *str, size_t offset, bool *valid, va_list args);
void    format_number(char *str, size_t offset, char fs, va_list args);
void    format_text(char *str, size_t offset, char end, va_list args);
void    extract_format_val(char *str, size_t offset, va_list args, t_form *mod);
void    allign_left(t_form mod, signed int snum, char *numstr);
void    allign_right(t_form mod, signed int snum, char *numstr);
void    field_fill_num(t_form mod, signed int snum, char fill);
void    write_sign(t_form mod, signed int num);
void    write_prefix(t_form mod, signed int snum);
void    write_arg(char *numstr, char end, int len);
void    precis_fill(t_form mod, int num);
void    write_space(t_form mod, signed int num);
int     get_sum(t_form mod, signed int snum);
void    capitalize_hex(char c);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned int n);
char	*ft_ptoa(uintptr_t n);
int     isflagnum_pf(char c);
int     isflag_pf(char c);
int     isnum_pf(char c);
bool    check_overflow(char *numstr);
bool    check_ending(char e);
void    init_struct(t_form *mod);
void    init_buf(char buf[3], char end);
void    init_arr(int *arr, int dim);
void    init_strarr(t_arrs *arrs);;
char    *write_str(t_arrs *arrs, char *str, size_t offset, t_form mod);
char    *write_spcf(size_t offset, t_form mod, t_arrs *arrs, char *str);
void    def_dig(char *str, size_t i, size_t offset, bool *dig);
void    def_extpts(bool *dig, int (*ext)[2], int i);
void    check_exend(char e, char *str, int i);
char    *convert_unum(t_arrs *arrs, int x, char *str, size_t offset);

#endif
