/**
 @file    total_acceleration_equation.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 30, 2016
 @brief   Brief description
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_SRC_TOTAL_ACCELERATION_EQUATION_H_
#define USER_TASK_DEPENDS_XPP_OPT_SRC_TOTAL_ACCELERATION_EQUATION_H_

#include <xpp/zmp/i_linear_equation_builder.h>
#include "com_spline4.h"

namespace xpp {
namespace zmp {

class TotalAccelerationEquation : public ILinearEquationBuilder {
public:
  TotalAccelerationEquation (const ComSpline4&);
  virtual ~TotalAccelerationEquation () {}

  MatVec BuildLinearEquation() const override;

private:
  const ComSpline4 splines_;
};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_SRC_TOTAL_ACCELERATION_EQUATION_H_ */
