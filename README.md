# Heat_Release_In_a_Closed_Room

This code is part of a paper work done for a school project. The paper talks about analyzing the way we can model the heat release of a heat source to the rest of the room. We are analyzing the system in a steady state, and assuming that no external heat source is involved. That is why we can think of this as taking only a short time frame and assuming how the energy would spread to the rest of the room, given that the source of the heat is no longer available.
Here we have included the C++ code that will simulate this idea and along with that we have included the SDL2 library, which has been used to handle the graphical interface of our program.
We have used Numerical methods to perform the calculation, such as Gauss-Siedel method and also some mathematical transformation to discretely the problem of the heat release.

## Code Implementation

Here we have shown both the gui aspect of our code, which will show every part of the room with a specific color. The lighter the color the higher the temperature of that room area. The number of square that we can separate the room with is a number that we can decide during code compilation. 

Here we have given to examples, the first with a 3 by 3 dimension and the second with a 7 by 7 dimension:

### [3 x 3]
![Capture33](https://user-images.githubusercontent.com/89484377/182245728-4d17b8f9-ad7a-45b0-8776-54d6d1ffbd91.PNG)

### [7 x 7]
![Capture](https://user-images.githubusercontent.com/89484377/182245673-3b40abab-70da-4287-b182-ece496da37a1.PNG)
