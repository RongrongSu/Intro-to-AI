
#ifndef _H_
#define _H_

#include <iostream>
#include <string>
#include <queue>
using namespace std;

//#define DEBUG 1
#define MAXNODE 100
#define _MAX 1<<30

class Node
{
	public:
		int self;
		int f, h, g;//for A star algorithm
		int parent;

		Node(){};
		Node(int self, int f, int h, int g, int parent)
		{
			this->self = self;
			this->f = f;
			this->h = h;
			this->g = g;
			this->parent = parent;
		}

};

class Graph
{
	private:
		int n, edges, src, dst;
		vector<Node> closetable;
		priority_queue<Node> opentable;
		int map[ MAXNODE ][ MAXNODE ];
	public:
		Graph();
		void input(void);
		bool extend(Node start);
		void astar(void);
		void result(void);

};

#endif
