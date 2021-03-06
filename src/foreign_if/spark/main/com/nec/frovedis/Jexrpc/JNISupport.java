package com.nec.frovedis.Jexrpc;

import com.nec.frovedis.Jmatrix.DummyMatrix;
import com.nec.frovedis.Jmatrix.DummyGetrfResult;
import com.nec.frovedis.Jmatrix.DummyGesvdResult;
import com.nec.frovedis.Jmatrix.DummyPCAResult;
import com.nec.frovedis.Jmllib.DummyGLM;
import com.nec.frovedis.Jmllib.IntDoublePair;

public class JNISupport {
 
  static {
    // Load native library libfrovedis_client.so at runtime
    System.loadLibrary("frovedis_client_spark");

    // to ensure server will be shut_down,
    // even if user program aborts abnormally
    Runtime.getRuntime().addShutdownHook(new Thread(new Runnable() {
        public void run() {
            FrovedisServer.shut_down();
        }
    }, "Shutdown-thread"));
  }

  public static native String checkServerException();
 
  // ---
  public static native MemPair loadFrovedisWorkerGLMData(Node t_node, 
                                                       long nrows, long ncols,
                                                       double lbl[],
                                                       int off[], 
                                                       int idx[], 
                                                       double val[]);
  public static native MemPair createFrovedisLabeledPoint(Node master_node,
                                                          MemPair eps[],
                                                          long nrows, long ncols);
  public static native void releaseFrovedisLabeledPoint(Node master_node, 
                                                        MemPair fdata, 
                                                        boolean isDense);
  public static native void showFrovedisLabeledPoint(Node master_node, 
                                                     MemPair fdata, 
                                                     boolean isDense);
  // ---
  public static native long loadFrovedisWorkerVectorStringData(Node t_node, 
                                                             String val[], 
                                                             int size);
  public static native long loadFrovedisWorkerData(Node t_node, 
                                                 long nrows, long ncols,
                                                 int off[], 
                                                 int idx[], 
                                                 double val[]);
  public static native DummyMatrix createFrovedisSparseMatrix(Node master_node,
                                                            long eps[],
                                                            short mtype);
  public static native long createFrovedisSparseData(Node master_node,
                                                   long eps[],
                                                   long nrows, long ncols);
  public static native void releaseFrovedisSparseData(Node master_node, 
                                                    long fdata); 
  public static native void showFrovedisSparseData(Node master_node, 
                                                 long fdata);
  // ---
  public static native long loadFrovedisWorkerRmajorData(Node t_node, 
                                                       long nrows, long ncols,
                                                       double val[]);
  public static native long loadFrovedisWorkerRmajorMatData(Node t_node, 
                                                            long nrows, long ncols,
                                                            double val[][]);
  public static native DummyMatrix getFrovedisRowmajorMatrix(Node master_node,
                                                           long fdata, 
                                                           short mtype);
  public static native long[] getAllLocalPointers(Node master_node, 
                                                  long dptr, short mtype);
  public static native double[] getLocalArray(Node t_node, 
                                              long l_dptr, short mtype);
  public static native long createFrovedisDenseData(Node master_node,
                                                  long eps[],
                                                  long nrows, long ncols,
                                                  short mtype);
  public static native void releaseFrovedisDenseData(Node master_node, 
                                                   long fdata, short mtype); 
  public static native void showFrovedisDenseData(Node master_node, 
                                                long fdata, short mtype);
  public static native void saveFrovedisDenseData(Node master_node, 
                                                long fdata, short mtype,
                                                String path, boolean isbinary);
  public static native DummyMatrix loadFrovedisDenseData(Node master_node, 
                                                       short mtype,
                                                       String path, 
                                                       boolean isbinary);
  // --- TODO ---
  public static native DummyMatrix transposeFrovedisDenseData(Node master_node,
                                                            long fdata, 
                                                            short mtype);
  public static native double[] getRowmajorArray(Node master_node, 
                                                 long fdata, short mtype);
  public static native double[] getColmajorArray(Node master_node, 
                                                 long fdata, short mtype);
  // ---
  public static native Node getMasterInfo(String cmd);
  public static native int getWorkerSize(Node master_node);
  public static native Node[] getWorkerInfo(Node master_node);
  public static native void finalizeFrovedisServer(Node master_node);
  public static native void cleanUPFrovedisServer(Node master_node);

