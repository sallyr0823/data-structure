/**
 * @file dsets.h
 *
 * Defintion for a class for disjoint set
 * This file, and dsets.cpp follows the instruction under doxygen and AMA slides
 *
 * @author Sally Rong
 * @date Fall 2022
 * 
 * 
 */
#pragma once
#include <vector>
#include <set>
using namespace std;

class DisjointSets {
    /*class SetNode {
        public:
        SetNode();
        SetNode(int value);
        ~SetNode();

        int value_;
        SetNode* parent_;
        
    };*/
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        //void UnionHelper(int s, int l);
        int size(int elem);
        int size_;

    private:
        vector<int> index_;
        //vector<SetNode*> nodes_;
        //int size_ = 0 ;
};