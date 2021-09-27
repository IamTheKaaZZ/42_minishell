/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:59:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/27 10:42:47 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BONUS_H
# define LIBFT_BONUS_H

# include "libft.h"
# include "ft_float_to_bin.h"
# include "get_next_line.h"
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>

/*
**	BASE defines
*/

# define B_DEFAULT "0123456789"
# define B_BIN "01"
# define B_BIN32 "01\032"
# define B_BIN64 "01\064"
# define B_BIN128 "01\0128"
# define B_OCT "01234567"
# define B_HEXLC "0123456789abcdef"
# define B_HEXUC "0123456789ABCDEF"

/*
**	Typedefs
*/

typedef unsigned int		t_ui;
typedef long long			t_ll;
typedef unsigned long		t_ul;
typedef unsigned short		t_us;
typedef unsigned char		t_uc;
typedef unsigned long long	t_ull;

/*
**	Bonus FTS
*/

int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_ischrinset(char const *set, int c);
void	ft_div_mod(int a, int b, int *div, int *mod);
void	ft_swap(int *a, int *b);
void	ft_sort_int_tab(int *tab, int size);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		*ft_range(int min, int max);
int		ft_strcmp(char *s1, char *s2);
void	ft_memdel(void **mem);
void	ft_strdel(char **str);
t_ll	ft_abs(t_ll n);
t_ull	ft_fibonacci(t_ll index);
t_ul	ft_find_next_prime(t_ul nb);
t_ull	ft_is_prime(t_ull nb);
t_ll	ft_iterative_factorial(t_ll nb);
t_ll	ft_recursive_factorial(t_ll nb);
t_ll	ft_iterative_power(t_ll nb, t_ll power);
t_ll	ft_recursive_power(t_ll nb, t_ll power);
t_ll	ft_sqrt(t_ll nb);
bool	ft_iscntrl(int c);
bool	ft_isgraph(int c);
bool	ft_isinf(double num);
bool	ft_ispunct(int c);
bool	ft_isspace(int c);

/*
**	REDO THESE
*/

void	*ft_realloc(char *oldptr, char *newptr, size_t oldsize, size_t newsize);

/*
**	FIXED & ADDED
*/

char	*ft_str_realloc(char *oldptr, size_t newlen);
char	*ft_int_to_base(char *res, char *basestr, int input);
size_t	ft_get_base_from_str(char *basestr);
void	ft_str_rev(char *str);
char	*ft_bin_32bit_str(char *str, int input, int negflag, int i);
char	*ft_bin_64bit_str(char *str, long input, int negflag, int i);
char	*ft_bin_128bit_str(char *str, t_ll input, int negflag, int i);
char	*ft_bin2compl_str(char *str, int i);
char	*ft_itoa_base(int n, char *basestr);
char	*ft_ui_to_base(char *res, char *basestr, t_ui input);
void	ft_putnbr_ui_fd(t_ui n, int fd);
char	*ft_uitoa_base(t_ui n, char *basestr);
char	*ft_long_to_base(char *res, char *basestr, long input);
void	ft_putnbr_long_fd(long n, int fd);
char	*ft_ltoa_base(long n, char *basestr);
void	ft_putnbr_ulong_fd(t_ul n, int fd);
char	*ft_ulong_to_base(char *res, char *basestr, t_ul input);
char	*ft_ultoa_base(t_ul n, char *basestr);
void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putendl(char *s);
void	ft_putnbr_ultimate_fd(t_ll n, int fd);
void	ft_putnbr_ult(t_ll n);
void	ft_putnstr_fd(char *s, size_t n, int fd);
void	ft_putnstr(char *s, size_t n);
bool	ft_strequal(char *s1, char *s2);
char	*ft_strjoin_char(const char *s1, char c);
char	*ft_strndup(const char *s, size_t n);
void	ft_putwidechar_fd(int fd, wchar_t wide_c);
void	ft_putwidechar(wchar_t wide_c);
size_t	ft_wstrlen(const wchar_t *wide_str);
void	ft_putwidestr_fd(int fd, wchar_t *wide_str);
void	ft_putwidestr(wchar_t *wide_str);
void	ft_putwidestr_nl(wchar_t *wide_str);
char	*ft_strjoin_plus_wide(const char *s1, const wchar_t *s2);
wchar_t	*ft_widestrjoin(const wchar_t *s1, const wchar_t *s2);
wchar_t	*ft_widestrdup(const wchar_t *s);
wchar_t	*ft_widestrndup(const wchar_t *s, size_t n);
void	ft_widestrdel(wchar_t **str);
char	*ft_strjoin_widechar(const char *s1, wchar_t c);
char	*ft_ftoa(double nb, int precision);
double	ft_modf(double x, double *iptr);
int		ft_floor_int(double x);
t_ll	ft_floor_ll(double x);
double	ft_floor(double x);
double	ft_abs_float(double x);
double	ft_bankers_round(double x, int precision);
double	ft_roundf(double nb, int decimals);
bool	ft_almost_eq_rel(float a, float b, float maxreldiff);
long	ft_atol(const char *numstr);
char	*ft_strjoin_realloc(char *s1, const char *s2);
void	ft_str_array_del(char ***str_array);

#endif
