#include "DarkGDK.h"
#include <string.h>
#include "world.h"

void movePersonOrWorld(int &, int &, int &);
world house;



void DarkGDK ( void )
{
	dbSyncOn   ( );
	dbSyncRate ( 60 );
	dbDisableEscapeKey();
	SetCurrentDirectory("GameContents");
	dbSetWindowTitle("Gaming Level");

	int xCord = 0;
	int yCord = 0;
	int direction = 2; //up = 1, down = 2, left = 3, right = 4;
	int finished = 0; //Used to state whether the game has ended
	
	house.setWorld("stage1",xCord,yCord);	
	dbColorBackdrop(dbRGB(0,0,0));
	house.finishedPntr = &finished;

	while ( LoopGDK ( ) && !finished)
	{
		movePersonOrWorld(xCord, yCord, direction);
		//dbCenterText(510,80,dbStr(dbMouseX()));
		//dbCenterText(550,80,dbStr(dbMouseY()));
		// update the screen
		dbSync ( );
	}

	return;
}


void movePersonOrWorld(int &xCord, int &yCord, int &direction) { //This function checks to see which direction you are planning for your character or world to move in, according to your arrow keys. It then checks to see if there are any collisions, or space bar events, and if not, it updates your new position. 
	if(dbUpKey()==1)
		{
			direction = 1;
			if(dbSpriteFrame(1) < 13) //If our frame for the character is not within its proper regions (In this case, is on a frame that's below our up animation):
			{
				dbSetSpriteFrame(1,13); //Set the first sprite frame to 13, so we can play through the upwards animation correctly.
			}

			if(dbShiftKey() == 1)
			{
				dbPlaySprite(1, 13, 16, 75); //play through our animations (from 13 to 16) with a 75 millisecond delay since we're running.
				if(house.checkSpriteCollision(xCord,yCord-3) == 0) 
				{
					yCord -= 3;
				}
			}
			else
			{
				dbPlaySprite(1, 13, 16, 150); //play through our animations (from 13 to 16) with a 150 millisecond delay because we're walking.
				if(house.checkSpriteCollision(xCord,yCord-1) == 0) 
				{
					yCord --;
				}
			}
		}
		else if(dbDownKey()==1)
		{
			direction = 2; //we set our direction variable to 2, which represents the downward motion.
			if(dbSpriteFrame(1) > 4) //Like before, if our sprite 1 frame is out of its desired regions, then set it to the correct location.
			{
				dbSetSpriteFrame(1, 4);
			}

			if(dbShiftKey() == 1)
			{
				dbPlaySprite(1, 1, 4, 75);
				if(house.checkSpriteCollision(xCord,yCord+3) == 0) 
				{
					yCord += 3;
				}
			}
			else
			{
				dbPlaySprite(1, 1, 4, 150);
				if(house.checkSpriteCollision(xCord,yCord+1) == 0) 
				{
					yCord ++;
				}
			}
		}
		else if(dbLeftKey()==1)
		{
			direction = 3; //Set our variable to 3 which represents leftward motion.
			if(dbSpriteFrame(1) < 5 || dbSpriteFrame(1) > 8)
			{
				dbSetSpriteFrame(1,5);
			}
			if(dbShiftKey() == 1)
			{
				dbPlaySprite(1, 5, 8, 75);
				if(house.checkSpriteCollision(xCord-3,yCord) == 0) 
				{
					xCord -= 3;
				}
			}
			else
			{
				dbPlaySprite(1, 5, 8, 150);
				if(house.checkSpriteCollision(xCord-1,yCord) == 0) 
				{
					xCord --;
				}
			}
		}
		else if(dbRightKey()==1)
		{
			direction = 4; //Set our variable to 4 which represents rightward motion.
			if(dbSpriteFrame(1) < 9 || dbSpriteFrame(1) > 12)
			{
				dbSetSpriteFrame(1,9);
			}
			if(dbShiftKey() == 1)
			{
				dbPlaySprite(1, 9, 12, 75);
				if(house.checkSpriteCollision(xCord+3,yCord) == 0) 
				{
					xCord += 3;
				}
			}
			else
			{
				dbPlaySprite(1, 9, 12, 150);
				if(house.checkSpriteCollision(xCord+1,yCord) == 0) 
				{
					xCord ++;
				}
			}
		}
		if(dbKeyState(57) == 1){ //If we pressed the space bar, check to see if we have an event associated with that object.
			house.getEvent(direction,xCord,yCord);
		}
	house.updateWorld(xCord,yCord); //Now let's update the world with our new information.
}

