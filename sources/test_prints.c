void	print_matrix_vector(t_matrix_vector vector)
{
	int	i;
		
	i = -1;
	while (++i < MTX)	
		printf("%f ", vector.axis[i]);	
	printf("\n\n");
}

void	print_matrix(t_matrix_vector matrix[])
{
	int	i;
	int	j;
		
	i = -1;
	while (++i < MTX)
	{
		j = -1;
		while (++j < MTX)
			printf("%f ", matrix[i].axis[j]);
		printf("\n");
	}
	printf("\n");
}

void	print_cam_content(t_data data)
{	
	printf("data.cam.origin_vect.axis[0]: %f\n",data.cam.origin_vect.axis[0]);
	printf("data.cam.origin_vect.axis[1]: %f\n",data.cam.origin_vect.axis[1]);
	printf("data.cam.origin_vect.axis[2]: %f\n",data.cam.origin_vect.axis[2]);
	printf("data.cam.forward_vect.axis[0]: %f\n",data.cam.forward_vect.axis[0]);
	printf("data.cam.forward_vect.axis[1]: %f\n",data.cam.forward_vect.axis[1]);
	printf("data.cam.forward_vect.axis[2]: %f\n",data.cam.forward_vect.axis[2]);
	printf("data.cam.forward_vect.axis[2]: %f\n",data.cam.forward_vect.axis[2]);	
	printf("data.cam.up_vect.axis[0]: %f\n",data.cam.up_vect.axis[0]);
	printf("data.cam.up_vect.axis[1]: %f\n",data.cam.up_vect.axis[1]);
	printf("data.cam.up_vect.axis[2]: %f\n",data.cam.up_vect.axis[2]);
	printf("data.cam.right_vect.axis[0]: %f\n",data.cam.right_vect.axis[0]);
	printf("data.cam.right_vect.axis[1]: %f\n",data.cam.right_vect.axis[1]);
	printf("data.cam.right_vect.axis[2]: %f\n",data.cam.right_vect.axis[2]);
	printf("resol0: %f\n",data.cam.resol[0]);
	printf("resol1: %f\n",data.cam.resol[1]);
	printf("fov: %f\n",data.cam.fov_deg);
	printf("fov: %f\n",data.cam.fov_rad);
	printf("scale: %f\n",data.cam.scale);
	printf("aspect: %f\n",data.cam.aspect);
	printf("focal_len: %f\n",data.cam.focal_len);
}

void	print_sphere(t_sphere sphere)
{
	printf("sphere.origin_vect.axis[0]: %f\n", sphere.origin_vect.axis[0]);
	printf("sphere.origin_vect.axis[1]: %f\n", sphere.origin_vect.axis[1]);
	printf("sphere.origin_vect.axis[2]: %f\n", sphere.origin_vect.axis[2]);
	printf("sphere.diameter: %f\n", sphere.diameter);
	printf("spheres.square_radius: %f\n", sphere.square_radius);
	printf("spheres.color.rgb[0]: %i\n", sphere.color.rgb[0]);
	printf("spheres.color.rgb[1]: %i\n", sphere.color.rgb[1]);
	printf("spheres.color.rgb[2]: %i\n", sphere.color.rgb[2]);
}
