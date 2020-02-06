t_inter	interpl(t_ray ray, void *ptr, double start, double max)
{
	t_pl	pl;
	t_inter	rt;
	t_vec	l;
	double	d;
	double	m;

	pl = *(t_pl*)ptr;
	m = prod_scal(pl.dir, ray.dir);
	if (d_abs(m) < start)
	{
		rt.inter = 0;
		return (rt);
	}
	else
	{
		l = sub_vec(ray.o, pl.p);
		d = prod_scal(pl.dir, l);
		rt.inter = -d / m;
	}
	if (rt.inter > start && rt.inter < max)
		rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	else
	{
		rt.inter = 0;
		return (rt);
	}
	rt.reflect = pl.reflect;
	rt.spec = pl.spec;
	rt.color = pl.color;
	rt.normal = prod_scal(sub_vec(pl.p, ray.o), pl.dir) < 0 ? pl.dir : mult_vec_d(pl.dir, -1);
	return (rt);
}
