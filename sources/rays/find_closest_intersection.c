# include "mlx.h"
# include "x_mini_struct.h"

//void	new_ray(t_cam *cam, t_ray *ray, int x, int y);

double	is_intersect_sphere(t_ray *ray, void *input_sphere, t_ray_vector *i);
double	is_intersect_plane(t_ray *ray, void *input_plane, t_ray_vector *i);
int	intersect_disc_plans(t_ray *ray, t_cylinder *cyl, t_ray_vector	*i);
double	is_intersect_cylinder(t_ray *ray, void *input_cyl, t_ray_vector *t);
int		is_behind_cam(double t);
void	get_sphere_color(t_ray *ray, double t, t_sphere *sphere, t_spotlight *spotlight, t_color *color, t_ambiant_light *ambiant_light);
void	get_plane_color(t_ray *ray, double t, t_plane *plane, t_spotlight *spotlight, t_color *color, t_sphere *sphere, t_ambiant_light *ambiant_light, t_cylinder *cylinder);
int	get_background_color(t_ray *ray);

void	put_pxl(t_mlx *mlx, int x, int y, unsigned int color);
int	get_color(unsigned char r, unsigned char g, unsigned char b);
void	scale_vector(double vect[], double scaler, double scaled_vect[]);
void    add_vector(double a[], double b[], double sum_vect[]);
void	normalize_vector(double vector[]);
void	get_closest_intersection_sp(t_data *data, t_ray ray, t_obj_intersect *obj);
void	get_closest_intersection_cy(t_data *data, t_ray ray, t_obj_intersect *obj);
void	get_closest_intersection_pl(t_data *data, t_ray ray, t_obj_intersect *obj);

void find_closest_intersection(t_intersection_params params)
{
	int		i;
	double	t;

	i = 0;
	while (i < params.obj_nbr)
	{
		t = params.intersect_func(&params.ray, ((char **)params.objects)[i], params.i);
		if (t && t < params.obj->t)
		{
			params.obj->t = t;
			params.obj->type = params.obj_type;
			params.obj->ref = ((t_sphere **)params.objects)[i];
		}
		i++;
	}
}

void	get_closest_intersection_sp(t_data *data, t_ray ray, t_obj_intersect *obj)
{
	t_intersection_params 	params_sp;
	t_sphere				*sphere_addresses[1000];
	int						i;

	i = -1;
	while (++i < data->sp_nbr)
		sphere_addresses[i] = &(data->spheres[i]);
	params_sp.objects = sphere_addresses;
	params_sp.ray = ray;
	params_sp.obj_nbr = data->sp_nbr;
	params_sp.intersect_func = is_intersect_sphere;
	params_sp.obj = obj;
	params_sp.obj_type = O_SP;
	params_sp.i = NULL;
	find_closest_intersection(params_sp);
}

void	get_closest_intersection_cy(t_data *data, t_ray ray, t_obj_intersect *obj)
{
	t_intersection_params 	params_cy;
	t_cylinder				*cylinders_addresses[1000];
	int						i;

	i = -1;
	while (++i < data->cy_nbr)
		cylinders_addresses[i] = &(data->cylinders[i]);
	params_cy.objects = cylinders_addresses;
	params_cy.ray = ray;
	params_cy.obj_nbr = data->cy_nbr;
	params_cy.intersect_func = is_intersect_cylinder;
	params_cy.obj = obj;
	params_cy.obj_type = O_CY;
	params_cy.i = NULL;
	find_closest_intersection(params_cy);
}

void	get_closest_intersection_pl(t_data *data, t_ray ray, t_obj_intersect *obj)
{
	t_intersection_params 	params_pl;
	t_plane				*planes_addresses[1000];
	int						i;

	i = -1;
	while (++i < data->pl_nbr)
		planes_addresses[i] = &(data->planes[i]);
	params_pl.objects = planes_addresses;
	params_pl.ray = ray;
	params_pl.obj_nbr = data->pl_nbr;
	params_pl.intersect_func = is_intersect_plane;
	params_pl.obj = obj;
	params_pl.obj_type = O_PL;
	params_pl.i = NULL;
	find_closest_intersection(params_pl);
}