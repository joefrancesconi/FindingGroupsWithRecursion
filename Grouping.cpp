/*
 * Name: Joe Francesconi
 * Date Submitted: 2/18/22
 * Lab Section: 005
 * Assignment Name: Finding Groups using recursion
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int ROWS_OF_GRID = 10;
const int COLUMNS_OF_GRID = 10;

//Represents an occupied square in the grid
//Do not modify the GridSquare class or its member functions
class GridSquare
{
    private:
        int row, col;
    public:
        GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square
        GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square
        //Compare with == operator, used in test cases
        bool operator== (const GridSquare r) const
        {
            if ((row == r.row) && (col == r.col))
            {
                return true;
            }
            return false;
        }
        int getRow() { return row; } //return row value
        int getCol() { return col; } //return column value
        //Output using << operator, used in Grouping::printGroups()
        friend ostream& operator<< (ostream& os, const GridSquare obj);
};

//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

/*
Groups squares in 10x10 grid upon construction
Additional private helper functions may be added
Need to implement the constructor that takes a file name
as well as findGroup
The findGroup function's parameter list may be changed based
on how the function is implemented
*/
class Grouping
{
    private:
        int grid[ROWS_OF_GRID][COLUMNS_OF_GRID];
        int place;
        vector<GridSquare> spaces;
        vector<vector<GridSquare>> groups;
    public:
        Grouping() : grid{},groups() {} //Default constructor, no groups
        Grouping(string fileName); //Implement this function
        void findGroup(int r, int c); //Implement this function (recursive)
        void printGroups() //Displays grid's groups of squares
        {
            for(int g=0; g<groups.size(); g++)
            {
                cout << "Group " << g+1 << ": ";
                for(int s=0; s<groups[g].size(); s++)
                {
                    cout << " " << groups[g][s];
                }
                cout << endl;
            }
        }
        vector<vector<GridSquare>> getGroups() //Needed in unit tests
        {
            return groups;
        }
        //reads file and then fills the integer array: grid[10][10]
        void readGrid(string fileName){
            string gLine;
            
            spaces.clear();
            
            ifstream readFile(fileName);
            int i = 0;
            while (getline(readFile, gLine)){
                for (int j = 0; j < gLine.size(); j++){
                    if (gLine[j] != '.'){
                        GridSquare space(i, j);
                        spaces.push_back(space);
                    }
                }
                i++;
            }
            
            readFile.close();
            
            return;
        }
};

//Implement the (parameterized) constructor and findGroup functions below
//constructor for Grouping class
Grouping::Grouping(string fileName){
    vector<GridSquare> singleGroup;
    place = 0;
    
    readGrid(fileName);
    
    while (!spaces.empty()){
        groups.push_back(singleGroup);
        GridSquare n = spaces[0];
                
        findGroup(n.getRow(), n.getCol());
        
        place++;
    }
}

//recursive dfs function to Find values with adjacent values
void Grouping::findGroup(int r, int c){
    //(x,y) -> (x-1,y) || (x,y-1) || (x+1,y) || (x,y+1)
    
    if (r < 0 || r > ROWS_OF_GRID || c < 0 || c > COLUMNS_OF_GRID || grid[r][c] == '.'){
        return;
    }
    
    GridSquare s(r, c);
    for (auto iterator = spaces.begin(); iterator != spaces.end(); ++iterator){
        if (*iterator == s){
            groups[place].push_back(s);
            spaces.erase(iterator);
            
            findGroup(r - 1, c);
            findGroup(r, c + 1);
            findGroup(r + 1, c);
            findGroup(r, c - 1);
            
            return;
        }
    }
    
    
    
    return;
}




//Simple main function to test Grouping
int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}