void world::setWorld(char input[], int &xCord, int &yCord) { //Used to we our current level or stage
	if(strcmp(input,"stage1") == 0) { //If it's equal to stage 1:
		strcpy(currentworld,"stage1"); //Set our current world to stage1
		strcpy(character,"character.png"); //Set our character map to character.png

		dbCreateAnimatedSprite(1,character,4,4,1); //Do our initial setups such as making our sprite sheet usable and setting our x and y coordinates.
		xCord = 150;
		yCord = 50;

		currentX = &xCord;
		currentY = &yCord;

		dbLoadImage("carpet.png",2); //Now we can load out images for later. These images can be used by both sprites and actual pictures.
		dbLoadImage("wall.png",3);
		dbLoadImage("closet.png",4);
		dbLoadImage("bunkBed.png",5);
		dbLoadImage("bedLower.png",6);
		dbLoadImage("characterTV.png",7);
		dbLoadImage("computer.png",8);
		dbLoadImage("mainTV.png",9);
		dbLoadImage("mainTable.png",10);
		dbLoadImage("couch.png",11);
		dbLoadImage("chair.png",12);
		dbLoadImage("kitchenTable.png",13);
		dbLoadImage("kitchenFloor.png",14);
		dbLoadImage("kitchenLeftCounter.png",15);
		dbLoadImage("kitchenRightCounter.png",16);
		dbLoadImage("background.png",17);
		dbLoadImage("doorRight.png",18);
		dbLoadImage("doorLeft.png",19);
		dbLoadImage("mainDoor.png",20);
		dbLoadImage("mainComputer.png",21);
		dbLoadImage("smallTable.png",22);
		dbLoadImage("doorFacing.png",23);
		dbLoadImage("roomDoorFacing.png",24);
		dbLoadImage("roomDoorSide.png",25);

		dbLoadSound("doorOpen.wav",1);
		dbLoadSound("doorClose.wav",2);
		dbLoadSound("silence.wav",3);
		dbLoadSound("TV.wav",4);
		dbLoadSound("mainTV.wav",5);
		dbLoadSound("mainPC.wav",6);
		dbLoadSound("characterComp.wav",7);
		dbLoadSound("sink.wav",8);
		dbLoadSound("fridge.wav",9);
		dbLoadSound("locked.wav",10);
		dbLoadSound("blocked.wav",11);
		dbLoadSound("beep.wav",12);
		dbLoadSound("wrong.wav",13);
		dbLoadSound("correct.wav",14);
		numOfImages = 25;


		//Sprites 2 through 17 are used for the walls. For demonstration on how to set sprites and objects, please see sprite 19+
		dbSprite(2,80,0,3);
		dbSizeSprite(2,15,440);
		setObject(80,0,15,440);

		dbSprite(3,80,0,3);
		dbSizeSprite(3,140,15);
		setObject(80,0,140,15);

		dbSprite(4,170,98,3);
		dbSizeSprite(4,15,47);
		setObject(170,98,15,47);

		dbSprite(5,220,0,3);
		dbSizeSprite(5,15,142);
		setObject(220,0,15,142);

		dbSprite(6,80,130,3);
		dbSizeSprite(6,98,135);
		setObject(80,145,98,120);

		dbSprite(7,227,0,3);
		dbSizeSprite(7,90,280);
		setObject(227,0,90,280);

		dbSprite(8,220,182,3);
		dbSizeSprite(8,30,38);
		setObject(220,182,30,38);

		dbSprite(9,170,185,3);
		dbSizeSprite(9,15,15);
		setObject(170,185,15,15);

		dbSprite(10,170,240,3);
		dbSizeSprite(10,15,113);
		setObject(170,240,15,112);

		dbSprite(12,220,260,3);
		dbSizeSprite(12,30,20);
		setObject(220,260,30,20);

		dbSprite(13,80,430,3);
		dbSizeSprite(13,305,15);
		setObject(80,430,305,15);

		dbSprite(14,376,280,3);
		dbSizeSprite(14,9,20);
		setObject(376,280,9,20);

		dbSprite(15,376,340,3);
		dbSizeSprite(15,9,100);
		setObject(376,340,9,100);

		dbSprite(16,95,110,4);
		dbSizeSprite(16,75,20);

		dbSprite(17,95,25,5);
		dbSizeSprite(17,35,53);

		//Whenever you wish to set object collision checking, you can simply use the setObject function. This function takes 4 arguments. The x1 coordinate, the y1 coordinate, the x length, and the y length. Within these boundaries, it is treated as solid material. Characters cannot walk through these coordinates on the screen.
		//Example: setObject(95,26,33,2) makes an object at x coordinate 95, y coordinate 26, and makes it have a width of 33 pixels and a height of 2 pixels.

		setObject(95,26,33,2); //Character bed top
		setObject(95,26,2,50); //Character bed left side
		setObject(95,74,34,1); //Character bed bottom

		setObject(193,29,27,34); //CharacterTV

		dbSprite(19,160,15,8); //Character computer
		dbSizeSprite(19,28,17); //Makes the image for the sprite stretch to the specifications. The second argument is width, and the third is height.
		setObject(160,15,28,17);

		dbSprite(20,265,303,9); //Character Tv (Rotation involved)
		dbSizeSprite(20,24,37);
		dbRotateSprite(20,-90);

		setObject(265,280,36,23);

		dbSprite(21,263,365,10); //Main table
		dbSizeSprite(21,40,25);
		setObject(263,365,40,25);

		dbSprite(22,95,265,15); //Left counter
		dbSizeSprite(22,21,90);
		setObject(95,265,21,66);

		dbSprite(23,149,265,16); //Right counter
		dbSizeSprite(23,21,90);
		setObject(149,265,21,83);

		setObject(95,384,33,46); //All of this chunk is the kitchen table. One for each. (Round objects to be implemented)
		setObject(95,381,23,3);
		setObject(130,388,2,42);
		setObject(133,391,1,39);
		setObject(136,394,1,36);
		setObject(137,396,1,34);
		setObject(138,397,1,33);
		setObject(139,399,1,31);
		setObject(140,402,1,28);

		dbSprite(24,218,142,18); //Relative room
		dbSizeSprite(24,9,40);
		setObject(220,142,9,40);

		dbSprite(25,218,220,18); //Closet below relative room
		dbSizeSprite(25,9,40);
		setObject(220,220,9,40);

		dbSprite(26,178,145,19); //Upper closet
		dbSizeSprite(26,9,40);
		setObject(178,145,7,40);

		dbSprite(27,178,200,19); //Bathroom
		dbSizeSprite(27,9,40);
		setObject(178,200,7,40);

		dbSprite(28,374,300,20); //Main door
		dbSizeSprite(28,11,40);
		setObject(376,300,9,40);

		dbSprite(29,185,316,21); //Main computer
		dbSizeSprite(29,16,32);
		setObject(185,316,16,32);

		dbSprite(30,360,370,22); //Small table
		dbSizeSprite(30,12,17);
		setObject(360,370,12,17);
		
		dbSprite(31,352,0,3); //Wall to the right of main closet
		dbSizeSprite(31,33,280);
		setObject(352,0,33,280);

		
		dbSprite(32,317,0,3); //Wall behind main closet
		dbSizeSprite(32,35,278);
		setObject(317,0,35,278);

		dbSprite(33,317,268,23); //Closet close to door
		dbSizeSprite(33,35,12);
		setObject(317,268,35,12);

		dbSprite(34,185,98,24); //Character door
		dbSizeSprite(34,35,12);
		setObject(185,98,35,12);

		numOfSprites = 34;

		//Much like the objects, to set an event at a certain coordinate, use the setEvent function. The arguments are the x1 coordinate, the y1 coordinate, the x length, the y length, the argument to be sent to the function, and the actual function name itself. Note: currently, the argument has to be a string.
		//Example: setEvent(80,24,50,54,"bed",printText) makes an event at the x coordinate 80 and y coordinate 24. It has a width of 50 and a height downward of 54. Whenever and event happens, the text "bed"  is sent to the printText function.
		setEvent(80,24,50,54,"bed",printText);
		setEvent(80,24,50,54,"40",dimArea);
		setEvent(193,29,27,34,"characterTV",printText);
		setEvent(160,15,28,17,"characterComputer",printText);
		setEvent(265,279,36,24,"familyTV",printText);
		setEvent(185,316,16,32,"familyComp",printText);
		setEvent(263,365,40,12,"tableFront",printText);
		setEvent(263,378,40,12,"tableBack",printText);
		setEvent(360,370,12,17,"smallTable",printText);
		setEvent(243,400,80,30,"couch",printText);
		setEvent(325,400,45,30,"chair",printText);
		setEvent(317,268,35,12,"mainCloset",printText);
		setEvent(93,375,55,55,"kitchnTable",printText);
		setEvent(95,265,21,22,"counter",printText);
		setEvent(95,288,21,20,"kitchnSink",printText);
		setEvent(95,309,21,23,"counter",printText);
		setEvent(149,265,21,20,"fridge",printText);
		setEvent(149,286,21,20,"counter",printText);
		setEvent(149,307,21,24,"stove",printText);
		setEvent(149,332,21,17,"counter",printText);
		setEvent(178,145,9,40,"upCloset",printText);
		setEvent(218,142,9,40,"upperRoom",printText);
		setEvent(178,200,9,40,"bathroom",printText);
		setEvent(218,220,9,40,"lowCloset",printText);
		setEvent(185,98,35,12,"roomDoor",changeState);
		setEvent(376,300,9,40,"mainDoor",passGuess);
		
	}
}

