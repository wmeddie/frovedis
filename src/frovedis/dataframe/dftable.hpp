#ifndef DFTABLE_HPP
#define DFTABLE_HPP

#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "dfcolumn.hpp"
#include "dfaggregator.hpp"
#include "../matrix/colmajor_matrix.hpp"
#include "../matrix/ell_matrix.hpp"

namespace frovedis {

class dftable;
class filtered_dftable; // defined in dfoperator.hpp
class sorted_dftable;
class hash_joined_dftable;
class bcast_joined_dftable;
class star_joined_dftable;
class grouped_dftable;
class dfoperator;

struct dftable_to_sparse_info;

// same as dftable w/o its specific member functions
class dftable_base {
public:
  virtual ~dftable_base(){}
  virtual size_t num_row() {return row_size;} 
  virtual size_t num_col() const {return col.size();}
  virtual std::vector<std::string> columns() const;
  virtual std::vector<std::pair<std::string, std::string>> dtypes();
  virtual dftable select(const std::vector<std::string>& cols);
  virtual dftable materialize();
  virtual filtered_dftable filter(const std::shared_ptr<dfoperator>& op);
  virtual sorted_dftable sort(const std::string& name);
  virtual sorted_dftable sort_desc(const std::string& name);
  virtual hash_joined_dftable
  hash_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual hash_joined_dftable
  outer_hash_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  outer_bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  // TODO: support outer_star_join
  virtual star_joined_dftable
  star_join(const std::vector<dftable_base*>& dftables, 
            const std::vector<std::shared_ptr<dfoperator>>& op);
  virtual grouped_dftable group_by(const std::vector<std::string>& cols);
  size_t count(const std::string& name);
  template <class T> T sum(const std::string& name);
  double avg(const std::string& name);
  template <class T> T max(const std::string& name);
  template <class T> T min(const std::string& name);
  template <class T> dvector<T> as_dvector(const std::string name);
  dftable head(size_t limit);
  dftable tail(size_t limit);
  void show(size_t limit);
  void show(); // == like Spark, show(20) + "..."
  void show_all(bool with_index = false);
  // like Pandas print, head(30), "...", and tail(30) is printed together with row_id
  void print(); 
  void save(const std::string& dir);
  std::vector<std::pair<std::string, std::string>>
    savetext(const std::string& file);
  std::vector<std::pair<std::string, std::string>>
    savetext(const std::string& file, const std::string& separator);
  colmajor_matrix<float>
  to_colmajor_matrix_float(const std::vector<std::string>&);
  colmajor_matrix<double>
  to_colmajor_matrix_double(const std::vector<std::string>&);
  rowmajor_matrix<float>
  to_rowmajor_matrix_float(const std::vector<std::string>&);
  rowmajor_matrix<double>
  to_rowmajor_matrix_double(const std::vector<std::string>&);
  // info is output; create matrix according to the table data
  ell_matrix<float>
  to_ell_matrix_float(const std::vector<std::string>& cols,
                      const std::vector<std::string>& cat,
                      dftable_to_sparse_info& info); 
  // info is input; create matrix based on mapping craeted before
  ell_matrix<float> to_ell_matrix_float(dftable_to_sparse_info& info);
  ell_matrix<double>
  to_ell_matrix_double(const std::vector<std::string>& cols,
                       const std::vector<std::string>& cat,
                       dftable_to_sparse_info& info); 
  ell_matrix<double> to_ell_matrix_double(dftable_to_sparse_info& info);

  crs_matrix<float>
  to_crs_matrix_float(const std::vector<std::string>& cols,
                      const std::vector<std::string>& cat,
                      dftable_to_sparse_info& info); 
  crs_matrix<float> to_crs_matrix_float(dftable_to_sparse_info& info);
  crs_matrix<double>
  to_crs_matrix_double(const std::vector<std::string>& cols,
                       const std::vector<std::string>& cat,
                       dftable_to_sparse_info& info); 
  crs_matrix<double> to_crs_matrix_double(dftable_to_sparse_info& info);

  // internally used methods, though they are public...
  // dfcolumn is only for implementation/debug, not for user's usage
  virtual std::shared_ptr<dfcolumn> column(const std::string& name);
  virtual std::shared_ptr<dfcolumn> raw_column(const std::string& name);
  virtual node_local<std::vector<size_t>> get_local_index();
  virtual bool is_right_joinable() {return true;}
  virtual void debug_print();
protected:
  std::map<std::string, std::shared_ptr<dfcolumn>> col;
  std::vector<std::string> col_order; // order of cols, though redundant...
  size_t row_size;

