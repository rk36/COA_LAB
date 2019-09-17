#include <bits/stdc++.h>


#include <iostream>


// code  for the program 

using namespace std;

struct process{
    int time;
    int id;
    bool operator<(const process &o) const
    {
        return time > o.time;
    }
};


vector<int> waiting_time(1000); 
vector<int> turnaround_time(1000);
vector<int> entry_to_ready(1000);

void intalize()
{
    //memset(waiting_time,0,sizeof(waiting_time));
    memset(&waiting_time[0], 0, sizeof(waiting_time[0]) * waiting_time.size());
    
}


typedef struct process process;

int running_time = INT_MAX;

process process_in_runninng ;//= new process; //new process;


// struct thing
// {
//     int a;
//     char b;

//     bool operator<(const thing &o) const
//     {
//         return a < o.a;
//     }
// };



void fillreadyqueue(queue<process>& waiting_queue,priority_queue < process >& ready_queue,vector< vector<int> > vec, vector<int>& process_pos);
void running(queue<process>& waiting_queue,priority_queue < process >& ready_queue,vector< vector<int> > vec, vector<int>& process_pos);

int global_time;
bool run;


void printqueue(priority_queue <process> p)
{
    cout<<"priority queue "<<endl;

    while(!p.empty())
    {
        cout<<p.top().id<<" ";
        p.pop();
    }
    cout<<endl;
}

void printarray(vector<int> vec,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<" process -> "<<i<<" "<<vec[i]<<"\n";
    }
}

int main()
{
    intalize();  // intialize the waiting time value 

     ifstream myReadFile;
 myReadFile.open("premptive_schedule.txt");
 char output[100];
 int j=0;
 vector< vector<int> > vec;
 

 
 vector<int> a;
 vec.push_back(a);
 int temp;
 if (myReadFile.is_open()) {
 while (!myReadFile.eof()) {


    myReadFile >> output;
    
    temp = atoi(output);
    if(temp == -1)
    {
        j++;
        if(!myReadFile.eof())
        {
        vec.push_back(a);
        }
        else
        {
            break;
        }
    }
    else
    {
        vec[j].push_back(temp); 
    }
    //cout<<output;
 }
}

process_in_runninng.time = 100;
process_in_runninng.id = -1;

for(int i=0;i<vec.size();i++)
{
    for(int j=0;j<vec[i].size();j++)
    {
        cout<<vec[i][j]<<" ";
    }
    cout<<endl;
}


myReadFile.close();

//priority_queue < process,vector<process>, greater<process> > ready_queue;
priority_queue < process > ready_queue;

int num_of_process = vec.size();

vector<int> process_pos(num_of_process);


cout<<"no of processes "<<num_of_process<<endl<<endl;

 //memset(process_pos,0,sizeof(process_pos));
for( int i=0;i<num_of_process;i++)
{
    process_pos[i] = 0;
}

queue<process> waiting_queue;
global_time = 0;
process p;



//  for(int i=0;i<vec.size();i++)
//      {
//          if(process_pos[i] == 0 && vec[i].size()>1 && vec[i][0] == global_time)
//          {
//              p.time = vec[i][1];
//              p.id = i;
//              ready_queue.push(p);
//              process_pos[i] = 1;
             
//          }
//      }
//  global_time++;    
//cout<<"good to go \n";

//printqueue(ready_queue);

//while(!ready_queue.empty() || !waiting_queue.empty())
run = true;
while(run)
{
    fillreadyqueue(waiting_queue,ready_queue,vec,process_pos);
    running(waiting_queue,ready_queue,vec,process_pos);
    global_time++;
   // if(global_time>2000) break;

}

cout<<"\n waiting time \n";
printarray(waiting_time,num_of_process);

cout<<"\n turnaround time \n";

printarray(turnaround_time,num_of_process);


cout<<"all process over \n"<<endl;

int sum=0;

for(int i=0;i<vec.size();i++)
{
 sum+= waiting_time[i];
}    
cout<<"\n average waiting time "<<sum/(vec.size())<<endl;

sum=0;
for(int i=0;i<vec.size();i++)
{
 sum+= turnaround_time[i];
}    
cout<<"\n average waiting time "<<sum/(vec.size())<<endl;

return 0;

}