void world::updateWorld(int xInputCord, int yInputCord) { //Updates the positions for the current stage / level.
	if(strcmp(currentworld,"stage1") == 0) {
		dbPasteImage(2,80,0);
		dbPasteImage(6,130,36);
		dbPasteImage(14,95,265);
		dbPasteImage(11,243,400,1);
		dbPasteImage(12,325,400,1);
		dbPasteImage(13,93,375,1);
		dbPasteImage(7,193,29);
		dbPasteSprite(1, xInputCord, yInputCord);
	}
}

void world::setObject(int x1,int y1,int x2,int y2){ //Increments our index variable, and stores the coordinates in our objects array.
	objectIndex++;
	objects[objectIndex][0][0] =  x1;
	objects[objectIndex][0][1] =  y1;
	objects[objectIndex][1][0] =  (x1+x2); //same as saying x1 + width = x2
	objects[objectIndex][1][1] =  (y1+y2); //same as saying y1 + height = y2
}

void world::setEvent(int x1, int y1, int x2, int y2, char referenceText[], void (*functionCallback)(char[],void *)){ //Increments our index variable, stores the coordinates in our events array, and sets up the appropriate action to happen.
	eventsIndex++;
	events[eventsIndex].x1 =  x1;
	events[eventsIndex].y1 =  y1;
	events[eventsIndex].x2 =  (x1+x2); //same as saying x1 + width = x2
	events[eventsIndex].y2 =  (y1+y2); //same as saying y1 + height = y2

	events[eventsIndex].functionCall = (*functionCallback); //Set our functionCall variable to the correct function.
	strcpy(events[eventsIndex].reference,referenceText); //Set our reference variable equal to the specified argument. This is what is sent to the function.
}

int world::checkSpriteCollision(const int &xCord, const int &yCord) {
			for(int i = 0; i <= objectIndex; i++) {
				if((yCord <= objects[i][1][1]) && ((yCord+32) >= objects[i][0][1]) && (xCord <= objects[i][1][0]) && ((xCord+28) >= objects[i][0][0])) { //This basically checks to see if our character position is overlapping an object's position. 
																																						 //NOTE: For each dimension (such as length, width, height, etc.), the syntax is: dimension1 position <= object2 position && dimension2 position >= object1 position. So if we wanted to do a depth dimension of z, it would be: zCord <= objects[i][1][z2Cord] && (zCord+Length) >= objects[i][0][z1Cord]. This allows easy addition of multiple dimensions. (3D, 4D, etc)
					return 1;
				}
			}
	return 0;
}

