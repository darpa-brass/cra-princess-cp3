## Sensor noise fields and their effects

The simulator has a simple augmented white noise model that is applied to 
each component sensor individually. The returned value is determined by:

1. With probability `anchorProbability`, send the `anchor` value.

2. Else, send `trueValue + bias + noiseDev * randn()`, where `randn()` is a 
a draw from the standard normal distribution.

The model has four parameters:

1. `bias` -- The bias is added to every measurement. It has the same units 
as the quantity being measured.

2. `noiseDev` -- The standard deviation of a white noise process. That is, a 
standard normal value is drawn, scaled by noiseDev, then added to the 
measurement. It has the same units as the quantity being measured.

3. `anchor` -- Rather than sending the measured and corrupted, send this 
value when the anchor event occurs. This has the same units as the quantity 
being measured. However as this represents an error state, there are no 
bounds on the value other than those imposed by the JSON format (NaN and Inf 
are not allowed).

4. `anchorProbability` -- With this probability, send the `anchor` value 
rather than the measured value.

The available sensors, their units, and reasonable ranges for the values are 
given below.

| Name        | Bias unit   | Bias range   | noiseDev unit   | noiseDev range   |  anchor unit   |
| ----------- | ----------- | ------------ | --------------- | ---------------- | -------------- |
| `dvl_roll`  | Degree      | [-10, 10]    | Degree          | [0, 5]           | Degree         | 
| `dvl_pitch` | Degree      | [-10, 10]    | Degree          | [0, 5]           | Degree         | 
| `dvl_yaw`   | Degree      | [-20, 20]    | Degree          | [0, 10]          | Degree         | 
| `dvl_depth` | Meter       | [-2, 2]      | Meter           | [0, 3]           | Meter          |
| `dvl_altitude` | Meter    | [-2, 2]      | Meter           | [0, 3]           | Meter          |
| `dvl_surge` | Meter/second | [-0.25, 0.25] | Meter/second  | [0, 0.5]         | Meter/second   |
| `dvl_sway`  | Meter/second | [-0.25, 0.25] | Meter/second  | [0, 0.5]         | Meter/second   |
| `dvl_heave` | Meter/second | [-0.25, 0.25] | Meter/second  | [0, 0.5]         | Meter/second   |
| `water_speed` | Meter/second | [-1, 1]   | Meter/second    | [0, 1.2]         | Meter/second   |
| `RPM`       | Rev/minute  | [-20, 20]    | Rev/minute      | [0, 30]          | Rev/minute     |


### Composite values

The values `vN`, `vE`, and `vU` that appear in the `DvlMessage` have more 
complicated error statistics due to how they are produced.  On a step where 
a `DvlMessage` is formed, they are produced as follows.

1. The roll, pitch, yaw, surge, sway, and heave values are drawn using the 
sensor noise model and ground truth as given above.  

2. The body to north-east-down rotation matrix `R` is formed from the 
measured roll, pitch, yaw values.

3. The north, east, down velocities are found by applying `R` to the (surge, 
sway, heave) vector.

4. The down velocity is flipped in sign to give the up velocity.

As can be seen, the e.g. northing velocity can have errors from all six of 
the variables that are used to produce it. The `AffineTransform` class in 
`com.metsci.dynamics.simple` can construct the matrix `R` described above.
