#!/bin/bash
CONVERTER="./json2kml.exe"
for json in data/*.json; do
	out="${json%.*}.kml"
	$CONVERTER -i $json -o $out
done