  // -------- Logistic Regression --------
  public static native void callFrovedisLRSGD(Node master_node,
                                            MemPair fdata,
                                            int numIter, 
                                            double stepSize,
                                            double miniBatchFraction,
                                            double regParam, 
                                            int mid, boolean movable,
                                            boolean isDense);

  public static native void callFrovedisLRLBFGS(Node master_node,
                                              MemPair fdata,
                                              int numIter, 
                                              double stepSize,
                                              int histSize,
                                              double regParam,
                                              int mid, boolean movable,
                                              boolean isDense);

  // -------- Linear SVM Regression --------
  public static native void callFrovedisSVMSGD(Node master_node,
                                             MemPair fdata,
                                             int numIter,
                                             double stepSize,
                                             double miniBatchFraction,
                                             double regParam,
                                             int mid, boolean movable,
                                             boolean isDense);

  public static native void callFrovedisSVMLBFGS(Node master_node,
                                               MemPair fdata,
                                               int numIter,
                                               double stepSize,
                                               int histSize,
                                               double regParam,
                                               int mid, boolean movable,
                                               boolean isDense);

  // -------- Linear Regression --------
  public static native void callFrovedisLNRSGD(Node master_node,
                                             MemPair fdata,
                                             int numIter,
                                             double stepSize,
                                             double miniBatchFraction,
                                             int mid, 
                                             boolean movable,
                                             boolean isDense);

  public static native void callFrovedisLNRLBFGS(Node master_node,
                                               MemPair fdata,
                                               int numIter,
                                               double stepSize,
                                               int histSize,
                                               int mid, 
                                               boolean movable,
                                               boolean isDense);

  // -------- Lasso Regression --------
  public static native void callFrovedisLassoSGD(Node master_node,
                                               MemPair fdata,
                                               int numIter,
                                               double stepSize,
                                               double miniBatchFraction,
                                               double regParam,
                                               int mid, 
                                               boolean movable,
                                               boolean isDense);

  public static native void callFrovedisLassoLBFGS(Node master_node,
                                                 MemPair fdata,
                                                 int numIter,
                                                 double stepSize,
                                                 int histSize,
                                                 double regParam,
                                                 int mid, 
                                                 boolean movable,
                                                 boolean isDense);
  
  // -------- Ridge Regression --------
  public static native void callFrovedisRidgeSGD(Node master_node,
                                               MemPair fdata,
                                               int numIter,
                                               double stepSize,
                                               double miniBatchFraction,
                                               double regParam,
                                               int mid, 
                                               boolean movable,
                                               boolean isDense);

  public static native void callFrovedisRidgeLBFGS(Node master_node,
                                                 MemPair fdata,
                                                 int numIter,
                                                 double stepSize,
                                                 int histSize,
                                                 double regParam,
                                                 int mid, 
                                                 boolean movable,
                                                 boolean isDense);

  // -------- Matrix Factorization Using ALS --------
  public static native void callFrovedisMFUsingALS(Node master_node,
                                                 long fdata,
                                                 int rank,
                                                 int numIter,
                                                 double alpha,
                                                 double lambda,
                                                 long seed,
                                                 int mid, boolean movable);

  // -------- KMeans --------
  public static native void callFrovedisKMeans(Node master_node,
                                             long fdata,
                                             int k,
                                             int numIter,
                                             long seed,
                                             double epsilon,
                                             int mid, 
                                             boolean movable,
                                             boolean isDense);

