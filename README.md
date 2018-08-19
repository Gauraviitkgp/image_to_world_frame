# image_to_world_frame
## Using 1to1 correspondence
Converts the cordinates in image to world frame

To do so, first select and image who has a all points at a single plane with known Z values. Open the using1to1.cpp file and do the following changes

    Change the camera matrix (line number 56)
    Uncomment the distortion coefficients if any
    Draw the 1to1 correspondence of a point in image to its known world cordinates and edit the imagepointpix and objectpointsm in the same 1to1 order
  
After the prelimnary changes for debug mode change the #if statement(line 67) to 
  
    #if 0
    This would change the code to debug mode in which you can check if the code is giving the correct output. Ensure that MIN is less than 100. MIN is the minimum error in pixels. 
For testing mode change it to 
    
    #if 1
    This would change the code to testing mode wherein you can check whether the desired output is correct or not. Each second it will try to take an input and will output Point matrix. If you dont provide input it will take previous inpurs
    Check whether camera_cordinates align with the output you got
 
 ### Run time arguments
 
    argv[1] Source image
    argv[2] Max Iterations 

Change the maximum iterations if the error is greater than 100.

## Using camera cordinates
This file is a general file, if given camera cordinates and (translation matrix or rotation matrix) we can calculate the world cordinates for any given pixel cordinates

Use the formula 

		Camera_cordinates=-rotationMatrix.t()*tvec
   
Any two of this is known and then world cordinates of every pixel of the image could be known

###To do
		Change the Camera matrix(line 37)
		Enter either of two of (camera cordinates rotation matrix or tvec)
		modify the code in accordance with above formula

And TADAAA! check your results. 

## Serious notes
Flat earthies please stay away, earh is not in a single plane, the code may not work for you

