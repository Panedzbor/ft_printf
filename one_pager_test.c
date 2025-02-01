#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <io.h>
//#include <unistd.h>
//#include "./printf/libftprintf.h"

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

static size_t   check_specifier(char *start, bool *valid);

int ft_printf(const char *fstring, ...);
static size_t   valid_ending(char *str, bool *val);
static void valid_chars(char *str, size_t offset, bool *val);
static void valid_dots(char *str, size_t offset, bool *val);
static void valid_zero(char *str, size_t offset, bool *val, size_t *i);
static void valid_digit(char *str, size_t offset, bool *val, size_t *i);
static void valid_asterisk(char *str, size_t offset, bool *val, size_t *i);
void valid_numerics(char *str, size_t offset, bool *val);
size_t  check_dependencies(char *start, bool *val);
int	ft_isdigit(int c);
int  pf_isflagnum(char c, int mode);
void    format_string(char *str, size_t offset, bool valid, va_list args);
static void valid_format(char *str, size_t offset, va_list args);
void    format_number(char *str, size_t offset, char end, va_list args);
int         get_len_d(int num, int *sign, char *numstr);
static void write_first_ch(char plus_or_space, int num, int *sign);
static void write_rest1(t_form mod, int num, int *sign, char* numstr);
static void fill_dec(t_form mod, int num, int sign, char *fill);
void    format_d(char *str, size_t offset, va_list args);
void    init_struct(t_form *mod);
static void extract_flags(char c, t_form *mod);
static void extract_numerics(char *str, char ending, va_list args, t_form *mod);
static void get_asterisk_val(va_list args, t_form *mod, bool *w);
static int get_number(char *str, t_form *mod, bool *w);
void    extract_format_val(char *str, size_t offset, va_list args, t_form *mod);
static char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
static int	substract(const char *str, int start, int end);
static int	add(const char *str, int start, int end);
static void	check_input(const char *str, int *start, int *end, int *negative);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t elements, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
static int		count_digits(unsigned int nb);
static void		convert(char *number, unsigned int nb, int digits);
char	*ft_itoa(int n);
void    allign_left_x(t_form mod, int len, char *numstr, char end);
void    allign_left_u(t_form mod, int len, char *numstr);
void    allign_left_d(t_form mod, int num, int *sign, char *numstr);
static void write_rest2(t_form mod, unsigned int num, char* numstr, int len);
static void fill_uns(t_form mod, unsigned int num, char *fill, int len);
void    format_u(char *str, size_t offset, va_list args);
static int		count_digits_u(unsigned int n);
static void		convert_u(char *number, unsigned int n, int digits);
char	*ft_utoa(unsigned int n);
static void write_rest3(t_form mod, unsigned int num, char* numstr, char end);
static void fill_hex(t_form mod, unsigned int num, char end, int len);
void    format_h(char *str, size_t offset, va_list args);
static int		count_digits_x(unsigned int n);
static void		convert_x(char *number, unsigned int n, int digits);
char	*ft_xtoa(unsigned int n);
static void capitalize_hex(char *numstr, int len, char end);
int	ft_toupper(int ch);
void    init_buf(char buf[3], char end);

int main()
{
    ft_printf("%#20.15X", 1515);
    printf("\n");
    return 0;
}

int ft_printf(const char *fstring, ...)
{
    va_list args;
    size_t  pos;
    size_t  fend;
    //size_t  j;
    bool    valid;

    va_start(args, fstring);
    //int a = va_arg(args, int);
    //pos = a;
    pos = 0;
    while (fstring[pos] != '\0')
    {
        if (fstring[pos] == '%')
        {
            valid = true;
            fend = check_specifier((char *)&fstring[pos], &valid);
            format_string((char *)&fstring[pos], fend, valid, args);
            pos += fend + 1;
            continue ;
        }
        _write(1, &fstring[pos], 1);
        pos++;
    }
    //printf("\n%s\n", valid == true ? "true" : "false");//test
    va_end(args);
    return ((int)pos);
}

