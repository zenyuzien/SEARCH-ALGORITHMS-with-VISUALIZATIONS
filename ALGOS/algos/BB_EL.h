#ifndef BBH_
#define BBH_

void BB_EL_util(int& maxora, struct graph &g ,vector<bool> &EL, int CC, int cnode,int goal, struct node* path, struct qnode_nel &Q, ofstream& f)
{
    
    f << to_string(cnode)<<" ";
    
    struct node* newnode = new node();
    newnode->next= path ;
    newnode->val = cnode;
    path = newnode;  
    
    EL[cnode]=true;

    for (int i = 0; i < g.n; i++)
    {
        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 && i==goal)
        {
            newnode = new node();
            newnode->next= path ;
            newnode->val = goal;
            path = newnode; 
            f << to_string(goal)<<" " ;
            print_path(path, CC + g.arr[cnode][goal]);
            if( maxora==0 || CC + g.arr[cnode][goal] < maxora )
            {
                gpath = path ;
                maxora = CC + g.arr[cnode][goal] ;
                continue;
            }
        }

        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 &&  EL[i]==0  )
        if( maxora==0 || (CC + g.arr[cnode][i] < maxora) )
        Q.q.push({ {CC + g.arr[cnode][i] , i} ,path  } ); 
         
    }
    
    while (!Q.q.empty())
    {
        auto x = Q.q.top();
        Q.q.pop();
        if(EL[x.first.second]==false && (maxora ==0 || x.first.first < maxora ))
        BB_EL_util(maxora, g, EL, x.first.first , x.first.second, goal, x.second, Q,  f);
    }
}

void BB_EL(struct graph & g, int S, int goal, ofstream& f )
{
    vector <bool>  EL(g.n) ;
    struct node* path = NULL; // common tree
    struct qnode_nel Q;
    int maxora=  0;
    
    BB_EL_util(maxora, g , EL, 0 , S , goal , path, Q, f );
    display_path(gpath,f);
    f << endl << to_string(S)<< " " << to_string(goal);
}


#endif 