void world::getEvent(const int &direction, const int &xCord, const int &yCord) { //Do we have an event at this location?
	if(direction == 1) { //If we're going upwards, set our event test coordinate to be to the right 14 (in the middle of the character), and up 3.
		tempX = xCord+14; 
		tempY = yCord-3;
	}
	else if(direction == 2){ //If we're going downwards, set our event test coordinate to be in the middle of the character, and down 35 (3 below the character)
		tempX = xCord+14;
		tempY = yCord+35;
	}
	else if(direction == 3) { //If we're going leftwards, set our event test coordinate to be 3 to the left of the character, and down 12 (to be at eye level for the character, not halfway)
		tempX = xCord-3;
		tempY = yCord+12;
	}
	else if(direction == 4) { //If we're going rightwards, set our event test coordinate to be 31 to the right (3 to the right of the character), and down 12 again.
		tempX = xCord+31;
		tempY = yCord+12;
	}

	for(int i = 0; i <= eventsIndex; i++) { //Now we check our event test coordinate against our events list.
		if(tempX >= events[i].x1 && tempX <= events[i].x2 && tempY >= events[i].y1 && tempY <= events[i].y2) { //This does the same checking as the checkSpriteCollision function, but just uses a different syntax for our dimensions. Instead of objects[60][2][2], it's events[60].dimension#. objects[i][0][0] = events[i].x1 (the same meaning. NOT the same value)
			events[i].functionCall(events[i].reference, this); //Hey. We have a match! Now let's call the function for that event, with our argument. 
		}
	}
}

