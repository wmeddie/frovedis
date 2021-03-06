#include <frovedis.hpp>

#include <boost/program_options.hpp>

using namespace std;
using namespace frovedis;

template <class T>
void to_text_vector(string& input, string& output) {
  auto m = make_dvector_loadbinary<T>(input);
  if (output == "-") {
    for(auto& i: m.gather()) cout << i << endl;
  }
  else m.saveline(output);
}

int main(int argc, char* argv[]) {
  use_frovedis use(argc, argv);

  using namespace boost::program_options;

  options_description opt("option");
  opt.add_options()
    ("help,h", "print help")
    ("input,i", value<string>(), "input binary matrix directory")
    ("output,o", value<string>(), "output text matrix file(- indicates stdout)")
    ("double", "assume double data")
    ("float", "assume float data")
    ("int", "assume int data");

  variables_map argmap;
  store(command_line_parser(argc,argv).options(opt).allow_unregistered().
        run(), argmap);
  notify(argmap);

  string input, output;
  
  if(argmap.count("help")){
    cerr << opt << endl;
    exit(1);
  }

  if(argmap.count("input")){
    input = argmap["input"].as<string>();
  } else {
    cerr << "input matrix directory is not specified" << endl;
    cerr << opt << endl;
    exit(1);
  }

  if(argmap.count("output")){
    output = argmap["output"].as<string>();
  } else {
    cerr << "output matrix file is not specified" << endl;
    cerr << opt << endl;
    exit(1);
  }

  if(argmap.count("double")) {
    to_text_vector<double>(input, output);
  } else if(argmap.count("float")) {
    to_text_vector<float>(input, output);
  } else if(argmap.count("int")) {
    to_text_vector<int>(input, output);
  } else {
    cerr << "data type is not specified" << endl;
    cerr << opt << endl;
    exit(1);
  }

}
