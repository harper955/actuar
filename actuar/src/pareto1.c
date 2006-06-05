/*  ===== actuar: an R package for Actuarial Science =====
 *
 *  Fonctions to compute density, cumulative distribution and quantile
 *  fonctions of the single-parameter Pareto distribution, and to simulate random
 *  variates. See ../R/pareto1.R for details.
 *
 *  AUTHORS: Mathieu Pigeon and Vincent Goulet <vincent.goulet@act.ulaval.ca>
 */

#include <R.h>
#include <Rmath.h>
#include "locale.h"
#include "dpq.h"

double dpareto1(double x, double shape, double min, int give_log)
{
    if (!R_FINITE(shape) ||
	!R_FINITE(min) ||
	shape <= 0.0 || 
	min <= 0.0)
	error(_("invalid arguments"));

     if (!R_FINITE(x)  ||
	x < min) 
      return R_D_d0;
    
    return  give_log ?
	log(shape) + shape * log(min) - (shape + 1.0) * log(x):
      shape * R_pow(min, shape) / R_pow(x, shape + 1.0);
}

double ppareto1(double q, double shape, double min, int lower_tail, int log_p)
{
  double tmp;

    if (!R_FINITE(shape) ||
	!R_FINITE(min) ||
	shape <= 0.0 ||
	min <= 0.0)
	error(_("invalid arguments"));

    if (q <= min)
	return R_DT_0;

    tmp = log(min) - log(q);
    
    return (lower_tail ? R_D_exp(log(1 - exp(shape * (tmp)))):
	    R_D_exp(shape * (tmp)));
}

double qpareto1(double p, double shape, double min, int lower_tail, int log_p)
{

  double tmp;
  double tmp1;

    if (!R_FINITE(shape) ||
	!R_FINITE(min) ||
	shape <= 0.0 ||
	min <= 0.0)
	error(_("invalid arguments"));

     R_Q_P01_boundaries(p, min, R_PosInf);
     tmp = R_D_qIv(p);
     tmp1 = (1.0 / shape);

    return (lower_tail ? min * R_pow(1.0 - tmp, -tmp1) :
	    min * R_pow(tmp, -tmp1));
}


double rpareto1(double shape, double min)
{	
    if (!R_FINITE(shape) ||
	!R_FINITE(min) ||
	shape <= 0.0 ||
	min <= 0.0)
	error(_("invalid arguments"));

    return min / R_pow(unif_rand(), 1.0 / shape);
}