void world::printText(char text[], void *classPointer) {
	char title[30]; //Our title for the object.
	char titleRow1[15] = "";
	char titleRow2[15] = "";
	char messageTotal[700]; //Our entire message
	char messageTemp[700]; //Our temp message that is printed to the screen.
	int *currentXCord = static_cast<world*>(classPointer)->currentX; //Our way to get the current xCord of our main class, using a static function. (Uses a class pointer)
	int *currentYCord = static_cast<world*>(classPointer)->currentY;
	int page = 0; //What page are we on? (Index numbered)
	int messageCharLength = 0; //What's the length of our temporary message?
	int totalLength; //The length of our entire message
	int iteration = 0; //Used later to see if we were able to find a space at the end of our text line.
	int numberCharsToEnd = 0; //How many characters are between our \n and the original end of the line?
	char *time = dbGetTime(); //dbGetTime returns the char pointer of a copy of the original time
	*(time+2) = '\0'; //Just an example. Same as "time[2] = '\0'" (educational purposes, and equivalent)
	int hour = atoi(time);
	int numberOfImagesPlus1 = (static_cast<world*>(classPointer)->numOfImages)+1;

	dbSyncOn   ( );
	dbSyncRate ( 60 );


	dbLoadImage("textBackground.png",numberOfImagesPlus1);
	
	if(strcmp(text,"bed") == 0) { //If our event text matches the given text
		strcpy(title,"Bed:");
		strcpy(messageTotal,"I\'m pretty tired. It\'s been a very long ");
		if(hour <= 12) {
			strncat(messageTotal,"morning. ", 9);
		}
		else if(hour >= 13 && hour <= 18) {
			strncat(messageTotal,"day. ",5);
		}
		else {
			strncat(messageTotal,"night. ", 7);
		}
		strncat(messageTotal,"I think I'm going to just take a rest...",40);
		
	}

	else if(strcmp(text,"characterTV") == 0) {
		strcpy(title,"Character\'s TV:");
		strcpy(messageTotal,"Oh. Awesome. My favorite show is on!");
		dbPlaySound(4);
	}

	else if(strcmp(text,"characterComputer") == 0) {
		strcpy(title,"Character\'s Computer:");
		strcpy(messageTotal,"Hm. It\'s been forever since I have done anything productive on here. Where is my flash drive?");
		dbPlaySound(7);
	}

	else if(strcmp(text,"familyTV") == 0) {
		strcpy(title,"Family TV:");
		strcpy(messageTotal,"Yes! Just in time to watch my favorite movie!");
		dbPlaySound(5);
	}

	else if(strcmp(text,"familyComp") == 0) {
		strcpy(title,"Family Computer:");
		strcpy(messageTotal,"What? There's a message from the creator of this game on my facebook: \"Hello. I hope you\'re enjoying the game. I put much time this game... Not sweat though. Programming doesn't usually make you sweat, thank goodness... As I was saying though, hope you're having fun!\"");
		dbPlaySound(6);
	}

	else if(strcmp(text,"tableFront") == 0) {
		strcpy(title,"Living Room Table:");
		strcpy(messageTotal,"The tiles are very smooth, and cold to the touch. Each one has its own wavy pattern to it, as the tiles rise and lower at seemingly random spots. Each appears as if it's slightly warped.");

	}

	else if(strcmp(text,"tableBack") == 0) {
		strcpy(title,"Living Room Table:");
		strcpy(messageTotal,"Where's the TV remote... Oh. Here it is. Now what do I watch though?");
	}

	else if(strcmp(text,"smallTable") == 0) {
		strcpy(title,"Small Table:");
		strcpy(messageTotal,"I'm not actually sure what goes here... poor little table.");
	}

	else if(strcmp(text,"couch") == 0) {
		strcpy(title,"Living Room Couch:");
		strcpy(messageTotal,"This is such a comfy couch. It\'s all cushiony and stuff. The pillows are awesome too. What a nice couch.");
	}

	else if(strcmp(text,"chair") == 0) {
		strcpy(title,"Living Room Chair:");
		strcpy(messageTotal,"The chair seems to radiate fall. It has various patterns, each created by an array of leaves changing their colors. The couch as a whole has a slight orange tint to it, from all of the various leaves... So very poetic!");
	}
	
	else if(strcmp(text,"mainCloset") == 0) {
		strcpy(title,"Living Room Closet:");
		strcpy(messageTotal,"There are several vaious objects behind the door, for no one to see. Not even I know what\'s behind there!");
	}

	else if(strcmp(text,"kitchnTable") == 0) {
		strcpy(title,"Kitchen Table:");
		strcpy(messageTotal,"The kitchen table has several various types of food on it. There are also four plates set out, each at its seemingly designated spot. It must be time for ");
		if(hour <= 11) {
			strncat(messageTotal,"breakfast. ", 11);
		}
		else if(hour >= 12 && hour <= 16) {
			strncat(messageTotal,"lunch. ",7);
		}
		else {
			strncat(messageTotal,"dinner. ", 8);
		}
	}

	else if(strcmp(text,"counter") == 0) {
		strcpy(title,"Kitchen Counter:");
		strcpy(messageTotal,"The counter has a few food items on it, each varying greatly from the other. They almost all seem to be focused around ");
		if(hour <= 11) {
			strncat(messageTotal,"breakfast ", 10);
		}
		else if(hour >= 12 && hour <= 16) {
			strncat(messageTotal,"lunch ",6);
		}
		else {
			strncat(messageTotal,"dinner ", 7);
		}
		strncat(messageTotal,"though. It makes sense, considering the time of day.",52);
	}

	else if(strcmp(text,"kitchnSink") == 0) {
		strcpy(title,"Kitchen Sink:");
		strcpy(messageTotal,"It's so shiny, I can almost see my reflection!...Wow. What a nice looking person!");
		dbPlaySound(8);
	}

	else if(strcmp(text,"fridge") == 0) {
		strcpy(title,"Fridge:");
		strcpy(messageTotal,"There are several different types of food in here...What? There's a note inside: \"Hello player. I hope you're enjoying this level. If this was the first thing that you went to though, I don\'t know what to tell you. Otherwise, congrats on exploring! By the way, remember the number 1433434...\"");
		dbPlaySound(9);
	}

	else if(strcmp(text,"stove") == 0) {
		strcpy(title,"Stove:");
		strcpy(messageTotal,"The stove is off. Good. Those pesky things can get hot sometimes!");
	}

	else if(strcmp(text,"upCloset") == 0) {
		strcpy(title,"Hallway Closet:");
		strcpy(messageTotal,"*Try to turn the door knob* Darn it. It's locked!");
		dbPlaySound(10);
	}

	else if(strcmp(text,"upperRoom") == 0) {
		strcpy(title,"Relative's Room:");
		strcpy(messageTotal,"*Get ready to turn door knob* Well... maybe I should wait to go in here. There's so much more to look at!");
	}

	else if(strcmp(text,"bathroom") == 0) {
		strcpy(title,"Bathroom:");
		strcpy(messageTotal,"Um...I'm not quite sure if I should narrate this... Let's say no for right now...");
	}

	else if(strcmp(text,"lowCloset") == 0) {
		strcpy(title,"Hallway Closet:");
		strcpy(messageTotal,"*Turn the door knob, but can't open the door* What? Seems like something is holding the door back... weird...");
		dbPlaySound(11);
	}



	////////////////////
	//
	//
	//Below is the main part of this function.
	//
	//
	////////////////////








	totalLength = strlen(messageTotal);

	//We're going to perform an initial check through our main message. This will allow us to already have all of the '\n's where they need to be, so we can easily
	//print our the message later. (Without any checking)

	for(int i = 0; i <= totalLength; i++) { //Loop through our main message
		if(((i+1)+numberCharsToEnd) % 29 == 0) { //So if the next character in the string is going to hit the edge (if it's divisible by 29 with no remainders, plus our difference which we'll talk about later.)
			if(messageTotal[i+1] == ' ') { //first check if our next character is a space. If so, then just change it out for a \n
				messageTotal[i+1] = '\n';
			}

			else { //I guess it wasn't. Now let's check to see if there's a space before this, at most 29 characters away. Let's also make sure that we stop if we reach 0. (That means we reached the beginning of the line, and there are no spaces in front of us)
				for(int j = i; j >= 0 && iteration < 29; j--) {
					if(messageTotal[j] == ' ') { //We found a character that's both a space and within our limits! Now we make it \n, tell the program that we found one by setting iteration to 0,
												 //And add the difference between our previous end of line, to our numberCharsToEnd variable.
						messageTotal[j] = '\n';
						iteration = 0;
						numberCharsToEnd = ((i+1)+numberCharsToEnd)-(j+1); //The j-1 makes it so our lines align properly.
						break;
					}
					
					iteration++; //we didn't find any spaces at this character, so let's keep looking. Since I'm looking further, I increment my variable to say how far back I'm looking. (remember 29 max!)
				}
			}

			if(iteration != 0) { //It looks like we didn't find any spaces. I guess we'll have to chop the word in half so it doesn't run off of the page (our only option)

				for(int j = totalLength; j >= i; j--) { //Move everything over to the right by 1.
					messageTotal[j+1] = messageTotal[j];					
				}
				totalLength++; //Remember: by moving everything over by 1, we made the string size 1 larger.
				messageTotal[i] = '\n'; //now insert our \n where we have our emprty space from moving everything over. (Technically our first duplicated space)
				iteration = 0; //Now, make sure to reset our iteration variable.
			}
		}
	}//End for i
	messageTotal[totalLength] = '\0'; //After all of that, we need to remember to have a \0 at the end of our string.

	if(strlen(title) > 15) { //If our title's going to run off of the page, we need to break it in half.
		char *spaceLocation = strchr(title,' ');
		while(strchr(spaceLocation + 1 ,' ') != NULL && (strchr(spaceLocation + 1 ,' ')-title) <= 15) { //Try and make our space cut-off as far on the first line as possible (get as much on the first line as we can)
			spaceLocation = strchr(spaceLocation + 1, ' ');
		}
		strncpy(titleRow1,title,spaceLocation-title); //Copy our first title row
		titleRow1[spaceLocation-title] = '\0';
		strncpy(titleRow2,title+(spaceLocation-title)+1,(strlen(title)-(spaceLocation-title))); //Now our second title row

	}

	dbWait(400);
	while(LoopGDK() && page < 1){ //Now we have to sustain our environment by pasting our images and sprites. Otherwise, they wouldn't stay on the screen as we type our characters.
		dbWait(10); //How quick the message is typed. (the delay)


		static_cast<world*>(classPointer)->updateWorld(*currentXCord,*currentYCord); //Let's send our xCord and yCord that we got to our class.
		dbPasteImage(numberOfImagesPlus1,385,0);

		if(dbKeyState(57) == 1) { //Did we press the space bar?
			dbWait(400);
			page++;
		}

		if(messageCharLength < totalLength) { //Now since we did all of our computation at the beginning, we can now just add characters to the string every time instead of looping through it.
			messageTemp[messageCharLength] = messageTotal[messageCharLength];
			messageTemp[messageCharLength+1] = '\0'; /*
													 NOTE: Since we check to make sure that our object is less than the total length, once it's equal to it, we have already added the \0 ahead of it! (the [messageCharLength+1] part)
													 */
			messageCharLength++;
		}

		if(titleRow1[0] != 0) { //If we had to split our title up
			dbSetTextSize(36);
			dbCenterText(512,12,titleRow1);
			dbCenterText(512,42,titleRow2);
			dbSetTextSize(12);
			dbText(395,85,messageTemp);

		}
		else {
			dbSetTextSize(36);
			dbCenterText(512,12,title);
			dbSetTextSize(12);
			dbText(395,55,messageTemp);
		}
		dbSync();
	}
	dbWait(400);
}

