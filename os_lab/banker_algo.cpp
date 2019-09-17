#include<bits/stdc++.h>

using namespace std;

typedef vector<int> ve;
void print_these(vector< ve > need,vector<ve> alloc, ve avai, vector<bool> tpr);

// bool compare(ve a,ve b,int pos)
// {
// if(a.size() != b.size()) return false;
// for(int i=0;i<a[pos].size();i++)
// {
//     if(a[pos][i] != b[pos][i]) return false;
// }
// return true;
// }



bool com_gre(ve need,ve req)
{
    for(int i=0;i<need.size();i++)
    {
        if(need[i] < req[i]) return false;
    }
    return true;
}


bool allcomplete(vector<bool> tpr)
{
    for(int i=0;i<tpr.size();i++)
    {
        if(!tpr[i])
        {
            return false;
        }
    }
    return true;
}

bool allzero(ve tpr)
{
    for(int i=0;i<tpr.size();i++)
    {
        if(tpr[i] != 0)
        {
            return false;
        }
    }
    return true;
}


bool safe_state(vector< ve > need,vector<ve> alloc, ve avai, int pr, vector<bool> tpr)
{
    bool check = true;
    vector<int> p_seq;
    int k;
    while(true)
    {
        check = true;
        for(int i=0;i<need.size();i++)
        {
            if(!tpr[i] && com_gre(avai,need[i]))
            {
                for(int j=0;j<avai.size();j++)
                {
                    avai[j] += alloc[i][j];
                    alloc[i][j] += 0;
                    need[i][j] = 0;
                    check = false;
                   
                
                }
                p_seq.push_back(i);
                tpr[i] = true;
                break;
            }

        }

        print_these(need,alloc,avai,tpr);

        cin>>k;

        if(allcomplete(tpr)) 
        {
            cout<<"success: the request is safe and the sequence of process is :-> \n";
            for(int i=0;i<p_seq.size();i++)
            {
                cout<<" "<<p_seq[i];
            }
            cout<<endl;
            return true;
        }
        if(check)
        {
            cout<<"error: request can not be granted and deadlock may occur\n";
            return false;

        }
        
    }
    return true;
}




bool req_grant(vector< ve > need,vector<ve> alloc, ve avai, ve req, int pr, vector<bool> tpr )
{
    if(!com_gre(need[pr],req)) { cout<<"error: processes requested more than stated resources\n ";  return false;}
    if(!com_gre(avai,req)) { 

        cout<<"error: requested resources are not available , please wait \n";
        return false;
    }
    for(int i=0;i<need[pr].size();i++)
    {
        need[pr][i] -= req[i];
        alloc[pr][i] += req[i];
        avai[i] -= req[i];
    }
    bool check = true;

    for(int i=0;i<need[pr].size();i++)
    {
       if(need[pr][i] != 0) 
        {
            check = false;
            break;
        }
    }

    if(check)
    {
        tpr[pr] = true;
        for(int i=0;i<avai.size();i++)
        {
            avai[i] += alloc[pr][i];
        }
    }

        print_these(need,alloc,avai,tpr);


   if( safe_state(need,alloc,avai,pr,tpr)) return true;
   else return false;

}

void remove_resource(vector< ve >& need,vector<ve>& alloc, ve& avai, ve& req, int pr, vector<bool> &tpr )
{
    if(tpr[pr]) 
    {
        cout<<"error: process already completed,no resource to remove \n";
        return;
    }

    if(!com_gre(alloc[pr],req)) 
    {
        cout<<"error: not enough resource to remove \n";
        return;
    }
    
    for(int i=0;i<need[pr].size();i++)
    {
        avai[i] += req[i];
        alloc[pr][i] -= req[i];
        need[pr][i] += req[i];
        cout<<" resource removed \n";
    }
    return ;
}


void print_these(vector< ve > need,vector<ve> alloc, ve avai, vector<bool> tpr)
{
    cout<<" need \n";
    for(int i=0;i<need.size();i++)
    {
        for(int j=0;j<need[i].size();j++)
        {
            cout<<need[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<" alloc \n";

     for(int i=0;i<need.size();i++)
    {
        for(int j=0;j<need[i].size();j++)
        {
            cout<<alloc[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<" avai \n";

    for(int i=0;i<avai.size();i++)
    {
        cout<<avai[i]<<" ";
    }
    cout<<endl;

     cout<<" status \n";

     for(int i=0;i<tpr.size();i++)
    {
        cout<<tpr[i]<<" ";
    }
    cout<<endl;

    return;

}



int main()
{
    int res;
    cin>>res;
    vector<int> max_resource(res);
    ve avai(res);
   

    for(int i=0;i<res;i++)
    {
        cin>>max_resource[i];
    }

    int process;
    cin>>process;

     vector<bool> pro_sta(process);

     for(int i=0;i<process;i++)
     {
         pro_sta[i] = false;
     }

    vector< vector<int> > need(process);
    ve temp_ve(res);

    for(int i=0;i<process;i++)
    {
        need[i] = vector<int>(res);
    }

    vector< vector<int> > alloc(process);

    for(int i=0;i<process;i++)
    {
        alloc[i] = vector<int>(res);
    }

    for(int i=0;i<process;i++)
    {
        for(int j=0;j<res;j++)
        {
            alloc[i][j] = 0;
        }
    }

    for(int i=0;i<process;i++)
    {
        for(int j=0;j<res;j++)
        {
            cin>>need[i][j];
        }
    }

    avai = max_resource;

    int pr_id;
    string op_type;
    ve temp_request(res);

    while(!allcomplete(pro_sta))
    {
        cin>>pr_id;
        cin>>op_type;
        for(int i=0;i<res;i++)
            {
            cin>>temp_request[i];
            }

        if(op_type == "a")
        {
            

            if(req_grant(need,alloc,avai,temp_request,pr_id,pro_sta))
            {
                for(int i=0;i<res;i++)
                {
                    need[pr_id][i] -= temp_request[i];
                    alloc[pr_id][i] += temp_request[i];
                    avai[i] -= temp_request[i];
                }
                if(allzero(need[pr_id]))
                {
                    pro_sta[pr_id] = true;
                    for(int i=0;i<res;i++)
                    {
                       
                        avai[i] += alloc[pr_id][i];
                        alloc[pr_id][i] = 0;
                    }
                    
                }
            }

            
        }

        else if(op_type == "r")
        {
            remove_resource(need,alloc,avai,temp_request,pr_id,pro_sta);
        }
        else if(op_type == "exit")
        {
            break;
        }
        else if(op_type == "show")
        {
            print_these(need,alloc,avai,pro_sta);
        }
        else
        {
            cout<<"wrong input \n";
            continue;
        }
    }

    return 0;
}