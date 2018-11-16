#include "hfunction.h"

//为优先队列，重载操作符
bool operator<(const Node &a, const Node &b)
{
	return a.f > b.f;
}

Graph::Graph()
{
	closetable.clear();
	dst = -1;//通过此标记，来查看最后是否问题有解
	memset( map, 0, sizeof(map) );
}

void Graph::input(void)
{
	int i;
	int s, e, v;
	cout << "please input the number of nodes, edges, and the start point in order:" << endl;
	cin >> n >> edges >> src ;
	cout << "please input every edges in this format: start node, end node, edge's value." << endl;
	while( edges-- )
	{
		cin >> s >> e >> v;
		map[ s ][ e ] = map[ e ][ s ] = v;
	}
	return ;
}
/*
*说明：用还没有扩展的节点构成的最小生成树，来作为评估函数
*/
bool Graph::extend(Node start)
{
	int i, j, k, p, min, max;
	int used[ MAXNODE ];
	int choiced[ MAXNODE ];
	int value[ MAXNODE ];
	Node temp;
	vector<int>::iterator iter;
	
	memset( used, 0, sizeof(used) );
	memset( choiced, 0, sizeof(choiced) );
	//memset( value, _MAX, sizeof(value) );
	for(i = 0; i < n; i++)
		value[ i ] = _MAX;

	//找出已经在close表中的节点
	choiced[ start.self ] = 1;
	p = start.parent;
	while( p != -1 )
	{
		choiced[ closetable[ p ].self ] = 1;
		p = closetable[ p ].parent;
	}

	//随便找一个节点不在choiced表中的
	p = -1;
	for(i = 0; i < n; i++)
	{
		if( !choiced[ i ] )
		{
			p = i;
			break;
		}
	}
	//no node for extend, mebey the problem is sloved, haha.
	if(-1 == p)
	{
		return false;
	}
	//对choiced之外的节点运行最小生成树算法
	used[ p ] = 1;
	for(i = 0; i < n; i++)
	{
		if( !choiced[i] && map[ p ][ i ] > 0 )
		{
			value[ i ] = map[ p ][ i ];
		}
	}
	for(i = 1; i < n; i++)
	{
		min = _MAX;
		p = -1;
		for(j = 0; j < n; j++)
		{
			if( (!used[ j ]) && (!choiced[ j ]) && (min > value[ j ]) )
			{
				min = value[ j ];
				p = j;
			}
		}
		if( p == -1)
		{
			break;
		}
		used[ p ] = 1;
		for(j = 0; j < n; j++)
		{
			if( (!used[ j ]) && (!choiced[ j ]) && (map[ p ][ j ]) && (value[ j ] > map[ p ][ j ] ) )
			{
				value[ j ] = map[ p ][ j ];
			}
		}
	}
	
	//the total value of span tree
	max = 0;
	for(i = 0; i < n; i++)
	{
		if( value[ i ] < _MAX )
		{
			max += value[i];
		}
	}

	//以下是扩展节点
	for(i = 0; i < n; i++)
	{
		if( (!choiced[ i ]) && (map[ start.self ][ i ])  )
		{
			Node node;
			
			min = _MAX;
			for(j = 0; j < n; j++)
			{
				if( !choiced[j] && (map[ src ][ j ]) && ( map[ src ][ j ] < min ) )//起点能够到达该点
				{
					min = map[ src ][ j ];	
				}
			}
			if( min == _MAX)//no right path
			{
				continue;
			}

			node.self = i;
			node.parent = closetable.size() -1 ;//记录为closetable中的下标
			node.g = start.g + map[ start.self ][ i ];
			node.h = max + min;
			node.f = node.g + node.h;
#ifdef DEBUG
	cout << "node infomation for in : " << endl;
	cout << "span = " << max << endl;
	cout << "min = " << min << endl;
	cout << "node.self = " << node.self << endl;
	cout << "node.parent = " << node.parent << endl;
	cout << "node.g = " << node.g << endl;
	cout << "node.h = " << node.h << endl;
	cout << "node.f = " << node.f << endl;
	cout << "-----------------------" << endl;
#endif

			//import step is here, mabey this node had in closetable, but is ok.
			opentable.push( node );
		}
	}
	return true;
}

void Graph::astar()
{
	bool result ;
	Node node(src, 0, 0, 0, -1);
	opentable.push(node);

	while( ! opentable.empty() )
	{
		node = opentable.top();
		opentable.pop();
#ifdef DEBUG
	cout << "node infomation for out : " << endl;
	cout << "node.self = " << node.self << endl;
	cout << "node.parent = " << node.parent << endl;
	cout << "node.g = " << node.g << endl;
	cout << "node.h = " << node.h << endl;
	cout << "node.f = " << node.f << endl;
	cout << "+++++++++++++++++++++++" << endl;
#endif
		closetable.push_back( node );
		
		result = extend( node );
		if( !result )
		{
			dst = closetable.size() - 1 ;		
			return ;
		}
	}
}


void Graph::result()
{
	int p;
	if( -1 == dst )
	{
		cout << "sorry this problem is no solution!@_@" << endl;
		return ;
	}
	cout << "total value is : " << closetable[ dst ].f << endl;
	cout << "The path is :" << endl;
	cout << src+1 ;
	p = dst ;
	while( -1 != p)
	{
		cout << " --> " << closetable[ p ].self + 1 ;
		p = closetable[ p ].parent ;
	}
	cout << "\n" << endl;
	return ;
}