  friend filtered_dftable;
  friend sorted_dftable;
  friend hash_joined_dftable;
  friend bcast_joined_dftable;
  friend star_joined_dftable;
  friend grouped_dftable;
};

template <class T> T dftable_base::sum(const std::string& name) {
    return column(name)->sum<T>();
}

template <class T> T dftable_base::max(const std::string& name) {
  return column(name)->max<T>();
}

template <class T> T dftable_base::min(const std::string& name) {
  return column(name)->min<T>();
}

template <class T>
dvector<T> dftable_base::as_dvector(const std::string name) {
  return column(name)->as_dvector<T>();
}

class dftable : public dftable_base {
public:
  virtual ~dftable(){}
  dftable(){}
  dftable(dftable_base& b) : dftable_base(b) {}
  dftable(dftable_base&& b) : dftable_base(std::move(b)) {}
  /*
    dfcolumn specific member functions
    As for other classes, return types are different
  */
  dftable& drop(const std::string& name);
  dftable& rename(const std::string& name, const std::string& name2);
  template <class T>
  dftable& append_column(const std::string& name, dvector<T>& d);
  template <class T>
  dftable& append_column(const std::string& name, dvector<T>&& d);
  // do not align dfcolumn, since it is used in other place
  // do not use this if you are not sure of the alignment!
  dftable& append_column(const std::string& name,
                         const std::shared_ptr<dfcolumn>& c);
  // do not support NULL items
  template <class R, class T1, class F>
  dftable& calc(const std::string& r, F f, const std::string& c1);
  template <class R, class T1, class T2, class F>
  dftable&  calc(const std::string& r, F f, const std::string& c1,
                 const std::string& c2);
  template <class R, class T1, class T2, class T3, class F>
  dftable&  calc(const std::string& r, F f, const std::string& c1,
                 const std::string& c2, const std::string& c3);
  template <class R, class T1, class T2, class T3, class T4, class F>
  dftable&  calc(const std::string& r, F f, const std::string& c1,
                 const std::string& c2, const std::string& c3,
                 const std::string& c4);
  template <class R, class T1, class T2, class T3, class T4, class T5, class F>
  dftable&  calc(const std::string& r, F f, const std::string& c1,
                 const std::string& c2, const std::string& c3,
                 const std::string& c4, const std::string& c5);
  template <class R, class T1, class T2, class T3, class T4, class T5,
            class T6, class F>
  dftable&  calc(const std::string& r, F f, const std::string& c1,
                 const std::string& c2, const std::string& c3,
                 const std::string& c4, const std::string& c5,
                 const std::string& c6);
  dftable& append_rowid(const std::string& name, size_t offset = 0);

  void load(const std::string& input);
  virtual bool is_right_joinable() {return true;}

