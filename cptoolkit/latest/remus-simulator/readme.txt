This program generates json scenario files from various fragments.

usage: generator

Generate a JSON scenario from a set of templates plus specified
perturbations.
 -b,--base <BASE>         Base JSON scenario to draw parameters from
 -h                       Print this message
 -i,--initial <E,N,U>     Initial vehicle offset in meters (east, north,
                          up) from coordinate origin. No spaces allowed.
 -o,--output <OUTPUT>     File to output final JSON Scenario to.
 -P <tag=vE,vN,vU>        If tag is found in world data, set the current
                          of that region to vE,vN,vU in m/s
 -s,--sensor <SENSOR>     JSON scenario to draw sensor parameters from.
                          Overrides base and vehicle.
 -v,--vehicle <VEHICLE>   JSON scenario to draw vehicle parameters from.
                          Overrides base.
 -w,--world <WORLD>       JSON scenario to draw world parameters from.
                          Overrides base.


Example:

To builda scenario with an r600, a noisy sensor, two current regions, and alter the
current in region one, do the following:

./bin/generator -b bin/base.json \
	-v vehicle/remus600.json \
	-s sensor/noisySensor.json \
	-w world/twoRegion.json \
	-P r1=1,2 \
	-o test.json

This will produce "test.json" with the current in the region tagged "r1" 
set to 1,2,3.

Metron, Inc. 2016; Please send inquiries to gratton@metsci.com
