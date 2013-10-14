class world {
public:
	world();
	void updateWorld(int, int); //Used to update our world, given the direction coordinates from functions such as movePersonOrWorld
	void setWorld(char[], int &, int &); //Says which level you need to load
	int checkSpriteCollision(const int &, const int &); //Do we have a collision present?
	void getEvent(const int &, const int &, const int &); //Is something supposed to happen now?
	int numOfSprites;
	int numOfImages;
	int *finishedPntr; //Used to say whether the program is finished
private:
	struct eventType { //Our event struct simply uses 6 data types. It has 4 integers to represent our x1, y1, x2, and y2 coordinates, 1 void pointer used for function calls, and 1 string of 12 characters.
		int x1;
		int y1;
		int x2;
		int y2;
		void (*functionCall)(char[],void *);
		char reference[30]; //Argument given to the function
	};
	eventType events[60]; //Now we make 60 or so event cases
	int objects[60][2][2]; //This is very important. Our objects array is a 3 dimensional array, composed of 60 2x2 arrays. The x1, x2, y1, and y2 coordinates are numbered in binary, with x1 being [0][0], x2 being [0][1], y1 being [1][0], and y2 being [1][1].
	int eventsIndex; //A variable used to say how many events we have.
	int *currentX; //A pointer for our x coordinate in our main.cpp
	int *currentY; //A pointer for our y coordinate in our main.cpp
	int tempX; //A temporary X cordinate to be used later
	int tempY; //A temporary Y cordinate to be used later
	int objectIndex; //A variable used to say how many objects we have.
	char character[20]; //Used to say the image name for our character sprite sheet
	char currentworld[5];
	void setObject(int,int,int,int);
	void setEvent(int,int,int,int,char[],void(*)(char[], void *));

	//Below are our possible event functions that can be triggered.
	static void printText(char[], void *);
	static void dimArea(char[], void *); //dims the screen
	static void changeState(char[], void *); //change the state for various objects
	static void passGuess(char[], void *);
	static void endingScreen(void *);
};

world::world() { //Our contrsuctor
	objectIndex = -1;
	eventsIndex = -1;
}
	