  friend filtered_dftable;
  friend sorted_dftable;
  friend hash_joined_dftable;
  friend bcast_joined_dftable;
  friend star_joined_dftable;
};

struct dftable_to_sparse_info {
  std::vector<std::string> columns;
  std::vector<std::string> categories;
  std::vector<dftable> mapping_tables;
  size_t num_row;
  size_t num_col;
  void save(const std::string& dir);
  void load(const std::string& dir);
};

dftable make_dftable_load(const std::string& input);

template <class T>
dftable& dftable::append_column(const std::string& name, dvector<T>& d) {
  if(col.find(name) != col.end())
    throw std::runtime_error("append_column: same column name already exists");
  std::shared_ptr<dfcolumn> c;
  if(col.size() == 0) {
    row_size = d.size();
    d.align_block();
    c = std::make_shared<typed_dfcolumn<T>>(d);
  } else {
    if(d.size() != row_size)
      throw std::runtime_error("different size of columns");
    auto sizes = column(col_order[0])->sizes();
    d.align_as(sizes);
    c = std::make_shared<typed_dfcolumn<T>>(d);
  }
  col.insert(std::make_pair(name, c));
  col_order.push_back(name);
  return *this;
}

template <class T>
dftable& dftable::append_column(const std::string& name, dvector<T>&& d) {
  if(col.find(name) != col.end())
    throw std::runtime_error("append_column: same column name already exists");
  std::shared_ptr<dfcolumn> c;
  if(col.size() == 0) {
    row_size = d.size();
    d.align_block();
    c = std::make_shared<typed_dfcolumn<T>>(std::move(d));
  } else {
    if(d.size() != row_size)
      throw std::runtime_error("different size of columns");
    auto sizes = column(col_order[0])->sizes();
    d.align_as(sizes);
    c = std::make_shared<typed_dfcolumn<T>>(std::move(d));
  }
  col.insert(std::make_pair(name, c));
  col_order.push_back(name);
  return *this;
}

template <class R, class T1, class F>
struct calc_helper1 {
  calc_helper1(){}
  calc_helper1(F f) : f(f) {}
  std::vector<R> operator()(std::vector<T1>& t1) {
    size_t size = t1.size();
    std::vector<R> ret(size);
    T1* t1p = &t1[0];
    R* retp = &ret[0];
    for(size_t i = 0; i < size; i++) {
      retp[i] = f(t1p[i]);
    }
    return ret;
  }
  F f;
  SERIALIZE(f)
};

template <class R, class T1, class F>
dftable& dftable::calc(const std::string& name, F f,
                       const std::string& c1) {
  auto tc1 = std::dynamic_pointer_cast<typed_dfcolumn<T1>>(column(c1));
  if(!tc1)
    throw std::runtime_error
      ("calc: column type is different from specified type");
  auto&& val1 = tc1->get_val();
  auto r = val1.template map<std::vector<R>>
    (calc_helper1<R,T1,F>(f));
  return append_column(name, r.template moveto_dvector<R>());
}

template <class R, class T1, class T2, class F>
struct calc_helper2 {
  calc_helper2(){}
  calc_helper2(F f) : f(f) {}
  std::vector<R> operator()(std::vector<T1>& t1, std::vector<T2>& t2) {
    size_t size = t1.size();
    std::vector<R> ret(size);
    T1* t1p = &t1[0];
    T2* t2p = &t2[0];
    R* retp = &ret[0];
    for(size_t i = 0; i < size; i++) {
      retp[i] = f(t1p[i], t2p[i]);
    }
    return ret;
  }
  F f;
  SERIALIZE(f)
};

template <class R, class T1, class T2, class F>
dftable& dftable::calc(const std::string& name, F f,
                       const std::string& c1, const std::string& c2) {
  auto tc1 = std::dynamic_pointer_cast<typed_dfcolumn<T1>>(column(c1));
  auto tc2 = std::dynamic_pointer_cast<typed_dfcolumn<T2>>(column(c2));
  if(!tc1 || !tc2)
    throw std::runtime_error
      ("calc: column types are different from specified types");
  auto&& val1 = tc1->get_val();
  auto&& val2 = tc2->get_val();
  auto r = val1.template map<std::vector<R>>
    (calc_helper2<R,T1,T2,F>(f),
     val2);
  return append_column(name, r.template moveto_dvector<R>());
}

template <class R, class T1, class T2, class T3, class F>
struct calc_helper3 {
  calc_helper3(){}
  calc_helper3(F f) : f(f) {}
  std::vector<R> operator()(std::vector<T1>& t1, std::vector<T2>& t2,
                            std::vector<T3>& t3) {
    size_t size = t1.size();
    std::vector<R> ret(size);
    T1* t1p = &t1[0];
    T2* t2p = &t2[0];
    T3* t3p = &t3[0];
    R* retp = &ret[0];
    for(size_t i = 0; i < size; i++) {
      retp[i] = f(t1p[i], t2p[i], t3p[i]);
    }
    return ret;
  }
  F f;
  SERIALIZE(f)
};

template <class R, class T1, class T2, class T3, class F>
dftable& dftable::calc(const std::string& name, F f,
                       const std::string& c1, const std::string& c2,
                       const std::string& c3) {
  auto tc1 = std::dynamic_pointer_cast<typed_dfcolumn<T1>>(column(c1));
  auto tc2 = std::dynamic_pointer_cast<typed_dfcolumn<T2>>(column(c2));
  auto tc3 = std::dynamic_pointer_cast<typed_dfcolumn<T3>>(column(c3));
  if(!tc1 || !tc2 || !tc3)
    throw std::runtime_error
      ("calc: column types are different from specified types");
  auto&& val1 = tc1->get_val();
  auto&& val2 = tc2->get_val();
  auto&& val3 = tc3->get_val();
  auto r = val1.template map<std::vector<R>>
    (calc_helper3<R,T1,T2,T3,F>(f),
     val2, val3);
  return append_column(name, r.template moveto_dvector<R>());
}

template <class R, class T1, class T2, class T3, class T4, class F>
struct calc_helper4 {
  calc_helper4(){}
  calc_helper4(F f) : f(f) {}
  std::vector<R> operator()(std::vector<T1>& t1, std::vector<T2>& t2,
                            std::vector<T3>& t3, std::vector<T4>& t4) {
    size_t size = t1.size();
    std::vector<R> ret(size);
    T1* t1p = &t1[0];
    T2* t2p = &t2[0];
    T3* t3p = &t3[0];
    T4* t4p = &t4[0];
    R* retp = &ret[0];
    for(size_t i = 0; i < size; i++) {
      retp[i] = f(t1p[i], t2p[i], t3p[i], t4p[i]);
    }
    return ret;
  }
  F f;
  SERIALIZE(f)
};

template <class R, class T1, class T2, class T3, class T4, class F>
dftable&  dftable::calc(const std::string& name, F f,
                        const std::string& c1, const std::string& c2,
                        const std::string& c3, const std::string& c4) {
  auto tc1 = std::dynamic_pointer_cast<typed_dfcolumn<T1>>(column(c1));
  auto tc2 = std::dynamic_pointer_cast<typed_dfcolumn<T2>>(column(c2));
  auto tc3 = std::dynamic_pointer_cast<typed_dfcolumn<T3>>(column(c3));
  auto tc4 = std::dynamic_pointer_cast<typed_dfcolumn<T4>>(column(c4));
  if(!tc1 || !tc2 || !tc3 || !tc4)
    throw std::runtime_error
      ("calc: column types are different from specified types");
  auto&& val1 = tc1->get_val();
  auto&& val2 = tc2->get_val();
  auto&& val3 = tc3->get_val();
  auto&& val4 = tc4->get_val();
  auto r = val1.template map<std::vector<R>>
    (calc_helper4<R,T1,T2,T3,T4,F>(f),
     val2, val3, val4);
  return append_column(name, r.template moveto_dvector<R>());
}

template <class R, class T1, class T2, class T3, class T4, class T5, class F>
struct calc_helper5 {
  calc_helper5(){}
  calc_helper5(F f) : f(f) {}
  std::vector<R> operator()(std::vector<T1>& t1, std::vector<T2>& t2,
                            std::vector<T3>& t3, std::vector<T4>& t4,
                            std::vector<T5>& t5) {
    size_t size = t1.size();
    std::vector<R> ret(size);
    T1* t1p = &t1[0];
    T2* t2p = &t2[0];
    T3* t3p = &t3[0];
    T4* t4p = &t4[0];
    T5* t5p = &t5[0];
    R* retp = &ret[0];
    for(size_t i = 0; i < size; i++) {
      retp[i] = f(t1p[i], t2p[i], t3p[i], t4p[i], t5p[i]);
    }
    return ret;
  }
  F f;
  SERIALIZE(f)
};

template <class R, class T1, class T2, class T3, class T4, class T5, class F>
dftable& dftable::calc(const std::string& name, F f,
                   const std::string& c1, const std::string& c2,
                   const std::string& c3, const std::string& c4,
                   const std::string& c5) {
  auto tc1 = std::dynamic_pointer_cast<typed_dfcolumn<T1>>(column(c1));
  auto tc2 = std::dynamic_pointer_cast<typed_dfcolumn<T2>>(column(c2));
  auto tc3 = std::dynamic_pointer_cast<typed_dfcolumn<T3>>(column(c3));
  auto tc4 = std::dynamic_pointer_cast<typed_dfcolumn<T4>>(column(c4));
  auto tc5 = std::dynamic_pointer_cast<typed_dfcolumn<T5>>(column(c5));
  if(!tc1 || !tc2 || !tc3 || !tc4 || !tc5)
    throw std::runtime_error
      ("calc: column types are different from specified types");
  auto&& val1 = tc1->get_val();
  auto&& val2 = tc2->get_val();
  auto&& val3 = tc3->get_val();
  auto&& val4 = tc4->get_val();
  auto&& val5 = tc5->get_val();
  auto r = val1.template map<std::vector<R>>
    (calc_helper5<R,T1,T2,T3,T4,T5,F>(f),
     val2, val3, val4, val5);
  return append_column(name, r.template moveto_dvector<R>());
}

template <class R, class T1, class T2, class T3, class T4, class T5,
          class T6, class F>
struct calc_helper6 {
  calc_helper6(){}
  calc_helper6(F f) : f(f) {}
  std::vector<R> operator()(std::vector<T1>& t1, std::vector<T2>& t2,
                            std::vector<T3>& t3, std::vector<T4>& t4,
                            std::vector<T5>& t5, std::vector<T6>& t6) {
    size_t size = t1.size();
    std::vector<R> ret(size);
    T1* t1p = &t1[0];
    T2* t2p = &t2[0];
    T3* t3p = &t3[0];
    T4* t4p = &t4[0];
    T5* t5p = &t5[0];
    T6* t6p = &t6[0];
    R* retp = &ret[0];
    for(size_t i = 0; i < size; i++) {
      retp[i] = f(t1p[i], t2p[i], t3p[i], t4p[i], t5p[i], t6p[i]);
    }
    return ret;
  }
  F f;
  SERIALIZE(f)
};

template <class R, class T1, class T2, class T3, class T4, class T5,
          class T6, class F>
dftable& dftable::calc(const std::string& name, F f,
                       const std::string& c1, const std::string& c2,
                       const std::string& c3, const std::string& c4,
                       const std::string& c5, const std::string& c6) {
  auto tc1 = std::dynamic_pointer_cast<typed_dfcolumn<T1>>(column(c1));
  auto tc2 = std::dynamic_pointer_cast<typed_dfcolumn<T2>>(column(c2));
  auto tc3 = std::dynamic_pointer_cast<typed_dfcolumn<T3>>(column(c3));
  auto tc4 = std::dynamic_pointer_cast<typed_dfcolumn<T4>>(column(c4));
  auto tc5 = std::dynamic_pointer_cast<typed_dfcolumn<T5>>(column(c5));
  auto tc6 = std::dynamic_pointer_cast<typed_dfcolumn<T6>>(column(c6));
  if(!tc1 || !tc2 || !tc3 || !tc4 || !tc5 || !tc6)
    throw std::runtime_error
      ("calc: column types are different from specified types");
  auto&& val1 = tc1->get_val();
  auto&& val2 = tc2->get_val();
  auto&& val3 = tc3->get_val();
  auto&& val4 = tc4->get_val();
  auto&& val5 = tc5->get_val();
  auto&& val6 = tc6->get_val();
  auto r = val1.template map<std::vector<R>>
    (calc_helper6<R,T1,T2,T3,T4,T5,T6,F>(f),
     val2, val3, val4, val5, val6);
  return append_column(name, r.template moveto_dvector<R>());
}

class sorted_dftable : public dftable_base {
public:
  sorted_dftable(dftable_base& table,
                 node_local<std::vector<size_t>>&& global_idx_,
                 const std::string& column_name,
                 std::shared_ptr<dfcolumn>&& sorted_column) :
    dftable_base(table), global_idx(std::move(global_idx_)),
    column_name(column_name), sorted_column(std::move(sorted_column)) {
    auto partitioned_idx = partition_global_index_bynode(global_idx);
    to_store_idx = make_to_store_idx(partitioned_idx, global_idx);
    exchanged_idx = exchange_partitioned_index(partitioned_idx);
    is_cachable = !table.raw_column(column_name)->is_string();
  }
  virtual dftable select(const std::vector<std::string>& cols);
  virtual filtered_dftable filter(const std::shared_ptr<dfoperator>& op);
  virtual sorted_dftable sort(const std::string& name);
  virtual sorted_dftable sort_desc(const std::string& name);
  virtual hash_joined_dftable
  hash_join(dftable_base& right, const std::shared_ptr<dfoperator>& op);
  virtual hash_joined_dftable
  outer_hash_join(dftable_base& right, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  outer_bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual star_joined_dftable
  star_join(const std::vector<dftable_base*>& dftables, 
            const std::vector<std::shared_ptr<dfoperator>>& op);
  virtual grouped_dftable group_by(const std::vector<std::string>& cols);
  virtual std::shared_ptr<dfcolumn> column(const std::string& name);
  virtual node_local<std::vector<size_t>> get_local_index() {
    throw std::runtime_error("get_local_index on sorted_dftable");
  }
  virtual bool is_right_joinable() {return false;}
  virtual void debug_print();

  dftable append_rowid(const std::string& name, size_t offset = 0);
private:
  node_local<std::vector<size_t>> global_idx;
  std::string column_name;
  std::shared_ptr<dfcolumn> sorted_column;
  node_local<std::vector<size_t>> to_store_idx;
  node_local<std::vector<std::vector<size_t>>> exchanged_idx;
  bool is_cachable;
};

std::vector<size_t> concat_idx(std::vector<size_t>& a, std::vector<size_t>& b);

class hash_joined_dftable : public dftable_base {
public:
  hash_joined_dftable(dftable_base& left, dftable_base& right,
                      node_local<std::vector<size_t>>&& left_idx_,
                      node_local<std::vector<size_t>>&& right_idx_) :
    dftable_base(left), is_outer(false), right(right),
    left_idx(std::move(left_idx_)), right_idx(std::move(right_idx_)) {
    time_spent t(DEBUG);
    auto unique_left_idx = left_idx.map(get_unique_idx);
    auto left_partitioned_idx = partition_global_index_bynode(unique_left_idx);
    left_to_store_idx = make_to_store_idx(left_partitioned_idx, left_idx);
    left_exchanged_idx = exchange_partitioned_index(left_partitioned_idx);
    auto unique_right_idx = right_idx.map(get_unique_idx);
    auto right_partitioned_idx = partition_global_index_bynode(unique_right_idx);
    right_to_store_idx = make_to_store_idx(right_partitioned_idx, right_idx);
    right_exchanged_idx = exchange_partitioned_index(right_partitioned_idx);
    t.show("init hash_joined_dftable: ");
  }
  hash_joined_dftable(dftable_base& left, dftable_base& right,
                      node_local<std::vector<size_t>>&& left_idx_,
                      node_local<std::vector<size_t>>&& right_idx_,
                      node_local<std::vector<size_t>>&& right_nulls_) :
    dftable_base(left), right(right),
    right_idx(std::move(right_idx_)), right_nulls(std::move(right_nulls_)) {
    if(right_nulls.template viewas_dvector<size_t>().size() == 0) {
      is_outer = false;
      left_idx = std::move(left_idx_);
    } else {
      is_outer = true;
      left_idx = left_idx_.map(concat_idx, right_nulls);
    }
    auto unique_left_idx = left_idx.map(get_unique_idx);
    auto left_partitioned_idx = partition_global_index_bynode(unique_left_idx);
    left_to_store_idx = make_to_store_idx(left_partitioned_idx, left_idx);
    left_exchanged_idx = exchange_partitioned_index(left_partitioned_idx);
    auto unique_right_idx = right_idx.map(get_unique_idx);
    auto right_partitioned_idx = partition_global_index_bynode(unique_right_idx);
    right_to_store_idx = make_to_store_idx(right_partitioned_idx, right_idx);
    right_exchanged_idx = exchange_partitioned_index(right_partitioned_idx);
  }
  virtual size_t num_col() const;
  virtual size_t num_row();
  virtual std::vector<std::string> columns() const;
  dftable select(const std::vector<std::string>& cols);
  virtual filtered_dftable filter(const std::shared_ptr<dfoperator>& op);
  virtual sorted_dftable sort(const std::string& name);
  virtual sorted_dftable sort_desc(const std::string& name);
  virtual hash_joined_dftable hash_join(dftable_base& dftable,
                                        const std::shared_ptr<dfoperator>& op);
  virtual hash_joined_dftable
  outer_hash_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  outer_bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual star_joined_dftable
  star_join(const std::vector<dftable_base*>& dftables, 
            const std::vector<std::shared_ptr<dfoperator>>& op);
  virtual grouped_dftable group_by(const std::vector<std::string>& cols);
  std::shared_ptr<dfcolumn> column(const std::string& name);
  virtual node_local<std::vector<size_t>> get_local_index() {
    throw std::runtime_error("get_local_index on hash_joined_dftable");
  }
  virtual bool is_right_joinable() {return false;}
  void debug_print();

