#ifndef X_EVENTS_H
# define X_EVENTS_H

typedef enum e_event_mesh
{
	E_CAM,	
	E_SPOTL,
	E_AMBL,
	E_MESH
}	t_event_mesh;

typedef struct s_event
{
	int				ctrl_ispressed;
	int				legend;
	t_event_mesh	actual_mode;
	t_obj			actual_mesh;
	t_color			color_sav;
}	t_event;

typedef enum e_event
{
	ESC = 65307,
	RST = 114,
	RST_CM = 65437,
	UP = 65434,
	DWN = 65435,
	LFT = 65363,
	RGHT = 65361,
	FWRD = 65362,
	BACK = 65364,
	R_UP = 65431,
	R_DWN = 65433,
	R_LFT = 65430,
	R_RGHT = 65432,
	S_LFT = 65436,
	S_RGHT = 65429,
	PLUS = 65451,
	MINUS = 65453,
	CAM = 99,
	AMBL = 97,
	LIGHT = 108,
	MESH = 111,
	CTRL = 65507,
	CTRL_2 = 65508,
	MAKE_RT_FILE = 109,
	VIDEO_NEXT_FRAME = 118,
	MAKE_BIN_FILE = 98
}	t_enum_event;

#endif