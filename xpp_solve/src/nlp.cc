/**
 @file    nlp.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jul 1, 2016
 @brief   Brief description
 */

#include <xpp_solve/nlp.h>

#include <algorithm>
#include <Eigen/Sparse>

namespace xpp {

NLP::NLP ()
{
}

void
NLP::Init (const OptimizationVariablesPtr& opt_variables)
{
  opt_variables_ = opt_variables;
  x_prev.clear();
}

int
NLP::GetNumberOfOptimizationVariables () const
{
  return opt_variables_->GetRows();
}

VecBound
NLP::GetBoundsOnOptimizationVariables () const
{
  return opt_variables_->GetBounds();
}

VectorXd
NLP::GetStartingValues () const
{
  return opt_variables_->GetValues();
}

void
NLP::SetVariables (const Number* x)
{
  opt_variables_->SetValues(ConvertToEigen(x));
}

double
NLP::EvaluateCostFunction (const Number* x)
{
  VectorXd g = VectorXd::Zero(1);
  if (HasCostTerms()) {
    SetVariables(x);
    g = costs_->GetValues();
  }
  return g(0);
}

VectorXd
NLP::EvaluateCostFunctionGradient (const Number* x)
{
  Jacobian jac = Jacobian(1,GetNumberOfOptimizationVariables());
  if (HasCostTerms()) {
    SetVariables(x);
    jac = costs_->GetJacobian();
  }

  return jac.row(0).transpose();
}

VecBound
NLP::GetBoundsOnConstraints () const
{
  return constraints_->GetBounds();
}

int
NLP::GetNumberOfConstraints () const
{
  return GetBoundsOnConstraints().size();
}

VectorXd
NLP::EvaluateConstraints (const Number* x)
{
  SetVariables(x);
  return constraints_->GetValues();
}

bool
NLP::HasCostTerms () const
{
  return costs_->GetRows()>0;
}

void
NLP::EvalNonzerosOfJacobian (const Number* x, Number* values)
{
  SetVariables(x);
  Jacobian jac = GetJacobianOfConstraints();

  jac.makeCompressed(); // so the valuePtr() is dense and accurate
  std::copy(jac.valuePtr(), jac.valuePtr() + jac.nonZeros(), values);
}

Jacobian
NLP::GetJacobianOfConstraints () const
{
  return constraints_->GetJacobian();
}

void
NLP::AddCost (ConstraintPtrU cost)
{
  costs_ = std::move(cost);
}

void
NLP::AddConstraint (ConstraintPtrU constraint)
{
  constraints_ = std::move(constraint);
}

void
NLP::PrintCurrent() const
{
//  opt_variables_->Print();
  constraints_->Print();
};

void
NLP::SaveCurrent()
{
  x_prev.push_back(opt_variables_->GetValues());
}

NLP::OptimizationVariablesPtr
NLP::GetOptVariables ()
{
  return GetOptVariables(GetIterationCount()-1);
}

NLP::OptimizationVariablesPtr
NLP::GetOptVariables (int iter)
{
  opt_variables_->SetValues(x_prev.at(iter));
  return opt_variables_;
}

VectorXd
NLP::ConvertToEigen(const Number* x) const
{
  return Eigen::Map<const VectorXd>(x,GetNumberOfOptimizationVariables());
}

NLP::~NLP ()
{
}

} /* namespace xpp */