void world::dimArea(char interval[], void *classPointer) {
	int timeInterval = atoi(interval);
	int *currentXCord = static_cast<world*>(classPointer)->currentX; //Get our x coordinate from our class
	int *currentYCord = static_cast<world*>(classPointer)->currentY; //Get our y coordinate from our class
	int numberOfSpritesPlus1 = (static_cast<world*>(classPointer)->numOfSprites)+1;
	int numberOfImagesPlus1 = (static_cast<world*>(classPointer)->numOfImages)+1;

	dbSyncOn   ( );
	dbSyncRate ( 60 );
	dbLoadImage("background.png",numberOfImagesPlus1);
	dbSprite(numberOfSpritesPlus1,0,0,numberOfImagesPlus1);
	dbPlaySound(3);

	for(int i = 0; i < 255 && LoopGDK(); i+=5) { //Make our screen slightly darker each time. The speed is controlled by the timeInterval variable.
		static_cast<world*>(classPointer)->updateWorld(*currentXCord,*currentYCord);
		dbSetSpriteAlpha(numberOfSpritesPlus1,i);
		dbPasteSprite(numberOfSpritesPlus1,0,0);
		dbWait(timeInterval);
		dbSync();
	}

	for(int i = 0; i <= 100 && LoopGDK(); i+=5) { //Keep out screen dark for a little bit
		static_cast<world*>(classPointer)->updateWorld(*currentXCord,*currentYCord);
		dbWait(timeInterval);
		dbSync();
	}

	for(int i = 255; i >= 0 && LoopGDK(); i-=5) { //Now make our screen lighter so we can see again.
		static_cast<world*>(classPointer)->updateWorld(*currentXCord,*currentYCord);
		dbSetSpriteAlpha(numberOfSpritesPlus1,i);
		dbPasteSprite(numberOfSpritesPlus1,0,0);
		dbWait(timeInterval);
		dbSync();
	}

}

void world::changeState(char triggerName[], void *classPointer) {
	int (*objectsPntr)[60][2][2] = &(static_cast<world*>(classPointer)->objects); //So basically we make a pointer that points to a 3 dimensional array (an array of arrays that have arrays inside of them) of [60][2][2]...

	//Now that we have a simple pointer(Which is very small and efficient) to our large multidimensional array, we can now use it later for our changing of the state.

	eventType (*eventsPntr)[60] = &(static_cast<world*>(classPointer)->events); //Make a pointer for our events array

	int *currentXCord = static_cast<world*>(classPointer)->currentX;
	int *currentYCord = static_cast<world*>(classPointer)->currentY;	

	for(int i = 0; i < 60; i++) { //We shuffle through our events array of 60 to see if we can find a match
		if(strcmp((*eventsPntr)[i].reference,triggerName) == 0) { //We need to do: (*eventsPntr)[i].reference for a very simple reason. If it wasn't an array, we could easily use a ->. This is used for pointers of a struct after all. Our array requires the actual value at that memory location though. Now we can do our indexes that we wanted.
			for(int j = 0; j < 60; j++) { //We found a matching event with the required name! Now lets use our number to find it in our objects array.
				if( ((*eventsPntr)[i].x1 == (*objectsPntr)[j][0][0]) && ((*eventsPntr)[i].y1 == (*objectsPntr)[j][0][1]) && ((*eventsPntr)[i].x2 == (*objectsPntr)[j][1][0]) && ((*eventsPntr)[i].y2 == (*objectsPntr)[j][1][1]) ) { //Lets see if we have a match here, between our event coords and our object coords!
							if(strcmp(triggerName,"roomDoor") == 0) {
								if((*objectsPntr)[j][1][0] == ((*objectsPntr)[j][0][0] + 35)) { //So if there's a difference of 35 on our x cords (The door is closed), do our first change:
									if(*currentXCord <= ((*objectsPntr)[j][0][0] + 5)) { //Let's move them out of they way so they don't get stuck in the door.
										*currentXCord = ((*objectsPntr)[j][0][0] + 6);
									}
									dbSprite(34,185,98,25); //Load our new door
									dbSizeSprite(34,6,30);
									(*objectsPntr)[j][1][0] = ((*objectsPntr)[j][0][0] + 5); //Change our object x cord by 5
									(*objectsPntr)[j][1][1] = ((*objectsPntr)[j][0][1] + 30);//Change our object y cord by 30
									(*eventsPntr)[i].x2 = ((*eventsPntr)[i].x1 + 5); //Change our event x cord by 5
									(*eventsPntr)[i].y2 = ((*eventsPntr)[i].y1 + 30); //change our event y cord by 30
									dbPlaySound(1);
								}

								else {  //else, do our second.
									if((*currentYCord <= ((*objectsPntr)[j][0][1] + 12)) && ((*currentYCord+32) >= ((*objectsPntr)[j][0][1] + 12))) { //If they're in the way of the door:
										*currentYCord = ((*objectsPntr)[j][0][1] + 13);
									}
									dbSprite(34,185,98,24); //Now we load our new door
									dbSizeSprite(34,35,12);
									(*objectsPntr)[j][1][0] = ((*objectsPntr)[j][0][0] + 35);
									(*objectsPntr)[j][1][1] = ((*objectsPntr)[j][0][1] + 12);
									(*eventsPntr)[i].x2 = ((*eventsPntr)[i].x1 + 35);
									(*eventsPntr)[i].y2 = ((*eventsPntr)[i].y1 + 12);
									dbPlaySound(2);
								}
							}//End of our roomDoor event
				}
			}
		}
	}
	dbWait(300);//To make sure this function doesn't trigger multiple times when hitting the space bar, we need to add a delay
}

