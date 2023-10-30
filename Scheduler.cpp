#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Job
{
    int job_id;
    string job_name;
    int at;
    int ct;
    int tat;
    int wt;
    int bt;
    int priority;

    public:
        Job()
        {
            cout<<"\nEnter job Id: ";
            cin>>job_id;
            cin.ignore();
            cout<<"\nEnter job name: ";
            cin>>job_name;
            cout<<"\nEnter Arrival time: ";
            cin>>at;
            cout<<"\nEnter Burst time: ";
            cin>>bt;
            // at = 0;
            ct = 0;
            tat = 0;
            wt = 0;
            priority = 0;
        }

        

        friend class Scheduler;
        friend bool Sort(Job&,Job&);

};

class Scheduler
{
    vector<Job> tasklist;
    int n;
    public:
        Scheduler()
        {
            cout<<"\nEnter number of tasks: ";
            cin>>n;

            for(int i=0;i<=n-1;i++)
            {
                Job j;
                tasklist.push_back(j);
            }
        }

        void FCFS();
        void prioritySch();
        void SJF();
        void acceptPriority()
        {
            for(auto &i : tasklist)
            {
                cout<<"\nEnter priority for "<<i.job_id<<" : ";
                cin>>i.priority;
            }
        }

        void display(){
        cout<<"id\tname\tat\tbt\tct\twt\ttat\tpriority"<<endl;
        for(auto i:tasklist){
            cout<<i.job_id<<"\t"<<i.job_name<<"\t"<<i.at<<"\t"<<i.bt<<"\t"<<i.ct<<"\t"<<i.wt<<"\t"<<i.tat<<"\t"<<i.priority<<endl;
        }
    }
};

void Scheduler::SJF()
{
    sort(tasklist.begin(),tasklist.end(),[](const Job &j1 , const Job &j2)
    {
        return j1.bt<j2.bt;
    });

    tasklist[0].wt = 0;
    tasklist[0].ct = tasklist[0].at + tasklist[0].bt;
    tasklist[0].tat = tasklist[0].ct - tasklist[0].at;

    for(int i=1;i<=n-1;i++)
    {
        tasklist[i].wt = max(0,tasklist[i-1].ct - tasklist[i].at);
        tasklist[i].ct = tasklist[i].at + tasklist[i].wt + tasklist[i].bt;
        tasklist[i].tat = tasklist[i].ct - tasklist[i].at;
    }

    display();
}

void Scheduler::prioritySch()
{
    sort(tasklist.begin(),tasklist.end(),[](const Job &j1 , const Job &j2)
    {
        return j1.priority<j2.priority;
    });
    tasklist[0].wt = 0;
    tasklist[0].ct = tasklist[0].at + tasklist[0].bt;
    tasklist[0].tat = tasklist[0].ct - tasklist[0].at;

    for(int i=1;i<=n-1;i++)
    {
        tasklist[i].wt = max(tasklist[i].ct-tasklist[i].at,0);
        tasklist[i].ct = tasklist[i].at + tasklist[i].bt + tasklist[i].wt;
        tasklist[i].tat = tasklist[i].ct - tasklist[i].at;
    }
    display();
}

// bool Sort(const Job &j1 ,const Job &j2)
// {
//     return j1.at<j2.at;
// }

void Scheduler::FCFS()
{
    acceptPriority();
    int totalTAT = 0 , totalWT = 0;
    sort(tasklist.begin(),tasklist.end(),[](const Job &j1 , const Job &j2)
    {
        return j1.at<j2.at;
    });

    tasklist[0].ct = tasklist[0].at + tasklist[0].bt;
    tasklist[0].tat = tasklist[0].ct - tasklist[0].at;
    tasklist[0].wt = 0;

    for(int i=1;i<=n-1;i++)
    {
        tasklist[i].wt = max(tasklist[i-1].ct-tasklist[i].at,0);
        tasklist[i].ct = tasklist[i].at + tasklist[i].wt + tasklist[i].bt;
        tasklist[i].tat = tasklist[i].ct - tasklist[i].at;
    }

    display();
}

int main()
{
    Scheduler sch;
    cout<<"\nFCFS: "<<endl;
    sch.FCFS();
    cout<<"\nPriority: "<<endl;
    sch.prioritySch();
    cout<<"\nSJF: "<<endl;
    sch.SJF();
}

// 1 p1 2 2 2 p2 0 1 3 p3 2 3 4 p4 3 5 5 p5 4 4 