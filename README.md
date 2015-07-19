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


Brought to you by:

&copy; _Physics of Complex Systems Laboratory - Physics and Astronomy Department - University of Bologna_
