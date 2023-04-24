/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:17:33 by johrober          #+#    #+#             */
/*   Updated: 2022/12/12 16:20:07 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <libft.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include <dirent.h>

# define WIDTH				1600
# define HEIGHT				900
# define WINDOW_NAME		"MiniRT"
# define M_PI				3.14159265358979323846
# define DEGREE_TO_RADIAN	0.017453293
# define CAMR				15.0
# define SPEC_SHN			32
# define SPEC_STR			1.0
# define CHK_CYL			10
# define CHK_SPH			16
# define TEXTURE_SIZE		6.0
# define LIGHT_RANGE		20.0

typedef enum e_form {SPHERE, CYLINDER, PLANE, LIGHT, AMBLIGHT, NONE}	t_form;
typedef enum e_imgs {BG, PLS, MIN, DIA, POS, DIREC, RGB, HEI, RAT, REF, \
	SPH, CYL, PLN, LGT, AMB}	t_imgs;

typedef struct s_img
{
	void			*image;
	unsigned char	*buf;
	int				l_bits;
	int				p_bits;
	int				endian;
	int				width;
	int				height;
}				t_img;

typedef struct s_bumpmap
{
	t_img	*img;
	double	**map;
}				t_bumpmap;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct s_quat
{
	double	w;
	double	x;
	double	y;
	double	z;
}				t_quat;

typedef struct s_hit
{
	t_form			type;
	void			*object;
	t_vec			norm;
	t_vec			pos;
	double			t;
}				t_hit;

typedef struct s_ray
{
	t_vec	*pos;
	t_vec	*dir;
	t_hit	*hit_list;
	int		debug;
}				t_ray;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}				t_rgb;

typedef struct s_gui
{
	t_hit	*selection;
	t_img	**imgs;
	void	*win;
	int		res_x;
	int		res_y;
}				t_gui;

typedef struct s_program
{
	void				*mlx;
	void				*win;
	int					res_x;
	int					res_y;
	t_img				*img;
	t_ray				***rays;
	struct s_sphere		*sphere;
	struct s_plane		*plane;
	struct s_amblight	*amblight;
	struct s_light		*light;
	struct s_cylinder	*cylinder;
	struct s_camera		*camera;
	t_rgb				**map;
	t_gui				*gui;
}				t_program;

typedef struct s_amblight
{
	double				ratio;
	t_rgb				*rgb;
}				t_amblight;

typedef struct s_camera
{
	t_vec			*pos;
	t_vec			*dir;
	t_vec			*x;
	t_vec			*y;
	t_vec			*z;
	double			fov;
	double			height;
	double			width;
}				t_camera;

typedef struct s_light
{
	t_vec			*pos;
	double			ratio;
	t_rgb			*rgb;
}				t_light;

typedef struct s_sphere
{
	t_vec			*pos;
	double			diameter;
	t_rgb			*rgb;
	struct s_sphere	*next;
}				t_sphere;

typedef struct s_plane
{
	t_vec			*pos;
	t_vec			*dir;
	t_rgb			*rgb;
	struct s_plane	*next;
}				t_plane;

typedef struct s_cylinder
{
	t_vec				*pos;
	t_vec				*dir;
	double				diameter;
	double				height;
	t_rgb				*rgb;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct s_lratio
{
	double	diffuse;
	double	specular;
	t_vec	vec_to_spot;
	t_vec	norm;
	t_ray	ray_to_spot;
	t_hit	spot_hit;
}			t_lratio;

////////////////////////////////////////
///////////	Basic program //////////////
////////////////////////////////////////

/****************	main.c	***************/
int			main(int argc, char **argv);
int			check_arg(char *str);
void		clean_exit(t_program *p, int exit_code, char *prompt);

/***********	window_management  ********/
int			hook_loop(t_program *p);
int			hook_key(int keycode, t_program *p);
int			hook_mouse(int button, int x, int y, t_program *p);
int			close_win(t_program *p);

/**************	 draw_management  *********/
void		render(t_program *p, t_rgb **tab);
t_img		*get_img(t_program *p, t_rgb **tab);
void		fill_img(t_img *img, t_rgb **tab);
void		fill_pixel(t_img *img, t_rgb **tab, int x, int y);

////////////////////////////////////////
/////////////// Parsing ////////////////
////////////////////////////////////////

/****************	get_scene.c	*******/
void		get_scene(t_program *program, char *filepath);

