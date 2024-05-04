#import "x_mini_struct.h"
#include <math.h>

double calculate_elevation(t_ray ray)
{
    double x = ray.dir_vect.axis[0];
    double y = ray.dir_vect.axis[1];
    double z = ray.dir_vect.axis[2];

    // Calculer l'élévation en radians
    double elevation = atan2(z, sqrt(x * x + y * y));

    // Convertir l'élévation en degrés
    elevation *= 180.0 / M_PI;

    return elevation;
}

