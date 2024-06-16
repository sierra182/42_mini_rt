#include "get_sph_pl_bck_color_bonus.h"
void	clamp_rgb_0(t_color *color);
#include <math.h>
void	modif_uv(t_get_color_params *params, t_ray_pack light_ray, int size);
void calculate_uv(t_ray_vector point, double *u, double *v);
void checker_color(double u, double v, int checker_size, t_color *color);
void checker_color_grayscale(double u, double v, int checker_size, t_color *color, double bump_coef);

#include "libft.h"
#define TEXTURE_WIDTH 512
#include <string.h>
#include <stdlib.h>
// void cartesian_to_spherical(t_ray_vector *point, float *theta, float *phi)
// {
// 	float r;
	
// 	r = sqrt(point->axis[0]* point->axis[0]+ point->axis[1] * point->axis[1] + point->axis[2] * point->axis[2]);
// 	*theta = acos(point->axis[2] / r);
// 	*phi = atan2(point->axis[1], point->axis[0]);
// }


/**========================================================================
 *                             COMMENT BLOCK
 *  modif_uv(params, light_ray, 10);
	apply_aces_tonemap(params->color);
*  			AND
void	modif_uv(t_get_color_params *params, t_ray_pack light_ray, int size);

*========================================================================**/


void uv_to_texture_coordinates(double u, double v, int *x, int *y) {
	*x = (int)(u * TEXTURE_WIDTH);
	*y = (int)(v * TEXTURE_WIDTH);

	if (*x < 0) *x = 0;
	if (*y < 0) *y = 0;
	if (*x >= TEXTURE_WIDTH) *x = TEXTURE_WIDTH - 1;
	if (*y >= TEXTURE_WIDTH) *y = TEXTURE_WIDTH - 1;
	// printf("%f, %f => %i, %i\n", u, v, *x, *y);
}	

int gray_to_hex_string(const char *gray_string, char *hex_output)
{
	if (ft_strncmp(gray_string, "black", 4) == 0) {
		// printf("Input string is not in the correct format\n");
		strcpy(hex_output, "#FFFFFF");
		return 1;
	}
	if (ft_strncmp(gray_string, "white", 4) == 0) {
		// printf("Input string is not in the correct format\n");
		strcpy(hex_output, "#000000");
		return 1;
	}
	
	if (ft_strncmp(gray_string, "gray", 4) != 0) {
		// printf("Input string is not in the correct format\n");
		strcpy(hex_output, "Invalid");
		return 0;
	}
	int gray_value = ft_atoi(gray_string + 4);
	if (gray_value < 0) gray_value = 0;
	if (gray_value > 100) gray_value = 100;
	int intensity = (int)(gray_value * 255 / 100);
	sprintf(hex_output, "#%02X%02X%02X", intensity, intensity, intensity);
	return (1);
}

int hex_to_int(const char *hex_string)
{
	if (hex_string[0] != '#')
	{
		printf("Invalid format\n");
		return -1;
	}
	int color_value = (int)strtol(hex_string + 1, NULL, 16);
	return color_value;
}

t_ray_vector apply_bump_map(t_ray_vector normal, t_ray_vector tangent, t_ray_vector bitangent, double bump_factor)
{
    // Calculer la nouvelle normale
    t_ray_vector perturbed_normal = {
        normal.axis[0] + bump_factor * tangent.axis[0] + bump_factor * bitangent.axis[0],
        normal.axis[1] + bump_factor * tangent.axis[1] + bump_factor * bitangent.axis[1],
        normal.axis[2] + bump_factor * tangent.axis[2] + bump_factor * bitangent.axis[2]
    };

    // Normaliser la normale perturbée
	self_normalize_vector(perturbed_normal.axis);
    return (perturbed_normal);
}

void	modif_uv(t_get_color_params *params, t_ray_pack light_ray, int size)
{
	double u;
	double v;
	t_sphere		*sphere;

	// printf("modif_uv\n");

	sphere = (t_sphere *) params->mesh->ref;
	if (sphere->checkerboard == 0 && sphere->bump_map_nbr == -1)
		return ;
	calculate_uv(*params->normal, &u, &v);
	if (sphere->checkerboard == 1)
	{
		checker_color(u, v, size, params->color);
		return ;
	}
	int x, y;
	uv_to_texture_coordinates(u, v, &x, &y);
	double bump_coef;
	bump_coef = params->data->bump_maps[sphere->bump_map_nbr][x][y];
	if (sphere->bump_map_nbr == 1)
		{printf("sphere->bump_map_path: %s, sphere->bump_map_nbr: %i\n", sphere->bump_map_path, sphere->bump_map_nbr);
		// printf("bump_coef: %f\n", bump_coef);
		printf("%i, %i: texture value: %f\n", x, y, bump_coef);}
	// printf("modif_uv: sphere->bump_map_nbr: %i, x: %i, y: %i\n", sphere->bump_map_nbr, x, y);
	checker_color_grayscale(u, v, size, params->color, bump_coef);
	// *params->normal = apply_bump_map(*params->normal, (t_ray_vector){1,1,1}, (t_ray_vector){1,1,1}, bump_coef);
	
}

void calculate_uv(t_ray_vector point, double *u, double *v) {
	double theta;
	double phi;
	
	theta = atan2(point.axis[2], point.axis[0]);
	phi = asin(point.axis[1]);

	*u = 0.5 + theta / (2 * M_PI);
	*v = 0.5 - phi / M_PI;
}

void checker_color_grayscale(double u, double v, int checker_size, t_color *color, double bump_coef)
{
	int u_index = (int)(u * checker_size);
	int v_index = (int)(v * checker_size);
	
	color->rgb[0] *= bump_coef;
	color->rgb[1] *= bump_coef;
	color->rgb[2] *= bump_coef;
}

void checker_color(double u, double v, int checker_size, t_color *color)
{
	int u_index = (int)(u * checker_size);
	int v_index = (int)(v * checker_size);
	int	is_checker;
		
	is_checker = (u_index % 2 == v_index % 2);
	if (is_checker)
	{
		color->rgb[0] *= 0.3;
		color->rgb[1] *= 0.3;
		color->rgb[2] *= 0.3;
	}
}