void world::passGuess(char triggerName[], void *classPointer) { 

	int *currentXCord = static_cast<world*>(classPointer)->currentX;
	int *currentYCord = static_cast<world*>(classPointer)->currentY;
	int numbers = 0;
	char messageTotal[150] = "Well you seem to have the\nurge to leave. Why not stay\nfor a bit though? If you\ntruly want to go, then\nsimply guess the password:";
	char messageTemp[150];
	int messageCharLength = 0;
	int totalLength = strlen(messageTotal);
	int numberOfImages = (static_cast<world*>(classPointer)->numOfImages);
	char passwordInput[8] = "";
	int spaceBar = 0;
	int correctPassword = 0;

	dbSyncOn   ( );
	dbSyncRate ( 60 );

	dbLoadImage("textBackground.png",numberOfImages+1);
	dbLoadImage("passwordBackground.png",numberOfImages+2);

	while(LoopGDK() && numbers <= 6){ //Now we have to sustain our environment again.
		dbWait(10); //How quick the message is typed
		//dbCenterText(30,90,dbStr(dbMouseX()));
		//dbCenterText(30,120,dbStr(dbMouseY()));

		static_cast<world*>(classPointer)->updateWorld(*currentXCord,*currentYCord); //Let's send our xCord and yCord that we got to our class.
		dbPasteImage((numberOfImages+1),385,0);
		dbPasteImage((numberOfImages+2),405,200);


		if(messageCharLength < totalLength) { //Just like in our printText function
			messageTemp[messageCharLength] = messageTotal[messageCharLength];
			messageTemp[messageCharLength+1] = '\0';
			messageCharLength++;
		}

		if(dbMouseClick() == 1) {
			if((dbMouseX() >= 449) && (dbMouseX() <= 472) && (dbMouseY() >= 273) && (dbMouseY() <= 297)) { //If our mouse is over the 1 button
				strncat(passwordInput,"1",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 500) && (dbMouseX() <= 523) && (dbMouseY() >= 273) && (dbMouseY() <= 297)) { //If our mouse is over the 2 button
				strncat(passwordInput,"2",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 552) && (dbMouseX() <= 575) && (dbMouseY() >= 273) && (dbMouseY() <= 297)) { //If our mouse is over the 3 button
				strncat(passwordInput,"3",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 449) && (dbMouseX() <= 472) && (dbMouseY() >= 306) && (dbMouseY() <= 330)) { //If our mouse is over the 4 button
				strncat(passwordInput,"4",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 500) && (dbMouseX() <= 523) && (dbMouseY() >= 306) && (dbMouseY() <= 330)) { //If our mouse is over the 5 button
				strncat(passwordInput,"5",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 552) && (dbMouseX() <= 575) && (dbMouseY() >= 306) && (dbMouseY() <= 330)) { //If our mouse is over the 6 button
				strncat(passwordInput,"6",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 449) && (dbMouseX() <= 472) && (dbMouseY() >= 339) && (dbMouseY() <= 363)) { //If our mouse is over the 7 button
				strncat(passwordInput,"7",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 500) && (dbMouseX() <= 523) && (dbMouseY() >= 339) && (dbMouseY() <= 363)) { //If our mouse is over the 8 button
				strncat(passwordInput,"8",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 552) && (dbMouseX() <= 575) && (dbMouseY() >= 339) && (dbMouseY() <= 363)) { //If our mouse is over the 9 button
				strncat(passwordInput,"9",1);
				numbers++;
				dbPlaySound(12);
			}

			else if((dbMouseX() >= 500) && (dbMouseX() <= 523) && (dbMouseY() >= 372) && (dbMouseY() <= 396)) { //If our mouse is over the 0 button
				strncat(passwordInput,"0",1);
				numbers++;
				dbPlaySound(12);
			}
			dbWait(300);
		}

		if(numbers == 7) { //Now let's create a local instance of our world for the new mesage
			strcpy(messageTemp,"");
			if(strcmp(passwordInput,"1433434") == 0) {//Now let's check to see if they got the password correct
				strcpy(messageTotal,"Congratulations! That's\nthe right password!");
				correctPassword++;
				dbInk(dbRGB(0,255,0),dbRGB(0,0,0));
				dbPlaySound(14);
			}
			else {
				strcpy(messageTotal,"Sorry, but that's not the\npassword. Please try again.");
				dbInk(dbRGB(255,0,0),dbRGB(0,0,0));
				dbPlaySound(13);
			}
			totalLength = strlen(messageTotal);
			messageCharLength = 0;
			while(LoopGDK() && spaceBar == 0) {
				dbWait(10);
				static_cast<world*>(classPointer)->updateWorld(*currentXCord,*currentYCord); //Let's send our xCord and yCord that we got to our class.
				dbPasteImage((numberOfImages+1),385,0);
				dbPasteImage((numberOfImages+2),405,200);
				
				if(messageCharLength < totalLength) { //Lets loop through our message again.
					messageTemp[messageCharLength] = messageTotal[messageCharLength];
					messageTemp[messageCharLength+1] = '\0'; 
					messageCharLength++;
				}
				if(dbKeyState(57) == 1) {
					spaceBar++;
				}

				dbSetTextSize(36);
				if(correctPassword == 1) {
					dbCenterText(512,12,"Correct");
					dbCenterText(512,42,"Password!:");

				}
				else {
					dbCenterText(512,12,"Incorrect");
					dbCenterText(512,42,"Password:");
				}
				dbSetTextSize(12);
				dbText(395,85,messageTemp);
				dbSetTextSize(36);
				dbText(455,220,passwordInput);
				dbSync();
			}
			dbInk(dbRGB(255,255,255),dbRGB(0,0,0)); //Now lets return our color back to white.
		}


		else {
			dbSetTextSize(36);
			dbCenterText(512,12,"Guess The");
			dbCenterText(512,42,"Password:");
			dbSetTextSize(12);
			dbText(395,85,messageTemp);
			dbSetTextSize(36);
			dbText(455,220,passwordInput);
			dbSync();
		}
	}
	if(correctPassword == 1){
		for(int i = 0; i <= 100; i++) {
			dbDeleteSprite(i);
			dbSync();
		}
		endingScreen(classPointer); //Go to the ending screen, since you won!

	}
	dbWait(300);	
}

