#ifndef DFS_
#define DFS_

void DFS_util(stack<pair<int,pair<struct node*,vector<bool>>>>&q, struct graph& g, int cnode, int goal, vector<bool> visit, struct node* path, bool &isFound, ofstream&f )
{
    if(isFound==true)
    return ;

    f<< to_string(cnode) << " ";
    
    visit[cnode]=true;
    
    struct node* newnode = new node();
    newnode->next= path ;
    newnode->val = cnode;
    path = newnode;
    
    for(int i = 0 ; i < g.n; i++)
    {
        if( i != cnode && g.arr[cnode][i] && visit[i]==false)
        {
            if(i==goal)
            {
                isFound= true;
                struct node* newnode = new node();
                newnode->next= path ;
                newnode->val = goal;
                path = newnode;
                f<< to_string(goal) << " ";
                display_path(path,f);
                return;
            }
            
            else
            {
                if(isFound==false)
                q.push({i,{path,visit}});
                
            }
        }
    }

    while(q.size())
    {
        auto x = q.top();
        q.pop(); 
        DFS_util(q,g,x.first,goal,x.second.second,x.second.first,isFound,f);
    }
    
}

void DFS(struct graph & g, int st, int gt, ofstream& f)
{
    vector<bool> visit(g.n);
    struct node* path =NULL ;
    bool isFound= false;
    stack<pair<int, pair<struct node*, vector<bool>>>>q; 
    DFS_util(q,g,st,gt,visit,path, isFound , f);
    f << endl << to_string(st)<< " " << to_string(gt);
}

#endif