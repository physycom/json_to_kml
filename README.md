### Installation
**Make** and a **C++11** compatible compiler are required. Clone the repo and type ``make all`` in your favourite shell.

Uses jsoncons library (https://github.com/danielaparker/jsoncons) and RapidXml (http://rapidxml.sourceforge.net/).

### Usage
```
json2kml.exe -i input.json -o output.kml 
```
where *input.json* must be an existing and valid .json file while *output.kml* is the name of the kml v2.2 produced file.


### Input Sample

Object-style:
```
{
    "gps_record_0000001":
    {
        "lat":44.5021611,
        "lon":11.3648926,
        "alt":11.3648926,
        "description":"whatever"
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
        "alt":11.3648926,
        "description":"whatever"
    },
    {
        "lat":44.5021381,
        "lon":11.3648768
    }
]
```

### Output Sample
```
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://www.opengis.net/kml/2.2">
<Document>
  <AnyField> AnyContent </AnyField>
  <Folder>
    <name>Positions</name>
    <Folder id="f2/3D">
      <Placemark>
        <name>Index: 2</name>
        <description> AnyJsonDescriptionFieldFound </description>
        <Point>
          <coordinates>11.3648768,44.5021381,49.3</coordinates>
         </Point>
      </Placemark>
    </Folder>
  </Folder>
</Document>
</kml>
```

If no altitude is found in the input.json, a default zero value will be used.


Brought to you by:

&copy; _Physics of Complex Systems Laboratory - Physics and Astronomy Department - University of Bologna_
