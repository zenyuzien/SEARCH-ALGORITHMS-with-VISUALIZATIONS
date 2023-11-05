#ifndef AO_
#define AO_ 

void reconstruct_path(const vector<int>& came_from, int current, ofstream& f) {
    f<<endl ;
    while (current != -1) {
        cout << (current)<<" <- ";
        f<<to_string(current)<<" ";
        current = came_from[current];
    }
}

void ao_star(struct graph& g, int start, int goal, ofstream& f) {
    priority_queue<node_ao, vector<node_ao>, greater<node_ao> > open_set;
    vector<int> came_from(g.n, -1);
    vector<int> g_score(g.n, I);
    vector<int> f_score(g.n, I);

    g_score[start] = 0;
    f_score[start] = g_score[start] + g.heur[start];
    open_set.push({start, g_score[start], f_score[start]});

    while (!open_set.empty()) {
        node_ao current = open_set.top();
        open_set.pop();

        f << to_string( current.id ) << " " ;
        if (current.id == goal) {
           // cout << "done\n";
            reconstruct_path(came_from, current.id, f);
        }

        for (int neighbor = 0; neighbor < g.n; ++neighbor) {
            if (g.arr[current.id][neighbor] != I && g.arr[current.id][neighbor]) {
                int tentative_g_score = g_score[current.id] + g.arr[current.id][neighbor];

                if (tentative_g_score < g_score[neighbor]) {
                    came_from[neighbor] = current.id;
                    g_score[neighbor] = tentative_g_score;
                    f_score[neighbor] = g_score[neighbor] + g.heur[neighbor];
                    open_set.push({neighbor, g_score[neighbor], f_score[neighbor]});
                }
            }
        }
    }
}


void AO_star(struct graph& g, int st, int gt, ofstream& f)
{
    ao_star(g, st, gt, f);
    f << endl << to_string(st)<< " " << to_string(gt);
}


#endif