void world::endingScreen(void *classPointer) { //Like a large version of our printText function
	dbWait(500);
	char messageTotal[1000] = "Player...";
	char messageTemp[100] = "";
	int totalLength = strlen(messageTotal);
	int tempLength = 0;
	int iteration = 0;
	int numberCharsToEnd = 0;
	dbSetTextSize(52);
	for(tempLength; LoopGDK() && tempLength <= totalLength; tempLength++) {
		messageTemp[tempLength] = messageTotal[tempLength];
		dbWait(200);
		dbText(200,80,messageTemp);
		dbSync();
	}
	while(dbKeyState(57) != 1) { //Show the message, with the blinking period controlled by your computer time. Waiting for you to press space.
		if((dbTimer()/1000) % 2 == 1)
		{
			messageTemp[tempLength-2] = '\0';
		}
		else {
			messageTemp[tempLength-2] = '.';
		}
		dbCLS();
		dbWait(40);
		dbText(200,80,messageTemp);
		dbSync();
	}
	dbCLS();
	strcpy(messageTotal,"Thank you very much for playing. This game has been coded in C++, one of my favorite languages, and it has been a blast to program. I hope you have enjoyed it as much as I have. I also wish to congratulate you on finding out the password. Either you're amazing at guessing, or you found the secret note... What an odd place to put it too...");
	totalLength = strlen(messageTotal);
	for(int i = 0; i <= totalLength; i++) { //Loop through our main message
		if(((i+1)+numberCharsToEnd) % 26 == 0) { //So if the next character in the string is going to hit the edge (if it's divisible by 26 with no remainders) (Plus our difference which we'll talk about later.
			if(messageTotal[i+1] == ' ') { //first check if our next character is a space. If so, then just change it out for a \n
				messageTotal[i+1] = '\n';
			}

			else { //I guess it wasn't. Now let's check to see if there's a space behind us, at most 26 characters away. Let's also make sure that we stop if we reach 0. (Then no spaces behind us)
				for(int j = i; j >= 0 && iteration < 26; j--) {
					if(messageTotal[j] == ' ') { //We found a character that's both a space and within our limits! Now we make it \n, tell the program that we found one by setting iteration to 0,
												 //And add the difference between our previous end of line, to our numberCharsToEnd variable.
						messageTotal[j] = '\n';
						iteration = 0;
						numberCharsToEnd = ((i+1)+numberCharsToEnd)-(j+1); //The j-1 makes it so our lines align properly.
						break;
					}
					
					iteration++; //we didn't find any spaces this round, so let's keep looking. Since I'm looking further, I increment my variable to say how far back I'm looking. (remember 26)
				}
			}

			if(iteration != 0) { //It looks like we didn't find any spaces. I guess we'll have to chop the word in half so it doesn't run off of the page (our only option)

				for(int j = totalLength; j >= i; j--) { //Move everything over to the right by 1.
					messageTotal[j+1] = messageTotal[j];					
				}
				totalLength++; //Remember: by moving everything over by 1, we made the string size 1 larger.
				messageTotal[i] = '\n'; //now insert our \n where we have our emprty space from moving everything over. (Technically our first duplicated space)
				iteration = 0; //Now, make sure to reset our iteration variable
			}
		}
	}//End for i
	for(int i = 500; i > -720 && LoopGDK(); i-=2) { //Move our text up the screen.
		dbCLS();
		dbWait(40);
		dbText(0,i,messageTotal);
		dbSync();
	}
	strcpy(messageTotal,"Thank you for playing");
	for(int i = 0; i <= 255 && LoopGDK(); i+=5){ //Fade our message in
		dbInk(dbRGB(i,i,i),dbRGB(0,0,0));
		dbCLS();
		dbWait(40);
		dbCenterText(310,150,messageTotal);
		dbSync();
	}
	for(int i = 255; i >= 0 && LoopGDK(); i-=5){ //Fade our message out
		dbInk(dbRGB(i,i,i),dbRGB(0,0,0));
		dbCLS();
		dbWait(40);
		dbCenterText(310,150,messageTotal);
		dbSync();
	}
	*(static_cast<world*>(classPointer)->finishedPntr) = 1; //You WON!!! YAY! Now let's tell the main darkGDK function that you won.

}