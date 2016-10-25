/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 10:33:47 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/19 10:54:22 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <errno.h>

# define O rt->var.o
# define REFR rt->tobj[rt->var.o].refr
# define REFL rt->tobj[rt->var.o].reflect
# define OB &rt->obj
# define WI &rt->win
# define LI (*line)
# define BA bal->bali[1]
# define LAMBERT tab[3]
# define FOV 2.0
# define PI	3.14159265359
# define AA rt->win.aa
# define NB_THREAD 8
# define LOAD_Y 200
# define LOAD_H 20
# define LOAD_COLOR 0x00FFFF
# define I rt->cam.i
# define J rt->cam.j
# define K rt->cam.k
# define KEYPRESS rt->event.key.keysym.sym

typedef	unsigned char			t_bytes;

typedef	struct		s_rgb2
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb2;

typedef	union		u_color
{
	size_t			color;
	t_rgb2			rgb;
}					t_color;

typedef	struct		s_obj
{
	int				type;
	t_vec			pos;
	t_vec			dir;
	double			rayon;
	double			rayontore;
	t_rgb			rgb;
	t_rgb			rgb_save;
	int				reflect;
	double			coef_refl;
	int				spec;
	int				refr;
	double			hauteur;
	double			ind_refr;
	double			coef_refr;
	int				text_on;
	char			*texture;
	SDL_Surface		*bmp;
	int				check[10];
	double			offset_x;
	double			offset_y;
	double			scale;
	struct s_obj	*next;
}					t_obj;

typedef	struct		s_light
{
	t_vec			pos;
	t_vec			norm;
	t_rgb			rgb;
	int				check[2];
	struct s_light	*next;
}					t_light;

typedef	struct		s_cam
{
	t_vec			pos;
	t_vec			dir;
	t_vec			i;
	t_vec			j;
	t_vec			k;
	int				check[2];
}					t_cam;

typedef	struct		s_win
{
	char			*windname;
	double			aa;
	int				res[2];
	int				check[6];
	int				creat;
	SDL_Event		event;
	int				win_id;
	SDL_Window		*win;
	SDL_Surface		*load;
	SDL_Surface		*surf;
}					t_win;

typedef	struct		s_bal
{
	char			**bali;
	int				i;
}					t_bal;

typedef	struct		s_ray
{
	t_vec			ray_dir;
	double			t;
	double			spec;
}					t_ray;

typedef struct		s_var
{
	double			radius;
	double			ref_now;
	double			max_ref;
	int				effect_on;
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	int				nbli;
	int				nbobj;
	int				prim;
	int				s_x;
	int				s_y;
	t_vec			norm;
	double			ambiant;
	double			t0;
	double			t1;
	double			n1;
	double			n2;
	t_vec			dist;
	double			spec;
	t_vec			ref;
	int				o;
	t_vec			*pos;
	int				check[4];
	int				text_bool;
}					t_var;

typedef struct		s_gui
{
	char			*action;
	SDL_Rect		pos;
	SDL_Surface		*img_static;
	SDL_Surface		*img_hover;
	SDL_Surface		*img_active;
	int				text_w;
	int				text_h;
	struct s_gui	*next;
}					t_gui;

typedef	struct		s_env
{
	t_light			*headli;
	t_obj			*headobj;
	t_obj			*obj;
	t_light			*li;
	t_obj			*tobj;
	t_light			*tli;
	t_ray			ray;
	t_cam			cam;
	t_win			win;
	t_win			tool;
	t_bal			bal;
	t_var			var;
	SDL_Event		event;
	t_gui			*gui;
	t_gui			*begin;
	TTF_Font		*font;
	int				selection;
	int				speed;
	int				sel_i;
}					t_env;

typedef struct		s_th
{
	t_obj			*tobj;
	t_light			*tli;
	t_ray			ray;
	t_cam			cam;
	t_win			win;
	t_var			var;
	SDL_Surface		*texture;
	SDL_Surface		*map;
}					t_th;

typedef struct		s_tab_th
{
	int				i;
	t_env			*rt;
}					t_tab_th;

