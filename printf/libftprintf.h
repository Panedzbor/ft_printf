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
    char    flags[4];
    size_t     width;
    size_t     precis;
} t_form;

static const char *endings = "cspdiuxX%";
//static const char *flags = "-0.# +";
static const char *numerics = "0123456789*";
//static const char *digits = "0123456789";
static const char *flags_numerics = "-0.# +123456789*";



int	ft_printf(const char *, ...);

#endif
