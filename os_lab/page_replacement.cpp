#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int fcfo(vector<int> vec,int nframes,int npages);
int LRU(vector<int> vec,int nframes,int npages);
int optimal(vector<int> vec,int nframes,int npages);

typedef pair<int,int> pa;

void printvec(vector<int> vec)
{
    cout<<"vector ";
    for(int i=0;i<vec.size();i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

void printq(list<int> vec)
{
   
    list<int>::iterator i;
    for(i=vec.begin();i!=vec.end();i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;
}

void printframelist(vector<pa> vec)
{
    
    for(int i=0;i<vec.size();i++)
    {
        cout<<vec[i].first<<" ";
    }
    cout<<endl;
}


int main()

{
    int nframes,npages;
    int temp;
    vector<int> vec; 
    cout<<"enter number of frames";
    cin>>nframes;
    cout<<"enter number of pages";
    cin>>npages;

    ifstream myReadFile;
    myReadFile.open("page_replacement_test.txt");
    char output[100];

     if (myReadFile.is_open()) {
      while (!myReadFile.eof()) {


    myReadFile >> output;
    
    temp = atoi(output);
    if(temp == -1)
    {
        break;
    }
    else
    {
        vec.push_back(temp); 
    }
    //cout<<output;
 }
 }

     myReadFile.close();


     printvec(vec);
     cout<<endl;


    cout<<" fifo \n number of page fault "<<endl;
    cout<<fcfo(vec,npages,nframes)<<endl;

    cout<<" LRU \n "<<endl; 
    cout<<LRU(vec,npages,nframes)<<endl;

    cout<<" optimal \n "<<endl;
    cout<<optimal(vec,npages,nframes)<<endl;


   

    return 0;
}



int fcfo(vector<int> vec,int npages,int nframes)
{

    int size = 0;
    bool page_map[npages];
    for(int i=0;i<npages;i++)
    {
        page_map[i] = false;
    }
    queue<int> q;
    int temp;
    int pg_flt= 0;

    for(int i=0;i<vec.size();i++)
    {
        if(size < nframes)
        {
            if(!page_map[vec[i]])
            {
                //page_map.insert(vec[i]);
                page_map[vec[i]] = true;
          
            size++;

            q.push(vec[i]);
            pg_flt++;

            }

        }
        else
        {
            if(!page_map[vec[i]])//== page_map.end())
            {
                temp = q.front();
                page_map[temp] = false;
                page_map[vec[i]] = true;
                q.push(vec[i]);
                pg_flt++;
            }
        }
    }
    return pg_flt;
}


int LRU(vector<int> vec,int npages,int nframes)
{

    int size = 0;
    //unordered_map<int> page_map;
    bool page_map[npages];
    unordered_map <int,list<int>::iterator> page_addr_map;
    vector<list<int>::iterator> vec_addr(npages);
    list<int> q;
    int temp;
    int pg_flt= 0;
    list<int>::iterator temp_addr;

    for(int i=0;i<vec.size();i++)
    {
        if(size < nframes)
        {
            if(!page_map[vec[i]])// == page_map.end())
            {
              
             //page_map.insert(vec[i]);
             page_map[vec[i]] = true;
             size++;
             q.push_front(vec[i]);
             vec_addr[vec[i]] = q.begin();
             pg_flt++;
            }
            else
            {
                q.erase(vec_addr[vec[i]]);
                q.push_front(vec[i]);
                vec_addr[vec[i]] = q.begin();
            }

        }
        else
        {
            if(!page_map[vec[i]])// == page_map.end())
            {
             
             temp = q.back();
             q.pop_back();
             //page_map.erase(temp);
            page_map[temp] = false;

             //page_map.insert(vec[i]);
             page_map[vec[i]] = true;

             q.push_front(vec[i]);

            ///page_addr_map.insert(q.begin());
            vec_addr[vec[i]] = q.begin();
            pg_flt++;
            }
            else
            {
                q.erase(vec_addr[vec[i]]);
                q.push_front(vec[i]);
                vec_addr[vec[i]] = q.begin();
                
            }
            
        }

        printq(q);
        cout<<endl;
    }
    return pg_flt;
}





int remote_page(vector<pa> q)
{
    int mini = q[0].second;
    int index = 0;
    for(int i=1;i<q.size();i++)
    {
        if(mini < q[i].second)
        {
            mini = q[i].second;
            index = i; 
        }
    }
    return index;
}

int optimal(vector<int> vec,int npages,int nframes)
{
  int n = vec.size();
  int pos_list[npages];
  int next_pos[n];
  bool page_map[nframes];
  int pg_flt =0;
  int size =0;
  int page_addr[npages];
  int rem;
  for(int i=0;i<)

  vector<pa> q(nframes);
  pa temp_pa;

  for(int i=0;i<nframes;i++)
  {
      page_map[i] = false;
  }


 for(int i=0;i<n;i++)
 {
     pos_list[i] = INT_MAX;
 }

  for(int i=n-1;i>=0;i--)
  {
      next_pos[i] = pos_list[vec[i]];
      pos_list[vec[i]] = i;

  }

  for(int i=0;i<vec.size();i++)
  {
      cout<<next_pos[i]<<" ";
  }
    cout<<endl;

    for(int i=0;i<n;i++)
    {
        if(size < nframes)
        {
            if(!page_map[vec[i]])
            {
                page_map[vec[i]] = true;
                page_addr[vec[i]] = size;
                temp_pa.first = vec[i];
                temp_pa.second = next_pos[i];
                q[size] = temp_pa;
                size++;
                pg_flt++;
            }
            else{
                q[page_addr[vec[i]]].second = next_pos[i];
            }
        
        }
        else
        {
            if(!page_map[vec[i]])
            {
                
                rem = remote_page(q);
                cout<<" remove page "<<q[rem].first<<" "<<q[rem].second<<endl;
                page_map[q[rem].first] = false;
                page_map[vec[i]] = true;
                temp_pa.first = vec[i];
                temp_pa.second = next_pos[i];
                q[rem] = temp_pa;
                page_addr[vec[i]] = rem;
                pg_flt++;

            }
            else 
            {
                q[page_addr[vec[i]]].second = next_pos[i];
            }
        }

        printframelist(q);
    }   
    return pg_flt; 
}