  // -------- Compute PCA --------
  public static native DummyPCAResult computePCA(Node master_node,
                                                 long fdata,
                                                 int k,
                                                 boolean movable);
  // -------- Compute SVD --------
  public static native DummyGesvdResult computeSVD(Node master_node,
                                                   long fdata,
                                                   int k,
                                                   boolean movable);
  public static native DummyGesvdResult getSVDResultFromFiles(Node master_node,
                                                              short mtype,
                                                              String s_file,
                                                              String u_file,
                                                              String v_file,
                                                              boolean wantU,
                                                              boolean wantV,
                                                              boolean isbinary);
  // -------- Frovedis Model Operations --------
  public static native void showFrovedisModel(Node master_node, int mid, short mkind);
  public static native void releaseFrovedisModel(Node master_node, int mid, short mkind);
  public static native long[] broadcast2AllWorkers(Node master_node, int mid, short mkind);

  // [GLM] for multiple test vectors (prediction done in parallel in Frovedis worker nodes)
  public static native double[] doParallelGLMPredict(Node t_node, long mptr, short mkind,
                                                     long nrows, long ncols,
                                                     int off[], int idx[],
                                                     double val[]);
  // [GLM] for single test vector (prediction done in master node)
  public static native double doSingleGLMPredict(Node master_node, int mid, short mkind,
                                                 long nrows, long ncols,
                                                 int off[], int idx[],
                                                 double val[]);
  // [KMM] for multiple test vectors (prediction done in parallel in Frovedis worker nodes)
  public static native int[] doParallelKMMPredict(Node t_node, long mptr, short mkind,
                                                  long nrows, long ncols,
                                                  int off[], int idx[],
                                                  double val[]);
  // [KMM] for single test vector (prediction done in master node)
  public static native int doSingleKMMPredict(Node master_node, int mid, short mkind,
                                              long nrows, long ncols,
                                              int off[], int idx[],
                                              double val[]);
  // [MFM] for multiple test vectors (prediction done in parallel in Frovedis worker nodes)
  public static native double[] doParallelALSPredict(Node t_node, long mptr, short mkind,
                                                     int uids[], int pids[]);
  // [MFM] for single test vector (prediction done in master node)
  public static native double doSingleALSPredict(Node master_node, int mid, short mkind,
                                                 int uid, int pid);

  // [MFM] for recommending 'num' no. of products (with rating) for a given user
  public static native IntDoublePair[] recommendProducts(Node master_node, 
                                                         int mid, short mkind,
                                                         int user, int num);
  // [MFM] for recommending 'num' no. of users (with rating) for a given product
  public static native IntDoublePair[] recommendUsers(Node master_node, 
                                                      int mid, short mkind,
                                                      int product, int num);

  public static native void setFrovedisGLMThreshold(Node master_node, 
                                                  int mid, short mkind, double thr);

  public static native DummyGLM loadFrovedisGLM(Node master_node, 
                                              int mid, short mkind, String path);
  public static native int loadFrovedisMFM(Node master_node, 
                                         int mid, short mkind, String path);
  public static native int loadFrovedisKMM(Node master_node, 
                                         int mid, short mkind, String path);
  public static native void saveFrovedisModel(Node master_node, int mid, 
                                            short mkind, String path);

  public static native void loadFrovedisModel(Node master_node,
                                          int model_Id, 
                                          short mkind,  
                                          String path);

  public static native void callFrovedisFM(Node master_node,
                                         MemPair fdata, double init_stdev,
					 double learning_rate,
					 int iteration,
					 String optimizer,
					 boolean is_regression,
					 int batch_size,
					 boolean global_bias,
					 boolean one_way_interaction,
					 int num_factor,
					 double intercept,
					 double reg1way,
					 double reg_pairWise,
					 int model_id,
                                         boolean movable);

  public static native void callFrovedisNBM(Node master_node, MemPair fdata,
                                            double lambda, int model_id,
                                            String modelType, boolean movable,
                                            boolean isDense);

  public static native String loadFrovedisNBM(Node master_node,
                                              int model_id,
                                              short mkind,String path);