double				check_value(char *val, int *verif, int i, int j);
char				*check_rgb(char *line, t_rgb *rgb, int i);
char				*check_vect(char *line, t_vec *vect, int i);
char				*check_double(char *line, double *radius, int i, int opt);
char				*take_para_word(void **tmp, char *line, int i);
char				*take_para_int(char *line, int *tmp, int i);
char				*take_para_type(char *line, int *type, int i, int j);
char				*take_refl(char *line, t_obj *obj, int i, int j);
char				*take_para_refract(char *line, t_obj *obj, int i, int j);
char				*take_t(char *line, int *text, void **texture, int i);
char				*take_para_intaa(char *line, double *tmp, int i, int opt);
char				*take_para_on(char *line, int *ref, int i);
char				*take_para_effect(char *line, int *type, int i);
int					test_scene_bal(t_env *rt, t_bal *bal, char *line, int i);
int					test_obj_bal(t_env *rt, t_bal *bal, int i);
int					check_obj(t_obj *obj, int line);
double				get_value(char *val, int j, int *verif);
void				cpy_env_to_th(t_env *rt, t_th *th);

int					obj_para(t_env *rt, char *line, int i, t_bal *bal);
int					light_para(t_env *rt, char *line, int i, t_bal *bal);
int					scene_para(t_env *rt, char *line, int i, t_bal *bal);
int					camera_para(t_env *rt, char *line, int i, t_bal *bal);

int					exit_free(t_env *rt, char *str, int r);
int					exit_error(char *str, int line);
void				*exit_null(char *str, int line);

t_bal				*check_tag(t_env *rt, char *line, int i, t_bal *bal);
int					ft_malloc_list(t_env *rt, char *str);

int					list_to_tab(t_env *rt);

void				check_img(t_env *rt);
void				effect(double *res, int effect);
void				draw_line_load(int x, int y, t_tab_th *tab, SDL_Rect *pos);
void				draw_average_color(t_env *rt);
void				set_system(t_env *rt);
double				inter_caps(t_var *rt, t_obj tmp, t_vec ray, t_vec pos);
int					ft_intersection(t_th *rt, t_obj *obj, t_vec ray, t_vec pos);
double				inter_plane(t_var *rt, t_obj tmp, t_vec ray, t_vec pos);
double				inter_cone(t_var *rt, t_obj tmp, t_vec ray, t_vec pos);
double				inter_cylinder(t_var *rt, t_obj tmp, t_vec ray, t_vec pos);
double				inter_sphere(t_var *rt, t_obj tmp, t_vec ray, t_vec pos);
unsigned int		ft_raytrace(double x, double y, t_th *rt, t_obj *obj);

t_vec				get_norm(t_th *rt, t_obj obj, t_vec pos);
double				*get_diffuse(t_th *rt, int o, t_vec *pos, double *tab);
double				*get_tabs(t_th *rt, t_vec *pos, double *tab, size_t cpt);

int					refl_init(t_th *rt, int o, t_vec *pos);
int					refr_init(t_th *rt, int o, t_vec *pos, int cpt);

int					take_part_of_vect(char *val, int j, double *vect);
int					verif_rgb(int rgb, int i);

void				create_window(t_env *rt);
void				draw_in_img(int x, int y, size_t color, SDL_Surface *surf);

t_gui				*init_ui(t_env *rt, char **action_tab);
char				**init_actions();
void				ft_ui(t_env *rt);
void				update_surface(t_env *rt);
void				initial_ui_surf(t_env *rt);
t_gui				*is_on_a_button(int x, int y, t_gui *gui);
int					is_movemement(int key);
int					handle_pos(t_env *rt, int key);
void				print_infos(t_env *rt, SDL_Surface *surf);
void				object_selection(t_env *rt);

double				inter_caps(t_var *rt, t_obj tmp, t_vec ray, t_vec pos);

t_vec				axis_rot(t_vec vec, t_vec axis, double ang);
void				move_n_scale(t_env *rt, int o, int key);
int					handle_object_pos(t_env *rt, int key);
void				handle_events(t_env *rt);
int					keydown(t_env *rt, int key);
void				calc_key(t_env *rt, t_vec axis, double offset, int info);

int					refr_inter(t_th *rt, int i, t_obj *obj, t_vec pos);
double				*ft_texture(t_th *rt, int o, double *tmp, t_vec pos);
float				noise3(float vec[3]);
double				ft_inter_tore(t_var *rt, t_obj tmp, t_vec ray, t_vec pos);
SDL_Rect			print_txt(SDL_Surface *dest, char *str, t_vec coord,
					TTF_Font *font);
void				clean_quit(t_env *rt);

#endif