  dftable append_rowid(const std::string& name, size_t offset = 0);
private:
  // left table is base class; if the input is filtered_dftable, sliced
  bool is_outer;
  dftable_base right; // if the input is filtered_dftable, sliced
  node_local<std::vector<size_t>> left_idx;
  node_local<std::vector<size_t>> right_idx;
  node_local<std::vector<size_t>> right_nulls;
  node_local<std::vector<size_t>> left_to_store_idx;
  node_local<std::vector<std::vector<size_t>>> left_exchanged_idx;
  node_local<std::vector<size_t>> right_to_store_idx;
  node_local<std::vector<std::vector<size_t>>> right_exchanged_idx;
};

class bcast_joined_dftable : public dftable_base {
public:
  bcast_joined_dftable(dftable_base& left, dftable_base& right,
                       node_local<std::vector<size_t>>&& left_idx_,
                       node_local<std::vector<size_t>>&& right_idx_) :
    dftable_base(left), is_outer(false), right(right),
    left_idx(std::move(left_idx_)), right_idx(std::move(right_idx_)) {
    auto unique_right_idx = right_idx.map(get_unique_idx);
    auto right_partitioned_idx = partition_global_index_bynode(unique_right_idx);
    right_to_store_idx = make_to_store_idx(right_partitioned_idx, right_idx);
    right_exchanged_idx = exchange_partitioned_index(right_partitioned_idx);
  }
  bcast_joined_dftable(dftable_base& left, dftable_base& right,
                       node_local<std::vector<size_t>>&& left_idx_,
                       node_local<std::vector<size_t>>&& right_idx_,
                       node_local<std::vector<size_t>>&& right_nulls_) :
    dftable_base(left), right(right),
    right_idx(std::move(right_idx_)), right_nulls(std::move(right_nulls_)) {
    if(right_nulls.template viewas_dvector<size_t>().size() == 0) {
      is_outer = false;
      left_idx = std::move(left_idx_);
    } else {
      is_outer = true;
      left_idx = left_idx_.map(concat_idx, right_nulls);
    }
    auto unique_right_idx = right_idx.map(get_unique_idx);
    auto right_partitioned_idx = partition_global_index_bynode(unique_right_idx);
    right_to_store_idx = make_to_store_idx(right_partitioned_idx, right_idx);
    right_exchanged_idx = exchange_partitioned_index(right_partitioned_idx);
  }
  virtual size_t num_col() const;
  virtual size_t num_row();
  virtual std::vector<std::string> columns() const;
  dftable select(const std::vector<std::string>& cols);
  virtual filtered_dftable filter(const std::shared_ptr<dfoperator>& op);
  virtual sorted_dftable sort(const std::string& name);
  virtual sorted_dftable sort_desc(const std::string& name);
  virtual hash_joined_dftable hash_join(dftable_base& dftable,
                                        const std::shared_ptr<dfoperator>& op);
  virtual hash_joined_dftable
  outer_hash_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  outer_bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual star_joined_dftable
  star_join(const std::vector<dftable_base*>& dftables, 
            const std::vector<std::shared_ptr<dfoperator>>& op);
  virtual grouped_dftable group_by(const std::vector<std::string>& cols);
  std::shared_ptr<dfcolumn> column(const std::string& name);
  virtual node_local<std::vector<size_t>> get_local_index() {
    throw std::runtime_error("get_local_index on bcast_joined_dftable");
  }
  virtual bool is_right_joinable() {return false;}
  void debug_print();

