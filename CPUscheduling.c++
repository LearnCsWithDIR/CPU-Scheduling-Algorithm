#include <iostream>
#define maxSize 200 // maximum queue size
using namespace std;

typedef struct process
{
    int p_id;      // process id
    int priority;  // process piority
    int burstTime; // process burst time
    int turnaroundTime;
    int waitingTime; // process waiting time
    int remainTime;  // remain time start time equal to burst time after changing its values for each process

} process;

process q0[maxSize], q1[maxSize], q2[maxSize], q3[maxSize];

/*
● q0 - Round Robin (RR)
● q1 - Shortest Job First (SJF)
● q2 - Shortest Job First (SJF)
● q3 - First-In-First-Out (FIFO)
*/

int size_q0 = 0, size_q1 = 0, size_q2 = 0, size_q3 = 0;
int totalTime = 0;

// Arrival time of all processes is 0
static int ArrivalTime = 0;

// Enqueue in to the queue (only use in RR)
void enqueue(process *queue, process p, int *Qsize)
{
    queue[*Qsize] = p;
    (*Qsize)++;
}

//  Dequeue from the queue
process dequeue(process *queue, int *Qsize)
{
    process currentProcess = queue[0];
    (*Qsize)--;
    for (int i = 0; i < (*Qsize); i++)
    {
        queue[i] = queue[i + 1];
    }
    return currentProcess;
}

// Round Robin function for process scheduling >> Queue 0
void RR(process *queue, int quantumTime, int switchTime, int *Qsize)
{

    while (switchTime != 0 && *Qsize > 0)
    {
        /* 
        switch time and quantum time is initialize values they are same values. Therefore below if condition always true
        If switch time < quantum time then, Round Robin Algorithm same to FCFS Algorithm 
        */
        if (switchTime >= quantumTime)
        {
            process exeProcess = dequeue(queue, Qsize);

            if (exeProcess.remainTime >= quantumTime)
            {

                exeProcess.remainTime -= quantumTime;
                totalTime += quantumTime;
                switchTime -= quantumTime;

                if (exeProcess.remainTime == 0)
                {
                    exeProcess.turnaroundTime = totalTime - ArrivalTime;
                    exeProcess.waitingTime = exeProcess.turnaroundTime - exeProcess.burstTime;

                    cout << "\nQueue: 0 \n\t>> Process: " << exeProcess.p_id << " is finished."
                         << "\n\t>> Remaining time  \t: " << switchTime
                         << "\n\t>> Turnaround time \t: " << exeProcess.turnaroundTime
                         << "\n\t>> Waiting time \t: " << exeProcess.waitingTime;
                }

                else
                {
                    cout << "\n..........\tProcess not finished !\t..........";
                    enqueue(queue, exeProcess, Qsize);
                }
            }
            // Process's remaining less than quantum Time
            else
            {
                switchTime -= exeProcess.remainTime;
                totalTime += exeProcess.remainTime;

                exeProcess.remainTime = 0;

                exeProcess.turnaroundTime = totalTime - ArrivalTime;
                exeProcess.waitingTime = exeProcess.turnaroundTime - exeProcess.burstTime;

                cout << "\nQueue: 0 \n\t>> Process: " << exeProcess.p_id << " is finished."
                     << "\n\t>> Remaining time  \t: " << switchTime
                     << "\n\t>> Turnaround time \t: " << exeProcess.turnaroundTime
                     << "\n\t>> Waiting time \t: " << exeProcess.waitingTime;
            }
        }
    }
    cout << "\n\n..........\tCPU EXECUTED TO NEXT QUEUE\t..........\n";
}

