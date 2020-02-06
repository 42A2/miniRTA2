t_inter	intersp(t_ray ray, void *ptr, double start, double max)
{
	double	t1;
	double	t2;
	double	a;
	double	b;
	double	c;
	double	dis;
	t_inter	rt;
	t_sp	sp;
	t_vec	oc;

	sp = *(t_sp*)ptr;
	oc = sub_vec(ray.o, sp.o);
	a = prod_scal(ray.dir, ray.dir);
	b = 2 * prod_scal(oc, ray.dir);
	c = prod_scal(oc, oc) - sp.r * sp.r;
	dis = b * b - 4 * a * c;
	if (dis > 0)
	{
		t1 = (-b + sqrt(dis)) / (2 * a);
		t2 = (-b - sqrt(dis)) / (2 * a);
		if (t1 < 0)
			rt.inter = t2;
		else if (t2 < 0)
			rt.inter = t1;
		else
			rt.inter = t1 < t2 ? t1 : t2;
	}
	else if (dis == 0)
		rt.inter = -b / 2 * a;
	else
		rt.inter = 0;
	rt.color = sp.color;
	rt.spec = sp.spec;
	rt.reflect = sp.reflect;
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	rt.normal = normalize(sub_vec(rt.ipoint, sp.o));
	return (rt);
}
