# AnaBarMC
To compile the code type:
make or gmake

To run the event generator type:
root -q GenCosmics.C++

This creates a root file in the data/ directory

To run the simulation interactively type:

AnaBarMC [return]
then at the prompt type:
/control/execute macros/vis.mac

To run the simaultion in batch mode type:

AnaBarMC macros/batch.mac

---Tanner's Comments---

To Run Simulation

>Go into ~/CDetOptical/batch directory and type: "root generate_160.C" to create the primary particle rootfiles that are then store in ~/CDetOptical/batch/data
                                                                                  
>ssh into the jlabanalysis.pcs.cnu.edu machine, then go into the ~CDetOptical/batch directory and type: "./sendjobs.sh runlist160" to send the primary particle rootfiles that are listed in the according runlist file that is sent as an argumant. The output data will be stored in ~/CDetOptical/data

>Once the simulation is run then all 160 output files will be stored in ~CDetOptical/data. Combine them all into one file using ./add_script_tanner_160. The single output file will have a run number of 8888.
                                                                                  
Changing the Primary Particle

>Switch the Generator Function in ~/CDetOptical/batch/GenCosmics.C at line 100

>Change PrimaryParticleID in ~/CDetOptical/AnalyseSignals.C at line 28

>Change PRIMARYPDG in ~/CDetOptical/FitADCSimBrash3.C at line 64

Detector Position and Coordinate Allignment

>X: Length of detector (~50cm for bar(x=-250 to x=250) and ~10cm for trigger paddle(y=-5cm to y=5cm)) 

>Y: Height/Thickness of detector (particles are generated @y=5cm, the Trigger Paddle exitsts from y=4cm to y=3cm, and the bar exists from y=2cm to y=-2cm) 

>Z: Width of detector (depends on #bars, 14 paddles per bar @ 0.5cm per bar) Goes from z=0 to z=-8cm for one bar (14 paddles @ 0.5cm per paddle plus some extra for the thicckness of mylar sheets between each paddle) and half-module goes from z=0 to z=-198 or so

Looking at Data via ROOT

>Open TBrowser and look at TTree sets

>Run AnalyseSignals('run#') and then call plotC1() -> plotC12() 

Analyzing Data with AnalyseSignals.C and FitADCSimBrash3.C

>Both of these programs have been updated to accept a bar number in each of their methods. For the half-module, these bars are ordered 0-13 where bar 0 is the bar beginning at z=0.

>AnalyseSignals.C has 10 plotting methods: plotC#(bar #)

>FitADCSimBrash3.C has two methods: plotC9(bar #) fits the simulated data and plot_adc_fit(pmt #) fits the real-life data
