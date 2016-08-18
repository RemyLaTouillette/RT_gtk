int		hit_triangle(t_obj *m, t_vect *r_pos, t_vect *r_dir, double *out)
{
	t_vect	e[2];
	t_vect	p[2];
	double	inv;
	double	det;
	double	v[3];

	subtract(set_to(&e[0], &(m->dir2)), &(m->dir));
	subtract(set_to(&e[1], &(m->dir3)), &(m->dir));
	cross_product(set_to(&p[0], r_dir), &e[1]);
	if ((det = dot_product(&e[0], &p[0])), det > -0.000001 && det < 0.000001)
		return (0);
	inv = 1.0 / det;
	subtract(set_to(&p[1], r_pos), &(m->dir));
	if ((v[0] = dot_product(&p[1], &p[0]) * inv), v[0] < 0 || v[0] > 1)
		return (0);
	cross_product(&p[1], &e[0]);
	if ((v[1] = dot_product(r_dir, &p[1]) * inv), v[1] < 0 || v[0] + v[1] > 1)
		return (0);
	if ((v[2] = dot_product(&e[1], &p[1]) * inv) > 0.000001)
	{
		*out = v[2];
		return (1);
	}
	return (0);
}
