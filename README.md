---
documentclass: physycomen
title:  "json_to_kml"
author: "Sinigardi"
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


### Input Sample

Object-style:
```
{
    "gps_record_0000001":
    {
        "lat":44.5021611,
        "lon":11.3648926,
        "alt":50.3,
        "description":"TODO"
    },
    "gps_record_0000002":
    {
        "lat":44.5021381,
        "lon":11.3648768
    }
}
```
array-style:
```
[
    {
        "lat":44.5021611,
        "lon":11.3648926,
        "alt":50.3,
        "description":"TODO"
    },
    {
        "lat":44.5021381,
        "lon":11.3648768
    }
]
```

### Output Sample
```
<?xml version="1.0" encoding="utf-8"?>
<kml xmlns="http://www.opengis.net/kml/2.2" xmlns:gx="http://www.google.com/kml/ext/2.2" xmlns:kml="http://www.opengis.net/kml/2.2" xmlns:atom="http://www.w3.org/2005/Atom">
	<Document>
		<name>json2kml export</name>
		<StyleMap id="green_point">
			<Pair>
				<Style>
					<IconStyle>
						<color>ff00ff00</color>
						<scale>0.21</scale>
						<Icon>
							<href>http://maps.google.com/mapfiles/kml/pal2/icon18.png</href>
						</Icon>
					</IconStyle>
				</Style>
			</Pair>
		</StyleMap>
		<Folder>
			<name>Positions</name>
			<open>1</open>
			<Folder id="f2/3D">
				<name>2/3D</name>
				<Placemark>
					<name>Index: 1</name>
					<description>TODO</description>
					<styleUrl>#green_point</styleUrl>
					<Point>
						<coordinates>11.3648926,44.5021611,50.3</coordinates>
					</Point>
				</Placemark>
			</Folder>
		</Folder>
	</Document>
</kml>
```

If no altitude is found in the input.json, a default zero value will be used.

More details can be found in our technical description of the file formats (document still not published)