/****************	checking	***********/
int			check_amblight(char **array);
int			check_light(char **array);
int			check_camera(char **array);
int			check_sphere(char **array);
int			check_plane(char **array);
int			check_cylinder(char **array);
int			check_rgb_parsing(char *str);
int			check_ratio_parsing(char *str);
int			check_size_parsing(char *str);
int			check_vector_parsing(char *str, int isnormalized);

/****************	init_structs.c	*******/
int			init_pos(t_vec *pos, char *str);
int			init_vector(t_vec *dir, char *str);
int			init_rgb(t_rgb *rgb, char *str);

////////////////////////////////////////
///// Raycasting and intersections /////
////////////////////////////////////////

/************	raycasting.c	***********/
t_ray		***get_camera_rays(t_camera *cam);
void		get_closest_hit(t_hit *hit, t_program *p, t_ray *ray);
void		render_scene(t_program *p);
void		cast_single_ray(t_rgb *rgb, t_program *p, t_ray *ray);
void		apply_lighting(t_rgb *rgb, t_program *p, t_hit *hit, t_ray *ray);

/*********** raycasting_utils.c ***********/
void		get_corner_vectors(t_vec *corners, t_camera *cam);
void		get_delta(t_vec *dx, t_vec *dy, t_vec *corners);

/***************  intersections  *****************/
void		get_closest_sphere_hit(t_hit *closest, t_ray *ray, t_sphere *sph);
void		hit_sphere(t_hit *hit, t_ray *ray, t_sphere *sph);
void		get_closest_cyl_hit(t_hit *hit, t_ray *ray, t_cylinder *lst);
void		hit_cylinder(t_hit *hit, t_ray *ray, t_cylinder *cyl);
void		get_closest_plane_hit(t_hit *hit, t_ray *ray, t_plane *list);
void		hit_plane(t_hit *hit, t_ray *ray, t_plane *pln);

////////////////////////////////////////
///////////	Struct utils ///////////////
////////////////////////////////////////

/**************** tcamera.c ***************/
t_camera	*tcamera_init(void);
int			tcamera_allocate(t_camera *cam);
void		tcamera_destroy(t_camera *cam);
int			lst_add_back_camera(t_program *p, char **array);

/**************** tamblight.c ***************/
t_amblight	*tamblight_init(void);
int			tamblight_allocate(t_amblight *amb);
void		tamblight_destroy(t_amblight *amb);
int			lst_add_back_amblight(t_program *p, char **array);

/**************** tsphere.c ***************/
t_sphere	*tsphere_init(void);
int			tsphere_allocate(t_sphere *sph);
void		tsphere_destroy(t_sphere *sph);
void		tsphere_destroy_all(t_sphere *sph);
int			lst_add_back_sphere(t_program *p, char **array);

/**************** tlight.c ***************/
t_light		*tlight_init(void);
int			tlight_allocate(t_light *light);
void		tlight_destroy(t_light *light);
void		tlight_destroy_all(t_light *light);
int			lst_add_back_light(t_program *p, char **array);

/**************** tplane.c ***************/
t_plane		*tplane_init(void);
int			tplane_allocate(t_plane *pln);
void		tplane_destroy(t_plane *pln);
void		tplane_destroy_all(t_plane *pln);
int			lst_add_back_plane(t_program *p, char **array);

/**************** tcylinder.c ***************/
t_cylinder	*tcylinder_init(void);
int			tcylinder_allocate(t_cylinder *cyl);
void		tcylinder_destroy(t_cylinder *cyl);
void		tcylinder_destroy_all(t_cylinder *cyl);
int			lst_add_back_cylinder(t_program *p, char **array);

/****************	tprogram.c	***********/
t_program	*tprogram_init(void);
void		tprogram_load(t_program *p);
void		free_rays(t_ray ***rays);
int			tprogram_destroy(t_program *p);

////////////////////////////////////////////
///////////////// Utils	////////////////////
////////////////////////////////////////////

/******************** Misc ****************/
void		blend_colors(t_rgb *color1, t_rgb *color2);
double		get_distance(t_vec *p1, t_vec *p2);
void		copy_rgb(t_rgb *map, t_rgb *cpy);
char		*ft_ftoa(float nbr);
char		*ft_ftoa_free(float nbr, char *to_free);
void		refresh_screen(t_program *p);

/*************** Vector basics ************/
t_vec		*get_vector_norm(t_vec *vec);
t_vec		*to_vector(t_vec *result, double x, double y, double z);
t_vec		*vector_normalize(t_vec *vec);
t_vec		*vector_copy(t_vec *result, t_vec *to_copy);
t_rgb		*to_rgb(t_rgb *result, double r, double g, double b);

