Game Structure
===================
**Version: 0.4.1**

Thank you for your interest in my Game Structure program. As the name may suggest, this program allows one to easily create their game concept, building off of a predefined game structure. This allows game design to flow smoothly, even for beginning programmers. Using this structure also helps beginning programmers learn C++, a very popular and powerful programming language. The game provided is an example of what can be done by using this program.

Installation Files:
--------------
*[August 2007 DirectX 9.0c SDK] (http://www.microsoft.com/en-us/download/details.aspx?id=13287)

*[Microsoft Visual C++ 2008 Redistributable] (http://www.microsoft.com/en-us/download/details.aspx?id=29)



How to Use
--------------



1.  void DarkGDK ()

	This is the most important function in the program. Almost everything that occurs in the game, uses this function. The commented sections inside allow the programmer to view their mouse's coordinates on the screen. This can be crucial when needing to know where to place objects.

2. void movePersonOrWorld (int &, int &, int &)

	This function manipulates your current character's x and y coordinates by checking your arrow keys. The function then changes your direction variable in order to send it to our house.checkSpriteCollision function. movePersonOrWorld also checks to see if you're pressing the shift key, and if so, magnifies your movement. After all of that has been done, the function then uses the house.getEvent function to see if you pressed the space bar on something that has an event associated with it. Lastly, the function then updates your world / level with the new information provided.

3. world class

	This is the largest part of the program. Almost everything that happens, excluding movement, uses this class.

4. void world::setWorld(char[], int &, int &)

	This function loads the necessary components for your level. This function can be used by stating:
```
name.setWorld("state name",xCord,yCord)
```
The argument provided in quotations is checked by the function to see if that level has been programmed yet. If so, the function executes all of the operations needed to load the level.

5. void world::updateWorld(int, int)

	This function loads all of the images necessary, and updates the sprite position. 
	
	**NOTE:** if you wish to have your character walk over something, if must be an image. If you wish for your character to walk under something, it must be a sprite.

6. void world::setObject(int,int,int,int)

	This is an essential function in the program. This allows the programmer to set physical boundaries in their game. The first argument is the left x position. This is the x position at the very top left of your object. The second argument is the top y position. This is the y position at the very top left of your object. The third argument is the width of the object. This is how far the object's physical boundaries will expand to the right. The last argument is the height of the object. This is how far the object's physical boundaries will expand downwards.

7. void world::setEvent(int,int,int,int,char[],void(*)(char[], void *))

	This function is much like the setObject function. The first argument is the top left x coordinate. The second argument is the top left y coordinate. The third argument is the width of the event boundaries. The fourth argument is the height of the event boundaries. The fifth argument is the parameter (or phrase) to be sent to the sixth argument, which is your function. The sixth argument takes the contents of the fifth argument as its parameter. For example: the statement 
```
setEvent(193,29,27,34,"characterTV",printText)
```
creates an event boundary starting at 193 x coordinate, 29 y coordinate. The boundaries expand 27 pixels to the right, and 34 pixels downward. If the correct event happens, the string "characterTV" is sent to the printText function.

8. int world::checkSpriteCollision(const int &, const int &)

	This function takes the DarkGDK function's xCord and yCord variables. It then checks to see if there is any overlapping present between your character and any object in the objects array. If there is, it returns a 1. Otherwise, a 0 is returned.  

9. void world::getEvent(const int &, const int &, const int &)

	This function checks to see if there is any event associated with the location that you had your character look at (by pressing the space bar). If so, it executes the function associated with that event, with the correct parameters.

10. void world:: printText(char[], void *)

	This function simply checks the first argument given to it, and if there is a match within its predefined words to look for, displays the correct message and title associated with it on the screen. 
	
	**NOTE:** it is incorrect to send the entire message to the function. The only statement that should be sent to the function is the reference text. 

11. void world::dimArea(char[], void *)

	This function takes a string that states a number, and dims the screen accordingly. The number sent to the function represents the time delay, in milliseconds, between each change for the function. For example: if the time delay sent to the function was 40, the function would wait 40 seconds before making the screen dimmer each time. After the screen is completely dark, the function then waits for 20 * 40 milliseconds (800 milliseconds), then waits another 40 milliseconds after each increment to make the screen lighter again.

12. void world::changeState(char[], void *)

	This function takes the .reference variable (called triggerName), and looks through the events array until it comes across an event with the same .reference name (hence the name "triggerName"). Once the required event is found, it then checks to see which event is requesting the change of state. After this is done, it completes the desired tasks inside the if statement for the given event. 
Example: ``` if(strcmp(triggerName,"roomDoor") == 0) { ```

13. void world::passGuess(char[], void *)

	This function takes a string called "triggerName" much like in our changeState function. The only difference is, this string is actually not used. The only reason that this string is necessary, is to accommodate to the requirements of our getEvent function. The line 
```
events[i].functionCall(events[i].reference, this) 
```
would not work if we did not have an events[i].reference to give it in the first place. Later on though, if needed, the triggerName may be used to allow multiple password guesses. This could possibly come in handy when requiring a password to turn on a certain object in world.

14. void world::endingScreen(void *)

	This function does not take a string, due to the fact that it does not need to comply to the requirements set by the getEvent function. The only argument for this function is a void pointer, which is used to give access to our world class (since the class is static). The main task completed by this function is to display the ending credits after guessing the correct password in our passGuess function. If needed, by changing the line in passGuess calling this function, and by changing both the prototype and actual function parameters to :
```
void world::endingScreen(char NAME[], void *classPointer)
```
it would be possible to make this function comply to the requirements set in our getEvent function. This would allow narration for certain events, or possibly more.

15. objects array

	Our objects array is very unique. It uses a three dimensional array, composed of 60 2x2 arrays. Through this different configuration, it is possible to have our x and y coordinates listed in binary from 0-3. For example: x1 = [0][0], y1 = [0][1], x2 = [1][0], y2 = [1][1]. 

16. events array

	Our events array can easily be broken down into 2 main parts. Our first part, the first four variables, are our location variables. These are x1-y2. Our next part is used for calling the correct function with the correct argument. The void pointer is used to reference our function, and the character array is used to give the function its proper first argument. 

17. checkSpriteCollision if statement

	This is the main part of the checkSpriteCollision function. This statement allows extremely easy checking for in world collision. The syntax to check overlapping in each dimension (length, width, height, etc) is to use the syntax:
``` dimension1 position <= object2 position && dimension2 position >= object1 position ```  
  This is evident from the AND statement:
```
(yCord <= objects[i][1][1]) && ((yCord+32) >= objects[i][0][1])
```
  in which yCord is dimension1, and (yCord+32) is dimension2. 

**NOTE:** dimension1 and dimension2 are not separate dimensions. They are simply used to represent the different variables for a single dimension. Much like x1 and x2.)
This statements works by simply saying that our character's lesser dimension coordinate should not be over our object's greater dimension coordinate. (y1 for the character should not be over y2 for the object). The same thing happens for the character's greater dimension coordinate. The character's greater dimension coordinate should not be over the object's lesser dimension coordinate.

For Learning More Code:
-----------
For more information on how smaller parts of the program work, please see the comments included within the code.

Authors:
----------
Chris McNealy
* [http://www.github.com/ChrisMcNealy] (http://www.github.com/ChrisMcNealy)
	



