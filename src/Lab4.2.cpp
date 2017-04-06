//============================================================================
// Name        : Lab4.cpp
// Author      : Kay Thao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


/**
 * Tracks the state of a single location, including its row and column on the map as well as whether there is a
 * robot or gold at that location. Ensure gold is removed from the map when it is picked up.
 */
class Location {

public:
    bool hasRob;
    /**
     * Super Cool Super Radical Constructor
     */
    Location(int row, int col, char token){
        myRow = row;
        myCol = col;
        myToken = token;
        hasRob = false;
    }

    /**
     * returns the column
     */
    int col(){
       return myCol;
    }

    /**
     * Return a character representing the display value for this location. If it contains a robot, return R.
     * If it contains gold (that has not been picked up), return *. Otherwise, return the character
     * from the input file (space, other punctuation, etc).
     */
    char display(){
        char retTok;
        if (hasRob){
            retTok = 'R';
        } else if (hasMoutain() == true){
            retTok = '#';
        } else if (hasGold() == true){
            retTok = '*';
        }
        return 0;
    }

    /**
     * Track that a robot enters the location.
     */
    void enter(){
        hasRob = true;
    }

    /**
     * Returns true if the location contains gold.
     */
    bool hasGold(){
        bool check = false;
        if (myToken == '*')
            check = true;
        return check;
    }

    /**
     * Returns true if the location contains a mountain.
     */
    bool hasMoutain(){
        bool check = false;
            if (myToken == '#')
                check = true;
        return check;
    }

    /**
     * Returns true if the current cell is occupied either by a mountain or a robot.
     */
    bool occupied(){
        return (hasRob == true || myToken == '#');
    }

    /**
     * The map location for this location of the row.
     */
    int row(){
        return myRow;
    }

    /**
     * Remove the gold from the current location, making the location "empty".
     */
    void takeGold(){
        myToken = ' ';
        bool hasGold();

    }

    /**
     * Track that a robot has left the current location.
     */
    void vacate(){
        hasRob = false;
    }

    char token(){
        return myToken;
    }

    void printMe(){
        cout << "\'"<< myToken << "\' at :(" << myRow << ", " << myCol << ")";
    }



private:
    int myRow;
    int myCol;
    char myToken;

};

/**
 * A map of all locations. Store the locations as a two-dimensional array, probably Locations *locations[HEIGHT][WIDTH].
 */
class Map {

public:

    Location *locations[10][20];     // array of pointers
    int maxNums = 100;               // we have a max of 100 moves
    int row;
    int col;

    Map(){

    }


    /**
     * Return true if a robot can move into a destination location (there's no robot
     * there and no mountain).
     */
    bool canMoveTo(Location* destination){
        bool canMove = true;
        // if we are not at a mountain and we don't have rob, we can move
        if ((destination->token() != '#') || !(destination->hasRob)){
            canMove = true;
        }
        return canMove;
    }

    /**
     * Return the location to the east of the source location, or nullptr if the east
     * is at a wall.
     */

    Location* eastOf(Location* source){
        // Because I don't implement walls I have to pretend that they are there! Rob is smart enough to see that he has reached the ends of the earth!
        int currRow = source->row();       // set your current row
        ++source;                           // look east
        int possNxtRow = source->row();     // set that location in your head
        if (currRow == possNxtRow)          // if we looked east and saw that there was land
            return source;                  // great it's safe to move there
        else
            return NULL;
    }

    /**
     * returns the location at that point
     */
    Location* locationAt(int row, int col){
        return locations[row][col];
    }


    /**
     * Return the location to the north of the source location, or nullptr if that
     * location is a wall.
     */
    Location* northOf(Location* source){

        return  NULL;
    }


    /**
     * Return the location to the south of the source location, or nullptr if that
     * location is a wall.
     */
    Location* southOf(Location* source){
        // return the location+10?
        return  NULL;
    }


    /**
     * Return the location to the west of the source location, or nullptr if that
     * location is a wall.
     */
    Location* westOf(Location* source){
        return  --source;
    }


