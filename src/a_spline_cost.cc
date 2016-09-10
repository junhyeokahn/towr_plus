/**
 @file    a_spline_cost.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 30, 2016
 @brief   Definition of the ASplineCost, QuadraticSplineCost, SquaredSplineCost
 */

#include <xpp/zmp/a_spline_cost.h>
#include <xpp/zmp/optimization_variables.h>

namespace xpp {
namespace zmp {

ASplineCost::ASplineCost ()
{
}

void
ASplineCost::Init (const MatVec& mat_vec)
{
  matrix_vector_ = mat_vec;
}

void
ASplineCost::UpdateVariables (const OptimizationVariables* opt_var)
{
  spline_coeff_ = opt_var->GetVariables(VariableNames::kSplineCoeff);
}

double
QuadraticSplineCost::EvaluateCost () const
{
  double cost = 0.0;

  cost += spline_coeff_.transpose() * matrix_vector_.M * spline_coeff_;
  cost += matrix_vector_.v.transpose() * spline_coeff_;

  return cost;
}

QuadraticSplineCost::VectorXd
QuadraticSplineCost::EvaluateGradientWrt(std::string var_set)
{
  VectorXd grad;

  if (var_set == VariableNames::kSplineCoeff)
    grad =  2.0 * matrix_vector_.M * spline_coeff_;

  return grad;
}

double
SquaredSplineCost::EvaluateCost () const
{
  return (matrix_vector_.M*spline_coeff_ + matrix_vector_.v).norm();
}

} /* namespace zmp */
} /* namespace xpp */