  dftable append_rowid(const std::string& name, size_t offset = 0);
private:
  // left table is base class; if the input is filtered_dftable, sliced
  bool is_outer;
  dftable_base right; // if the input is filtered_dftable, sliced
  node_local<std::vector<size_t>> left_idx; // local index
  node_local<std::vector<size_t>> right_idx;
  node_local<std::vector<size_t>> right_nulls;
  node_local<std::vector<size_t>> right_to_store_idx;
  node_local<std::vector<std::vector<size_t>>> right_exchanged_idx;
};

// TODO: support outer_star_join
class star_joined_dftable : public dftable_base {
public:
  star_joined_dftable(dftable_base& left, std::vector<dftable_base>&& rights_,
                      node_local<std::vector<size_t>>&& left_idx_,
                      std::vector<node_local<std::vector<size_t>>>&& 
                      right_idxs_) :
    dftable_base(left), rights(std::move(rights_)),
    left_idx(std::move(left_idx_)), right_idxs(std::move(right_idxs_)) {
    size_t rightssize = rights.size();
    right_to_store_idxs.resize(rightssize);
    right_exchanged_idxs.resize(rightssize);
    for(size_t i = 0; i < rightssize; i++) {
      auto unique_right_idx = right_idxs[i].map(get_unique_idx);
      auto right_partitioned_idx = 
        partition_global_index_bynode(unique_right_idx);
      right_to_store_idxs[i] = make_to_store_idx(right_partitioned_idx,
                                                 right_idxs[i]);
      right_exchanged_idxs[i] = 
        exchange_partitioned_index(right_partitioned_idx);
    }
  }
  virtual size_t num_col() const;
  virtual size_t num_row();
  virtual std::vector<std::string> columns() const;
  dftable select(const std::vector<std::string>& cols);
  virtual filtered_dftable filter(const std::shared_ptr<dfoperator>& op);
  virtual sorted_dftable sort(const std::string& name);
  virtual sorted_dftable sort_desc(const std::string& name);
  virtual hash_joined_dftable hash_join(dftable_base& dftable,
                                        const std::shared_ptr<dfoperator>& op);
  virtual hash_joined_dftable
  outer_hash_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual bcast_joined_dftable
  outer_bcast_join(dftable_base& dftable, const std::shared_ptr<dfoperator>& op);
  virtual star_joined_dftable
  star_join(const std::vector<dftable_base*>& dftables, 
            const std::vector<std::shared_ptr<dfoperator>>& op);
  virtual grouped_dftable group_by(const std::vector<std::string>& cols);
  std::shared_ptr<dfcolumn> column(const std::string& name);
  virtual node_local<std::vector<size_t>> get_local_index() {
    throw std::runtime_error("get_local_index on star_joined_dftable");
  }
  virtual bool is_right_joinable() {return false;}
  void debug_print();

