#ifndef BFS_
#define BFS_

void BFS_util(queue<pair<int, pair<struct node*,vector<bool> >>>&q, struct graph& g, int cnode, int goal, vector<bool> visit, struct node* path, bool &isFound, ofstream& f )
{
    if(isFound)
    return ;
    f << to_string(cnode)<<" ";
    visit[cnode]=true;

    struct node* newnode = new node();
    newnode->next= path ;
    newnode->val = cnode;
    path = newnode;
    
    for(int i = 0 ; i < g.n; i++)
    {
        if( (i != cnode) && g.arr[cnode][i]!=0 && visit[i]==false)
        {
            if(i==goal)
            {
                isFound= true;
                f << to_string(goal)<<" ";
                display_path(path,f);
                return;
            }
            
            else if(isFound==false)
            {
                q.push({i,{path,visit}});
            }
        }
    }
    while(q.size())
    {
        auto x = q.front();
        q.pop();
        if(visit[x.first]==0)
        BFS_util(q,g,x.first,goal,x.second.second,x.second.first,isFound, f);
    }
    
    
}

void BFS(struct graph & g, int st, int gt, ofstream& f)
{
    queue< pair<int, pair<struct node*, vector<bool> > > >q ;
    vector<bool> visit(g.n);
    struct node* path =NULL ;
    bool isFound= false;
    BFS_util(q, g,st,gt,visit,path, isFound, f );
    f << endl << to_string(st) << " "<< to_string(gt);
}

#endif 