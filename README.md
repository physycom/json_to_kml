---
documentclass: physycomen
title:  "json_to_kml"
author: "Fabbri, Sinigardi"
---

<a href="http://www.physycom.unibo.it"> 
<div class="image">
<img src="https://cdn.rawgit.com/physycom/templates/697b327d/logo_unibo.png" width="90" height="90" alt="© Physics of Complex Systems Laboratory - Physics and Astronomy Department - University of Bologna"> 
</div>
</a>
<a href="https://travis-ci.org/physycom/json_to_kml"> 
<div class="image">
<img src="https://travis-ci.org/physycom/json_to_kml.svg?branch=master" width="90" height="20" alt="Build Status"> 
</div>
</a>
<a href="https://ci.appveyor.com/project/cenit/json-to-kml"> 
<div class="image">
<img src="https://ci.appveyor.com/api/projects/status/tk7a69ly5xqm35m7?svg=true" width="90" height="20" alt="Build Status"> 
</div>
</a>


## `json_to_kml`
### Purpose
This tool has been written to convert data to the Keyhole Markup Language format from our .json structure, in order to be able to plot our output with software like Google Earth.


### Installation
**make** and a **C++11** compatible compiler are required. Clone the repo and type ``make`` in your favourite shell, it should be enough in most cases.   
There's also a **VS2015** solution avalaible.   
Contains [jsoncons](https://github.com/danielaparker/jsoncons) and [RapidXml](https://github.com/physycom/rapidxml) as git submodules.

### Usage
```
json_to_kml.exe -i input.json -o output.kml 
```
where `input.json` must be an existing and valid .json file while `output.kml` is the name of the kml v2.2 produced file.
If no altitude is found in the input.json, a default zero value will be used.


## `kml_to_json`
### Purpose
This tool has been written to convert data from the Keyhole Markup Language format to our .json structure, in order to be able to use data coming into .kml format inside our tools.

### Installation
**make** and a **C++11** compatible compiler are required. Clone the repo and type ``make``, it should be enough in most cases!   
There's also a **VS2015** solution avalaible.   
Contains [jsoncons](https://github.com/danielaparker/jsoncons) and [RapidXml](https://github.com/physycom/rapidxml) as git submodules.

### Usage
```
kml_to_json.exe -i input.kml -o output.json -f [output style]
[output style]: 'a' (no quotes) for array or 'o' for object
```
where `input.kml` must be an existing and valid .kml file (versions 2.1 and 2.2 supported) while `output.json` is the name of the output file.
The optional -f specifies the style of the output .json file. If omitted, the object-style will be used.


More details about file formats is available [here](https://github.com/physycom/file_format_specifications/blob/master/formati_file.md).

