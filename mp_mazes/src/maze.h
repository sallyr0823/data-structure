/**
 * @file maze.h
 * Defintion for a class for disjoint set
 * This file, and maze.cpp follows the instruction under doxygen and AMA slides
 *
 * @author Sally Rong
 * @date Fall 2022
 * 
 * 
 */
#pragma once
#include <vector>
#include <set>
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;

class SquareMaze {
    
    public:
        SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
        void makeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        /*class Node {
            public:
            bool down_;
            bool right_;
            bool visited_ = false;
            Node(bool down, bool right) {
                down_ = down;
                right_ = right;
        }
    };*/
    private:


        int height_;
        int width_;
       // vector<Node*> maze_;
       vector<bool> right_;
       vector<bool> down_;
       


};