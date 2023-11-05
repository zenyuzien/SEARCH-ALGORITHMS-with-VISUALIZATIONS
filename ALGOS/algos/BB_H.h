#ifndef BBH
#define BBH

void BB_H_util(struct graph &g, bool* isFound ,vector<bool> visit, int CC, int cnode,int goal, struct node* path, struct qnode_h &Q, ofstream& f)
{
    if (*isFound == true)
        return;
    
    f << to_string(cnode)<<" ";
    visit[cnode] = true;
    
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

        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 && visit[i]==0   )
        Q.q.push({ {CC + g.arr[cnode][i] + g.heur[i], CC + g.arr[cnode][i]   }, {i,{path,visit} } }); 
         
    }
    
    while (!Q.q.empty())
    {
        if(*isFound==true)
        return;
        auto x = Q.q.top();
        Q.q.pop();
        if(visit[x.second.first]==false)
        BB_H_util(g, isFound, x.second.second.second, x.first.second , x.second.first, goal, x.second.second.first, Q,  f);
    }
}

void BB_H(struct graph & g, int S, int goal, ofstream& f )
{
    vector <bool> visit(g.n);
    struct node* path = NULL; // common tree
    bool isFound = false;
    struct qnode_h Q;
    
    BB_H_util( g , &isFound , visit, 0 , S , goal , path, Q, f );
    f << endl << to_string(S)<< " " << to_string(goal);
}

#endif