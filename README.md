# Iteration 1: Creating a Viewport and Rendering an image by lerp a blue sky color over the norm of the ray
The direction vector by default is not normalized (for the sake of speed later on?) but when we enter the ray to color vector we normalize it so that each value becomes in the interval -1/1 we add 1 and multiply by 0.5 so that it becomes between 0 and 1 and we lerp using that.
![image](https://github.com/user-attachments/assets/821746f0-c317-47dc-99fb-4a2df1d068d3)
# Iteration 0: Creating a PPM image and rendering it using the pixel indices
![image](https://github.com/user-attachments/assets/86748ea9-0071-4eeb-bb2e-72c4f209500a)
