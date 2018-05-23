# image_to_world_frame
Converts the cordinates in image to world frame

To do so, first select and image who has a all points at a single plane with known Z values. Open the pixel_to_world.cpp file and do the following changes

    Change the camera matrix (line number 90)
    Uncomment the distortion coefficients if any
    Draw the 1to1 correspondence of a point in image to its known world cordinates and edit the imagepointpix and objectpointsm in the same 1to1 order
  
After the prelimnary changes for debug mode change the #if statement(line 130) to 
  
    #if 0
    This would change the code to debug mode in which you can check if the code is giving the correct output. Ensure that MIN is less than 100. MIN is the minimum error in pixels. 
For testing mode change it to 
    
    #if 1
    This would change the code to testing mode wherein you can check whether the desired output is correct or not. Each second it will try to take an input and will output Point matrix. If you dont provide input it will take previous inpurs
 
 ## Run time arguments
 
    argv[1] Source image
    argv[2] Max Iterations 

Change the maximum iterations if the error is greater than 100
    
