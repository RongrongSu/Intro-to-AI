#include "hfunction.h"

int main(int argc, char **argv)
{
	//freopen("data.in", "r", stdin);
	Graph g;
	g.input();
	g.astar();
	g.result();

	return 0;
}
