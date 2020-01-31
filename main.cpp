//
//  main.cpp
//  Game_of_life_cplus
//
//  Created by Mohammad Jabeen on 24/01/2020.
//  Copyright © 2020 Mohammad Jabeen. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <map>
#include <unistd.h>
#include <fstream>
#include <string>


using namespace std;
int** dead_state(int,int);
int** random_state(int**,int,int);
int** next_state(int**,int,int);
int calculate_circle(int,int,int**,int,int);
int rule_check(int,int);
void render_output(int**,int,int);
int ** read_from_file(string,int,int);

int main(int argc, const char * argv[]) {

    int height = 0;
    int width = 0;
    bool choice;
    string val;
    string fileadd = "/Users/Momo/Documents/Practise_Projects/Game_of_life_cplus/Game_of_life_cplus/";
    string filename;
    ifstream infile;

    int ** grid;
    
    cout << "HELLO AND WELCOME TO THE GAME OF LIFE, (1) RANDOM or (0) FILE:\n";
    cin >> choice;
    
    if (choice)
    {
        cout << "PLEASE ENTER WIDTH AND HEIGHT\n";
        cout << "WIDTH:";
        cin >> width;
        cout << "HEIGHT:";
        cin >> height;
        
        grid = dead_state(width, height);
        grid = random_state(grid, width, height);
            
    }
    else
    {
        
        cout << "PLEASE ENTER FILE NAME:";
        cin >> filename;
        
        infile.open(fileadd + filename);

        if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
        }

        while(infile >> val)
        {
            height++;
        }
      
        width = val.size();
        infile.close();
        
        grid = read_from_file(fileadd+filename, width, height);
    
    }

    render_output(grid, width, height);
    while (1)
    {
        grid = next_state(grid, width, height);
        render_output(grid, width, height);
        sleep(2);
    }

    return 0;
}

int** dead_state(int width, int height)
{
    int ** grid = new int*[height];
    for (int i = 0; i< height; i++)
        grid[i] = new int[width];
    
    for (int i = 0; i< height;i++)
    {
        for(int j =0; j < width; j++)
        {
            grid[i][j] = 0;
        }
    }
    
    return grid;
}

int** random_state(int ** grid, int width, int height)
{
    for (int i = 0; i< height;i++)
    {
        for(int j =0; j < width; j++)
        {
            grid[i][j] = rand()%2;      //Uses seed controlled using srand()
        }
    }
    
    return grid;
}

int** next_state(int** grid,int width, int height)
{
    int ** newgrid = dead_state(width, height);
    int numboflive = 0;
    
    for(int i =0; i < height; i++)
    {
        for(int j = 0; j< width; j++)
        {
             numboflive = calculate_circle(i,j,grid, width, height);
            newgrid[i][j] = rule_check(numboflive,grid[i][j]);
        }
    }
    
    return newgrid;
}

int calculate_circle(int i, int j, int** grid, int width, int height)
{
    int numboflive = 0;
    if ((i-1)>=0)
        if (grid[i-1][j])
            numboflive ++;
    if ((i-1)>=0 && (j+1)< width)
         if (grid[i-1][j+1])
             numboflive ++;
    if ((j+1)< width)
         if (grid[i][j+1])
             numboflive ++;
    if ((i+1)<height && (j+1)<width)
         if (grid[i+1][j+1])
             numboflive ++;
    if ((i+1)< height)
         if (grid[i+1][j])
             numboflive ++;
    if ((i+1)< height && (j-1)>= 0)
         if (grid[i+1][j-1])
             numboflive ++;
    if ((j-1)>=0)
         if (grid[i][j-1])
             numboflive ++;
    if ((i-1)>=0 && (j-1)>=0)
         if (grid[i-1][j-1])
             numboflive ++;
    
    return numboflive;
}

int rule_check(int numboflive, int cell)
{
    if (cell)
    {
        if (numboflive <=1)
            return 0;
        else if (numboflive >= 2 && numboflive <= 3)
            return 1;
        else
            return 0;
    }
    else
    {
        if (numboflive ==3)
            return 1;
        else
            return 0;
    }
}

int** read_from_file(string filename, int width, int height)
{
    int ** grid;
    string val;
    ifstream infile;

    grid = dead_state(width, height);
    infile.open(filename);
    
    int j = 0;
    int i =0;

    while(infile >> val)
    {
        for(j =0; j < (width-1) ; j++)
        {
            if (val[j] == '1')
                grid[i][j] = 1;
            else
                grid[i][j] = 0;
        }
        i++;
    }    
    return grid;
}

void render_output(int** grid, int width, int height)
{
    map<int,string> ouput_lookup = {{0," "}, {1,"\u2588"}};
	int i = 0;
	string starter = "";
	string middle ="";
	string end = "";
	for(i =0; i< width; i++)
		starter += "-";
    starter += "\n";
	cout << starter;
	for (i =0 ; i < height ; i++)
    {
        for (int j =0; j < width ; j++)
        middle += ouput_lookup[grid[i][j]];
        //middle += grid[i][j];
        middle += "\n";
		cout << middle;
		middle ="";
    }
	cout << starter;
}