  public static native void callFrovedisDT(Node master_node,
					MemPair fdata,
					String Algo ,
					int maxDepth,
					int num_classes,
					int max_bins,
					String quantile_strategy,
					double min_info_gain,
                                        int min_instance_per_node,
                                        String impurityType,
                                 	int keys[],
					int values[], int size,
                                        int model_id,
                                        boolean movable,
                                        boolean isDense);  

  // [p]blas level 1 routines   
  public static native void swap(Node master_node, short mtype, 
                                 long vptr1, long vptr2);
  public static native void copy(Node master_node, short mtype,
                                 long vptr1, long vptr2);
  public static native void scal(Node master_node, short mtype,
                                 long vptr,  double alpha);
  public static native void axpy(Node master_node, short mtype,
                                 long vptr1, long vptr2, double alpha);
  public static native double dot(Node master_node, short mtype,
                                  long vptr1, long vptr2);
  public static native double nrm2(Node master_node, short mtype,
                                   long vptr);

  // [p]blas level 2 routines   
  public static native DummyMatrix gemv(Node master_node, short mtype,
                                        long mptr, long vptr,
                                        boolean isTrans, 
                                        double alpha, double beta);
  public static native DummyMatrix ger(Node master_node, short mtype,
                                       long vptr1, long vptr2,
                                       double alpha);

  // [p]blas level 3 routines   
  public static native DummyMatrix gemm(Node master_node, short mtype,
                                        long mptr1, long mptr2,
                                        boolean isTransM1, boolean isTransM2, 
                                        double alpha, double beta);
  public static native void geadd(Node master_node, short mtype,
                                  long mptr1, long mptr2,
                                  boolean isTrans, 
                                  double alpha, double beta);
  
  // [sca]lapack results
  public static native void saveAsFrovedisDiagMatrixLocal(Node master_node, 
                                                        long dptr, String path,
                                                        boolean isbinary);   //SVAL
  public static native double[] getDoubleArray(Node master_node, long dptr); //SVAL
  public static native void releaseDoubleArray(Node master_node, long dptr); //SVAL
  public static native void releaseIPIV(Node master_node, short mtype, long dptr);
 
  // [sca]lapack routines  
  public static native DummyGetrfResult getrf(Node master_node, short mtype,
                                              long mptr);
  public static native int getri(Node master_node, short mtype,
                                 long mptr, long ipiv_ptr);
  public static native int getrs(Node master_node, short mtype,
                                 long mptrA, long mptrB, 
                                 long ipiv_ptr, boolean isTrans);
  public static native int gesv(Node master_node, short mtype,
                                long mptrA, long mptrB);
  public static native int gels(Node master_node, short mtype,
                                long mptrA, long mptrB, 
                                boolean isTrans);
  public static native DummyGesvdResult gesvd(Node master_node, short mtype,
                                              long mptr, 
                                              boolean wantU, boolean wantV);
  // Dvector and DataFrame
  public static native long loadFrovedisWorkerIntVector(Node t_node, long size,
                                                      int data[]);
  public static native long loadFrovedisWorkerLongVector(Node t_node, long size,
                                                       long data[]);
  public static native long loadFrovedisWorkerFloatVector(Node t_node, long size,
                                                        float data[]);
  public static native long loadFrovedisWorkerDoubleVector(Node t_node, long size,
                                                         double data[]);
  public static native long loadFrovedisWorkerStringVector(Node t_node, long size,
                                                         String data[]);
  public static native long loadFrovedisWorkerBoolVector(Node t_node, long size,
                                                       boolean data[]);
  public static native long createFrovedisDvector(Node master_node, long proxies[],
                                                long sizes[], long size, short dtype);

  // frovedis dataframe column extraction
  public static native long[] getLocalIntColumnPointers(Node master_node,
                                                       long proxy, String cname);
  public static native int[] getLocalIntVector(Node wnode, long dptr);