static size_t  check_specifier(char *start, bool *valid)
{
    size_t  offset;
    size_t  offst;
    bool    val;

    offst = 0;
    val = true;
    offset = check_dependencies(start, &val);
    if (val == true && *valid == true)
        return (offset);
    if (start[offset] == '%' && start[offset + 1] != '\0')
    {
        offst += check_specifier(&start[offset], &val);
        if (offst == 0)
            offset -= 1;
        else
            offset += offst;
    }
    if (val == true && *valid == false)
        return (0);
    *valid = false;
    return (offset);
}

size_t  check_dependencies(char *start, bool *val)
{
    size_t  offset;

    offset = valid_ending(start, val);
    if (*val == true)
        valid_chars(start, offset, val);
    if (*val == true)
        valid_dots(start, offset, val);
    if (*val == true)
        valid_numerics(start, offset, val);
    return (offset);
}

static size_t   valid_ending(char *str, bool *val)
{
    size_t  i;
    size_t  e;

    i = 1;
    while (str[i] != '\0')
    {
        e = 0;
        while (endings[e] != '\0')
        {
            if (endings[e] == str[i])
                return i;
            e++;
        }
        i++;
    }
    *val = false;
    return (i - 1);
}

static void valid_chars(char *str, size_t offset, bool *val)
{
    size_t  i;
    size_t  n;
    bool    invalid_char;

    invalid_char = false;
    i = 1;
    while (i < offset)
    {
        invalid_char = true;
        if (pf_isflagnum(str[i], 2) == 1)
            invalid_char = false;
        if (invalid_char == true)
        {    
            *val = false;
            return ;
        }
        i++;
    }
}

static void valid_dots(char *str, size_t offset, bool *val)
{
    size_t  i;
    size_t  n;

    i = 1;
    while (i < offset)
    {
        if (str[i++] != '.')
            continue ;
        while (i < offset)
        {
            if (pf_isflagnum(str[i], 1) == 0)
            {
                *val = false;
                return ;
            }
            i++;
        }
    }
}
int  pf_isflagnum(char c, int mode)
{
    int n;

    n = 0;
    if (mode == 1)
    {
        while (numerics[n] != '\0')
        {
            if (c == numerics[n])
                return (1);
            n++;
        }
    }
    else if (mode == 2)
    {
        while (flags_numerics[n] != '\0')
        {
            if (c == flags_numerics[n])
                return (1);
            n++;
        }
    }
    return (0);
}


void valid_numerics(char *str, size_t offset, bool *val)
{
    size_t  i;

    i = 1;
    while (i < offset && *val == true)
    {
        if (str[i] == '0')
            valid_zero(str, offset, val, &i);
        else if (ft_isdigit(str[i]) == 1)
            valid_digit(str, offset, val, &i);
        else if (str[i] == '*')
            valid_asterisk(str, offset, val, &i);
        i++;
    }
}

static void valid_zero(char *str, size_t offset, bool *val, size_t *i)
{
    if (ft_isdigit(str[*i - 1]) == 1 || str[*i - 1] == '.')
    {
        if (ft_isdigit(str[*i + 1]) == 0 
        && str[*i + 1] != '.' && str[*i + 1] != str[offset])
            *val = false;
    }
}

static void valid_digit(char *str, size_t offset, bool *val, size_t *i)
{
    if (ft_isdigit(str[*i + 1]) == 0 
    && str[*i + 1] != '.' && str[*i + 1] != str[offset])
        *val = false;
}

static void valid_asterisk(char *str, size_t offset, bool *val, size_t *i)
{
    if (str[*i + 1] != '.' && str[*i + 1] != str[offset])
        *val = false;
}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/* static void invalid_format(char *str, size_t offset); */

void    format_string(char *str, size_t offset, bool valid, va_list args)
{
    if (valid == true)
        valid_format(str, offset, args);
    /* else
        invalid_format(str, offset); */
}

