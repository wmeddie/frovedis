#include <frovedis.hpp>
#include <frovedis/matrix/pblas_wrapper.hpp>

#define BOOST_TEST_MODULE FrovedisTest
#include <boost/test/unit_test.hpp>

using namespace frovedis;
using namespace std;

BOOST_AUTO_TEST_CASE( frovedis_test )
{
    int argc = 1;
    char** argv = NULL;
    use_frovedis use(argc, argv);

    // scaling a distributed std::vector
    std::vector<float> in = {1,2,3,4}; 
    std::vector<float> out = {2,4,6,8};
    auto in_bm = vec_to_bcm<float> (in); // distributed vector in
    scal<float> (in_bm,2); // in_bm = in_bm*2
    BOOST_CHECK (in_bm.moveto_vector() == out);

    auto bm = make_blockcyclic_matrix_load<float> ("./sample_4x4");
  
    // checking scal() operation  
    auto row = make_row_vector<float> (bm,1);
    scal<float>(row,5); // row = 5 * row
    bm.save("./out_4x4");

    // checking whether the above operation successfully taken place 
    BOOST_CHECK (system("diff ./out_4x4 ./ref_4x4") == 0);
    system("rm -f ./out_4x4");
}

