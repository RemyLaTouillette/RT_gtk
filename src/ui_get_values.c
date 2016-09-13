#include <rtv1.h>

t_vec	get_cam_pos_from_ui(t_env *e)
{
	GObject	*o;
	t_vec	cam_pos;
	double	x;
	double	y;
	double	z;

	// TODO: check override, else return NULL ?
	// X
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_x");
	x = gtk_range_get_value(GTK_RANGE(o));
	// Y
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_y");
	y = gtk_range_get_value(GTK_RANGE(o));
	// Z
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_z");
	z = gtk_range_get_value(GTK_RANGE(o));
	return (init_vector(x, y, z));
}

t_vec	get_cam_dir_from_ui(t_env *e)
{
	GObject	*o;
	t_vec	cam_pos;
	double	x;
	double	y;
	double	z;

	// TODO: check override, else return NULL ?
	// X
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_x");
	x = gtk_range_get_value(GTK_RANGE(o));
	// Y
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_y");
	y = gtk_range_get_value(GTK_RANGE(o));
	// Z
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_z");
	z = gtk_range_get_value(GTK_RANGE(o));
	return (init_vector(x, y, z));
}

int	cartoon_mode_is_active(t_env *e)
{
	GObject		*o;
	gboolean	active;

	o = gtk_builder_get_object(e->builder, "switch_cartoon");
	active = gtk_switch_get_state(GTK_SWITCH(o));
	if (active)
		return (1);
	return (0);
}
