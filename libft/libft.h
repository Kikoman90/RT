/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:58:21 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/14 16:39:58 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define BUFF_SIZE 1000

typedef struct		s_info
{
	double			a;
	int				e;
	int				c;
	int				sign;
	int				i;
	int				count;
}					t_info;

typedef	struct		s_rgb
{
	double			r;
	double			g;
	double			b;
}					t_rgb;

typedef	struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef	struct		s_get
{
	int				nb_read;
	int				fd;
	int				i;
	char			*read;
	struct s_get	*next;
}					t_get;

void				ft_error(char *str, int i);

int					ft_atoi(const char *str);
char				*ft_ftoa(float nb);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_memset_int(int *tab, int i, int limit);
void				ft_putchar(char c);
void				ft_putnbr(int n);
void				ft_putstr(char const *s);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char *s1, char *s2, char type);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
size_t				ft_strclen(char c, const char *str);
char				*ft_strncat(char *dest, const char *src, size_t nb);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_matoi(const char *str, int *tab);
int					ft_matoi2(const char *str);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_toupper(int s);
int					ft_tolower(int s);
char				**ft_strsplit(char const *s, char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_strclr(char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_itoa(int n);
double				ft_atof(char *s);
double				ft_pow(double i, int p);
double				ft_clamp(double value, double min, double max);
void				ft_vec_para(t_vec *xyz, double x, double y, double z);
void				ft_rgb_para(t_rgb *rgb, int r, int g, int b);
void				ft_sinvec(t_vec *vec);
void				ft_tanvec(t_vec *vec);
float				dot(t_vec *v1, t_vec *v2);
t_vec				ft_vectorscale(t_vec *v, float n);
t_vec				ft_vectorsub(t_vec *v1, t_vec *v2);
t_vec				ft_vectorcross(t_vec *v1, t_vec *v2);
t_vec				ft_vectoradd(t_vec v1, t_vec v2);
void				ft_vectornorm(t_vec *v);
void				ft_cosvec(t_vec *vec);
int					get_next_line(int const fd, char **line);
void				ft_dzero(double *s, int n);
void				ft_fzero(float *s, int n);
double				*ft_tab_coef(double *tab, double coef, int size);

#endif
