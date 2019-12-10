# Mattrix #
#### Developed by Matthew Hokinson ####
#### v.1.0 ####

<br/>

## Uses ## 
#### Mattrix #####
This is a Matrix calculator that can handle basic arithmetic operations, along with some other functionality like equation solving, with more features to come in the future. It uses a command line input style to parse through an expression string to either simplify an expression or complete some other operation as given above. It can also suppose regular scalar math in the same way it computes matrix operations. 
Currently, the supported operations are:
1. Expression Simplification 
2. Determinants 
3. Linear Equation Solving
4. Least Square Approximation Solving 

<br/>

## External Libraries Used ##
1. Open Frameworks 
2. ofxDatGUI (openframeworks addon)
3. ofxGUI (openframeworks addon) 
4. Armadillo (Matrix/Scientific Computing Library)

## Compilation Instructions ## 
1. Requirements 
    * Works with MacOS only 
    * Needs XCode GUI IDE 
    * Need to download and install Armadillo Library (instructions can be found on their website) 
    * Need to download current OpenFrameworks release 
    * Need to download ofxDatGUI (from github, link found on ofxAddons website)
        *  Be sure to add ofxDatGUI (Drag the cloned directory) to the addons directory in the open frameworks folder that was downloaded. 

2. Setup 
    *  After cloning, open the openFrameworks Project Generator and select the Mattrix project, then the update option should appear with the addons (listed above). Then, click update, and open in IDE (You should have XCode installed) 
    *  Now, you need to link Armadillo, which should have been installed using the instructions on the website (Found in the README file on the github link) 
        * To do this, find the linker tags in the build settings, then add the tag -larmadillo
        * Then, find the Searth Paths options, then add the paths to the include and lib files to Header and Library search paths respectively. (For me, these are /usr/local/include and /usr/local/lib)
        
3. Compiling and Running 
    * Your project should be able to compile at this time. However, if you get an issue with duplicates in the main function, go to the build phases page of the project settings. There, make sure to find the tests-main.cpp file, and any other labeled *test.cpp, and delete if from the compile sources section. 
    * Finally, you will need to drag the ofxbraitsch directory to the bin/data/ directory in the project.