  dftable append_rowid(const std::string& name, size_t offset = 0);
private:
  // left table is base class; if the input is filtered_dftable, sliced
  std::vector<dftable_base> rights; // if the input is filtered_dftable, sliced
  node_local<std::vector<size_t>> left_idx; // local index
  std::vector<node_local<std::vector<size_t>>> right_idxs;
  std::vector<node_local<std::vector<size_t>>> right_to_store_idxs;
  std::vector<node_local<std::vector<std::vector<size_t>>>>
  right_exchanged_idxs;
};

// not derived from dftable_base, since I/F is different
class grouped_dftable {
public:
  grouped_dftable(const dftable_base& table, 
                  node_local<std::vector<size_t>>&& local_grouped_idx_,
                  node_local<std::vector<size_t>>&& local_idx_split_,
                  node_local<std::vector<std::vector<size_t>>>&& hash_divide_,
                  node_local<std::vector<std::vector<size_t>>>&& merge_map_,
                  std::vector<std::shared_ptr<dfcolumn>>&& grouped_cols_,
                  const std::vector<std::string>& grouped_col_names_) :
    org_table(table),
    local_grouped_idx(local_grouped_idx_),
    local_idx_split(local_idx_split_),
    hash_divide(hash_divide_),
    merge_map(merge_map_),
    grouped_cols(grouped_cols_),
    grouped_col_names(grouped_col_names_) {}

