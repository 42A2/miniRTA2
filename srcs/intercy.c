t_inter	intercy(t_ray ray, void *ptr, double start, double max)
{
	t_vec	L;
	t_cy	cy;
	t_vec	w;
	double	sqr_omega;
	t_vec	wn;
	double	R;
	t_vec	E;
	double	t;
	t_inter	rt;
	t_vec	F;
	t_vec	Fn;
	double	s;
	t_vec	cp;
	double	cq;
	t_vec	qp;
	int		boo;

	cy = *(t_cy*)ptr;
	boo = 0;
	L = sub_vec(ray.o, cy.p);
	w = cross_prod(ray.dir, cy.dir);
	sqr_omega = prod_scal(w, w);
	if (!sqr_omega)
		rt.inter = 0;
	else
	{
		wn = div_vec_d(w, sqrt(sqr_omega));
		R = d_abs(prod_scal(L, wn));
		if (R > cy.r)
			rt.inter = 0;
		else
		{
			E = cross_prod(L, cy.dir);
			t = prod_scal(mult_vec_d(E, -1), wn) / sqrt(sqr_omega);
			F = cross_prod(wn, cy.dir);
			Fn = div_vec_d(F, norm_vec(F));
			s = sqrt(cy.r * cy.r - R * R) / d_abs(prod_scal(ray.dir, Fn));
			rt.inter = t - s;
			if (norm_vec(add_vec(cy.dir, ray.dir)) < norm_vec(add_vec(mult_vec_d(cy.dir, -1), ray.dir)))
				mult_vec_d(cy.dir, -1);
			if (norm_vec(sub_vec(add_vec(ray.o, mult_vec_d(ray.dir, rt.inter)), cy.p)) > sqrt(cy.h / 2 * cy.h / 2 + cy.r * cy.r))
			{
				rt.inter = t + s;
				boo = 1;
				if (norm_vec(sub_vec(add_vec(ray.o, mult_vec_d(ray.dir, rt.inter)), cy.p)) > sqrt(cy.h / 2 * cy.h / 2 + cy.r * cy.r))
					rt.inter = 0;
			}
			else if (rt.inter < 0)
			{
				rt.inter = t + s;
				boo = 1;
			}
		}
	}
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	rt.color = cy.color;
	rt.reflect = cy.reflect;
	rt.spec = cy.spec;
	cp = sub_vec(rt.ipoint, cy.p);
	cq = prod_scal(cp, cy.dir);
	qp = sub_vec(cp, mult_vec_d(cy.dir, cq));
	rt.normal = boo ? cy.dir : div_vec_d(qp, cy.r);
	return (rt);
}