// shortest job first function for process scheduling >> Queue 1,2
void SJF(process *queue, int switchTime, int *Qsize)
{
    while (switchTime != 0 && *Qsize > 0)
    {
        int shortest_id = 0;
        for (int i = 0; i < *Qsize; i++)
        {
            if (queue[shortest_id].remainTime > queue[i].remainTime)
                shortest_id = i;
        }
        process exeProcess = dequeue((queue + shortest_id), Qsize);

        if (exeProcess.remainTime >= switchTime)
        {
            exeProcess.remainTime -= switchTime;
            totalTime += switchTime;
            switchTime = 0;

            if (exeProcess.remainTime == 0)
            {
                exeProcess.turnaroundTime = totalTime - ArrivalTime;
                exeProcess.waitingTime = exeProcess.turnaroundTime - exeProcess.burstTime;
                cout << "\nQueue: 1 or 2 \n\t>> Process: " << exeProcess.p_id << " is finished."
                     << "\n\t>> Remaining time  \t: " << switchTime
                     << "\n\t>> Turnaround time \t: " << exeProcess.turnaroundTime
                     << "\n\t>> Waiting time \t: " << exeProcess.waitingTime;
            }
            else
            {
                cout << "\n..........\tProcess not finished !\t..........";
                enqueue(queue, exeProcess, Qsize);
            }
        }
        else
        {
            switchTime -= exeProcess.remainTime;
            totalTime += exeProcess.remainTime;
            exeProcess.remainTime = 0;

            exeProcess.turnaroundTime = totalTime - ArrivalTime;
            exeProcess.waitingTime = exeProcess.turnaroundTime - exeProcess.burstTime;
            cout << "\nQueue: 1 or 2 \n\t>> Process: " << exeProcess.p_id << " is finished."
                 << "\n\t>> Remaining time  \t: " << switchTime
                 << "\n\t>> Turnaround time \t: " << exeProcess.turnaroundTime
                 << "\n\t>> Waiting time \t: " << exeProcess.waitingTime;
        }
    }
    cout << "\n\n..........\tCPU EXECUTED TO NEXT QUEUE\t..........\n";
}

// first come first serve function for process scheduling >> Queue 3
void FCFS(process *queue, int switchTime, int *Qsize)
{
    while (switchTime != 0 && *Qsize > 0)
    {
        if (queue[0].remainTime > switchTime)
        {
            queue[0].remainTime -= switchTime;
            totalTime += switchTime;
            switchTime = 0;
        }
        else
        {
            switchTime -= queue[0].remainTime;
            totalTime += queue[0].remainTime;
            queue[0].remainTime = 0;

            queue[0].turnaroundTime = totalTime - ArrivalTime;
            queue[0].waitingTime = queue[0].turnaroundTime - queue[0].burstTime;

            cout << "\nQueue: 3 \n\t>> Process: " << queue[0].p_id << " is finished."
                 << "\n\t>> Remaining time  \t: " << switchTime
                 << "\n\t>> Turnaround time \t: " << queue[0].turnaroundTime
                 << "\n\t>> Waiting time \t: " << queue[0].waitingTime;

            dequeue(queue, Qsize);
        }
    }
    cout << "\n\n..........\tCPU EXECUTED TO NEXT QUEUE\t..........\n";
}

int main()
{

    int switchTime = 20;  // CPU Switch each queues
    int quantumTime = 20; // for RR scheduling

    int No_process; // total number of process

    cout << "\n....... Multilevel Queue Scheduling Algorithem Implimentation .......\n\n";

    cout << "Priority Queues: \n\n\t 0 > RR \n\t 1 > SJF \n\t 2 > SJF \n\t 3 > FCFS \n";

    cout << "Enter the number of process : ";
    cin >> No_process;

    cout << "\nEnter Priority and Burst time for each Process : \n";
    int i;
    for (i = 1; i <= No_process; ++i)
    {
        process new_process;
        // newly created process id  = i
        new_process.p_id = i;

        cout << "\n\t Process _" << i << " >>>";
        cout << "\n\t\tBurst Time : ";
        cin >> new_process.burstTime;

        // Choose the queue using priority for that process
        cout << "\t\tPriority : ";
        cin >> new_process.priority;

        new_process.remainTime = new_process.burstTime;

        // choose the priority for input process and that process enqueue to the queue
        switch (new_process.priority)
        {
        case 0: // RR

            enqueue(q0, new_process, &size_q0);
            break;

        case 1: // SJF
            enqueue(q1, new_process, &size_q1);
            break;

        case 2: // SJF
            enqueue(q2, new_process, &size_q2);
            break;

        case 3: // FCFS
            enqueue(q3, new_process, &size_q3);
            break;
        }
    }

    while (size_q0 || size_q1 || size_q2 || size_q3)
    {
        if (size_q0)
        {
            RR(q0, quantumTime, switchTime, &size_q0);
            cout << "\n";
        }
        else if (size_q1)
        {
            SJF(q1, switchTime, &size_q1);
            cout << "\n";
        }
        else if (size_q2)
        {
            SJF(q2, switchTime, &size_q2);
            cout << "\n";
        }
        else if (size_q3)
        {
            FCFS(q3, switchTime, &size_q3);
            cout << "\n";
        }
    }
    cout << "\n.......... All queues are Executed ..........\n";
    // total number of process
    cout << "\nTotal number of Process \t>> " << No_process << "\n";
    // process total time
    cout << "\nTotal Process Time \t>> " << totalTime << "\n";
    // avarege process time
    cout << "\nAverage Process Time \t>> " << totalTime / No_process << "\n\n";

    return 0;
}