/************* Vector allocation **********/
t_vec		*to_allocated_vector(double x, double y, double z);
t_vec		*vector_allocated_copy(t_vec *to_copy);
t_rgb		*to_allocated_rgb(double r, double g, double b);
t_rgb		*copy_new_rgb(t_rgb *src);

/************** Vector operations **********/
t_vec		*vector_sum(t_vec *result, t_vec *v1, t_vec *v2);
t_vec		*vector_sub(t_vec *result, t_vec *orig, t_vec *pos);
t_vec		*vector_multiplication(float f, t_vec *vec);
t_vec		*vector_fsum(float f, t_vec *v);

/************ Geometrical algebra *********/
double		dot_product(t_vec *v1, t_vec *v2);
t_vec		*cross_product(t_vec *result, t_vec *v1, t_vec *v2);
void		vector_reflect(t_vec *result, t_vec *a, t_vec *b);

/************** Quaternion utils **********/
t_quat		*get_allocated_quaternion(t_vec *axis, double rotation);
t_quat		*get_quaternion(t_quat *result, t_vec *axis, double rotation);
t_vec		*apply_rotation(t_vec *vec, t_quat *quat);
t_quat		*quaternion_mult(t_quat *result, t_quat *a, t_quat *b);

/***************** move ******************/
void		move_camera(t_program *p, int key);
void		rotate_camera(t_program *p, int key);

////////////////////////////////////////////
///////////////// Gui   ////////////////////
////////////////////////////////////////////

/***************** blit ******************/
void		blit_sphere_imgs(void *mlx, t_gui *gui);
void		blit_cylinder_imgs(void *mlx, t_gui *gui);
void		blit_plane_imgs(void *mlx, t_gui *gui);
void		blit_amblight_imgs(void *mlx, t_gui *gui);
void		blit_light_imgs(void *mlx, t_gui *gui);

/***************** change *****************/
void		change_sph_rgb(t_program *p, int x, unsigned char c);
void		change_sph_pos(t_program *p, int x, unsigned char c);
void		change_sph_diameter(t_program *p, int x);
void		change_cyl_diameter(t_program *p, int x);
void		change_cyl_height(t_program *p, int x);
void		change_cyl_dir(t_program *p, int x, unsigned char c);
void		change_cyl_rgb(t_program *p, int x, unsigned char c);
void		change_cyl_pos(t_program *p, int x, unsigned char c);
void		change_pln_dir(t_program *p, int x, unsigned char c);
void		change_pln_rgb(t_program *p, int x, unsigned char c);
void		change_pln_pos(t_program *p, int x, unsigned char c);
void		change_light_pos(t_program *p, int x, unsigned char c);
void		change_light_rgb(t_program *p, int x, unsigned char c);
void		change_light_ratio(t_program *p, int x);
void		change_amb_ratio(t_program *p, int x);
void		change_amb_rgb(t_program *p, int x, unsigned char c);

/***************** init *****************/
void		load_gui_images(t_gui *gui, void *mlx);

/***************** print *****************/
void		print_sphere(t_program *p, t_hit *hit);
void		print_cylinder(t_program *p, t_hit *hit);
void		print_plane(t_program *p, t_hit *hit);
void		print_light(t_program *p, t_hit *hit);
void		print_amblight(t_program *p, t_hit *hit);

/************** print utils **************/
int			print_diameter(void *mlx, t_gui *gui, int x, int y);
int			print_height(void *mlx, t_gui *gui, int x, int y);
int			print_position(void *mlx, t_gui *gui, int x, int y);
int			print_direction(void *mlx, t_gui *gui, int x, int y);
int			print_ratio(void *mlx, t_gui *gui, int x, int y);
int			print_rgb(void *mlx, t_gui *gui, int x, int y);
void		print_to_gui(t_program *p, double n, int x, int y);

/******************* gui ********************/
void		clear_screen(void *mlx, void *win, void *bg);
int			tgui_destroy(void *mlx, t_gui *gui);
t_gui		*init_gui(void *mlx);

/******************* hooks ********************/
void		sphere_hook(int x, int y, t_program *p);
void		cylinder_hook(int x, int y, t_program *p);
void		plane_hook(int x, int y, t_program *p);
void		amblight_hook(int x, int y, t_program *p);
void		light_hook(int x, int y, t_program *p);
int			gui_hook_mouse(int button, int x, int y, t_program *p);
int			gui_hook_key(int keycode, t_program *p);

#endif//MINIRT_H

/***********************	TODO	**************************
 * Better button hitboxes
 * clean code
 * push
 * ???
 * profit
*/