  dftable
  select(const std::vector<std::string>& cols,
         const std::vector<std::shared_ptr<dfaggregator>>& aggs);
  size_t num_row(){return grouped_cols[0]->size();}
  // size_t num_col(){return org_table.num_col();}
  dftable select(const std::vector<std::string>& cols);
  void debug_print();
private:
  dftable_base org_table;
  node_local<std::vector<size_t>> local_grouped_idx;
  node_local<std::vector<size_t>> local_idx_split;
  node_local<std::vector<std::vector<size_t>>> hash_divide;
  node_local<std::vector<std::vector<size_t>>> merge_map;
  std::vector<std::shared_ptr<dfcolumn>> grouped_cols;
  std::vector<std::string> grouped_col_names;
};


// for to_colmajor_matrix
template <class T>
void append_column_to_colmajor_matrix(colmajor_matrix_local<T>& mat,
                                      size_t i, size_t num_col,
                                      std::vector<T>& v) {
  if(i == 0) {
    mat.local_num_row = v.size();
    mat.local_num_col = num_col;
    mat.val.resize(mat.local_num_row * mat.local_num_col);
  }
  T* valp = mat.val.data();
  T* vp = v.data();
  size_t size = v.size();
  if(mat.local_num_row != size)
    throw std::runtime_error("internal error in to_colmajor_matrix: column sizes are not the same?");
  for(size_t j = 0; j < v.size(); j++) {
    valp[size * i + j] = vp[j];
  }
}

// for to_ell_matrix
template <class T>
void to_ell_matrix_init(ell_matrix_local<T>& mat, size_t physical_col_size,
                        std::vector<size_t>& row_sizes, size_t num_col) {
  mat.local_num_row = row_sizes[get_selfid()];
  mat.local_num_col = num_col;
  mat.val.resize(mat.local_num_row * physical_col_size);
  mat.idx.resize(mat.local_num_row * physical_col_size);
}

template <class T>
void to_ell_matrix_addcategory(ell_matrix_local<T>& mat,
                               std::vector<size_t> col,
                               size_t physical_col) {
  size_t* colp = col.data();
  T* valp = mat.val.data();
  size_t* idxp = mat.idx.data();
  size_t num_row = mat.local_num_row;
  for(size_t i = 0; i < num_row; i++) {
    valp[num_row * physical_col + i] = 1; // one-hot encoding
  }
  for(size_t i = 0; i < num_row; i++) {
    idxp[num_row * physical_col + i] = colp[i];
  }
}

template <class T>
void to_ell_matrix_addvalue(ell_matrix_local<T>& mat,
                            std::vector<T>& v,
                            size_t logical_col,
                            size_t physical_col) {
  T* vp = v.data();
  T* valp = mat.val.data();
  size_t* idxp = mat.idx.data();
  size_t num_row = mat.local_num_row;
  for(size_t i = 0; i < num_row; i++) {
    valp[num_row * physical_col + i] = vp[i];
  }
  for(size_t i = 0; i < num_row; i++) {
    idxp[num_row * physical_col + i] = logical_col;
  }
}

}
#endif
