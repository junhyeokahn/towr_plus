/**
 @file    initial_acceleration_equation.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 26, 2016
 @brief   Brief description
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_INITIAL_ACCELERATION_EQUATION_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_INITIAL_ACCELERATION_EQUATION_H_

#include <xpp/zmp/i_linear_equation_builder.h>
#include "com_spline4.h"

namespace xpp {
namespace zmp {

class InitialAccelerationEquation : public ILinearEquationBuilder {
public:
  typedef Eigen::Vector2d Vector2d;

  InitialAccelerationEquation (const Vector2d& initial_acceleration_xy,
                               const ComSpline4&);
  virtual ~InitialAccelerationEquation () {}

  MatVec BuildLinearEquation() const override;

private:
  Vector2d initial_acceleration_xy_;
  const ComSpline4 splines_;
};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_INITIAL_ACCELERATION_EQUATION_H_ */
