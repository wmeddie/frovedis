#include "python_client_headers.hpp"
#include "exrpc_data_storage.hpp"
#include "short_hand_dense_type.hpp"
#include "short_hand_sparse_type.hpp"

extern "C" {

  // --- frovedis crs matrx create/load/save/view/release ---
  std::vector<exrpc_ptr_t>
  get_each_II_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        int* vv, int* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<int,int,size_t> mloc(nrow, ncol);
    std::vector<int> val(nelem);     int* valp    = &val[0];
    std::vector<int> idx(nelem);     int* idxp    = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = ii[i]; 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT44>,mdist[i]).get();
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_IL_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        int* vv, long* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<int,size_t,size_t> mloc(nrow, ncol);
    std::vector<int> val(nelem);     int* valp    = &val[0];
    std::vector<size_t> idx(nelem);  size_t* idxp = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = static_cast<size_t>(ii[i]); 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side    
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT45>,mdist[i]).get();
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    } 
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_LI_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        long* vv, int* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<long,int,size_t> mloc(nrow, ncol);
    std::vector<long> val(nelem);    long* valp   = &val[0];
    std::vector<int> idx(nelem);     int* idxp    = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = ii[i]; 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side    
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT34>,mdist[i]).get();
      }
    }
    catch(std::exception& e) {
      set_status(true,e.what());
    }
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_LL_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        long* vv, long* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<long,size_t,size_t> mloc(nrow, ncol);
    std::vector<long> val(nelem);    long* valp   = &val[0];
    std::vector<size_t> idx(nelem);  size_t* idxp = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = static_cast<size_t>(ii[i]); 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side    
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT35>,mdist[i]).get();
      }
    }
    catch(std::exception& e) {
      set_status(true,e.what());
    }
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_FI_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        float* vv, int* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<float,int,size_t> mloc(nrow, ncol);
    std::vector<float> val(nelem);   float* valp  = &val[0];
    std::vector<int> idx(nelem);     int* idxp    = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = ii[i]; 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side    
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT24>,mdist[i]).get();
      }
    }
    catch(std::exception& e) {
      set_status(true,e.what());
    }
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_FL_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        float* vv, long* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<float,size_t,size_t> mloc(nrow, ncol);
    std::vector<float> val(nelem);   float* valp  = &val[0];
    std::vector<size_t> idx(nelem);  size_t* idxp = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = static_cast<size_t>(ii[i]); 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side    
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT25>,mdist[i]).get();
      }
    }
    catch(std::exception& e) {
      set_status(true,e.what());
    }
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_DI_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        double* vv, int* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<double,int,size_t> mloc(nrow, ncol);
    std::vector<double> val(nelem);  double* valp = &val[0];
    std::vector<int> idx(nelem);     int* idxp    = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = ii[i]; 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side    
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT14>,mdist[i]).get();
      }
    }
    catch(std::exception& e) {
      set_status(true,e.what());
    }
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_DL_crs_matrix_local_pointers(const char* host, int port,
                                        ulong nrow, ulong ncol,
                                        double* vv, long* ii, long* oo, 
                                        ulong nelem) {
    ASSERT_PTR(vv); ASSERT_PTR(ii); ASSERT_PTR(oo);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // constructing frovedis crs_matrix structure from python raw data 
    crs_matrix_local<double,size_t,size_t> mloc(nrow, ncol);
    std::vector<double> val(nelem);  double* valp = &val[0];
    std::vector<size_t> idx(nelem);  size_t* idxp = &idx[0];
    std::vector<size_t> off(nrow+1); size_t* offp = &off[0];
    for(size_t i=0; i<nelem;  ++i) valp[i] = vv[i]; 
    for(size_t i=0; i<nelem;  ++i) idxp[i] = static_cast<size_t>(ii[i]); 
    for(size_t i=0; i<nrow+1; ++i) offp[i] = static_cast<size_t>(oo[i]); 
    mloc.val.swap(val); mloc.idx.swap(idx); mloc.off.swap(off);
    // scattering scipy crs-data in (python) client side    
    auto mdist = get_scattered_crs_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<S_LMAT15>,mdist[i]).get();
      }
    }
    catch(std::exception& e) {
      set_status(true,e.what());
    }
    return eps;
  }

  PyObject* create_frovedis_crs_II_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          int* vv, int* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_II_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT4,DT4,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* create_frovedis_crs_IL_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          int* vv, long* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_IL_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT4,DT5,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* create_frovedis_crs_LI_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          long* vv, int* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_LI_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT3,DT4,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* create_frovedis_crs_LL_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          long* vv, long* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_LL_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT3,DT5,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* create_frovedis_crs_FI_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          float* vv, int* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_FI_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT2,DT4,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* create_frovedis_crs_FL_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          float* vv, long* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_FL_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT2,DT5,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  } 

  PyObject* create_frovedis_crs_DI_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          double* vv, int* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_DI_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT1,DT4,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* create_frovedis_crs_DL_matrix(const char* host, int port,
                                          ulong nrow, ulong ncol,
                                          double* vv, long* ii, long* oo,
                                          ulong nelem) {
    auto eps = get_each_DL_crs_matrix_local_pointers(host,port,nrow,ncol,
                                                     vv,ii,oo,nelem);
    // creating (frovedis) server side global matrix from dist local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      m = exrpc_async(fm_node,(create_crs_data<DT1,DT5,DT5>),eps,r,c).get();
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* load_frovedis_crs_matrix(const char* host, int port,
                                     const char* fname, bool bin,
                                     short dtype, short itype) {
    ASSERT_PTR(fname);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    std::string path(fname);
    dummy_matrix m;
    try {
      if(itype == INT) {
         switch(dtype) {
           case INT:    m = exrpc_async(fm_node,(load_crs_matrix<DT4,DT4,DT5>),path,bin).get(); break;
           case LONG:   REPORT_ERROR(USER_ERROR,"long type crs matrix data can't be loaded from file!\n");
           case FLOAT:  m = exrpc_async(fm_node,(load_crs_matrix<DT2,DT4,DT5>),path,bin).get(); break;
           case DOUBLE: m = exrpc_async(fm_node,(load_crs_matrix<DT1,DT4,DT5>),path,bin).get(); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
         }
      }
      else if(itype == LONG) {
         switch(dtype) {
           case INT:    m = exrpc_async(fm_node,(load_crs_matrix<DT4,DT5,DT5>),path,bin).get(); break;
           case LONG:   REPORT_ERROR(USER_ERROR,"long type crs matrix data can't be loaded from file!\n");
           case FLOAT:  m = exrpc_async(fm_node,(load_crs_matrix<DT2,DT5,DT5>),path,bin).get(); break;
           case DOUBLE: m = exrpc_async(fm_node,(load_crs_matrix<DT1,DT5,DT5>),path,bin).get(); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
         }
      }
      else REPORT_ERROR(USER_ERROR, "Unsupported itype for crs_matrix is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return to_py_dummy_matrix(m);
  }

  void save_frovedis_crs_matrix(const char* host, int port,
                                long dptr, const char* path,
                                bool bin, short dtype, short itype) {
    ASSERT_PTR(path);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    std::string fs_path(path);
    try {
      if(itype == INT){
         switch(dtype) {
           case INT:    exrpc_oneway(fm_node,save_matrix<S_MAT44>,f_dptr,fs_path,bin); break;
           case LONG:   exrpc_oneway(fm_node,save_matrix<S_MAT34>,f_dptr,fs_path,bin); break;
           case FLOAT:  exrpc_oneway(fm_node,save_matrix<S_MAT24>,f_dptr,fs_path,bin); break;
           case DOUBLE: exrpc_oneway(fm_node,save_matrix<S_MAT14>,f_dptr,fs_path,bin); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
         }
      }
      else if(itype == LONG){
         switch(dtype) {
           case INT:    exrpc_oneway(fm_node,save_matrix<S_MAT45>,f_dptr,fs_path,bin); break;
           case LONG:   exrpc_oneway(fm_node,save_matrix<S_MAT35>,f_dptr,fs_path,bin); break;
           case FLOAT:  exrpc_oneway(fm_node,save_matrix<S_MAT25>,f_dptr,fs_path,bin); break;
           case DOUBLE: exrpc_oneway(fm_node,save_matrix<S_MAT15>,f_dptr,fs_path,bin); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
         }
      }
      else REPORT_ERROR(USER_ERROR, "Unsupported itype for crs_matrix is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  void release_frovedis_crs_matrix(const char* host, int port,
                                   long dptr, short dtype, short itype) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      if(itype == INT){
         switch(dtype) {
           case INT:    exrpc_oneway(fm_node,release_data<S_MAT44>,f_dptr); break;
           case LONG:   exrpc_oneway(fm_node,release_data<S_MAT34>,f_dptr); break;
           case FLOAT:  exrpc_oneway(fm_node,release_data<S_MAT24>,f_dptr); break;
           case DOUBLE: exrpc_oneway(fm_node,release_data<S_MAT14>,f_dptr); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
         }
      }
      else if(itype == LONG){
         switch(dtype) {
           case INT:    exrpc_oneway(fm_node,release_data<S_MAT45>,f_dptr); break;
           case LONG:   exrpc_oneway(fm_node,release_data<S_MAT35>,f_dptr); break;
           case FLOAT:  exrpc_oneway(fm_node,release_data<S_MAT25>,f_dptr); break;
           case DOUBLE: exrpc_oneway(fm_node,release_data<S_MAT15>,f_dptr); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
        }
      }
      else REPORT_ERROR(USER_ERROR, "Unsupported itype for crs_matrix is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  void show_frovedis_crs_matrix(const char* host, int port,
                                long dptr, short dtype, short itype) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      if(itype == INT){
         switch(dtype) {
           case INT:    exrpc_oneway(fm_node,show_data<S_MAT44>,f_dptr); break;
           case LONG:   exrpc_oneway(fm_node,show_data<S_MAT34>,f_dptr); break;
           case FLOAT:  exrpc_oneway(fm_node,show_data<S_MAT24>,f_dptr); break;
           case DOUBLE: exrpc_oneway(fm_node,show_data<S_MAT14>,f_dptr); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
         }
       }
      else if(itype == LONG){
         switch(dtype) {
           case INT:    exrpc_oneway(fm_node,show_data<S_MAT45>,f_dptr); break;
           case LONG:   exrpc_oneway(fm_node,show_data<S_MAT35>,f_dptr); break;
           case FLOAT:  exrpc_oneway(fm_node,show_data<S_MAT25>,f_dptr); break;
           case DOUBLE: exrpc_oneway(fm_node,show_data<S_MAT15>,f_dptr); break;
           default:     REPORT_ERROR(USER_ERROR,"Unsupported dtype for crs_matrix is encountered!\n");
         }
       }
    else REPORT_ERROR(USER_ERROR, "Unsupported itype for crs_matrix is encountered!\n");
   }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  // --- Frovedis Dense matrices load/save/transpose/view/release ---
  std::vector<exrpc_ptr_t>
  get_each_double_rml_pointers_from_numpy_matrix(const char* host, int port,
                                                 ulong nrow, ulong ncol, 
                                                 double* vv) {
    ASSERT_PTR(vv); 
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // scattering numpy matrix in (python) client side
    rowmajor_matrix_local<double> mloc(nrow,ncol,vv);
    auto mdist = get_scattered_rowmajor_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) { 
        eps[i] = exrpc_async(nodes[i],load_local_data<R_LMAT1>,mdist[i]).get();
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_float_rml_pointers_from_numpy_matrix(const char* host, int port,
                                                ulong nrow, ulong ncol, 
                                                float* vv) {
    ASSERT_PTR(vv);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // scattering numpy matrix in (python) client side
    rowmajor_matrix_local<float> mloc(nrow,ncol,vv);
    auto mdist = get_scattered_rowmajor_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<R_LMAT2>,mdist[i]).get();
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return eps;
  }
  
  std::vector<exrpc_ptr_t>
  get_each_long_rml_pointers_from_numpy_matrix(const char* host, int port,
                                               ulong nrow, ulong ncol, 
                                               long* vv) {
    ASSERT_PTR(vv);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // scattering numpy matrix in (python) client side
    rowmajor_matrix_local<long> mloc(nrow,ncol,vv);
    auto mdist = get_scattered_rowmajor_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<R_LMAT3>,mdist[i]).get();
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    } 
    return eps;
  }

  std::vector<exrpc_ptr_t>
  get_each_int_rml_pointers_from_numpy_matrix(const char* host, int port,
                                              ulong nrow, ulong ncol, 
                                              int* vv) {
    ASSERT_PTR(vv);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    // getting frovedis worker information
    exrpc_node fm_node(host,port);
    auto nodes = get_worker_nodes(fm_node);
    auto wsize = nodes.size();
    // scattering numpy matrix in (python) client side
    rowmajor_matrix_local<int> mloc(nrow,ncol,vv);
    auto mdist = get_scattered_rowmajor_matrices(mloc,wsize);
    std::vector<exrpc_ptr_t> eps(wsize);
    try {
      for(size_t i=0; i<wsize; ++i) {
        eps[i] = exrpc_async(nodes[i],load_local_data<R_LMAT4>,mdist[i]).get();
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return eps;
  }

  // create from python (numpy) data
  PyObject* create_frovedis_double_dense_matrix(const char* host, int port,
                                                ulong nrow, ulong  ncol, 
                                                double* vv, char mtype) {
    auto eps = get_each_double_rml_pointers_from_numpy_matrix(host,port,nrow,ncol,vv);
    // creating (frovedis) server side dense matrix from local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      switch(mtype) {
        case 'R': m = exrpc_async(fm_node,create_rmm_data<DT1>,eps,r,c).get(); break;
        case 'C': m = exrpc_async(fm_node,create_cmm_data<DT1>,eps,r,c).get(); break;
        case 'B': m = exrpc_async(fm_node,create_bcm_data<DT1>,eps,r,c).get(); break;
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }
   
  PyObject* create_frovedis_float_dense_matrix(const char* host, int port,
                                               ulong nrow, ulong ncol,
                                               float* vv, char mtype) {
    auto eps = get_each_float_rml_pointers_from_numpy_matrix(host,port,nrow,ncol,vv);
    // creating (frovedis) server side dense matrix from local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      switch(mtype) {
        case 'R': m = exrpc_async(fm_node,create_rmm_data<DT2>,eps,r,c).get(); break;
        case 'C': m = exrpc_async(fm_node,create_cmm_data<DT2>,eps,r,c).get(); break;
        case 'B': m = exrpc_async(fm_node,create_bcm_data<DT2>,eps,r,c).get(); break;
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }  
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  PyObject* create_frovedis_long_dense_matrix(const char* host, int port,
                                              ulong nrow, ulong ncol,
                                              long* vv, char mtype) {
    auto eps = get_each_long_rml_pointers_from_numpy_matrix(host,port,nrow,ncol,vv);
    // creating (frovedis) server side dense matrix from local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      switch(mtype) {
        case 'R': m = exrpc_async(fm_node,create_rmm_data<DT3>,eps,r,c).get(); break;
        case 'C': m = exrpc_async(fm_node,create_cmm_data<DT3>,eps,r,c).get(); break;
        case 'B': REPORT_ERROR(USER_ERROR,"blockcyclic_matrix<long> is not supported!\n"); 
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    } 
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }
  
  PyObject* create_frovedis_int_dense_matrix(const char* host, int port,
                                             ulong nrow, ulong ncol,
                                             int* vv, char mtype) {
    auto eps = get_each_int_rml_pointers_from_numpy_matrix(host,port,nrow,ncol,vv);
    // creating (frovedis) server side dense matrix from local pointers
    exrpc_node fm_node(host,port);
    auto r = static_cast<size_t>(nrow);
    auto c = static_cast<size_t>(ncol);
    exrpc_ptr_t m = 0;
    try {
      switch(mtype) {
        case 'R': m = exrpc_async(fm_node,create_rmm_data<DT4>,eps,r,c).get(); break;
        case 'C': m = exrpc_async(fm_node,create_cmm_data<DT4>,eps,r,c).get(); break;
        case 'B': REPORT_ERROR(USER_ERROR,"blockcyclic_matrix<int> is not supported!\n"); 
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    dummy_matrix dmat(m,r,c);
    return to_py_dummy_matrix(dmat);
  }

  // load from file
  PyObject* load_frovedis_dense_matrix(const char* host, int port,
                                       const char* path, 
                                       bool bin, char mtype, short dtype) {
    ASSERT_PTR(path);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    std::string fs_path(path);
    dummy_matrix ret;
    try {
      if(mtype == 'R'){
         switch(dtype) {
           case DOUBLE: ret = exrpc_async(fm_node,load_rmm_matrix<DT1>,fs_path,bin).get(); break;
           case FLOAT:  ret = exrpc_async(fm_node,load_rmm_matrix<DT2>,fs_path,bin).get(); break;
           case LONG:   REPORT_ERROR(USER_ERROR,"rowmajor_matrix<long> can't be loaded from file!\n");
           case INT:    ret = exrpc_async(fm_node,load_rmm_matrix<DT4>,fs_path,bin).get(); break;
           default:     REPORT_ERROR(USER_ERROR,"Unknown rowmajor_matrix type is encountered!\n");
         }
      }
      else if(mtype == 'C'){
         switch(dtype) {
           case DOUBLE: ret = exrpc_async(fm_node,load_cmm_matrix<DT1>,fs_path,bin).get(); break;
           case FLOAT:  ret = exrpc_async(fm_node,load_cmm_matrix<DT2>,fs_path,bin).get(); break;
           case LONG:   REPORT_ERROR(USER_ERROR,"colmajor_matrix<long> can't be loaded from file!\n");
           case INT:    ret = exrpc_async(fm_node,load_cmm_matrix<DT4>,fs_path,bin).get(); break;
           default:     REPORT_ERROR(USER_ERROR,"Unknown colmajor_matrix type is encountered!\n");
         }
      }
      else if(mtype == 'B'){
         switch(dtype) {
           case DOUBLE: ret = exrpc_async(fm_node,load_bcm_matrix<DT1>,fs_path,bin).get(); break;
           case FLOAT:  ret = exrpc_async(fm_node,load_bcm_matrix<DT2>,fs_path,bin).get(); break;
           default:     REPORT_ERROR(USER_ERROR,"Unknown blockcyclic_matrix type is encountered!\n");
         }
      }
      else  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return to_py_dummy_matrix(ret);
  }

  void save_frovedis_dense_matrix(const char* host, int port,
                                  long dptr, const char* path, 
                                  bool bin, char mtype, short dtype) {
    ASSERT_PTR(path);
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    std::string fs_path(path);
    try {
      if(mtype == 'R') {
         switch(dtype) {
           case DOUBLE: exrpc_oneway(fm_node,save_matrix<R_MAT1>,f_dptr,fs_path,bin); break;
           case FLOAT:  exrpc_oneway(fm_node,save_matrix<R_MAT2>,f_dptr,fs_path,bin); break;
           case LONG:   exrpc_oneway(fm_node,save_matrix<R_MAT3>,f_dptr,fs_path,bin); break;
           case INT:    exrpc_oneway(fm_node,save_matrix<R_MAT4>,f_dptr,fs_path,bin); break;
           default:     REPORT_ERROR(USER_ERROR,"Unknown rowmajor_matrix type is encountered!\n");
         }
      }
      else if(mtype == 'C'){
         switch(dtype) {
           case DOUBLE: exrpc_oneway(fm_node,save_matrix<C_MAT1>,f_dptr,fs_path,bin); break;
           case FLOAT:  exrpc_oneway(fm_node,save_matrix<C_MAT2>,f_dptr,fs_path,bin); break;
           case LONG:   exrpc_oneway(fm_node,save_matrix<C_MAT3>,f_dptr,fs_path,bin); break;
           case INT:    exrpc_oneway(fm_node,save_matrix<C_MAT4>,f_dptr,fs_path,bin); break;
           default:     REPORT_ERROR(USER_ERROR,"Unknown colmajor_matrix type is encountered!\n");
         }
      }
      else if(mtype == 'B'){
         switch(dtype) {
           case DOUBLE:exrpc_oneway(fm_node,save_matrix<B_MAT1>,f_dptr,fs_path,bin); break;
           case FLOAT: exrpc_oneway(fm_node,save_matrix<B_MAT2>,f_dptr,fs_path,bin); break;
           default:    REPORT_ERROR(USER_ERROR,"Unknown blockcyclic_matrix type is encountered!\n");
        }
      }
      else REPORT_ERROR(USER_ERROR, "Unknown dense matrix kind is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  PyObject* copy_frovedis_dense_matrix(const char* host, int port, 
                                       long dptr, char mtype, short dtype) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    dummy_matrix ret;
    try {
      if(mtype == 'R') 
        REPORT_ERROR(USER_ERROR,"deepcopy a rowmajor_matrix is not supported!\n");
      else if(mtype == 'C') 
        REPORT_ERROR(USER_ERROR,"deepcopy a colmajor_matrix is not supported!\n");
      else if(mtype == 'B'){ 
         switch(dtype) {
           case DOUBLE: ret = exrpc_async(fm_node,copy_matrix<B_MAT1>,f_dptr).get(); break; 
           case FLOAT:  ret = exrpc_async(fm_node,copy_matrix<B_MAT2>,f_dptr).get(); break; 
           default:     REPORT_ERROR(USER_ERROR,"Unknown blockcyclic_matrix type is encountered!\n");
         }
       }
      else REPORT_ERROR(USER_ERROR, "Unknown dense matrix kind is encountered!\n");
    } 
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return to_py_dummy_matrix(ret);
  }
  
  PyObject* transpose_frovedis_dense_matrix(const char* host, int port, 
                                            long dptr, char mtype,short dtype) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    dummy_matrix ret;
    try {
      if(mtype == 'R'){
         switch(dtype) {
           case DOUBLE: ret = exrpc_async(fm_node,transpose_matrix<R_MAT1>,f_dptr).get(); break;
           case FLOAT:  ret = exrpc_async(fm_node,transpose_matrix<R_MAT2>,f_dptr).get(); break;
           case LONG:   ret = exrpc_async(fm_node,transpose_matrix<R_MAT3>,f_dptr).get(); break;
           case INT:    ret = exrpc_async(fm_node,transpose_matrix<R_MAT4>,f_dptr).get(); break;
           default:     REPORT_ERROR(USER_ERROR,"Unknown rowmajor_matrix type is encountered!\n");
         }
      }
      else if(mtype == 'C')
        REPORT_ERROR(USER_ERROR,"transpose on colmajor_matrix is not supported currently!\n");
      
      else if(mtype == 'B'){
         switch(dtype) {
           case DOUBLE: ret = exrpc_async(fm_node,transpose_matrix<B_MAT1>,f_dptr).get(); break;
           case FLOAT:  ret = exrpc_async(fm_node,transpose_matrix<B_MAT2>,f_dptr).get(); break;
           default:     REPORT_ERROR(USER_ERROR,"Unknown blockcyclic_matrix type is encountered!\n");
         }
      }
      else REPORT_ERROR(USER_ERROR, "Unknown dense matrix kind is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return to_py_dummy_matrix(ret);
  }
 
  // converts matrix to rowmajor_matrix
  PyObject* get_frovedis_rowmatrix(const char* host, int port, 
                                   long dptr, 
                                   ulong nrow, ulong ncol, 
                                   char mtype, short dtype) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    dummy_matrix ret;
    try {
      if(mtype == 'R') ret = dummy_matrix(f_dptr,nrow,ncol);
      else if(mtype == 'C') {
        switch(dtype) {
          case DOUBLE: ret = exrpc_async(fm_node,(to_rowmajor_matrix<DT1,C_MAT1>),f_dptr).get(); break;
          case FLOAT:  ret = exrpc_async(fm_node,(to_rowmajor_matrix<DT2,C_MAT2>),f_dptr).get(); break;
          case LONG:   ret = exrpc_async(fm_node,(to_rowmajor_matrix<DT3,C_MAT3>),f_dptr).get(); break;
          case INT:    ret = exrpc_async(fm_node,(to_rowmajor_matrix<DT4,C_MAT4>),f_dptr).get(); break;
          default:     REPORT_ERROR(USER_ERROR,"Unknown colmajor_matrix type is encountered!\n");
        }
      }
      else if(mtype == 'B'){
        switch(dtype) {
          case DOUBLE: ret = exrpc_async(fm_node,(to_rowmajor_matrix<DT1,B_MAT1>),f_dptr).get(); break;
          case FLOAT:  ret = exrpc_async(fm_node,(to_rowmajor_matrix<DT2,B_MAT2>),f_dptr).get(); break;
          default:     REPORT_ERROR(USER_ERROR,"Unknown blockcyclic_matrix type is encountered!\n");
        }
      }
      else REPORT_ERROR(USER_ERROR, "Unknown dense matrix kind is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
    return to_py_dummy_matrix(ret);
  }

  // --- Frovedis dense distributed matrix to Rowmajor Array Conversion ---
  // 1. convert input dense matrix to rowmajor_matrix at Frovedis server side
  // 2. get each rowmajor_matrix_local pointers
  // 3. gather local vectors from Frovedis worker nodes one-by-one
  // 4. fill the gathered data in client side buffer (ret)
  void get_double_rowmajor_array(const char* host, int port, 
                                 long dptr, char mtype, 
                                 double* ret, ulong sz) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      // (1) and (2)
      std::vector<exrpc_ptr_t> eps;
      switch(mtype) {
        case 'R': eps = exrpc_async(fm_node,(get_all_local_pointers<R_MAT1,R_LMAT1>),f_dptr).get(); break;
        case 'C': eps = exrpc_async(fm_node,(convert_and_get_all_rml_pointers<DT1,C_MAT1>),f_dptr).get(); break;
        case 'B': eps = exrpc_async(fm_node,(convert_and_get_all_rml_pointers<DT1,B_MAT1>),f_dptr).get(); break;
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
      // (3) 
      auto nodes = get_worker_nodes(fm_node);
      auto wsize = nodes.size();
      std::vector<std::vector<double>> evs(wsize);
      size_t k = 0, total = 0;
      for(size_t i=0; i<wsize; ++i) { 
        evs[i] = exrpc_async(nodes[i],(get_local_array<DT1,R_LMAT1>),eps[i]).get();
        total += evs[i].size();
      }
      // The gathered size and expected size from client side should match
      checkAssumption(total == sz);
      // (4)
      for(size_t i=0; i<wsize; ++i) {
        for(size_t j=0; j<evs[i].size(); ++j) ret[k++] = evs[i][j];
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    } 
  }

  void get_float_rowmajor_array(const char* host, int port,
                                long dptr, char mtype, 
                                float* ret, ulong sz) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      // (1) and (2)
      std::vector<exrpc_ptr_t> eps;
      switch(mtype) {
        case 'R': eps = exrpc_async(fm_node,(get_all_local_pointers<R_MAT2,R_LMAT2>),f_dptr).get(); break;
        case 'C': eps = exrpc_async(fm_node,(convert_and_get_all_rml_pointers<DT2,C_MAT2>),f_dptr).get(); break;
        case 'B': eps = exrpc_async(fm_node,(convert_and_get_all_rml_pointers<DT2,B_MAT2>),f_dptr).get(); break;
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
      // (3)
      auto nodes = get_worker_nodes(fm_node);
      auto wsize = nodes.size();
      std::vector<std::vector<float>> evs(wsize);
      size_t k = 0, total = 0;
      for(size_t i=0; i<wsize; ++i) {
        evs[i] = exrpc_async(nodes[i],(get_local_array<DT2,R_LMAT2>),eps[i]).get();
        total += evs[i].size();
      }
      // The gathered size and expected size from client side should match
      checkAssumption(total == sz);
      // (4)
      for(size_t i=0; i<wsize; ++i) {
        for(size_t j=0; j<evs[i].size(); ++j) ret[k++] = evs[i][j];
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  void get_long_rowmajor_array(const char* host, int port,
                               long dptr, char mtype, 
                               long* ret, ulong sz) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      // (1) and (2)
      std::vector<exrpc_ptr_t> eps;
      switch(mtype) {
        case 'R': eps = exrpc_async(fm_node,(get_all_local_pointers<R_MAT3,R_LMAT3>),f_dptr).get(); break;
        case 'C': eps = exrpc_async(fm_node,(convert_and_get_all_rml_pointers<DT3,C_MAT3>),f_dptr).get(); break;
        case 'B': REPORT_ERROR(USER_ERROR,"blockcylic matrix<long> is not supported!\n");break;
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
      // (3)
      auto nodes = get_worker_nodes(fm_node);
      auto wsize = nodes.size();
      std::vector<std::vector<long>> evs(wsize);
      size_t k = 0, total = 0;
      for(size_t i=0; i<wsize; ++i) {
        evs[i] = exrpc_async(nodes[i],(get_local_array<DT3,R_LMAT3>),eps[i]).get();
        total += evs[i].size();
      }
      // The gathered size and expected size from client side should match
      checkAssumption(total == sz);
      // (4)
      for(size_t i=0; i<wsize; ++i) {
        for(size_t j=0; j<evs[i].size(); ++j) ret[k++] = evs[i][j];
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  void get_int_rowmajor_array(const char* host, int port,
                              long dptr, char mtype, 
                              int* ret, ulong sz) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      // (1) and (2)
      std::vector<exrpc_ptr_t> eps;
      switch(mtype) {
        case 'R': eps = exrpc_async(fm_node,(get_all_local_pointers<R_MAT4,R_LMAT4>),f_dptr).get(); break;
        case 'C': eps = exrpc_async(fm_node,(convert_and_get_all_rml_pointers<DT4,C_MAT4>),f_dptr).get(); break;
        case 'B': REPORT_ERROR(USER_ERROR,"blockcylic_matrix<int> is not supported!\n");break;
        default:  REPORT_ERROR(USER_ERROR,"Unknown dense matrix kind is encountered!\n");
      }
      // (3)
      auto nodes = get_worker_nodes(fm_node);
      auto wsize = nodes.size();
      std::vector<std::vector<int>> evs(wsize);
      size_t k = 0, total = 0;
      for(size_t i=0; i<wsize; ++i) {
        evs[i] = exrpc_async(nodes[i],(get_local_array<DT4,R_LMAT4>),eps[i]).get();
        total += evs[i].size();
      }
      // The gathered size and expected size from client side should match
      checkAssumption(total == sz);
      // (4)
      for(size_t i=0; i<wsize; ++i) {
        for(size_t j=0; j<evs[i].size(); ++j) ret[k++] = evs[i][j];
      }
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  void show_frovedis_dense_matrix(const char* host, int port, 
                                  long dptr, char mtype, short dtype) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      if(mtype == 'R'){
        switch(dtype) {
          case DOUBLE: exrpc_oneway(fm_node,show_data<R_MAT1>,f_dptr); break;
          case FLOAT:  exrpc_oneway(fm_node,show_data<R_MAT2>,f_dptr); break;
          case LONG:   exrpc_oneway(fm_node,show_data<R_MAT3>,f_dptr); break;
          case INT:    exrpc_oneway(fm_node,show_data<R_MAT4>,f_dptr); break;
          default:     REPORT_ERROR(USER_ERROR,"Unknown rowmajor_matrix type is encountered!\n");
        }
      }
      else if(mtype == 'C'){
        switch(dtype) {
          case DOUBLE: exrpc_oneway(fm_node,show_data<C_MAT1>,f_dptr); break;
          case FLOAT:  exrpc_oneway(fm_node,show_data<C_MAT2>,f_dptr); break;
          case LONG:   exrpc_oneway(fm_node,show_data<C_MAT3>,f_dptr); break;
          case INT:    exrpc_oneway(fm_node,show_data<C_MAT4>,f_dptr); break;
          default:     REPORT_ERROR(USER_ERROR,"Unknown colmajor_matrix type is encountered!\n");
        }
      }
      else if(mtype == 'B'){
        switch(dtype) {
          case DOUBLE: exrpc_oneway(fm_node,show_data<B_MAT1>,f_dptr); break;
          case FLOAT:  exrpc_oneway(fm_node,show_data<B_MAT2>,f_dptr); break;
          default:     REPORT_ERROR(USER_ERROR,"Unknown blockcyclic_matrix type is encountered!\n");
        }
      }
      else REPORT_ERROR(USER_ERROR, "Unknown dense matrix kind is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

  void release_frovedis_dense_matrix(const char* host, int port, 
                                   long dptr, char mtype, short dtype) {
    if(!host) REPORT_ERROR(USER_ERROR,"Invalid hostname!!");
    exrpc_node fm_node(host,port);
    auto f_dptr = (exrpc_ptr_t) dptr;
    try {
      if(mtype == 'R'){
        switch(dtype) {
          case DOUBLE: exrpc_oneway(fm_node,release_data<R_MAT1>,f_dptr); break;
          case FLOAT:  exrpc_oneway(fm_node,release_data<R_MAT2>,f_dptr); break;
          case LONG:   exrpc_oneway(fm_node,release_data<R_MAT3>,f_dptr); break;
          case INT:    exrpc_oneway(fm_node,release_data<R_MAT4>,f_dptr); break;
          default:     REPORT_ERROR(USER_ERROR,"Unknown rowmajor_matrix type is encountered!\n");
        }
     }
     else if(mtype == 'C'){
       switch(dtype) {
         case DOUBLE: exrpc_oneway(fm_node,release_data<C_MAT1>,f_dptr); break;
         case FLOAT:  exrpc_oneway(fm_node,release_data<C_MAT2>,f_dptr); break;
         case LONG:   exrpc_oneway(fm_node,release_data<C_MAT3>,f_dptr); break;
         case INT:    exrpc_oneway(fm_node,release_data<C_MAT4>,f_dptr); break;
         default:     REPORT_ERROR(USER_ERROR,"Unknown colmajor_matrix type is encountered!\n");
       }
     }
     else if(mtype == 'B'){
       switch(dtype) {
         case DOUBLE: exrpc_oneway(fm_node,release_data<B_MAT1>,f_dptr); break;
         case FLOAT:  exrpc_oneway(fm_node,release_data<B_MAT2>,f_dptr); break;
         default:     REPORT_ERROR(USER_ERROR,"Unknown blockcyclic_matrix type is encountered!\n");
       }
     }
     else REPORT_ERROR(USER_ERROR, "Unknown dense matrix kind is encountered!\n");
    }
    catch (std::exception& e) {
      set_status(true, e.what());
    }
  }

}
