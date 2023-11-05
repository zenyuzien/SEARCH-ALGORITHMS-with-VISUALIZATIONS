#ifndef BB_
#define BB_

void BB_util(int& maxora, struct graph &g, vector<bool> visit, int CC, int cnode,int goal, struct node* path, struct qnode &Q, ofstream& f)
{
    
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
            print_path(path,CC + g.arr[cnode][goal]);
            if( maxora==0 || CC + g.arr[cnode][goal] < maxora )
            {
                gpath = path ;
                maxora = CC + g.arr[cnode][goal] ;
                continue;
            }
        }

        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 && visit[i]==0  )
        if( maxora==0 || (CC + g.arr[cnode][i] < maxora) )
        Q.q.push({ {CC + g.arr[cnode][i] , i} ,{path,visit}  } ); 
         
    }
    
    while (!Q.q.empty())
    {
        auto x = Q.q.top();
        Q.q.pop();
        if(visit[x.first.second]==false  && (maxora ==0 || x.first.first < maxora )) 
        BB_util(maxora, g, x.second.second, x.first.first , x.first.second, goal, x.second.first, Q,  f);
    }
}

void BB(struct graph & g, int S, int goal, ofstream& f )
{
    vector <bool> visit(g.n) ;
    struct node* path = NULL; // common tree
    struct qnode Q;
    int maxora = 0 ;
    
    BB_util( maxora, g , visit, 0 , S , goal , path, Q, f );
    display_path(gpath,f);
    f << endl << to_string(S)<< " " << to_string(goal);
    
}

#endif