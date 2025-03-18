# Iteration 4 Result: A new World
Now that we have the hittable class, we can define a world using hittables, if we define two sphere one small and 1 big we get the following image.
(Notes: Some conventions taken here is that the normals always point against the ray and the normal are always unit vectors)

![image](https://github.com/user-attachments/assets/531757ab-53e1-4491-85d0-b57349f22fa9)


# Iteration 4: Small organization with OOP
Hittable has a virtual = 0 function that MUST be implemented by any class that inherites from it
Sphere has a hit function that uses the equation of a sphere
Hittable_List has a dynamic list of shared pointers that point to Hittable objects

![image](https://github.com/user-attachments/assets/0ecfcb0e-76ac-4af6-86b0-47ebc8da8343)



# Iteration 3: Shading using normal maps
The normal of each point on the surface of the sphere can be seen as the vector going from it's center to the point of impact, when we normalize that vector we'll have each component going from -1 to 1, if we add 1 and multiply by 0.5 we can make them between 0 and 1 and thus we can use those values as colors.

![image](https://github.com/user-attachments/assets/abc4f6fe-c83b-4ef7-aac7-894f20940bdc)
# Iteration 2: Adding the Ray to sphere intersection formula and rendering an image of a sphere

![image](https://github.com/user-attachments/assets/2f57aa34-599b-4aca-bfb1-02578349d4e7)
# Iteration 1: Creating a Viewport and Rendering an image by LERPing a blue sky color over the norm of the ray
The direction vector by default is not normalized (for the sake of speed later on?) but when we enter the ray to color vector we normalize it so that each value becomes in the interval -1/1 we add 1 and multiply by 0.5 so that it becomes between 0 and 1 and we lerp using that.

![image](https://github.com/user-attachments/assets/821746f0-c317-47dc-99fb-4a2df1d068d3)
# Iteration 0: Creating a PPM image and rendering it using the pixel indices
![image](https://github.com/user-attachments/assets/86748ea9-0071-4eeb-bb2e-72c4f209500a)
