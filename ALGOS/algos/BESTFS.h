#ifndef BEST_
#define BEST_

void BESTFS_util(struct qnode_nel& Q, vector<bool>& closed, struct graph &g, bool* isFound , int cnode,int goal, struct node* path, ofstream& f)
{
    if (*isFound == true)
        return;
    
    f << to_string(cnode)<<" ";
    closed[cnode] = true;
    
    struct node* newnode = new node();
    newnode->next= path ;
    newnode->val = cnode;
    path = newnode; 
    

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

        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 &&  closed[i]==0 )
        Q.q.push({ { g.heur[i] , i} ,path  } ); 
         
    }
    
    while(Q.q.size())
    {
        auto x = Q.q.top();
        Q.q.pop();
        if(closed[x.first.second]==false)
        BESTFS_util(Q,closed,g, isFound, x.first.second, goal, x.second,  f);
    }
}

void BESTFS(struct graph & g, int S, int goal, ofstream& f )
{
    vector <bool> visit(g.n) , closed(g.n) ; // closed list
    struct node* path = NULL; // common tree
    bool isFound = false;
    struct qnode_nel Q; // open list
    
    BESTFS_util( Q, closed, g , &isFound ,  S , goal , path,  f );
    f << endl << to_string(S)<< " " << to_string(goal);
}


#endif