static void valid_format(char *str, size_t offset, va_list args)
{
    char    end;

    end = str[offset];
    /* if (end == 'c' || end == 's' || end == '%') */
//        format_text(str, offset, end, args);
        /* format_text(end, args); */
    /* else */
//        format_number(str, offset, end, args);
        format_number(str, offset, end, args);
}

void    format_number(char *str, size_t offset, char end, va_list args)
{
    if (end == 'd' || end == 'i')
        format_d(str, offset, args);
     else if (end == 'u')
        format_u(str, offset, args);
     else if (end == 'x' || end == 'X')
        format_h(str, offset, args);
    //else if (end == 'p')
    //    f_pointer(str, offset, args); 
}


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
    write_rest1(mod, num, &sign, numstr);
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
        _write(1, "+", 1);
        *sign = 1;
    }
    else if (plus_or_space == ' ' && num >= 0)
        _write(1, " ", 1);
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
        _write(1, fill, 1);
        i++;
    }
    free(numstr);
}

static void    write_rest1(t_form mod, int num, int *sign, char* numstr)
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
            _write(1, "-", 1);
        i = 0;
        while (i < mod.precis - len)
        {
            _write(1, "0", 1);
            i++;
        }
        if (num < 0)
            _write(1, &numstr[1], len);
        else
            _write(1, numstr, len); 
    }
}

void    init_struct(t_form *mod)
{
    int i;
    
    i = 0;
    while (i < 4)
    {
        mod->flags[i] = '_';
        i++;
    }
    mod->flags[4] = '\0';
    mod->precis = 0;
    mod->width = 0;
}


void    extract_format_val(char *str, size_t offset, va_list args, t_form *mod)
{
    int i;

    i = 1;
    while (i < offset)
    {
        if ((pf_isflagnum(str[i], 1) == 1 && str[i] != '0') || str[i] == '.')
        //{
          //printf("Yuhu\n");//test
          break ;
        //}
        extract_flags(str[i], mod);
        i++;
    }
    extract_numerics(&str[i], str[offset], args, mod);
}

static void extract_flags(char c, t_form *mod)
{
    if (c == '#')
        mod->flags[0] = '#';
    else if (c == '+')
        mod->flags[1] = '+';
    else if (c == ' ' && mod->flags[1] != '+')
        mod->flags[1] = ' ';
    else if (c == '-')
        mod->flags[2] = '-';
    else if (c == '0' && mod->flags[2] != '-')
        mod->flags[2] = '0';
}

static void extract_numerics(char *str, char ending, va_list args, t_form *mod)
{
    int i;
    int jump;
    bool    w;
    
    w = true;
    i = 0;
    while (str[i] != ending)
    {
        jump = 0;
        if (str[i] == '*')
            get_asterisk_val(args, mod, &w);
        else if (str[i] == '.')
        {
            w = false;
            mod->flags[3] = '.';
        }
        else if (ft_isdigit(str[i]) == 1)
            jump = get_number(&str[i], mod, &w) - 1;
        i += jump;
        i++;
    }
}

static void get_asterisk_val(va_list args, t_form *mod, bool *w)
{
    if (*w)
    {
        mod->width = va_arg(args, int);
        *w = false;
    }
    else
        mod->precis = va_arg(args, int);
}

