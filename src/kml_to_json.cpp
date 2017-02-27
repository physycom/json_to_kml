/* Copyright 2015 - Alessandro Fabbri, Stefano Sinigardi */

/***************************************************************************
This file is part of kml_to_json.

kml_to_json is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

kml_to_json is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with kml_to_json. If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/


#include <string.h>
#include <stdio.h>
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

#define MAJOR_VERSION						1
#define MINOR_VERSION						1

#define VERBOSE									1

int main(int argc, char** argv)
{
  // Usage
  std::cout << "kml_to_json v" << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
  std::cout << "Usage: " << argv[0] << " -i [input.xml] -o [output.json] -f [output format specifier]" << std::endl;
  std::cout << "\t- [input.xml] xml-like file to parse" << std::endl;
  std::cout << "\t- [output.json] json location to store parsed file" << std::endl;
  std::cout << "\t- [format specifier] use 'a' (without quotes) for array json, 'o' for object json" << std::endl;
  std::cout << "\t- -f is optional, if omitted the output format will default to object-style" << std::endl;

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
        case 'f':
          outjson_type = argv[++i];
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

  if (input_name.size() > 4) {
    if (input_name.substr(input_name.size() - 4, 4) != ".kml" && input_name.substr(input_name.size() - 4, 4) != ".xml"){
      std::cout << input_name << " is not a valid .kml file. Quitting..." << std::endl;
      exit(2);
    }
  }
  else{
    std::cout << input_name << " is not a valid .kml file. Quitting..." << std::endl;
    exit(22);
  }
  input_file.open(input_name.c_str());
  if (!input_file.is_open()) {
    cout << "FAILED: Input file " << input_name << " could not be opened." << endl;
    cout << "Hit ENTER to close.\n"; cin.get();
    exit(222);
  }
  else { cout << "SUCCESS: file " << input_name << " opened!\n"; }

  if (output_name.size() > 5){
    if (output_name.substr(output_name.size() - 5, 5) != ".json"){
      std::cout << output_name << " is not a valid .json file. Quitting..." << std::endl;
      exit(3);
    }
  }
  else{
    std::cout << output_name << " is not a valid .json file. Quitting..." << std::endl;
    exit(33);
  }

  json outjson;

  // decide output type
  if(outjson_type == "a") //array
    outjson = jsoncons::json::array();
  else if(outjson_type == "o" || outjson_type == "") {} //object or omitted
  else {
    std::cout << "Output type not recognized. Quitting..." << std::endl;
    exit(4);
  }

  // try opening output file
  output_file.open(output_name.c_str());
  if (!output_file.is_open()) {
    cout << "FAILED: Output file " << output_name << " could not be opened." << endl;
    cout << "Hit ENTER to close.\n"; cin.get();
    exit(333);
  }
  else { cout << "SUCCESS: file " << output_name << " opened!\n"; }

  // Parsing XML
  xml_document<> doc;
  xml_node<> * kml_node;
  char * token;
  std::stringstream ss;
  std::string folder_name, folder_id;
  std::string placemark_index, placemark_description, placemark_coordinates;

  // Read the xml file into a vector
  vector<char> buffer((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
  buffer.push_back('\0');

  // Parse the buffer using the xml file parsing library into doc 
  doc.parse<0>(&buffer[0]);

  // Find our root node
  kml_node = doc.first_node("kml");

  std::string version = kml_node->first_attribute("xmlns")->value();
  version = version.substr(version.size() - 3, 3);
  std::cout << "KML version : " << version << std::endl;

  kml_node = kml_node->first_node("Document");

  if (version == "2.1"){
    // Iterate over FOLDER
    for (xml_node<> * folder_node = kml_node->first_node("Folder"); folder_node; folder_node = folder_node->next_sibling())
    {
      folder_name = folder_node->first_node("name")->value();
#if (VERBOSE) 
      std::cout << "Folder : " << folder_name << std::endl;
#endif		

      // Iterate over FOLDER_ID
      for (xml_node<> * folder_id_node = folder_node->first_node("Folder"); folder_id_node; folder_id_node = folder_id_node->next_sibling())
      {
        folder_id = folder_id_node->first_node("name")->value();
#if (VERBOSE) 
        std::cout << "\tFolder_name : " << folder_id << std::endl;
#endif
        // Iterate over PLACEMARK
        for (xml_node<> * placemark_node = folder_id_node->first_node("Placemark"); placemark_node; placemark_node = placemark_node->next_sibling())
        {
          ss.str("\0");
          ss.seekp(0, std::ios::beg);

          placemark_index = placemark_node->first_node("name")->value();
          placemark_description = placemark_node->first_node("description")->first_node()->value();
          placemark_coordinates = placemark_node->first_node("MultiGeometry")->first_node("Point")->first_node("coordinates")->value();
          
          json ijson;
          ijson["coordinates"] = placemark_coordinates;                       // WARNING: save before using STRTOK
          token = std::strtok((char *)placemark_coordinates.c_str(), ",");
          ijson["lon"] = atof(token);
          token = std::strtok(NULL, ",");
          ijson["lat"] = atof(token);
          ijson["description"] = placemark_description;

          token = std::strtok((char *)placemark_index.c_str(), " ");
          token = std::strtok(NULL, " ");
          ss << setfill('0') << setw(7) << atoi(token);
          placemark_index = "gps_record_" + ss.str();

          if(outjson.is_array()) outjson.add(ijson);
          else outjson[placemark_index] = ijson;
        }
      }
    }        

  }
  else if (version == "2.2"){
    // Iterate over FOLDER
    for (xml_node<> * folder_node = kml_node->first_node("Folder"); folder_node; folder_node = folder_node->next_sibling())
    {
      folder_name = folder_node->first_node("name")->value();
#if (VERBOSE) 
      std::cout << "Folder : " << folder_name << std::endl;
#endif		

      // Iterate over FOLDER_ID
      for (xml_node<> * folder_id_node = folder_node->first_node("Folder"); folder_id_node; folder_id_node = folder_id_node->next_sibling())
      {
        folder_id = folder_id_node->first_attribute("id")->value();
#if (VERBOSE) 
        std::cout << "\tFolderid : " << folder_id << std::endl;
#endif

        // Iterate over PLACEMARK
        for (xml_node<> * placemark_node = folder_id_node->first_node("Placemark"); placemark_node; placemark_node = placemark_node->next_sibling())
        {
          ss.str("\0");
          ss.seekp(0, std::ios::beg);

          placemark_index = placemark_node->first_node("name")->value();
          placemark_description = placemark_node->first_node("description")->value();
          placemark_coordinates = placemark_node->first_node("Point")->first_node("coordinates")->value();

          json ijson;
          ijson["coordinates"] = placemark_coordinates;                       // WARNING: save before using STRTOK
          token = std::strtok((char *)placemark_coordinates.c_str(), ",");
          ijson["lon"] = atof(token);
          token = std::strtok(NULL, ",");
          ijson["lat"] = atof(token);
          ijson["description"] = placemark_description;

          token = std::strtok((char *)placemark_index.c_str(), " ");
          token = std::strtok(NULL, " ");
          ss << setfill('0') << setw(7) << atoi(token);
          placemark_index = "gps_record_" + ss.str();
          if(outjson.is_array()) outjson.add(ijson);
          else outjson[placemark_index] = ijson;
        }
      }
    }
  }

  output_file << jsoncons::pretty_print(outjson) << std::endl;
  output_file.close();

  return 0;
}