    /**
     * Write the map to standard output using the same format as load (with the
     * exception that the robot's position is marked by R).
     */
    void write(){
        cout << "+--------------------+" << endl;

        for (int i = 0; i < 10; ++i){
            cout << "|";
                for (int j = 0; j < 20; ++j){
                    char temp = locations[i][j]->token();
                    cout << temp;

                }
                cout << "|" << endl;
            }

        cout << "+--------------------+" << endl;

    }

    /**
     * Read the map from standard input, setting up the location data as required.
     */
    void load(){
        string arrayLines[maxNums]; // this will actaully hold all the needed lines
        string locationLines[9];
        string line;

        getline(cin, line);
        int ptr = 0;
        while (cin) {
            arrayLines[ptr] = line;
            getline(cin, line);
            ++ptr;
        }
        // this loop will remove the locations to a seperate array
        for (int i = 1; i < 10; ++i){
            // cout << arrayLines[i] << endl;
            locationLines[i-1] = arrayLines[i];
        }

        // will now throw into a matrix
        // MatrixAll(arrayLines);
        // cout << arrayLines[13];
        setRobRow(arrayLines[12]);
        setRobCol(arrayLines[12]);
        // getDirections(arrayLines[13]);


    }

    void setRobRow(string locationLine) {
        // cout << "Rob is at: (" << locationLine[0] << ", " << locationLine[2] << ") with "<< "[to be implemented] " << "gold " << endl;
        row = locationLine[0] - 48;
    }

    int getRobRow(){
        return row;
    }

    void setRobCol(string locationLine){
        col = locationLine[2] - 48;

    }

    int getRobCol(){
        return col;
    }

    void getDirections(string directions){
        int len = directions.length();

        for (int i = 0; i < len; ++i){
            if (i % 2 == 0)
                // robot moves here???
                cout << directions[i];
        }

    }

    void MatrixAll(string Array[]){

        for (int i = 1; i <= 10; ++i){
            // this takes the line from the array
            string temp = Array[i];
            for (int j = 1; j <= 20; ++j) {
                // this parses the entire line into it's pieces then to locations
                locations[i-1][j-1] = new Location (i-1, j-1, temp[j]);    // actual location stored
            }

        }

    }


};

/*
 * Tracks the state of a robot including the map the robot is in as well as its current location and the amount
 * of gold the robot has picked up.
 */
class Robot {

public:

    // how do I implement the map???
    Robot(Map* map, int startRow, int startCol){
        myMap = map;
        myRow = startRow;
        myCol = startCol;
    }

    /*
     * Returns the map of the world in which the robot is moving around.
     */
    Map* map(){
        // not sure of functionality
        return NULL;
    }

    char getDirections(){
        char moveSet[];
        return moveSet;
    }

    /**
     * Write the Robot's status to standard output using the format
     * Robot at row, column (amount gold)
     */
    void displayStatus(){
        cout << "Rob is at: (" << myRow << ", " << myCol << ") with "<< "[to be implemented] " << "gold " << endl;
    }

    /**
     * Move the robot one location in the specified direction (east, west, north, south). Returns true if the robot moves,
     * false if moving the robot would make it exit the map or climb a mountain. This method should also ensure the robot
     * picks up any gold that it encounters.
     */
    bool move(char direc){
        bool robMoved = true;
        switch(direc){
            case 'n' :
                // move north
                break;
            case 's' :
                // move south
                break;
            case 'e':
                // move east
                break;
            case 'w':
                // move west
                break;
            default:
                // don't move
                robMoved = false;
        }
        return robMoved;
    }

private:
    Map* myMap;
    int myRow;
    int myCol;

};



int main() {
    Map* mapPntr = new Map;
    mapPntr->load();

    int row = mapper.getRobRow();
    int col = mapper.getRobCol();

    Robot robHasker(mapPntr, row, col);
    Robot robbieChan(mapPntr, row, col);

    return 0;
}

// TODO: Ask: how do we get the robot to move? From here I have loaded in the map and I have all the data in place ready for movment? Some mental barrier?
