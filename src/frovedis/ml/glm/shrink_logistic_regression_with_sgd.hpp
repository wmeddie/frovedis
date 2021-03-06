#ifndef _SH_LR_SGD_HPP_
#define _SH_LR_SGD_HPP_

#include <iostream>
#include "shrink_sgd_parallelizer.hpp"

namespace frovedis {

class logistic_regression_with_sgd {
public:
  template <class T, class I, class O>
  static logistic_regression_model<T> train (
    crs_matrix<T,I,O>& data,
    dvector<T>& label,
    size_t numIteration=1000, 
    double alpha=0.01, 
    double miniBatchFraction=1.0, 
    double regParam=0.01, 
    RegType regTyp=ZERO, 
    bool isIntercept=false,
    double convergenceTol=0.001, 
#if defined(_SX) || defined(__ve__)
    MatType mType = HYBRID 
#else
    MatType mType = CRS
#endif 
  );

  template <class T, class I, class O>
  static logistic_regression_model<T> train (
    crs_matrix<T,I,O>&& data,
    dvector<T>& label,
    size_t numIteration=1000, 
    double alpha=0.01, 
    double miniBatchFraction=1.0, 
    double regParam=0.01, 
    RegType regTyp=ZERO, 
    bool isIntercept=false, 
    double convergenceTol=0.001, 
#if defined(_SX) || defined(__ve__)
    MatType mType = HYBRID 
#else
    MatType mType = CRS
#endif 
  );

  template <class T, class I, class O>
  static logistic_regression_model<T> train (
    crs_matrix<T,I,O>&& data,
    dvector<T>& label,
    logistic_regression_model<T>& lrm,
    size_t numIteration=1000, 
    double alpha=0.01, 
    double miniBatchFraction=1.0, 
    double regParam=0.01, 
    RegType regTyp=ZERO, 
    bool isIntercept=false, 
    double convergenceTol=0.001, 
#if defined(_SX) || defined(__ve__)
    MatType mType = HYBRID 
#else
    MatType mType = CRS
#endif 
  );

  template <class T, class I, class O>
  static logistic_regression_model<T> train (
    crs_matrix<T,I,O>& data,
    dvector<T>& label,
    logistic_regression_model<T>& lrm,
    size_t numIteration=1000, 
    double alpha=0.01, 
    double miniBatchFraction=1.0, 
    double regParam=0.01, 
    RegType regTyp=ZERO, 
    bool isIntercept=false,
    double convergenceTol=0.001, 
#if defined(_SX) || defined(__ve__)
    MatType mType = HYBRID, 
#else
    MatType mType = CRS,
#endif 
    bool inputMovable=false
  );
};

template <class T, class I, class O>
logistic_regression_model<T>
logistic_regression_with_sgd::train (crs_matrix<T,I,O>& data,
                                     dvector<T>& label,
                                     size_t numIteration,
                                     double alpha,
                                     double miniBatchFraction,
                                     double regParam,
                                     RegType regTyp,
                                     bool isIntercept,
                                     double convergenceTol,
                                     MatType mType) {
  size_t numFeatures = data.num_col;
  T intercept = isIntercept ? 1.0 : 0.0;
  logistic_regression_model<T> initModel(numFeatures,intercept);
  return train<T>(data,label,initModel,numIteration,alpha,miniBatchFraction,
                  regParam,regTyp,isIntercept,convergenceTol,mType,false);
}

template <class T, class I, class O>
logistic_regression_model<T>
logistic_regression_with_sgd::train (crs_matrix<T,I,O>&& data,
                                     dvector<T>& label,
                                     size_t numIteration,
                                     double alpha,
                                     double miniBatchFraction,
                                     double regParam,
                                     RegType regTyp,
                                     bool isIntercept,
                                     double convergenceTol,
                                     MatType mType) {
  size_t numFeatures = data.num_col;
  T intercept = isIntercept ? 1.0 : 0.0;
  logistic_regression_model<T> initModel(numFeatures,intercept);
  return train<T>(data,label,initModel,numIteration,alpha,miniBatchFraction,
                  regParam,regTyp,isIntercept,convergenceTol,mType,true);
}

template <class T, class I, class O>
logistic_regression_model<T>
logistic_regression_with_sgd::train (crs_matrix<T,I,O>&& data,
                                     dvector<T>& label,
                                     logistic_regression_model<T>& initModel,
                                     size_t numIteration,
                                     double alpha,
                                     double miniBatchFraction,
                                     double regParam,
                                     RegType regTyp,
                                     bool isIntercept,
                                     double convergenceTol,
                                     MatType mType) {
  return train<T>(data,label,initModel,numIteration,alpha,miniBatchFraction,
                  regParam,regTyp,isIntercept,convergenceTol,mType,true);
}

// --- main api with sparse data support ---
template <class T, class I, class O>
logistic_regression_model<T>
logistic_regression_with_sgd::train (crs_matrix<T,I,O>& data,
                                     dvector<T>& label,
                                     logistic_regression_model<T>& initModel,
                                     size_t numIteration,
                                     double alpha,
                                     double miniBatchFraction,
                                     double regParam,
                                     RegType regTyp,
                                     bool isIntercept,
                                     double convergenceTol,
                                     MatType mType,
                                     bool inputMovable) {
#ifdef _DEBUG_
  std::cout << "Initial model: \n";
  initModel.debug_print(); std::cout << "\n";
#endif

  sgd_parallelizer par(miniBatchFraction);
  logistic_regression_model<T> ret;

  if (regTyp == ZERO)
    ret = par.template parallelize<T,I,O,logistic_regression_model<T>,
                                   logistic_gradient<T>, zero_regularizer<T>> 
          (data,label,initModel,numIteration,alpha,regParam,
           isIntercept,convergenceTol,mType,inputMovable);
  else if (regTyp == L1)
    ret = par.template parallelize<T,I,O,logistic_regression_model<T>,
                                   logistic_gradient<T>, l1_regularizer<T>> 
          (data,label,initModel,numIteration,alpha,regParam,
           isIntercept,convergenceTol,mType,inputMovable);
  else if (regTyp == L2)
    ret = par.template parallelize<T,I,O,logistic_regression_model<T>,
                                   logistic_gradient<T>, l2_regularizer<T>> 
          (data,label,initModel,numIteration,alpha,regParam,
           isIntercept,convergenceTol,mType,inputMovable);
  return ret;
}

}
#endif