static int get_number(char *str, t_form *mod, bool *w)
{
    int i;
    int number;
    char *s;

    i = 0;
    while (ft_isdigit(str[i]) == 1)
        i++;
    s = ft_substr(str, 0, i);
    number = ft_atoi((const char *)s);
    free(s);
    if (*w)
    {
        mod->width = number;
        *w = false;
    }
    else
        mod->precis = number;
    return (i);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
	{
		sub = (char *)ft_calloc(1, sizeof(char));
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (start + len > slen)
		len = slen - start;
	sub = (char *)ft_calloc(len + 1, sizeof(char));
	if (sub == NULL)
		return (NULL);
	ft_strncpy(sub, &s[start], len);
	sub[len] = '\0';
	return (sub);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}



int	ft_atoi(const char *str)
{
	int		num;
	int		negative;
	int		start;
	int		end;

	start = 0;
	end = 0;
	negative = 0;
	check_input(str, &start, &end, &negative);
	if (!(ft_isdigit(str[start])))
		return (0);
	if (negative == 1)
		num = substract(str, start, end);
	else
		num = add(str, start, end);
	return (num);
}

static void	check_input(const char *str, int *start, int *end, int *negative)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		*negative = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	*start = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i > 0)
		*end = i - 1;
}

static int	substract(const char *str, int start, int end)
{
	int	num;
	int	mult;

	num = 0;
	mult = 1;
	while (end >= start)
	{
		num -= (str[end] - '0') * mult;
		end--;
		mult *= 10;
	}
	return (num);
}

static int	add(const char *str, int start, int end)
{
	int	num;
	int	mult;

	num = 0;
	mult = 1;
	while (end >= start)
	{
		num += (str[end] - '0') * mult;
		end--;
		mult *= 10;
	}
	return (num);
}

size_t	ft_strlen(const char *str)
{
	size_t	chars;

	chars = 0;
	while (str[chars] != '\0')
		chars++;
	return (chars);
}

void	*ft_calloc(size_t elements, size_t size)
{
	void	*memory;

	if (size != 0)
	{
		if (elements > (SIZE_MAX / size))
			return (NULL);
	}
	memory = malloc(elements * size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, elements * size);
	return (memory);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (s);
}


char	*ft_itoa(int n)
{
	unsigned int		nb;
	int					digits;
	char				*ptr;

	digits = 0;
	if (n < 0)
	{
		nb = (-1) * n;
		digits++;
	}
	else
		nb = n;
	digits += count_digits(nb);
	ptr = (char *)ft_calloc(digits + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (n < 0)
		ptr[0] = '-';
	convert(ptr, nb, digits);
	ptr[digits] = '\0';
	return (ptr);
}

static int	count_digits(unsigned int nb)
{
	int	counter;

	counter = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		counter++;
	}
	return (counter);
}

static void	convert(char *number, unsigned int nb, int digits)
{
	int	r;
	int	i;

	r = nb % 10;
	i = nb / 10;
	number[digits - 1] = r + '0';
	digits--;
	while (i > 0)
	{
		nb = i;
		r = nb % 10;
		i = nb / 10;
		number[digits - 1] = r + '0';
		digits--;
	}
}

void    allign_left_d(t_form mod, int num, int *sign, char *numstr)
{
    int i;
    int len;

    len = get_len_d(num, sign, numstr);
    if (num < 0)
        _write(1, "-", 1);
    i = 0;
    while (i < mod.precis - len)
    {
        _write(1, "0", 1);
        i++;
    }
    if (num < 0)
        _write(1, &numstr[1], len);
    else
        _write(1, numstr, len);
    i = 0;
    while (i < mod.width - mod.precis - *sign && i < mod.width - len - *sign)
    {
        _write(1, " ", 1);
        i++;
    }   
}

void    allign_left_u(t_form mod, int len, char *numstr)
{
    int i;

    i = 0;
    while (i < mod.precis - len)
    {
        _write(1, "0", 1);
        i++;
    }
    _write(1, numstr, len);
    i = 0;
    while (i < mod.width - mod.precis && i < mod.width - len)
    {
        _write(1, " ", 1);
        i++;
    }   
}

