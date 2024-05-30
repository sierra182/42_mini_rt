#ifndef X_GENERAL_H
# define X_GENERAL_H

typedef struct s_data t_data;

typedef struct s_mlx
{
	void		*connect;
	void		*window;
	t_img		img;
	t_img_items	img_items;
}	t_mlx;

typedef enum e_obj_type
{
	O_SP,
	O_CY,
	O_PL
} t_obj_type;

typedef	struct s_obj_intersect
{
	double			t;
	enum e_obj_type	type;
	void			*ref;
}	t_obj;


#endif