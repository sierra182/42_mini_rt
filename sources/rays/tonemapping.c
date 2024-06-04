# include "se_mini_struct.h"
# include "x_linear_algebra.h"
# include "x_color_effect.h"

int		has_shadow(t_data *data, t_ray_vector *normal, t_obj *mesh, t_ray *light_ray);
void	get_intersect_point(t_ray *ray, double t, t_ray_vector *inter_pt);
int		is_sphere_surface_between(t_sphere *sphere, t_spotlight *spotlight);


float aces_tonemap(float x) {
    const float a = 2.51f;
    const float b = 0.03f;
    const float c = 2.43f;
    const float d = 0.59f;
    const float e = 0.14f;
    
    return (x * (a * x + b)) / (x * (c * x + d) + e);
}