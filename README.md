# indian_traffic_simulator
## Task 2 of the COP290 Course<br>

## Running the Simulator
The config file is provided which sets the various parameters for simulation.
To run the simulation, modify the config file to set your parameters.

### Config File
<table>
  <tr><th> Parameter</th><th>Value</th></tr>
  <tr><td colspan=2 align="center"><h4>Road Properties</h4></td></tr>
  <tr><td>Road_Length</td><td>(int) Sets the length of Road</td></tr>
  <tr><td>Road_Width</td><td>(int) Sets the width of Road</td></tr>
  <tr><td>Road_Signal</td><td>(int) Sets the location of Signal on the Road</td></tr>
  <tr><td>Road_Length</td><td>(int) Sets the length of Road</td></tr>
  <tr><td colspan=2 align="center"><h4>Default Properties</h4></td></tr>
  <tr><td>Default_MaxSpeed</td><td>(int) Sets the <b>maximum speed</b> the vehicles can have on the Road </td></tr>
  <tr><td>Default_Acceleration</td><td>(int) Sets the accelaration of the vehicles</td></tr>
  <tr><td colspan=2 align="center"><h4>Vehicle Properties</h4></td></tr>
  <tr><td>Vehicle_Type</td><td>(string) Sets the type of the vehicle. eg. Car, Bus, Bike, Truck etc.</td></tr>
  <tr><td>Vehicle_Length</td><td>(int) Sets the length of Vehicle</td></tr>
  <tr><td>Vehicle_Width</td><td>(int) Sets the width of Vehicle</td></tr>
  <tr><td>Vehicle_MaxSpeed</td><td>(int) Sets the <b>maximum speed</b> the vehicle can have on the Road</td></tr>
  <tr><td>Vehicle_Acceleration</td><td>(int) Sets the accelaration of the vehicle</td></tr>
  <tr><td colspan=2 align="center"><h4>Simulation Commands</h4></td></tr>
  <tr><td>START</td><td> Simulation Commands will be written below this</td></tr>
  <tr><td><pre> @(int) [RED/GREEN]</pre></td><td> @(int) denotes the column number for the signal eg. <b> @20 RED</b></td></tr>
  <tr><td><pre>(Vehicle Type) COLOR</pre></td><td> eg.<b> Car GREEN</b></td></tr>
  <tr><td><pre>Pass (int) </pre></td><td>where int is the no. of iterations/secs to pass eg. <b> Pass 15</b></td></tr>
  <tr><td>STOP</td><td>End the simulation</td></tr>
</table>

<h3> Notes on the config file</h3>
<ul>
<li>Note that the Speed of the vehicle will be randomly selected between <b>0 to MaxSpeed</b>.
<li>You do not need to provide MaxSpeed and Accelaration for all the vehicles. It will take the default.
<li>Write consecutive Statements under one another for initializing multiple vehicles.
</ul>

### Execution
After setting the config file, run
<pre>$ make
$ ./main.out [INT]</pre>
providing INT as 1 will output in terminal while 2 will show in OpenGL
