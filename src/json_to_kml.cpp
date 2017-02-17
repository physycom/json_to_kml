/* Copyright 2015 - Stefano Sinigardi, Alessandro Fabbri */

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
#include <sstream>
#include <vector>
#include "jsoncons/json.hpp"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace jsoncons;
using namespace rapidxml;
using namespace std;

#define MAJOR_VERSION     1
#define MINOR_VERSION     0


int main(int argc, char** argv) {
  // Usage
  std::cout << "json_to_kml v" << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
  std::cout << "Usage: " << argv[0] << " -i [input.json] -o [output.kml]" << std::endl;
  std::cout << "\t- [input.json] json file to parse" << std::endl;
  std::cout << "\t- [output.kml] kml v2.2 file produced by this utility" << std::endl;

  // Parsing command line
  std::string input_name, output_name, outjson_type{};
  if(argc > 2) { /* Parse arguments, if there are arguments supplied */
    for(int i = 1; i < argc; i++) {
      if((argv[i][0] == '-') || (argv[i][0] == '/')) {       // switches or options...
        switch(tolower(argv[i][1])) {
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

  if(input_name.size() > 5) {
    if(input_name.substr(input_name.size() - 5, 5) != ".json") {
      std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
      exit(2);
    }
  }
  else {
    std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
    exit(22);
  }
  input_file.open(input_name.c_str());
  if(!input_file.is_open()) {
    cout << "FAILED: Input file " << input_name << " could not be opened." << endl;
    cout << "Hit ENTER to close.\n"; cin.get();
    exit(222);
  }
  else { cout << "SUCCESS: file " << input_name << " opened!\n"; }
  input_file.close();

  if(output_name.size() > 4) {
    if(output_name.substr(output_name.size() - 4, 4) != ".kml") {
      std::cout << output_name << " is not a valid .kml file. Quitting..." << std::endl;
      exit(3);
    }
  }
  else {
    std::cout << output_name << " is not a valid .kml file. Quitting..." << std::endl;
    exit(33);
  }
  output_file.open(output_name.c_str());
  if(!output_file.is_open()) {
    cout << "FAILED: Output file " << output_name << " could not be opened." << endl;
    cout << "Hit ENTER to close.\n"; cin.get();
    exit(333);
  }
  else { cout << "SUCCESS: file " << output_name << " opened!\n"; }


  string document_name = "json2kml export";
  string folder_name = "Positions";
  string folder_open = "1";
  string subfolder_attribute = "f2/3D";
  string subfolder_name = "2/3D";
  string styleUrl_name = "green_point";
  string styleUrl_value = "#green_point";
  string color_value = "ff00ff00";
  string point_scale = "0.21";
  string href_point_value = "http://maps.google.com/mapfiles/kml/pal2/icon18.png";

  jsoncons::json gps_records = jsoncons::json::parse_file(input_name);

  xml_document<> doc;

  // xml declaration
  xml_node<>* decl = doc.allocate_node(node_declaration);
  decl->append_attribute(doc.allocate_attribute("version", "1.0"));
  decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
  doc.append_node(decl);

  // kml node
  xml_node<>* kml = doc.allocate_node(node_element, "kml");
  kml->append_attribute(doc.allocate_attribute("xmlns", "http://www.opengis.net/kml/2.2"));
  kml->append_attribute(doc.allocate_attribute("xmlns:gx", "http://www.google.com/kml/ext/2.2"));
  kml->append_attribute(doc.allocate_attribute("xmlns:kml", "http://www.opengis.net/kml/2.2"));
  kml->append_attribute(doc.allocate_attribute("xmlns:atom", "http://www.w3.org/2005/Atom"));
  doc.append_node(kml);

  // Document node
  xml_node<>* Document = doc.allocate_node(node_element, "Document");
  kml->append_node(Document);

  // name node
  xml_node<>* documentname = doc.allocate_node(node_element, "name");
  documentname->value(document_name.c_str());
  Document->append_node(documentname);

  // StyleMap node
  xml_node<>* StyleMap = doc.allocate_node(node_element, "StyleMap");
  StyleMap->append_attribute(doc.allocate_attribute("id", styleUrl_name.c_str()));
  Document->append_node(StyleMap);

  // Pair node
  xml_node<>* Pair = doc.allocate_node(node_element, "Pair");
  StyleMap->append_node(Pair);

  // Style node
  xml_node<>* Style = doc.allocate_node(node_element, "Style");
  Pair->append_node(Style);

  // IconStyle node
  xml_node<>* IconStyle = doc.allocate_node(node_element, "IconStyle");
  Style->append_node(IconStyle);

  // color node
  xml_node<>* color = doc.allocate_node(node_element, "color");
  color->value(color_value.c_str());
  IconStyle->append_node(color);

  // scale node
  xml_node<>* scale = doc.allocate_node(node_element, "scale");
  scale->value(point_scale.c_str());
  IconStyle->append_node(scale);

  // Icon node
  xml_node<>* Icon = doc.allocate_node(node_element, "Icon");
  IconStyle->append_node(Icon);
  // href_green_point node
  xml_node<>* href_green_point = doc.allocate_node(node_element, "href");
  href_green_point->value(href_point_value.c_str());
  Icon->append_node(href_green_point);

  // Folder node
  xml_node<>* Folder = doc.allocate_node(node_element, "Folder");
  Document->append_node(Folder);

  // foldername node
  xml_node<>* foldername = doc.allocate_node(node_element, "name");
  foldername->value(folder_name.c_str());
  Folder->append_node(foldername);

  // folderopen node
  xml_node<>* folderopen = doc.allocate_node(node_element, "open");
  folderopen->value(folder_open.c_str());
  Folder->append_node(folderopen);

  // subfolder node
  xml_node<>* subfolder = doc.allocate_node(node_element, "Folder");
  subfolder->append_attribute(doc.allocate_attribute("id", subfolder_attribute.c_str()));
  Folder->append_node(subfolder);

  // subfoldername node
  xml_node<>* subfoldername = doc.allocate_node(node_element, "name");
  subfoldername->value(subfolder_name.c_str());
  subfolder->append_node(subfoldername);


  vector<string> vec_name(gps_records.size());
  vector<string> vec_desc(gps_records.size());
  vector<string> vec_coordinate(gps_records.size());

  if(gps_records.is_array()) { //array-style
    for(size_t in = 0; in < gps_records.size(); in++) {
      vec_name[in] = "index: " + to_string(in);

      if(gps_records[in].has_member("desc"))
        vec_desc[in] = gps_records[in]["desc"].as_string();
      else
        vec_desc[in] = "no_description";

      vec_coordinate[in] = to_string(gps_records[in]["lon"].as_double()) + "," + to_string(gps_records[in]["lat"].as_double());
      if(gps_records[in].has_member("alt"))
        vec_coordinate[in] += "," + to_string(gps_records[in]["alt"].as_double());
      else vec_coordinate[in] += ",0";
    }
  }
  else { //object-style
    int in = 0;
    for(auto rec = gps_records.begin_members(); rec != gps_records.end_members(); ++rec, ++in) {
      vec_name[in] = rec->name();

      if(rec->value().has_member("desc"))
        vec_desc[in] = rec->value()["desc"].as_string();
      else
        vec_desc[in] = "no_description";

      vec_coordinate[in] = to_string(rec->value()["lon"].as<double>()) + "," + to_string(rec->value()["lat"].as<double>());
      if(rec->value().has_member("alt"))
        vec_coordinate[in] += "," + to_string(rec->value()["alt"].as_double());
      else vec_coordinate[in] += ",0";
    }
  }

  for(size_t in = 0; in < gps_records.size(); in++) {
    xml_node<>* Placemark = doc.allocate_node(node_element, "Placemark");
    subfolder->append_node(Placemark);
    // Placemarkname node
    xml_node<>* Placemarkname = doc.allocate_node(node_element, "name");
    Placemarkname->value(vec_name[in].c_str());
    Placemark->append_node(Placemarkname);
    // Placemarkdescription node
    xml_node<>* Placemarkdescription = doc.allocate_node(node_element, "description");
    Placemarkdescription->value(vec_desc[in].c_str());
    Placemark->append_node(Placemarkdescription);
    // styleurl node
    xml_node<>* styleurl = doc.allocate_node(node_element, "styleUrl");
    styleurl->value(styleUrl_value.c_str());
    Placemark->append_node(styleurl);
    // point node
    xml_node<>* point = doc.allocate_node(node_element, "Point");
    Placemark->append_node(point);
    // coordinates node
    xml_node<>* coordinates = doc.allocate_node(node_element, "coordinates");
    coordinates->value(vec_coordinate[in].c_str());
    point->append_node(coordinates);
  }

  std::string xml_as_string;
  // watch for name collisions here, print() is a very common function name!

  rapidxml::print(std::back_inserter(xml_as_string), doc);
  output_file << xml_as_string << std::endl;

  //output_file << doc << std::endl;
  output_file.close();


  return 0;
}

