#  Beamtracer 
Beamtracer is a raytracer that I implemented by following the Raytracing in 1 weekend book, it allows you to render ppm images that contains spheres of different materials (Glass / Diffuse / Dielectric), Some other features are also implemented such as Antialiasing Gamma correction, and Defocus blur, The camera is also controllable and can move throught the scene.
This is a very basic implementation that is very slow if the number of spheres in the scene increases.

![image](https://github.com/user-attachments/assets/d84fd699-e3ed-4dfa-b166-b5ce431b188e)

# Iteration 9: Adding the Possibility to change camera position 

The idea is to define an orthonormal base around the center of the image, imagine we have two points, the first one is the position of your head's center of mass let's call it lookfrom, now we have where your head is originally looking at let's define a point from the lookfrom to a given point in the direction of the lookat, now we have our first vector in the basis  (which by convention will be from lookat to lookfrom for our basis to be right handed ); Next we need a second vector which MUST be orthonormal to the first, to do that we take a random vector usually called the up vector that  guess what looks up 🤣 and do the cross product betwee it and the first vector and we get our second, the thrid vector will just be the cross product between the two previous ones and will be the true up vector, now the first one will help us define the focal length, the second one help us define the vieport horizental and third one the viewport vertical.

![CameraChange](https://github.com/user-attachments/assets/a07a074f-4ea5-418b-aad3-098aaa49cb91)



# Iteration 8: Adding the Dielectric class
Dielectrics are materials that when light interacts with it gets refracted inside the material, each Dielectric has a specific index, and using Snell's law we can solve for the direction of the reflected ray.
![Reflectance](https://github.com/user-attachments/assets/3e640ebc-0fc6-4f24-8efe-55d731ee5890)


# Iteration 7: (Improvement) Controlling Metal reflectance through fuzziness
![Fuzzz](https://github.com/user-attachments/assets/2cba8cee-81bd-495a-941e-0725897e085a)



# Iteration 7: The Material Class (Lambertian and Metalic)
We create a new class called Material and two other classes that extends and override it, Lambertian and Metalic; They both have an albedo color attribute and a an overridable scatter function that differs from material to the other, for the Lambertian we do the same as previously, we sample a point on the hemisphere centered around the point that we get from adding the normal vector to the point of impact and the the point of impact to the sampled point is our random ray, for the metalic we don't sample random vectors but we use **the Reflection Formula** which works aas follows: we project the incident ray into the normal ray (dot product) this gives us a scalar of how much they're aligned, we use that scalar to scale the normal vector and then we double it and negate it and we add it to the incident vector to get the reflected ray.
![image](https://github.com/user-attachments/assets/7c67abda-8af7-4186-8cd4-a83e5c4ce686)


# Iteration 6: (Improvement) Gamma Correction
Computers expect images to be  gamma corrected, the problem here is that we aren't doing that, we're just calculating the color in what is called linear space and then  writing it into the file, we can see the problem in the file above where there's a very fast trasition between colors in the first part, 0.5% doesn't really look as it should be as the middle point between black and white, to solve this we just pass from linear space to gamma space by calling the square root.
 
![Presentation1](https://github.com/user-attachments/assets/b29634a5-e2ab-441d-9ffb-d14e7cf5ee6f)



# Iteration 6: (Improvement) Lambertian Reflection 
Instead of samling vectors on the hemisphere centered on the impact point, we now apply the normal vector to displace us from the point of impact and we sample vectors fromm that sphere, doing this assures us that we only send our rays in directions close to the normal, since we do this we can see the effect on the shadows since now they'll be bouncing more on the adjacent surfaces instead of randomly which make the shadows darker.

![Presentation1](https://github.com/user-attachments/assets/ecada6f6-65ee-48b5-9b7a-29d9e09a86d6)



# Iteration 6: (Improvement) Shadow Acnee and less child bounces
Since we're using a recurive function to make the bouncing, it's a wise idea to limit the number of bounces to not overflow the stack causing the program to be killed.
Shadow acnee is happening because of float imprecisions, sometimes the ray bounces to the same surface thus causing more loss of energy that shouldn't actually happen, we fix this by ignoring the very close ray bounces.

If the Ray Bounces a lot, it loses energy with each bounce(50%) thus making it blacker (Shadow regions have surfaces that are very close and that occludes each other)
If the Ray Doesn't hit anything we render the gradient.
If the Ray hits only once it keeps most of its energy.

![image](https://github.com/user-attachments/assets/e67d6b0c-d1d1-4d71-ab29-9c092b5515c5)
# Iteration 6: Diffuse Material
Instead of using normal maps as colors, we do some real Ray tracing
We start by camera center, go to the viewport where we choose a center of pixel + some offset for antialiasing, then this ray goes until it meets a surface, if it does it bounces to a random direction recursively until it no longer intersects with anything.. and we do this for all the rays of the vewport.. 
for occluded parts of the scene, there will be a lot of bouncing so it loses almost all the energy, that's why we have shadows.

![image](https://github.com/user-attachments/assets/5c268157-4d05-4637-b4d4-fbb006f3140a)



# Iteration 5 : Less Shaggy pixels ! Antialiasing
What we were doing so far is called point sampling, and it has some flaws (the chessboard example) to solve this we sample n random points for each pixel instead of just the center, we then average the sum of their contributions.

![image](https://github.com/user-attachments/assets/f931aa78-3f92-4ff6-86cf-f9c4768178a7)


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
