#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pa;

int memory_s;

void intialize(int n,list<pa>& l)
{
    pa p;
    p.first = n-1;
    p.second = -1;
    l.push_front(p);
    cout<<"success: memory intialized with "<<n<<" unit\n";
    return ;
}

void alloc(int n, list<pa>&l)
{
    if(l.empty()) 
    {
        cout<<" no memory,please allocate \n";
        return;
    }
    pa temp_pair;
    list<pa>::iterator temp;

    temp = l.begin();

    if(temp->second == -1 )
    {
        if(n < temp->first )
        {
            temp_pair.first = 0;
            temp_pair.second = n;

            l.push_front(temp_pair);
            cout<<"success: memory allocated from "<<temp_pair.first<<" to "<<temp_pair.second-1<<endl;

            return ;
        }
        else{
            cout<<" there is not much space as requested \n";
            return ;
        }
    }

    int pos = 1;
    int last_pos;

    if( temp->first != 0)
    {
        if(n <= temp->first )
        {
            temp_pair.first = 0;
            temp_pair.second = n;
            l.push_front(temp_pair);
        }
    
        else
        {
            last_pos = temp->first + temp->second - 1;
            temp++;
            if(temp->second == -1)
            {
                if(last_pos + n  < temp->first )
                {
                    temp_pair.first = last_pos + 1;
                    temp_pair.second = n;
                    l.insert(temp,temp_pair);
                    cout<<"success: memory allocated from "<<temp_pair.first<<" to "<<temp_pair.second-1<<endl;
                }
                else{
                    cout<<" error: not enough space left \n";
                    return ;
                }
            }
            else
            {

            while(temp->second != -1 && last_pos + n > temp->first )
            {
                last_pos = temp->first + temp->second - 1;
                temp++;
            }
              
             if(last_pos + n  < temp->first )
                {
                    temp_pair.first = last_pos + 1;
                    temp_pair.second = n;
                    l.insert(temp,temp_pair);
                    cout<<"success: memory allocated from "<<temp_pair.first<<" to "<<temp_pair.second-1<<endl;

                }
                else
                {
                   cout<<" error: not enough space left \n";
                   return ;
                }
            }
        }
    }
    else
    {
        last_pos = temp->second-1;
        temp++;
        while(temp->second != -1 && last_pos + n  > temp->first )
            {
                last_pos = temp->first + temp->second - 1;
                temp++;
            }
        
          if(last_pos + n  < temp->first )

            {
                    temp_pair.first = last_pos + 1;
                    temp_pair.second = n;
                    l.insert(temp,temp_pair);
                    cout<<"success: memory allocated from "<<temp_pair.first<<" of size  "<<temp_pair.second-1<<endl;
            }
            else
           {
                cout<<" error: not enough space left \n";
                return ;
           }


    }
    return ;

}

void removemem(int n,list<pa> &l)
{
  

    if(l.empty()) 
    {
        cout<<"error : no memory allocated \n";
        return;
    }
    
    list<pa>::iterator temp;
    temp = l.begin();

    if(temp->second == -1)
    {
        cout<<"error : nothing is to remove \n";
        return;
    }
    else
    {
        while(temp->second != -1 && temp->second != n)
        {
            temp++;
        }
        
        if(temp->second == n)
        {
            cout<<"success: memory allocation removed from "<<temp->first<<" of size  "<<temp->second-1<<endl;
            temp++;
            l.erase(temp);
            //cout<<"success: removed \n";
            return ;
        }
    }

    cout<<"error: the given memory size is not allocated to any process \n";
    return;
}


void printlist(list<pa> l)
{

    if(l.empty()) 
    {
        cout<<"error: memory is not allocated \n";
        return ;
    }
  
    list<pa>::iterator it;
    it= l.begin();

    if(it->second == -1)
    {
        cout<<" error: memory is having no allocation \n";
        return;
    }


    cout<<"  memory used ... \n";
    cout<<" start location    "<<"    end location    \n";

    while(it->second != -1)
    {
        cout<<" "<<it->first<<"                      "<<it->second+it->first -1<<"    \n";
        it++;
    }
    return;
}


int main()
{
    list<pa> ls;
    string s;
    int val;
    list<pa> l;

    while(true)
    {
        cin>>s;
        cin>>val;

        if(s == "alloc")
        {
            alloc(val,l);
        }
        else if(s == "intialize")
        {
            intialize(val,l);
        }
        else if(s == "remove")
        {
            removemem(val,l);
        }
        else if(s == "exit")
        {
            break;
        }
        else if( s == "show")
        {
            printlist(l);
            cout<<"\n";
        }
        else
        {
            cout<<" wrong input \n";
        }
        
    }

    return 0;
}