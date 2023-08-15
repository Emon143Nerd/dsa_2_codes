#include<iostream>
#include<bits/stdc++.h>
using namespace std;

const int v = 6;

int selectMinVertex(vector<int>&value, vector<bool>&setMST)
{// value contains all the node weights and setMST keeps tracks of included nodes in mst
  int minimum = INT_MAX;
  int vertex;
  for(int i=0; i<v; ++i)
  {
    if(setMST[i]==false && value[i]<minimum)
    {
      vertex = i;
      minimum = value[i];
    }
  }
  return vertex; // return the vertex having the min value which is not stored in MST
}


void findMST(int graph[v][v])
{
  int parent[v]; //storing the mst
  vector<int>value(v,INT_MAX); //used for edge relexation, stores the node values
  vector<bool> setMST(v,false); // true -> vertices that are already included in mst
  
  int minCost = 0;

  // assuming 0 as the starting vertex
  parent[0]  = -1; // 0 has no parent, so it's -1
  value[0] = 0;  // source node  has 0 value

  // form mst with (v-1)  edges
  for(int i= 0; i<v-1; ++i)
  {
    //select best vertex by applying greedy method
    int u = selectMinVertex(value,setMST); // step-1: u is the starting/ src node, now from node u to j and find the apppropriate j with min value of edge
    setMST[u] = true; // step-2: include vertex into the mst

  // relax adjacent vertices ( not visited in mst)
    for(int j=0; j<v; ++j)
    {
      // 3 constraints to relax
      //1. edge is present from u to v
      //2. vertex j is not included in mst
      //3. edge weight is smaller than current edge weight
      if(graph[u][j] !=0 && setMST[j]==false && graph[u][j]<value[j])
      {
        value[j] =graph[u][j];  // update value of j with new min value (graph[u][j])
        parent[j] = u;
      }
    } 
  }

  // find minimum cost
  for(int i = 1; i < v; ++i)
  {
    minCost += graph[parent[i]][i];
  }

  // print MST

  for(int i=1;i<v; ++i)
  {
    cout<<"u->v: "<<parent[i]<<"-"<<i<<" wt = "<<graph[parent[i]][i]<<endl;
  }

  cout<<"Minimum cost  = "<<minCost<<endl;
}


int main()
{
  int graph[v][v] = {
                      {0, 4, 6, 0, 0, 0},
                      {4, 0, 6, 3, 4, 0},
                      {6, 6, 0, 1, 8, 0},
                      {0, 3, 1, 0, 2, 3}, 
                      {0, 4, 8, 2, 0, 7},
                      {0, 0, 0, 3, 7, 0}
                    }; 

  findMST(graph);
   return 0;
}