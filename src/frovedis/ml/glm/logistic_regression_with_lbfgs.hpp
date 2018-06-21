#ifndef _LR_LBFGS_HPP_
#define _LR_LBFGS_HPP_

#include "lbfgs_parallelizer.hpp"

namespace frovedis {

class logistic_regression_with_lbfgs {
public:
  template <class T>
  static logistic_regression_model<T> train (
    crs_matrix<T>& data,
    dvector<T>& label,
    size_t numIteration=1000, 
    T alpha=0.01, 
    size_t hist_size=10, 
    T regParam=0.01, 
    RegType regTyp=ZERO, 
    bool isIntercept=false,
    T convergenceTol=0.001, 
#if defined(_SX) || defined(__ve__)
    MatType mType = HYBRID 
#else
    MatType mType = CRS
#endif 
  );

  template <class T>
  static logistic_regression_model<T> train (
    crs_matrix<T>&& data,
    dvector<T>& label,
    size_t numIteration=1000, 
    T alpha=0.01, 
    size_t hist_size=10, 
    T regParam=0.01, 
    RegType regTyp=ZERO, 
    bool isIntercept=false, 
    T convergenceTol=0.001, 
#if defined(_SX) || defined(__ve__)
    MatType mType = HYBRID 
#else
    MatType mType = CRS
#endif 
  );

  template <class T>
  static logistic_regression_model<T> train (
    crs_matrix<T>& data,
    dvector<T>& label,
    logistic_regression_model<T>& lrm,
    size_t numIteration=1000, 
    T alpha=0.01, 
    size_t hist_size=10, 
    T regParam=0.01, 
    RegType regTyp=ZERO, 
    bool isIntercept=false,
    T convergenceTol=0.001, 
#if defined(_SX) || defined(__ve__)
    MatType mType = HYBRID, 
#else
    MatType mType = CRS,
#endif 
    bool inputMovable=false
  );
};

template <class T>
logistic_regression_model<T>
logistic_regression_with_lbfgs::train (crs_matrix<T>& data,
                                       dvector<T>& label,
                                       size_t numIteration,
                                       T alpha,
                                       size_t hist_size,
                                       T regParam,
                                       RegType regTyp,
                                       bool isIntercept,
                                      T convergenceTol,
                                      MatType mType) {
  size_t numFeatures = data.num_col;
 
  if(!numFeatures)
    REPORT_ERROR(USER_ERROR,
                 "Incompatible Test Vector with only Single Column!!\n");
    
  T intercept = isIntercept ? 1.0 : 0.0;
  logistic_regression_model<T> initModel(numFeatures,intercept);
  return train<T>(data,label,initModel,numIteration,alpha,hist_size,
                  regParam,regTyp,isIntercept,convergenceTol,mType,false);
}

template <class T>
logistic_regression_model<T>
logistic_regression_with_lbfgs::train (crs_matrix<T>&& data,
                                       dvector<T>& label,
                                       size_t numIteration,
                                       T alpha,
                                       size_t hist_size,
                                       T regParam,
                                       RegType regTyp,
                                       bool isIntercept,
                                       T convergenceTol,
                                       MatType mType) {
  size_t numFeatures = data.num_col;
 
  if(!numFeatures)
    REPORT_ERROR(USER_ERROR,
                 "Incompatible Test Vector with only Single Column!!\n");
    
  T intercept = isIntercept ? 1.0 : 0.0;
  logistic_regression_model<T> initModel(numFeatures,intercept);
  return train<T>(data,label,initModel,numIteration,alpha,hist_size,
                  regParam,regTyp,isIntercept,convergenceTol,mType,true);
}

template <class T>
logistic_regression_model<T>
logistic_regression_with_lbfgs::train (crs_matrix<T>& data,
                                       dvector<T>& label,
                                       logistic_regression_model<T>& initModel,
                                       size_t numIteration,
                                       T alpha,
                                       size_t hist_size,
                                       T regParam,
                                       RegType regTyp,
                                       bool isIntercept,
                                       T convergenceTol,
                                       MatType mType,
                                       bool inputMovable) {
#ifdef _DEBUG_
  std::cout << "Initial model: \n";
  initModel.debug_print(); std::cout << "\n";
#endif

  lbfgs_parallelizer<T> par(hist_size);
  logistic_regression_model<T> ret;

  if (regTyp == ZERO)
    ret = par.template parallelize<logistic_regression_model<T>,
                                   logistic_gradient<T>, zero_regularizer<T>>
          (data,label,initModel,numIteration,alpha,regParam,
           isIntercept,convergenceTol,mType,inputMovable);
  else if (regTyp == L1)
    ret = par.template parallelize<logistic_regression_model<T>,
                                   logistic_gradient<T>, l1_regularizer<T>>
          (data,label,initModel,numIteration,alpha,regParam,
           isIntercept,convergenceTol,mType,inputMovable);
  else if (regTyp == L2)
    ret = par.template parallelize<logistic_regression_model<T>,
                                   logistic_gradient<T>, l2_regularizer<T>>
          (data,label,initModel,numIteration,alpha,regParam,
           isIntercept,convergenceTol,mType,inputMovable);
  return ret;
}

}
#endif
