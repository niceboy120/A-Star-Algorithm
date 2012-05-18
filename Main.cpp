/** 
*	We need to include many system libraries in order to be able to use certain functionality.
*/
// To output to the console and to accept input;
#include <iostream>
#include <map>
// Using some advanced math operators;
#include <cmath>
// Using the Vector utility. This is a good alternative to normal arrays;
#include <vector>
// Using the Queuing system to form an array with a "first-in-first-out" basis;
#include <queue>
// Just some extra algorithm library; NOT USED SO FAR.
#include <string>
/**
*	Include our own custom made classes and header files.
*	Remember NEVER include a "*.cpp" file. Always include the header files.
*	
*	We need both our Vector2D.h that we made to easily manipulate the x, and y coordinated. And
*	We also need the Heuristic.h file to perform the Heuristic operation and calculations for each open node.
*/
#include "Heuristic.h"
#include "Vector2D.h"
/**
*	We want to use the std namespace;
*	Otherwise we would have to type std::* before all the std namespace functions, and or classes.
*/
using namespace std;
/**
*	Parent Struct
*	This will store the coordinates with it's parent.
*	It will allow us to perform a retrace of the path and actually form it.
*/
struct Parent{
	Vector2D coordinates;
	Vector2D parent;
};

/**
*	Setting up the parent nodes;
*	This will be a 2D array.
*	Array{
*		Parent(Vector2D coord(), Vector2D parent());
*	}
*/
vector<Parent*> parentlist;
/**
*	We need a 2D array map for the grid containing each specialized node.
*	we add the prefix "(char)" before any outputting or using the litteral characters.
*	Otherwise they will be interpretted as numbers because of the "int" type;
*/
int mapGrid[20][20] =
{
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
	{ '#', 'A', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B', '#' },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
};

bool isDiagonal(int x, int y)
{
	if(
		(y == 1 && x == -1) ||
		(y == 1 && x == 2)  ||
		(y == -1 && x == -1)||
		(y == -1 && x == 2)
	)
		return true;
	else
		return false;
}

bool aStar(Vector2D* start, Vector2D* end)
{
	struct score{
		int f_;
		int g_;
		int h_;
		score(int g__, int h__){
			f_ = g__ + h__;
			g_ = g__;
			h_ = h__;
		}
		score(void){}
	};

	struct Point{
		Vector2D* position;
		score f_;
		Point(Vector2D* pos, score g)
		{
			position = pos;
			f_ = g;
		}
		Point(void){}
	};

	struct parent{
		Point parentID;
		Point element;
		parent(Point _parentID, Point _element)
		{
			parentID = _parentID;
			element  = _element;
		}
	};

	vector<Point> openlist;
	vector<Vector2D*> closedlist;
	vector<Vector2D> pathToNode; // Loop through and make the path;
	/**
	*	Setting up the parent array;
	*	We have the a 2D vector array containing the node, and it's parent node; 
	*/
	vector<parent> parentNodes;

	//Scores;
	vector<score> g_score;
	vector<score> h_score;
	vector<score> f_score;
	//vector<score> currentNodeScore;

	//Create a new Heuristic with a bounding value; (Max value)
	Heuristic *h = new Heuristic(19,19);
	//Initialzie the new heuristic from the "start" vector and the "end" vector.
	int heuristic_value = h->find(*start, *end);
	//g_score->insert(pair<Vector2D*, int>(start, 0));
	//h_score->insert(pair<Vector2D*, int>(start, he));
	//f_score->insert(pair<Vector2D*, int>(start, he + 0));

	//Current g_score for the start point;
	//g_score.push_back(score(*start, 0, 0)); //Push a new struct "score" object with a reverse-pointer based Vector2D, and a score of 0;
	//h_score.push_back(score(*start, 0, heuristic_value)); //Push a new struct "score" object with a reverse-pointer based Vector2D, and the new Heuristic score;
	//f_score.push_back(score(*start, 0, heuristic_value)); //Push a new struct "score" object with a reverse-pointer based Vector2D, and add the two previous values together! (** Which is effectivily only the heuristic value)

	openlist.push_back(Point(start, score(0, heuristic_value))); //Add the start point to the openlist.
	/**
	*	We are only looping if the openlist is not empty.
	*	If the openlist is empty then that means we cannot find the end point with the path generated.
	*/
	while(!openlist.size() == 0) 
	{
		//Start with the first one in the list;
		/**
		*	Loop through the Y-axis.
		*/
		int openX = openlist.front().position->getX();
		int openY = openlist.front().position->getY();

		for(int y = 2; y>=-1;y--){
			int nY = y;
			if(nY == 0) continue;
			if(nY == 1) nY = 0;
			if(nY == 2) nY = 1;
			/**
			*	This loops through the X-axis three times each time it loops through a single Y box
			*/
			for(int x = -1; x<=2; x++)
			{
				int nX = x;
				if(nX == 0) continue;
				if(nX == 1) nX = 0;
				if(nX == 2) nX = 1;

				int g_ = 0;
				//Check if we are going diagonally:
				if(isDiagonal(nX, nY))
				{
					g_ = 14;
				}
				else
				{
					g_ = 10;
				}
				
				//Now get the heuristic value;
				int h_ = h->find(Vector2D(openX + nX, openY + nY), *end);
				//Add the current score;
				//currentNodeScore.push_back(score(Vector2D(nX, nY), g_, h_));

				//Some typical debugging purposes!
				//cout << "Y: " << nY << endl;
				//cout << "X: " << nX << endl << endl;
				//End

				//Now let's find those positions;
				Vector2D *adj = new Vector2D(openX + nX, openY + nY);
				//THE BUG IS THE NEXT LINE UNDER THIS; \/
				if(! ((((openX + nX) == 1) && ((openY + nY) == 1)) && (openX == 1 && openY == 1)))
				{
					if((char)mapGrid[adj->getY()][adj->getX()] == '#')
					{
						//Forgot about this vector2D, because it's not a valid (Walkable surface or Vector)
						//Add it to the closed lists;
						closedlist.push_back(adj);
					}
					else
					{
						//Check if this one is in the closed list;
						//for(int pos = 0; pos< closedlist.size(); pos++)
						//{
							//if(closedlist.at(pos)->getX() != adj->getX() && closedlist.at(pos)->getY() != adj->getY())
							//{
								openlist.push_back(Point(adj, score(g_, h_)));
							//}
						//}
					}
				}
			}
			//cout << "==================" << endl;
		}
		
		//Delete the previous object from the openlist and keep it here;
		Point previousObj = openlist.front();
		openlist.pop_back(); //Delete it;

		//Now loop through each
		int lower_score = 0;
		for(int ik = 0; ik<=openlist.size(); ik++)
		{
			if(openlist.size() == 1)
				break;
			//Now check which score is lower;
			if((lower_score == 0 && openlist[ik].f_.f_ > 0) || (openlist[ik].f_.f_ < lower_score && openlist[ik].f_.f_ > 0)){
				lower_score = openlist[ik].f_.f_;
				//cout << lower_score;
			}
			else
				openlist.erase(openlist.begin() + ik, openlist.begin() + 1 + ik); // Delete it
			if(ik == openlist.size())
				ik = 0;
		}
		//Woot Woot!! We got the lowest "F" score; Now hopefully we only have a single element left in the openlist;
		if(openlist.size() == 1)
		{
			//Now add the parent with the proper score (Adding the parent score to this one;
			openlist[0].f_.f_ += previousObj.f_.f_;
			parentNodes.push_back(parent(previousObj, openlist[0]));
			pathToNode.push_back(*(openlist[0].position));
			//cout << openlist[0].position->getY();
		}

		break;
	}

	bool apartOfPath = false;
	for(int height = 0; height<20; height++)
	{
		for(int width = 0;width<20; width++)
		{
			apartOfPath = false;
			//cout << "Height: " << height << " Width: " << width << endl;
			for(int pass = 0; pass<pathToNode.size(); ++pass)
			{
				//cout << pathToNode.at(pass).x << pathToNode.at(pass).y << endl;
				if(width == pathToNode.at(pass).getX() && height == pathToNode.at(pass).getY())
				{
					//cout << "Width: " << width << " Height: " << height << endl;
					//cout << "X: " << pathToNode.at(pass).x << " Y: " << pathToNode.at(pass).y << endl << endl;
					apartOfPath = true;
					break;
				}
			}


			if (width % 20 == 0)
				cout << endl;

			if(apartOfPath == true)
			{
				cout << ">";
			}
			else
			{
				cout << (char)mapGrid[height][width];
			}

		}
	}

	return false;
}

/**
*	Our starting point for our application;
*	We setup the whole algorithm here and bootstrap anything else.
*	The two parameters are for passing arguments through the command line interface. NOT USED.
*/
int main(int argc, char** argv)
{
	/**
	*	Now let's actually start all this path-finding stuff;
	*	We need to call the "aStar" function that accepts two "Vector2D" parameters.
	*/
	Vector2D* start = new Vector2D(1,1);
	Vector2D* end   = new Vector2D(18,18);
	bool done = aStar(start, end);

	if(done)
	{
		//Woot Woot Woot!!
		cout << "The A* path-finding algorithm finished successfully." << endl << endl;
		cout << "Here is the new path: " << endl;
		// Print the new map;
		for(int height = 0; height<20; height++)
		{
			for(int width = 0;width<20; width++)
			{
				if (width % 20 == 0)
					cout << endl;
				cout << (char)mapGrid[height][width];
			}
		}
	}

	//Heuristic *h = new Heuristic(19,19);
	//Vector2D start(1,1);
	//Vector2D end(18,18);
	//Find the Heuristic Value of a specific node; for this example we use the starting node;
	//int a = h->find(*start, *end);
	//cout << a;

	cout << endl;
	cin.get();
	return 0;
}