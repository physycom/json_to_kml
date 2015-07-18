/* Copyright 2015 - Alessandro Fabbri, Stefano Sinigardi */

/***************************************************************************
This file is part of json_to_kml.

json_to_kml is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

json_to_kml is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with json_to_kml. If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include "jsoncons/json.hpp"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace jsoncons;
using namespace rapidxml;
using namespace std;

#define MAJOR_VERSION     0
#define MINOR_VERSION     1

#define VERBOSE           1

int main(int argc, char** argv)
{
  // Usage
  std::cout << "json2kml v" << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
  std::cout << "Usage: " << argv[0] << " -i [input.json] -o [output.kml]" << std::endl;
  std::cout << "\t- [input.json] json file to parse" << std::endl;
  std::cout << "\t- [output.kml] kml v2.2 file produced by this utility" << std::endl;

  // Parsing command line
  std::string input_name, output_name, outjson_type{};
  if (argc > 2){ /* Parse arguments, if there are arguments supplied */
    for (int i = 1; i < argc; i++){
      if ((argv[i][0] == '-') || (argv[i][0] == '/')){       // switches or options...
        switch (tolower(argv[i][1])){
        case 'i':
          input_name = argv[++i];
          break;
        case 'o':
          output_name = argv[++i];
          break;
        default:    // no match...
          std::cout << "Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
          exit(1);
        }
      }
      else {
        std::cout << "Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
        exit(11);
      }
    }
  }
  else { std::cout << "No flags specified. Read usage and relaunch properly." << std::endl; exit(111); }

  // Safety checks for file manipulations
  ofstream output_file;
  ifstream input_file;

  if (input_name.size() > 5) {
    if (input_name.substr(input_name.size() - 5, 5) != ".json"){
      std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
      exit(2);
    }
  }
  else{
    std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
    exit(22);
  }
  input_file.open(input_name.c_str());
  if (!input_file.is_open()) {
    cout << "FAILED: Input file " << input_name << " could not be opened." << endl;
    cout << "Hit ENTER to close.\n"; cin.get();
    exit(222);
  }
  else { cout << "SUCCESS: file " << input_name << " opened!\n"; }

  if (output_name.size() > 4){
    if (output_name.substr(output_name.size() - 4, 4) != ".kml"){
      std::cout << output_name << " is not a valid .kml file. Quitting..." << std::endl;
      exit(3);
    }
  }
  else{
    std::cout << output_name << " is not a valid .kml file. Quitting..." << std::endl;
    exit(33);
  }
  output_file.open(output_name.c_str());
  if (!output_file.is_open()) {
    cout << "FAILED: Output file " << output_name << " could not be opened." << endl;
    cout << "Hit ENTER to close.\n"; cin.get();
    exit(333);
  }
  else { cout << "SUCCESS: file " << output_name << " opened!\n"; }



  json inputjson;
  return 0;
}

