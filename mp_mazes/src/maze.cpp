/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
using namespace std;
using namespace cs225;

SquareMaze::SquareMaze() {
}


void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    // right, down, wall
    int grid = width_*height_;
    DisjointSets disjoint;
    disjoint.addelements(grid);
    // original: has wall
   /* Node* node= new Node(true, true); 
    for(int i = 0; i < grid; i++) {
        maze_.push_back(node);
    }*/
    for (int i = 0; i < grid; i++) {
		right_.push_back(true);
		down_.push_back(true);
	}
    //no more points
    //std::cout << grid << std::endl;
    int count = 0;
    while(count < grid - 1) {
        int x = rand() % width_;
        int y = rand() % height_;
        int link = y * width_ + x;
        int dir = rand();
        if(dir % 2 == 0) {
            // right
            if(x < width_ -1  && disjoint.find(link) != disjoint.find(link + 1)) {
                // no wall
                setWall(x,y,0,false);
                disjoint.setunion(link,link+1);
                count++;
                //std::cout << count << std::endl;
        } 
        } else {
            // down
            if(y < height_ - 1  && disjoint.find(link) != disjoint.find(link + width_)) {
                    // no wall
                    setWall(x,y,1,false);
                    disjoint.setunion(link,link+width_);
                    count++;
            } 
        }
    }



}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    // x in horizon(column)
    // y in vertical(row)
    // true wall, false no wall

    if(dir == 0) {
        if(x == width_ - 1) {return false;}
        return !right_[y*width_ + x] ;
    } else if(dir == 1) {
        if(y == height_ - 1) {return false;}
        return !down_[y*width_ + x] ;
    } else if(dir == 2) {
        if(x == 0) {return false;}
        return !right_[y * width_+ x - 1];
    } else if(dir == 3) {
        if (y == 0) {return false;}
        return !down_[(y-1) * width_ + x];
    }

    return false;
}


PNG* SquareMaze::drawMaze() const {
    PNG* pic = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    HSLAPixel b = HSLAPixel(0,0,0,1);
    // left most column
    for(unsigned w = 10; w < pic -> width(); w++) {
        pic -> getPixel(w,0) = b;
    }
     pic -> getPixel(0,0) = b;
    // top most row
    for(unsigned h = 0; h < pic -> height(); h++) {
        pic -> getPixel(0,h) = b;
    }
    // each square in maze
    for (int i = 0; i < width_ * height_; i++) {
        int x = i % width_;
        int y = i / width_;
			if (!canTravel(x,y,0)) {
				for (int k = 0; k<= 10; k++) {
					pic->getPixel((x + 1) * 10, y * 10 + k) = b;
				}
			}

			if (!canTravel(x,y,1)) {
				for (int k = 0; k <= 10; k++) {
					pic->getPixel(x * 10 + k, (y + 1) * 10) = b;
				}
			}
	}
    return pic;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {

    if(dir == 0) {
        right_[y*width_ + x] = exists;
    } else if(dir == 1) {
        down_[y*width_ + x] = exists;
    }

}

vector<int> SquareMaze::solveMaze() {
    // solve saves the final solution : one route
    // it stores direction
    queue<int> queue;
    queue.push(0);
    // path regarding direction
    vector<int> path(width_*height_,-1);
    // length regarding length
    vector<int> length(width_*height_, -1);
    // prev regarding point
    vector<int> prev(width_*height_,-1);
    int front = 0;
    while(!queue.empty()) {
        front = queue.front();
        queue.pop();
        int y = front / width_;
        int x = front % width_;
                // right
                if(canTravel(x,y,0) && length[front + 1]<0) {
                    queue.push(front + 1);
                    
                    prev[front + 1] = front;
                    length[front + 1] = length[front] + 1;
                    path[front + 1] = 0;

                } 
                // down
                if(canTravel(x,y,1) && length[front + width_] < 0) {
                    queue.push(front + width_);
                    
                    prev[front + width_] = front;
                    length[front + width_] = length[front] + 1;
                    path[front + width_] = 1;
                }
                // left
                if(canTravel(x,y,2) && length[front - 1] < 0) {
                    queue.push(front - 1);
                   
                    prev[front - 1] = front;
                    length[front - 1] = length[front] + 1;
                    path[front - 1] = 2;
                }
                // up
                if(canTravel(x,y,3) && length[front - width_] < 0) {
                    queue.push(front - width_);
                    
                    prev[front - width_] = front;
                    length[front - width_] = length[front] + 1;
                    path[front - width_] = 3;
                    
        }
    }
    // now select the point with longest path
    // search in the last row
    int point = -1;
    int maxl = -1;
    for(int i = width_ * (height_ - 1); i < width_ * height_; i++) {
        if(length[i] > maxl) {
            point = i;
            maxl = length[i];
        }
    }
    

    vector<int> solve;
    while(point > 0) {
        solve.push_back(path[point]);
        point = prev[point];
    }

    reverse(solve.begin(),solve.end());

   return solve;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* pic = drawMaze();
    int x = 5;
    int y = 5;
    HSLAPixel r = HSLAPixel(0,1,0.5);
    vector<int> path = solveMaze();
    for(int i : path) {
        switch(i) {
            case 0://right
            for(int i = 0; i <  11; i++) {
                pic -> getPixel(x+i,y) = r;
            }
            x += 10;
            break;
            case 1://down
            for(int j = 0; j < 11; j++) {
                pic -> getPixel(x,y+j) = r;
            }
            y += 10;
            break;
            case 2: //left
            for(int i = 0; i< 11; i++) {
                pic -> getPixel(x-i,y) = r;
            }
            x -= 10;
            break;
            case 3: // up
            for(int j = 0; j < 11; j++) {
                pic -> getPixel(x,y-j) = r;
            }
            y -= 10;
            break;
        }
    }
    // make exit
    HSLAPixel w = HSLAPixel(0,0,1);
    for(int k = 1; k <=9; k++) {
        pic -> getPixel(x - 5 + k, y + 5) = w;
    }
    return pic;
}
