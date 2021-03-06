#include "exrpc_data_storage.hpp"
#include "exrpc_dataframe.hpp"

using namespace frovedis;

void expose_frovedis_dataframe_functions() {
  // --- frovedis dataframe ---
  expose(create_dataframe);
  expose(release_data<dftable>);
  expose(release_data<grouped_dftable>);
  expose(show_dataframe);
  expose(get_dfoperator<int>);
  expose(get_dfoperator<long>);
  expose(get_dfoperator<float>);
  expose(get_dfoperator<double>);
  expose(get_str_dfoperator);
  expose(get_dfANDoperator);
  expose(get_dfORoperator);
  expose((release_data<std::shared_ptr<dfoperator>>));
  expose(filter_df);
  expose(select_df);
  expose(sort_df);
  expose(join_df);
  expose(group_by_df);
  expose(frovedis_df_size);
  expose(frovedis_df_cnt);
  expose(frovedis_df_sum);
  expose(frovedis_df_avg);
  expose(frovedis_df_min);
  expose(frovedis_df_max);
  expose(frovedis_df_std);
  expose(frovedis_df_rename);
  expose(get_df_int_col);
  expose(get_df_long_col);
  expose(get_df_float_col);
  expose(get_df_double_col);
  expose(get_df_string_col);
  expose(frovedis_gdf_aggr);
  expose(df_to_colmajor_float);
  expose(df_to_colmajor_double);
  expose(df_to_rowmajor_float);
  expose(df_to_rowmajor_double);
  expose(df_to_crs_float);
  expose(df_to_crs_double);
  expose(df_to_crs_float_using_info);
  expose(df_to_crs_double_using_info);
  expose(load_sparse_conversion_info);
  expose(save_sparse_conversion_info);
  expose(release_sparse_conversion_info);
}
