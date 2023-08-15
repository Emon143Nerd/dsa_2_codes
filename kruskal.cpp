#include<bits/stdc++.h>
using namespace std;

struct node{
  int parent;
  int rank;
};

struct Edge{
  int src;
  int dst;
  int wt;
};

vector<node> dsuf;
vector<Edge> mst;

int find(int v)
{
  if(dsuf[v].parent==-1)
  {
    return v;
  }
  return dsuf[v].parent = find(dsuf[v].parent); // recursive call to find the root
}

void union_op(int fromP, int toP)
{
  // union by rank
  if(dsuf[fromP].rank>dsuf[toP].rank)//source having higher rank
  {
    dsuf[toP].parent = fromP;
  }
  else if(dsuf[fromP].rank<dsuf[toP].rank) // dst having higher rank
  {
    dsuf[fromP].parent = toP;
  }
  else{  // both having same rank
    dsuf[fromP].parent = toP;
    dsuf[toP].rank++;
  }
}

bool comparator(Edge a, Edge b)
{
  return a.wt<b.wt;
}

void printEdgeList(vector<Edge>&edge_List)
{
  for(auto p: edge_List)
  {
    cout<<"src: "<<p.src<<", dst: "<<p.dst<<", wt"<<p.wt<<endl;
    cout<<"---------------"<<endl;
  }
}

void Kruskals(vector<Edge>&edge_List, int V, int E)
{

  // sort in ascending order by weight
  sort(edge_List.begin(), edge_List.end(), comparator);
  
  int i = 0, j = 0;
  while(i<V-1 && j<E)
  {
    int fromP = find(edge_List[j].src);
    int toP = find(edge_List[j].dst);

    if(fromP == toP)
    {
      ++j;
      continue;
    }

    //else do union operation
    union_op(fromP, toP);
    mst.push_back(edge_List[j]);
    ++i;
    
  }
}

//display the formed MSt
void printMST(vector<Edge> &mst)
{
  cout<<"Mst formed is: "<<endl;
  for(auto p: mst)
  {
    cout<<"Src: "<<p.src<<", dest: "<<p.dst<<", wt: "<<p.wt<<endl;
  }
}


int main()
{
  int E;// no of edges
  int V; // no of vertices

  cout<<"Enter no of edges and vertices : "<<endl;
  cin>>E>>V;

  dsuf.resize(V); // Mark all vertices as separate subsets with only 1 element
  // resize will initialize all the vertices as separate sets
  
  for(int i=0; i<V; i++) // Mark all nodes as independent sets
  {
    dsuf[i].parent = -1;  // initialize parents with -1, which means they are not connected
    dsuf[i].rank = 0; // single element means 0 rank
  }

  vector<Edge> edge_List;
  Edge temp;
  cout<<"Create adjacency list: "<<endl;
  for(int i=0; i<E; i++)
  {
    int from, to, wt;
    cout<<"Enter src, dest and we8: "<<endl;
    cin>>from>>to>>wt;
    temp.src = from;
    temp.dst =to;
    temp.wt = wt;
    edge_List.push_back(temp);
  }

  Kruskals(edge_List,V,E);
  printMST(mst);
  
  
   return 0;
}