void    allign_left_x(t_form mod, int len, char *numstr, char end)
{
    int i;
    int h;
    char buf[3];

    init_buf(buf, end);
    h = 0;
    if (mod.flags[0] == '#')
    {
        h = 2;
        _write(1, buf, 2);
    }
    i = 0;
    while (i < mod.precis - len)
    {
        _write(1, "0", 1);
        i++;
    }
    capitalize_hex(numstr, len, end);
    i = 0;
    while (i < mod.width - mod.precis - h && i < mod.width - len - h)
    {
        _write(1, " ", 1);
        i++;
    }   
}

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
    write_rest2(mod, num, numstr, len);
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
        _write(1, fill, 1);
        i++;
    }
    free(numstr);
}

static void    write_rest2(t_form mod, unsigned int num, char* numstr, int len)
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
            _write(1, "0", 1);
            i++;
        }
        _write(1, numstr, len); 
    }
}

char	*ft_utoa(unsigned int n)
{
	int					digits;
	char				*ptr;

	digits = count_digits_u(n);
	ptr = (char *)ft_calloc(digits + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	convert_u(ptr, n, digits);
	ptr[digits] = '\0';
	return (ptr);
}

static int	count_digits_u(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static void	convert_u(char *number, unsigned int n, int digits)
{
	int	r;
	int	i;

	r = n % 10;
	i = n / 10;
	number[digits - 1] = r + '0';
	digits--;
	while (i > 0)
	{
		n = i;
		r = n % 10;
		i = n / 10;
		number[digits - 1] = r + '0';
		digits--;
	}
}

void    format_h(char *str, size_t offset, va_list args)
{
    unsigned int num;
    char    *numstr;
    t_form  mod;
    int     len;

    init_struct(&mod);
    extract_format_val(str, offset, args, &mod);
    num = va_arg(args, unsigned int);
    numstr = ft_xtoa(num);
    write_rest3(mod, num, numstr, str[offset]);
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
    if (mod.flags[0] == '#')
        h = 2;
    fill[1] = '\0';
    numstr = ft_xtoa(num); 
    if (mod.flags[2] == '0' && mod.flags[3] != '.')
        fill[0] = '0';
    if (mod.flags[0] == '#' && mod.flags[2] == '0')
        _write(1, buf, 2);
    i = 0;
    while (i < mod.width - mod.precis - h && i < mod.width - len - h)
    {
        _write(1, fill, 1);
        i++;
    }
    free(numstr);
}

static void    write_rest3(t_form mod, unsigned int num, char* numstr, char end)
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
            _write(1, buf, 2);
        i = 0;
        while (i < mod.precis - len)
        {
            _write(1, "0", 1);
            i++;
        }
        if (mod.flags[0] == '#' && mod.flags[2] != '0' && mod.precis <= len)
            _write(1, buf, 2);
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
        _write(1, numstr, len);
    else
    {
        while (i < len)
        {
            buf[0] = ft_toupper(numstr[i]);
            _write(1, buf, 1);
            i++;
        }
    }
}


char	*ft_xtoa(unsigned int n)
{
	int					digits;
	char				*ptr;

	digits = count_digits_x(n);
	ptr = (char *)ft_calloc(digits + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	convert_x(ptr, n, digits);
	ptr[digits] = '\0';
	return (ptr);
}

static int	count_digits_x(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		counter++;
	}
	return (counter);
}

static void	convert_x(char *number, unsigned int n, int digits)
{
	int	r;
	int	i;

	r = n % 16;
	i = n / 16;
	if (r < 10)
		number[digits - 1] = r + '0';
	else
		number[digits - 1] = r - 10 + 'a';
	digits--;
	while (i > 0)
	{
		n = i;
		r = n % 16;
		i = n / 16;
		if (r < 10)
			number[digits - 1] = r + '0';
		else
			number[digits - 1] = r - 10 + 'a';
		digits--;
	}
}

int	ft_toupper(int ch)
{
	int	dif;

	dif = 'a' - 'A';
	if (ch >= 'a' && ch <= 'z')
		return (ch - dif);
	return (ch);
}

void    init_buf(char buf[3], char end)
{
    buf[0] = '0';
    buf[1] = end;
    buf[2] = '\0';
}