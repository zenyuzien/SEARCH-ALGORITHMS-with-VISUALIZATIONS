#ifndef BS_
#define BS_


void BS_util(struct graph &g, bool* isFound ,vector<bool> visit,  int cnode,int goal, struct node* path, ofstream& f, int bw)
{
    if (*isFound == true)
        return;
    
    f << to_string(cnode)<<" ";
    visit[cnode] = true;
    
    struct node* newnode = new node();
    newnode->next= path ;
    newnode->val = cnode;
    path = newnode; 
    
    struct qnode Q;

    for (int i = 0; i < g.n; i++)
    {
        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 && i==goal)
        {
            newnode = new node();
            newnode->next= path ;
            newnode->val = goal;
            path = newnode; 
            f << to_string(goal)<<" " ;
            display_path(path,f);
            *isFound = true;
            return;
        }

        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 && visit[i]==0  )
        Q.q.push({ { g.heur[i] , i} ,{path,visit}  } ); 
         
    }
    
    int cnt = bw;
    while(Q.q.size() && cnt)
    {
        cnt--;
        auto x = Q.q.top();
        Q.q.pop();
        if(visit[x.first.second]==false)
        BS_util(g, isFound, x.second.second, x.first.second, goal, x.second.first,  f, bw);
    }
}

void BS(struct graph & g, int S, int goal, ofstream& f )
{
    vector <bool> visit(g.n) ;
    struct node* path = NULL; // common tree
    bool isFound = false;
    cout << "Enter beam width \n";
    int bw ;
    cin >> bw ; 
    
    BS_util( g , &isFound , visit, S , goal , path,  f , bw);
    f << endl << to_string(S)<< " " << to_string(goal);
}


#endif