void fillreadyqueue(queue<process>& waiting_queue,priority_queue < process >& ready_queue,vector< vector<int> > vec, vector<int>& process_pos)
{
    
    process p ;//= new process;
    int time_left;
    process temporary_process;
    for(int i=0;i<vec.size();i++)
     {
         if(process_pos[i] == 0 && vec[i].size()>1 && vec[i][0] == global_time)
         {
             p.time = vec[i][1];
             p.id = i;
             ready_queue.push(p);
             process_pos[i] = 1;
             //cout<<"process "<<i<<" inserted at "<<global_time<<" ";
             cout<<global_time<<"::"<<"process-> "<<p.id<<" inserted "<<endl;
             //printqueue(ready_queue);
             //cout<<"running time "<<running_time<<" ready_time "<<ready_queue.top().time<<endl;
             if(running_time > ready_queue.top().time && running_time != INT_MAX) 
             {   
                 //time_left = vec[process_in_runninng.id][process_pos[process_in_runninng.id]] - running_time;
                 time_left = running_time;
                 temporary_process = process_in_runninng;
                 temporary_process.time = time_left;
                 ready_queue.push(temporary_process);
                 running_time = ready_queue.top().time;
                 process_in_runninng = ready_queue.top();
                 //cout<<"running time "<<running_time<<" ready_time "<<ready_queue.top().time<<endl;
                 //cout<<" printed ";
                 process_in_runninng.time = global_time + ready_queue.top().time;
                 ready_queue.pop();
                 cout<<global_time<<"::"<<"process-> "<<process_in_runninng.id<<" ready_2_run_prempt  "<<endl;
             }
             entry_to_ready[p.id] = global_time;
             cout<<"running time "<<running_time<<" ready_time "<<ready_queue.top().time<<endl;
             //printqueue(ready_queue);
             //process_pos[i] = 1;
             
         }
     }
    
    process temp;                                         //an auxilary variable for the process
    
    //temp = waiting_queue.front();

    while(!waiting_queue.empty())// && temp.time == global_time)
    {
       temp = waiting_queue.front(); 
      if(temp.time == global_time)
      { 
      temp = waiting_queue.front();
      
      if(process_pos[temp.id] < vec[temp.id].size() )
      {

      p.time = vec[temp.id][process_pos[temp.id]];  // insert in ready queue if the process is of current time stamp;
      p.id = temp.id;  
      ready_queue.push(p);
      //cout<<" process "<<p.id <<" wait_2_ready  "<<global_time<<" ";
      cout<<global_time<<"::"<<"process-> "<<p.id<<" wait_2_ready "<<endl;
      entry_to_ready[p.id] = global_time;
      //printqueue(ready_queue);
      waiting_queue.pop();
      //process_pos[temp.id] += 2 ;  not required as in running it is taken care. 
      
      }
      }
      else{
          break;
      }
      
    }


    

}



void running(queue<process>& waiting_queue, priority_queue< process>& ready_queue,vector< vector<int> > vec, vector<int>& process_pos)
{
    //process p;
   

    //static int running_time = -1;
    //static process p;
    process temp_process;
    // for new process
    if(running_time == 0 || running_time == INT_MAX)     //&& ready_queue.empty())
    {
        if(ready_queue.empty() && waiting_queue.empty())
        {
            //cout<<"running over\n";
            
            cout<<global_time<<"::"<<"process-> "<<process_in_runninng.id<<" run_2_exit "<<endl;  
            turnaround_time[process_in_runninng.id] = global_time - vec[process_in_runninng.id][0];
            cout<<global_time<<"::"<<" running over \n";
            run = false;
            return;
        }
       else if(ready_queue.empty() && !waiting_queue.empty())
       {
           return ;
       }
       else{
       if(process_pos[process_in_runninng.id]+1 < vec[process_in_runninng.id].size() && process_in_runninng.id != -1)
       {
           temp_process.time = global_time + vec[process_in_runninng.id][process_pos[process_in_runninng.id]+1];
           temp_process.id = process_in_runninng.id;                                             
           process_pos[process_in_runninng.id] += 2;                                               // move to the next burst time 
           if(waiting_queue.empty())
           {
               waiting_queue.push(temp_process);
           }
           else{
               temp_process.time += waiting_queue.back().time;
               waiting_queue.push(temp_process); 
            }
            //cout<<" process  "<<temp_process.id<<" run_2_wait at "<<temp_process.time<<endl;
           cout<<global_time<<"::"<<"process-> "<<temp_process.id<<" run_2_wait "<<endl;
           
       }
       else if(process_in_runninng.id != -1)
       {
         cout<<global_time<<"::"<<"process-> "<<process_in_runninng.id<<" run_2_exit "<<endl;  
         turnaround_time[process_in_runninng.id] = global_time - vec[process_in_runninng.id][0];
         //cout<<"process "<<p.id<<" run_2_exit at "<<global_time<<endl;
       }
     
     process_in_runninng = ready_queue.top();
     waiting_time[process_in_runninng.id] += global_time - entry_to_ready[process_in_runninng.id]; // waiting time of the process 
     cout<<global_time<<"::"<<"process-> "<<process_in_runninng.id<<" ready_2_run "<<endl; 
     ready_queue.pop();
     running_time = process_in_runninng.time;
     running_time--;
       }

    }

  else if(process_in_runninng.id != -1){
   running_time--;
  }
  
  return;

}