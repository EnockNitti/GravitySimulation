# Gravity Simulation

This is a gravity simulation where I tried to optimize for speed and accuracy.
 On my system I get ~15000000 iteration / revolution on a 2 planet system. Revolution time: ~12 S, CPU load ~13% when testing
with a single "planet" in an elliptic  trajectory
 Your mileage may vary. Change TIME_STEP in planet.h to change speed.

In the code are various possible combinations activated with "#if true"s.   
I have added 3 combinations.   
A single planet in an elliptic orbit. Just to check the long term stability.   
A single planet in an circular orbit having a satellite at Lagrange 4. Has long term stability.   
A single planet in an circular orbit having a satellite at Lagrange 2. Despite my fiddling. Runs only for ~1.5 revolution before running off.   

 You need SDL2.lib, SDL2main.lib, zlib1.dll, libpng16-16.dll, SDL2.dll, SDL2_image.dll,
 and SDL-includes to run this when using VS2019

Credit for the basic code to GitHub/Feeeeddmmmeee
