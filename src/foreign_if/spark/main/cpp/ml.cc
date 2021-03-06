#include "exrpc_ml.hpp"
#include "short_hand_dense_type.hpp"
#include "short_hand_sparse_type.hpp"
#include "spark_client_headers.hpp"

using namespace frovedis;

extern "C" {

// (1) --- Logistic Regression ---
// initiates the training call at Frovedis master node for LogisticRegressionWithSGD
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisLRSGD
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata, 
   jint numIter, jdouble stepSize, jdouble mbf, 
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {
  
  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool isDense = (bool) dense;
  int rtype = 0; // ZERO (default)
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node (" 
            << fm_node.hostname << "," << fm_node.rpcport 
            << ") to train frovedis LR_SGD.\n";
#endif
  try{
    if(isDense) 
      exrpc_oneway(fm_node,(frovedis_lr_sgd<DT1,D_MAT1>),f_dptr,numIter,stepSize,mbf,rtype,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_lr_sgd<DT1,S_MAT1>),f_dptr,numIter,stepSize,mbf,rtype,regParam,icpt,tol,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// initiates the training call at Frovedis master node for LogisticRegressionWithLBFGS
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisLRLBFGS
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata,
   jint numIter, jdouble stepSize, jint histSize,
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool isDense = (bool) dense;
  int rtype = 0; // ZERO (default)
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node ("
            << fm_node.hostname << "," << fm_node.rpcport
            << ") to train frovedis LR_LBFGS.\n";
#endif
  try {
    if (isDense)
      exrpc_oneway(fm_node,(frovedis_lr_lbfgs<DT1,D_MAT1>),f_dptr,numIter,stepSize,histSize,rtype,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_lr_lbfgs<DT1,S_MAT1>),f_dptr,numIter,stepSize,histSize,rtype,regParam,icpt,tol,vb,mid,mvbl);
  } 
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (2) --- Linear SVM ---
// initiates the training call at Frovedis master node for SVMWithSGD
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisSVMSGD
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata, 
   jint numIter, jdouble stepSize, jdouble mbf, 
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {
  
  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  int rtype = 0; // ZERO (default)
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node (" 
            << fm_node.hostname << "," << fm_node.rpcport 
            << ") to train frovedis SVM_SGD.\n";
#endif
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_svm_sgd<DT1,D_MAT1>),f_dptr,numIter,stepSize,mbf,rtype,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_svm_sgd<DT1,S_MAT1>),f_dptr,numIter,stepSize,mbf,rtype,regParam,icpt,tol,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// initiates the training call at Frovedis master node for SVMWithLBFGS
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisSVMLBFGS
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata,
   jint numIter, jdouble stepSize, jint histSize,
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  int rtype = 0; // ZERO (default)
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node ("
            << fm_node.hostname << "," << fm_node.rpcport
            << ") to train frovedis SVM_LBFGS.\n";
#endif
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_svm_lbfgs<DT1,D_MAT1>),f_dptr,numIter,stepSize,histSize,rtype,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_svm_lbfgs<DT1,S_MAT1>),f_dptr,numIter,stepSize,histSize,rtype,regParam,icpt,tol,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (3) --- Linear Regression ---
// initiates the training call at Frovedis master node for LinearRegressionWithSGD
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisLNRSGD
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata, 
   jint numIter, jdouble stepSize, jdouble mbf, 
   jint mid, jboolean movable, jboolean dense) {
  
  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool icpt = false; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node (" 
            << fm_node.hostname << "," << fm_node.rpcport 
            << ") to train frovedis LNR_SGD.\n";
#endif
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_lnr_sgd<DT1,D_MAT1>),f_dptr,numIter,stepSize,mbf,icpt,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_lnr_sgd<DT1,S_MAT1>),f_dptr,numIter,stepSize,mbf,icpt,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// initiates the training call at Frovedis master node for LinearRegressionWithLBFGS
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisLNRLBFGS
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata,
   jint numIter, jdouble stepSize, jint histSize,
   jint mid, jboolean movable, jboolean dense) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool icpt = false; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node ("
            << fm_node.hostname << "," << fm_node.rpcport
            << ") to train frovedis LNR_LBFGS.\n";
#endif 
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_lnr_lbfgs<DT1,D_MAT1>),f_dptr,numIter,stepSize,histSize,icpt,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_lnr_lbfgs<DT1,S_MAT1>),f_dptr,numIter,stepSize,histSize,icpt,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (4) --- Lasso Regression ---
// initiates the training call at Frovedis master node for LassoWithSGD
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisLassoSGD
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata, 
   jint numIter, jdouble stepSize, jdouble mbf, 
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {
  
  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node (" 
            << fm_node.hostname << "," << fm_node.rpcport 
            << ") to train frovedis Lasso_SGD.\n";
#endif
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_lasso_sgd<DT1,D_MAT1>),f_dptr,numIter,stepSize,mbf,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_lasso_sgd<DT1,S_MAT1>),f_dptr,numIter,stepSize,mbf,regParam,icpt,tol,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// initiates the training call at Frovedis master node for LassoWithLBFGS
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisLassoLBFGS
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata,
   jint numIter, jdouble stepSize, jint histSize,
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node ("
            << fm_node.hostname << "," << fm_node.rpcport
            << ") to train frovedis Lasso_LBFGS.\n";
#endif
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_lasso_lbfgs<DT1,D_MAT1>),f_dptr,numIter,stepSize,histSize,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_lasso_lbfgs<DT1,S_MAT1>),f_dptr,numIter,stepSize,histSize,regParam,icpt,tol,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (5) --- Ridge Regression ---
// initiates the training call at Frovedis master node for RidgeRegressionWithSGD
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisRidgeSGD
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata, 
   jint numIter, jdouble stepSize, jdouble mbf, 
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {
  
  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node (" 
            << fm_node.hostname << "," << fm_node.rpcport 
            << ") to train frovedis Ridge_SGD.\n";
#endif
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_ridge_sgd<DT1,D_MAT1>),f_dptr,numIter,stepSize,mbf,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_ridge_sgd<DT1,S_MAT1>),f_dptr,numIter,stepSize,mbf,regParam,icpt,tol,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// initiates the training call at Frovedis master node for RidgeRegressionWithLBFGS
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisRidgeLBFGS
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata,
   jint numIter, jdouble stepSize, jint histSize,
   jdouble regParam, jint mid, jboolean movable, jboolean dense) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool icpt = false; // default
  double tol = 0.001; // default
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node ("
            << fm_node.hostname << "," << fm_node.rpcport
            << ") to train frovedis Ridge_LBFGS.\n";
#endif
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_ridge_lbfgs<DT1,D_MAT1>),f_dptr,numIter,stepSize,histSize,regParam,icpt,tol,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_ridge_lbfgs<DT1,S_MAT1>),f_dptr,numIter,stepSize,histSize,regParam,icpt,tol,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (6) --- Matrix Factorization using ALS ---
// initiates the training call at Frovedis master node for MatrixFactorizationUsingALS 
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisMFUsingALS
  (JNIEnv *env, jclass thisCls, jobject master_node, jlong fdata,
   jint rank, jint numIter, jdouble alpha, jdouble regParam,
   jlong seed, jint mid, jboolean movable) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = (exrpc_ptr_t) fdata;
  bool mvbl = (bool) movable;
  int vb = 0; // no log (default)
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node ("
            << fm_node.hostname << "," << fm_node.rpcport
            << ") to train frovedis MatrixFactorization using ALS.\n";
#endif
  try {
    exrpc_oneway(fm_node,(frovedis_mf_als<DT1,S_MAT1>),f_dptr,rank,numIter,alpha,regParam,seed,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (7) --- Kmeans ---
// initiates the training call at Frovedis master node for KMeans 
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisKMeans
  (JNIEnv *env, jclass thisCls, jobject master_node, jlong fdata,
   jint k, jint numIter, jlong seed, jdouble epsilon,
   jint mid, jboolean movable, jboolean dense) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = (exrpc_ptr_t) fdata;
  bool mvbl = (bool) movable;
  int vb = 0; // no log (default)
  bool isDense = (bool) dense;
#ifdef _EXRPC_DEBUG_
  std::cout << "Connecting to master node ("
            << fm_node.hostname << "," << fm_node.rpcport
            << ") to train frovedis KMeans.\n";
#endif
  try {
    if(isDense) // kmeans accepts rowmajor matrix as for dense data
      exrpc_oneway(fm_node,(frovedis_kmeans<DT1,R_MAT1>),f_dptr,k,numIter,seed,epsilon,vb,mid,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_kmeans<DT1,S_MAT1>),f_dptr,k,numIter,seed,epsilon,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (8) --- Factorization Machine ---
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisFM
  (JNIEnv *env, jclass thisClass, jobject master_node, jobject fdata, 
   jdouble init_stdev, jdouble learn_rate, jint iteration, jstring optimizer, 
   jboolean is_regression, jint batch_size, 
   jboolean dim_1, jboolean dim_2, jint dim3, 
   jdouble reg1, jdouble reg2, jdouble reg3, 
   jint mid, jboolean movable) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  auto opt = to_cstring(env,optimizer);
  bool regr = (bool) is_regression;
  bool dim1 = (bool) dim_1;
  bool dim2 = (bool) dim_2;
  bool mvbl = (bool) movable;
  int vb = 0; // no log (default)

  fm::fm_config<DT1> conf(dim1, dim2, dim3, init_stdev, iteration, learn_rate,
                             reg1, reg2, reg3, regr, batch_size);
  try {
    exrpc_oneway(fm_node,(frovedis_fm<DT1,S_MAT1>),f_dptr,opt,conf,vb,mid,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (9) --- Decision Tree ---
std::unordered_map<size_t,size_t> 
get_kv_pair(JNIEnv *env, jintArray jkeys, jintArray jvals, size_t size) {
  auto keys = to_int_vector(env, jkeys, size);
  auto vals = to_int_vector(env, jvals, size);
  std::unordered_map<size_t,size_t> ret;
  for (size_t i=0; i<keys.size(); ++i) {
    auto k = static_cast<size_t> (keys[i]);
    auto v = static_cast<size_t> (vals[i]);
    ret[k] = v;
  }
  return ret;
}

JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisDT
  (JNIEnv *env, jclass thisClass, jobject master_node, jobject fdata, 
   jstring algoname, jint max_depth, jint num_classes, jint max_bins, 
   jstring quantile_strategy, jdouble min_info_gain, jint min_instance, 
   jstring impurityType, 
   jintArray keys, jintArray values, jint size,
   jint mid, jboolean movable, jboolean dense) { 

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  auto cat_ftr_info = get_kv_pair(env,keys,values,size);
  bool mvbl = (bool) movable;
  bool isDense = (bool) dense;
  int vb = 0; // no log (default)

  auto al = to_cstring(env,algoname);
  tree::algorithm algo = tree::algorithm::Classification; // initializing
  if (al == "Classification")  algo = tree::algorithm::Classification;
  else if (al == "Regression") algo = tree::algorithm::Regression;
  else REPORT_ERROR(USER_ERROR, "Unsupported quantile strategy is provided!\n");

  auto qn = to_cstring(env,quantile_strategy);
  tree::quantile_strategy qns = tree::quantile_strategy::ApproxHist; // initializing
  if (qn == "ApproxHist") qns = tree::quantile_strategy::ApproxHist;
  else REPORT_ERROR(USER_ERROR, "Unsupported quantile strategy is provided!\n");

  auto impt = to_cstring(env,impurityType);
  tree::impurity_type impurity = tree::impurity_type::Default; // initializing
  if (impt == "default")       impurity = tree::impurity_type::Default;
  else if (impt == "gini")     impurity = tree::impurity_type::Gini;
  else if (impt == "entropy")  impurity = tree::impurity_type::Entropy;
  else if (impt == "variance") impurity = tree::impurity_type::Variance;
  else REPORT_ERROR(USER_ERROR, "Unsupported impurity type is provided!\n");

  tree::strategy<DT1> str(
      algo, impurity, 
      max_depth, num_classes, max_bins,
      qns, tree::categorize_strategy::Single,
      std::move(cat_ftr_info),
      min_instance, min_info_gain);

  try{
    if(isDense) 
      exrpc_oneway(fm_node,(frovedis_dt<DT1,D_MAT1>),f_dptr,str,vb,mid,mvbl);
    else
      REPORT_ERROR(USER_ERROR, "currently Frovedis doesn't support decision tree train with sparse data!\n");
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

// (11) --- Naive Bayes ---
// calling frovedis server side Naive Bayes trainer
JNIEXPORT void JNICALL Java_com_nec_frovedis_Jexrpc_JNISupport_callFrovedisNBM
  (JNIEnv *env, jclass thisCls, jobject master_node, jobject fdata,
   jdouble lambda, jint model_id, jstring modelType, 
   jboolean movable, jboolean dense) {

  auto fm_node = java_node_to_frovedis_node(env, master_node);
  auto f_dptr = java_mempair_to_frovedis_mempair(env, fdata);
  bool mvbl = (bool) movable;
  bool isDense = (bool) dense;
  int vb = 0; // no log (default)
  auto mtype = to_cstring(env,modelType);
  try {
    if(isDense)
      exrpc_oneway(fm_node,(frovedis_nb<DT1,D_MAT1,D_LMAT1>),f_dptr,mtype,lambda,vb,model_id,mvbl);
    else
      exrpc_oneway(fm_node,(frovedis_nb<DT1,S_MAT1,S_LMAT1>),f_dptr,mtype,lambda,vb,model_id,mvbl);
  }
  catch(std::exception& e) { set_status(true,e.what()); }
}

}
