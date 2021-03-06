#include <frovedis.hpp>
#include <frovedis/dataframe.hpp>

int main(int argc, char* argv[]){
  frovedis::use_frovedis use(argc, argv);

  auto t1 = frovedis::make_dftable_loadtext("./t1.csv", 
                                          {"int", "double", "int"},
                                          {"t1c1", "t1c2", "t1c3"});
  
  auto t2 = frovedis::make_dftable_loadtext("./t2.csv", 
                                            {"int", "string"},
                                            {"t2c1", "t2c2"});

  std::cout << "join" << std::endl;
  auto joined = t1.hash_join(t2, frovedis::eq("t1c3", "t2c1")); 
  //auto joined = t1.bcast_join(t2, frovedis::eq("t1c3", "t2c1")); 
  joined.show();
  std::cout << std::endl;

  std::cout << "filtered join" << std::endl;
  auto filtered_t2 = t2.filter(frovedis::is_not_regex("t2c2","d"));
  auto filter_joined = t1.filter(frovedis::ge_im("t1c1", 2)).
    hash_join(filtered_t2,frovedis::eq("t1c3", "t2c1"));
  //bcast_join(filtered_t2,frovedis::eq("t1c3", "t2c1"));
  filter_joined.show();
  std::cout << std::endl;

  std::cout << "outer join" << std::endl;
  auto outer_joined = t1.outer_hash_join(t2, frovedis::eq("t1c3", "t2c1")); 
  //auto outer_joined = t1.outer_bcast_join(t2, frovedis::eq("t1c3", "t2c1")); 
  outer_joined.show();
  auto t3 = frovedis::make_dftable_loadtext("./t3.csv", 
                                            {"int", "double"},
                                            {"t3c1", "t3c2"});
                                           

  std::cout << std::endl;
  std::cout << "star join" << std::endl;
  auto star_joined = t1.star_join({&filtered_t2, &t3}, 
                                  {frovedis::eq("t1c3", "t2c1"),
                                   frovedis::eq("t1c3", "t3c1")});
  star_joined.show();
}