  public static native long[] getLocalLongColumnPointers(Node master_node,
                                                        long proxy, String cname);
  public static native long[] getLocalLongVector(Node wnode, long dptr);

  public static native long[] getLocalFloatColumnPointers(Node master_node,
                                                         long proxy, String cname);
  public static native float[] getLocalFloatVector(Node wnode, long dptr);

  public static native long[] getLocalDoubleColumnPointers(Node master_node,
                                                          long proxy, String cname);
  public static native double[] getLocalDoubleVector(Node wnode, long dptr);

  public static native long[] getLocalStringColumnPointers(Node master_node,
                                                           long proxy, String cname);
  public static native String[] getLocalStringVector(Node wnode, long dptr);

  public static native long createFrovedisDataframe(Node master_node,
                                                  short dtypes[],
                                                  String cols_names[],
                                                  long dvecs[], long size);
  public static native void releaseFrovedisDataframe(Node master_node, long data);

  public static native void showFrovedisDataframe(Node master_node, long data);

  public static native long getDFOperator(Node master_node, String op1, String op2,
                                          short tid, short optid, boolean isImmed);
  public static native long getDFAndOperator(Node master_node,
                                             long proxy1, long proxy2);
  public static native long getDFOrOperator(Node master_node,
                                            long proxy1, long proxy2);
  public static native void releaseFrovedisDFOperator(Node master_node, long proxy);
  public static native long filterFrovedisDataframe(Node master_node,
                                                  long data_proxy, long opt_proxy);
  public static native long joinFrovedisDataframes(Node master_node,
                                                 long dproxy1, long dproxy2,
                                                 long opt_proxy, String type,
                                                 String algo);
  public static native long sortFrovedisDataframe(Node master_node,
                                                long dproxy, String targets[],
                                                long size, boolean isDesc);
  public static native long selectFrovedisDataframe(Node master_node,
                                                  long dproxy,
                                                  String targets[], long size);
  public static native long groupFrovedisDataframe(Node master_node,
                                                 long dproxy, String targets[],
                                                 long size);
  public static native long renameFrovedisDataframe(Node master_node,
                                                    long dproxy,
                                                    String[] name, String[] new_name,
                                                    int size);
  public static native long getFrovedisDFSize(Node master_node, long dproxy);
  public static native String[] getFrovedisDFCounts(Node master_node,
                                                    long dproxy, String[] cname,
                                                    int size);
  public static native String[] getFrovedisDFMeans(Node master_node,
                                                   long dproxy, String[] cname,
                                                   int size);
  public static native String[] getFrovedisDFTotals(Node master_node,
                                                    long dproxy, String[] cname,
                                                    short[] tids,
                                                    int size);
  public static native String[] getFrovedisDFMins(Node master_node,
                                                  long dproxy, String[] cname,
                                                  short[] tids,
                                                  int size);
  public static native String[] getFrovedisDFMaxs(Node master_node,
                                                  long dproxy, String[] cname,
                                                  short[] tids,
                                                  int size);
  public static native String[] getFrovedisDFStds(Node master_node,
                                                  long dproxy, String[] cname,
                                                  short[] tids,
                                                  int size);
  public static native DummyMatrix DFToRowmajorMatrix(Node master_node, long dproxy, 
                                                      String[] cname, int size); 
  public static native DummyMatrix DFToColmajorMatrix(Node master_node, long dproxy, 
                                                      String[] cname, int size); 
  public static native DummyMatrix DFToCRSMatrix(Node master_node, long dproxy, 
                                                 String[] cname, int size1,
                                                 String[] cat_name, int size2,
                                                 long info_id); 
  public static native DummyMatrix DFToCRSMatrixUsingInfo(Node master_node, long dproxy, 
                                                          long info_id); 

  // --- dftable_to_sparse_info ---
  public static native void loadSparseConversionInfo(Node master_node,long info_id,String dirname);
  public static native void saveSparseConversionInfo(Node master_node,long info_id,String dirname);
  public static native void releaseSparseConversionInfo(Node master_node,long info_id);
}
