#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

struct ProcessDescription
{
    int ProcessID;
    int ArrivalTime;
    int BurstTime;
    int PriorityValue;
    int WaitTime = 0;
    int TurnaroundTime = 0;
    int ResponseTime = 0;
    int RemainingTime = 0;
    int TimeOfCompletion = 0;
    int TimeBeforeInterruption = 0;
    bool IsReady = false;
    bool HasStarted = false;
    bool IsCompleted = false;
    bool PreviouslyEdited = false;
    //waiting time is when process is waiting for another process to be processed
    //turnaround time is the total running time of the process (actual process + waiting time)
    //response time is when cpu busy and process ready to run (first time)
};

bool compareByArrivalTime(const ProcessDescription &a, const ProcessDescription &b)
{
    return a.ArrivalTime < b.ArrivalTime;
}

bool compareByProcessID(const ProcessDescription &a, const ProcessDescription &b)
{
    return a.ProcessID < b.ProcessID;
}

bool compareByBurstTime(const ProcessDescription &a, const ProcessDescription &b)
{
    return a.BurstTime < b.BurstTime;
}

bool compareByRemainingTime(const ProcessDescription &a, const ProcessDescription &b)
{
    return a.RemainingTime < b.RemainingTime;
}

bool compareByPriority(const ProcessDescription &a, const ProcessDescription &b)
{
    return a.PriorityValue < b.PriorityValue;
}

void processCaseOutput(int t, vector<ProcessDescription> &ListOfProcesses, vector<string> &ResultsPerCase, vector<string> StepByStep)
{
    int TotalBurstTime = 0;
    int CPUUtil = 0;
    float Throughput = 0;
    float AverageWait;
    float AverageTurnaround;
    float AverageResponse;
    //https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros
    std::ostringstream ThroughputFormat, AveWaitFormat, AveTAFormat, AveResFormat;
    ThroughputFormat << std::fixed; //https://stackoverflow.com/questions/12453557/setprecision-is-not-a-member-of-std
    AveWaitFormat << std::fixed;
    AveTAFormat << std::fixed;
    AveResFormat << std::fixed;

    for(int i = 0; i < ListOfProcesses.size(); i++)
    {
        TotalBurstTime += ListOfProcesses[i].BurstTime;
    }

    for(int i = 0; i < StepByStep.size(); i++)
    {
        ResultsPerCase.push_back(StepByStep[i]);
    }
    CPUUtil = (TotalBurstTime*100 / t);
    Throughput = ((float)ListOfProcesses.size() / t);
    ThroughputFormat << std::setprecision(4);
    ThroughputFormat << Throughput;
    std::string ThroughputOutput = ThroughputFormat.str();


    ResultsPerCase.push_back("Total time elapsed: " + to_string(t) + "ns"); //https://stackoverflow.com/questions/25925290/c-round-a-double-up-to-2-decimal-places
    ResultsPerCase.push_back("Total CPU burst time: " + to_string(TotalBurstTime) + "ns");
    ResultsPerCase.push_back("CPU Utilization: " + to_string(CPUUtil) + "%");
    ResultsPerCase.push_back("Throughput: " + ThroughputOutput + " processes/ns");

    ResultsPerCase.push_back("Waiting times:");
    for(int i = 0; i < ListOfProcesses.size(); i++)
    {
        ProcessDescription temp = ListOfProcesses[i];
        ResultsPerCase.push_back("Process " + to_string(temp.ProcessID) + ": " + to_string(temp.WaitTime) + "ns");
        AverageWait += temp.WaitTime;
    }
    AverageWait /= ListOfProcesses.size();
    AveWaitFormat << std::setprecision(2);
    AveWaitFormat << AverageWait;
    std::string AveWaitOutput = AveWaitFormat.str();

    ResultsPerCase.push_back("Average waiting time: " + AveWaitOutput + "ns");



    ResultsPerCase.push_back("Turnaround times: ");
    for(int i = 0; i < ListOfProcesses.size(); i++)
    {
        ProcessDescription temp = ListOfProcesses[i];
        ResultsPerCase.push_back("Process " + to_string(temp.ProcessID) + ": " + to_string(temp.TurnaroundTime) + "ns");
        AverageTurnaround += temp.TurnaroundTime;
    }
    AverageTurnaround /= ListOfProcesses.size();
    AveTAFormat << std::setprecision(2);
    AveTAFormat << (AverageTurnaround*100.0)/100.0;
    std::string AveTAOutput = AveTAFormat.str();

    ResultsPerCase.push_back("Average turnaround time: " + AveTAOutput + "ns");



    ResultsPerCase.push_back("Response times: ");
    for(int i = 0; i < ListOfProcesses.size(); i++)
    {
        ProcessDescription temp = ListOfProcesses[i];
        ResultsPerCase.push_back("Process " + to_string(temp.ProcessID) + ": " + to_string(temp.ResponseTime) + "ns");
        AverageResponse += temp.ResponseTime;
    }
    AverageResponse /= ListOfProcesses.size();
    AveResFormat << std::setprecision(2);
    AveResFormat << AverageResponse;
    std::string AveResOutput = AveResFormat.str();

    ResultsPerCase.push_back("Average response time: " + AveResOutput + "ns");
}

int getNumOfTestCases()
{
    int UserInput;
    cin >> UserInput;
    return UserInput;
}

void runFCFS(vector<ProcessDescription> &ListOfProcesses, vector<string> &ResultsPerCase)
{
    int time = 0;
    std::vector<string> OperationStepByStep;

    //setup queue
    std::vector<ProcessDescription> QueueToModify(ListOfProcesses.size());
    QueueToModify = ListOfProcesses;
    std::sort(QueueToModify.begin(), QueueToModify.end(), compareByArrivalTime); 

    for(int i = 0; i < QueueToModify.size(); i++)
    {
        ProcessDescription temp = QueueToModify[i];
        //https://afteracademy.com/blog/what-is-burst-arrival-exit-response-waiting-turnaround-time-and-throughput
        if(temp.ArrivalTime < time)
        {
            temp.ResponseTime = time - temp.ArrivalTime;
        }
        if(time < temp.ArrivalTime)
        {
            time = temp.ArrivalTime;
        }
        time += temp.BurstTime;
        temp.TimeOfCompletion = time;
        temp.TurnaroundTime = temp.TimeOfCompletion - temp.ArrivalTime;
        temp.WaitTime = temp.TurnaroundTime - temp.BurstTime;
        QueueToModify[i] = temp;

        OperationStepByStep.push_back(to_string(time-temp.BurstTime) + " " + to_string(temp.ProcessID) + " " + to_string(temp.BurstTime) + "X");
    }

    std::sort(QueueToModify.begin(), QueueToModify.end(), compareByProcessID);
    processCaseOutput(time, QueueToModify, ResultsPerCase, OperationStepByStep);
}

void runSJF(vector<ProcessDescription> &ListOfProcesses, vector<string> &ResultsPerCase)
{
    int time = 0;
    std::vector<string> OperationStepByStep;

    //setup queue
    std::vector<ProcessDescription> QueueBasedOnArrival(ListOfProcesses.size());
    QueueBasedOnArrival = ListOfProcesses;
    std::sort(QueueBasedOnArrival.begin(), QueueBasedOnArrival.end(), compareByArrivalTime); 
    std::vector<ProcessDescription> QueueToModify(0);

    //Set RemainingTime equal to BurstTime
    for(int i = 0; i <QueueBasedOnArrival.size(); i++)
    {
        QueueBasedOnArrival[i].RemainingTime = QueueBasedOnArrival[i].BurstTime;
    }

    time = QueueBasedOnArrival[0].ArrivalTime;
    //https://www.cplusplus.com/reference/vector/vector/clear/
    while(true)
    {
        for(int i = 0; i <QueueBasedOnArrival.size(); i++)
        {
            if((time >= QueueBasedOnArrival[i].ArrivalTime) && (!QueueBasedOnArrival[i].IsCompleted))
            {
                QueueToModify.push_back(QueueBasedOnArrival[i]);
            }
        }
        if(QueueToModify.size() == 0)
        {
            break;
        }
        std::sort(QueueToModify.begin(), QueueToModify.end(), compareByRemainingTime);
        QueueToModify[0].RemainingTime = 0;
        //to edit-start
        QueueToModify[0].TimeBeforeInterruption == QueueToModify[0].BurstTime;
        if(!QueueToModify[0].PreviouslyEdited) //if currentprocess is not the previously edited process
        {
            if(!QueueToModify[0].HasStarted)
            {
                QueueToModify[0].HasStarted = true;
                QueueToModify[0].ResponseTime = time - QueueToModify[0].ArrivalTime;
            }
            QueueToModify[0].PreviouslyEdited = true;
            for(int i = 1; i<QueueToModify.size(); i++)
            {
                QueueToModify[i].PreviouslyEdited = false;
                if(QueueToModify[i].TimeBeforeInterruption != 0) //if previousprocess has running time
                {
                    OperationStepByStep.push_back(to_string(time-QueueToModify[0].BurstTime) + " " + to_string(QueueToModify[i].ProcessID) + " " + to_string(QueueToModify[0].BurstTime));
                    QueueToModify[i].TimeBeforeInterruption = 0;
                }
            }
        }
        time += QueueToModify[0].BurstTime;
        if(QueueToModify[0].RemainingTime==0)
        {
            QueueToModify[0].IsCompleted = true;
            QueueToModify[0].TimeOfCompletion = time;
            QueueToModify[0].TurnaroundTime = QueueToModify[0].TimeOfCompletion - QueueToModify[0].ArrivalTime;
            QueueToModify[0].WaitTime = QueueToModify[0].TurnaroundTime - QueueToModify[0].BurstTime;
            OperationStepByStep.push_back(to_string(time-QueueToModify[0].BurstTime) + " " + to_string(QueueToModify[0].ProcessID) + " " + to_string(QueueToModify[0].BurstTime) + "X");
        }
        //to edit-end
        std::sort(QueueToModify.begin(), QueueToModify.end(), compareByArrivalTime);
        for(int i = 0; i<QueueBasedOnArrival.size(); i++)
        {
            for(int j = 0; j < QueueToModify.size(); j++)
            {
                if(QueueBasedOnArrival[i].ProcessID == QueueToModify[j].ProcessID)
                {
                    QueueBasedOnArrival[i] = QueueToModify[j];
                    break;
                }
            }
        }
        QueueToModify.clear();
    }
    
    std::sort(QueueBasedOnArrival.begin(), QueueBasedOnArrival.end(), compareByProcessID);
    processCaseOutput(time, QueueBasedOnArrival, ResultsPerCase, OperationStepByStep);
}

void runSRTF(vector<ProcessDescription> &ListOfProcesses, vector<string> &ResultsPerCase)
{
    int time = 0;
    std::vector<string> OperationStepByStep;

    //setup queue
    std::vector<ProcessDescription> QueueBasedOnArrival(ListOfProcesses.size());
    QueueBasedOnArrival = ListOfProcesses;
    std::sort(QueueBasedOnArrival.begin(), QueueBasedOnArrival.end(), compareByArrivalTime); 
    std::vector<ProcessDescription> QueueToModify(0);

    //Set RemainingTime equal to BurstTime
    for(int i = 0; i <QueueBasedOnArrival.size(); i++)
    {
        QueueBasedOnArrival[i].RemainingTime = QueueBasedOnArrival[i].BurstTime;
    }

    time = QueueBasedOnArrival[0].ArrivalTime;
    //https://www.cplusplus.com/reference/vector/vector/clear/
    while(true)
    {
        for(int i = 0; i <QueueBasedOnArrival.size(); i++)
        {
            if((time >= QueueBasedOnArrival[i].ArrivalTime) && (!QueueBasedOnArrival[i].IsCompleted))
            {
                QueueToModify.push_back(QueueBasedOnArrival[i]);
            }
        }
        if(QueueToModify.size() == 0)
        {
            break;
        }
        std::sort(QueueToModify.begin(), QueueToModify.end(), compareByRemainingTime);
        QueueToModify[0].RemainingTime--;
        //to edit-start
        QueueToModify[0].TimeBeforeInterruption++;
        if(!QueueToModify[0].PreviouslyEdited) //if currentprocess is not the previously edited process
        {
            if(!QueueToModify[0].HasStarted)
            {
                QueueToModify[0].HasStarted = true;
                QueueToModify[0].ResponseTime = time - QueueToModify[0].ArrivalTime;
            }
            QueueToModify[0].PreviouslyEdited = true;
            for(int i = 1; i<QueueToModify.size(); i++)
            {
                QueueToModify[i].PreviouslyEdited = false;
                if(QueueToModify[i].TimeBeforeInterruption != 0) //if previousprocess has running time
                {
                    OperationStepByStep.push_back(to_string(time-QueueToModify[i].TimeBeforeInterruption) + " " + to_string(QueueToModify[i].ProcessID) + " " + to_string(QueueToModify[i].TimeBeforeInterruption));
                    QueueToModify[i].TimeBeforeInterruption = 0;
                }
            }
        }
        time++;
        //to edit-end
        if(QueueToModify[0].RemainingTime==0)
        {
            QueueToModify[0].IsCompleted = true;
            QueueToModify[0].TimeOfCompletion = time;
            QueueToModify[0].TurnaroundTime = QueueToModify[0].TimeOfCompletion - QueueToModify[0].ArrivalTime;
            QueueToModify[0].WaitTime = QueueToModify[0].TurnaroundTime - QueueToModify[0].BurstTime;
            OperationStepByStep.push_back(to_string(time-QueueToModify[0].TimeBeforeInterruption) + " " + to_string(QueueToModify[0].ProcessID) + " " + to_string(QueueToModify[0].TimeBeforeInterruption) + "X");
        }

        std::sort(QueueToModify.begin(), QueueToModify.end(), compareByArrivalTime);
        for(int i = 0; i<QueueBasedOnArrival.size(); i++)
        {
            for(int j = 0; j < QueueToModify.size(); j++)
            {
                if(QueueBasedOnArrival[i].ProcessID == QueueToModify[j].ProcessID)
                {
                    QueueBasedOnArrival[i] = QueueToModify[j];
                    break;
                }
            }
        }
        QueueToModify.clear();
    }
    
    std::sort(QueueBasedOnArrival.begin(), QueueBasedOnArrival.end(), compareByProcessID);
    processCaseOutput(time, QueueBasedOnArrival, ResultsPerCase, OperationStepByStep);
}

void runP(vector<ProcessDescription> &ListOfProcesses, vector<string> &ResultsPerCase)
{
    int time = 0;
    std::vector<string> OperationStepByStep;

    //setup queue
    std::vector<ProcessDescription> QueueBasedOnArrival(ListOfProcesses.size());
    QueueBasedOnArrival = ListOfProcesses;
    std::sort(QueueBasedOnArrival.begin(), QueueBasedOnArrival.end(), compareByArrivalTime); 
    std::vector<ProcessDescription> QueueToModify(0);

    //Set RemainingTime equal to BurstTime
    for(int i = 0; i <QueueBasedOnArrival.size(); i++)
    {
        QueueBasedOnArrival[i].RemainingTime = QueueBasedOnArrival[i].BurstTime;
    }

    time = QueueBasedOnArrival[0].ArrivalTime;
    //https://www.cplusplus.com/reference/vector/vector/clear/
    while(true)
    {
        for(int i = 0; i <QueueBasedOnArrival.size(); i++)
        {
            if((time >= QueueBasedOnArrival[i].ArrivalTime) && (!QueueBasedOnArrival[i].IsCompleted))
            {
                QueueToModify.push_back(QueueBasedOnArrival[i]);
            }
        }
        if(QueueToModify.size() == 0)
        {
            break;
        }
        std::sort(QueueToModify.begin(), QueueToModify.end(), compareByPriority);
        QueueToModify[0].RemainingTime--;
        //to edit-start
        QueueToModify[0].TimeBeforeInterruption++;
        if(!QueueToModify[0].PreviouslyEdited) //if currentprocess is not the previously edited process
        {
            if(!QueueToModify[0].HasStarted)
            {
                QueueToModify[0].HasStarted = true;
                QueueToModify[0].ResponseTime = time - QueueToModify[0].ArrivalTime;
            }
            QueueToModify[0].PreviouslyEdited = true;
            for(int i = 1; i<QueueToModify.size(); i++)
            {
                QueueToModify[i].PreviouslyEdited = false;
                if(QueueToModify[i].TimeBeforeInterruption != 0) //if previousprocess has running time
                {
                    OperationStepByStep.push_back(to_string(time-QueueToModify[i].TimeBeforeInterruption) + " " + to_string(QueueToModify[i].ProcessID) + " " + to_string(QueueToModify[i].TimeBeforeInterruption));
                    QueueToModify[i].TimeBeforeInterruption = 0;
                }
            }
        }
        time++;

        if(QueueToModify[0].RemainingTime==0)
        {
            QueueToModify[0].IsCompleted = true;
            QueueToModify[0].TimeOfCompletion = time;
            QueueToModify[0].TurnaroundTime = QueueToModify[0].TimeOfCompletion - QueueToModify[0].ArrivalTime;
            QueueToModify[0].WaitTime = QueueToModify[0].TurnaroundTime - QueueToModify[0].BurstTime;
            OperationStepByStep.push_back(to_string(time-QueueToModify[0].TimeBeforeInterruption) + " " + to_string(QueueToModify[0].ProcessID) + " " + to_string(QueueToModify[0].TimeBeforeInterruption) + "X");
        }

        std::sort(QueueToModify.begin(), QueueToModify.end(), compareByArrivalTime);
        for(int i = 0; i<QueueBasedOnArrival.size(); i++)
        {
            for(int j = 0; j < QueueToModify.size(); j++)
            {
                if(QueueBasedOnArrival[i].ProcessID == QueueToModify[j].ProcessID)
                {
                    QueueBasedOnArrival[i] = QueueToModify[j];
                    break;
                }
            }
        }
        QueueToModify.clear();
    }
    
    std::sort(QueueBasedOnArrival.begin(), QueueBasedOnArrival.end(), compareByProcessID);
    processCaseOutput(time, QueueBasedOnArrival, ResultsPerCase, OperationStepByStep);
}

void runRR(vector<ProcessDescription> &ListOfProcesses, int q, vector<string> &ResultsPerCase)
{
    int time = 0;
    std::vector<string> OperationStepByStep;

    //setup queue
    std::vector<ProcessDescription> QueueCopyOfOriginal(ListOfProcesses.size());
    QueueCopyOfOriginal = ListOfProcesses;
    std::sort(QueueCopyOfOriginal.begin(), QueueCopyOfOriginal.end(), compareByArrivalTime); 
    std::vector<ProcessDescription> QueueToModify(0);

    //Set RemainingTime equal to BurstTime
    for(int i = 0; i <QueueCopyOfOriginal.size(); i++)
    {
        QueueCopyOfOriginal[i].RemainingTime = QueueCopyOfOriginal[i].BurstTime;
    }
    time = QueueCopyOfOriginal[0].ArrivalTime;
    QueueToModify.push_back(QueueCopyOfOriginal[0]);

    int BackJump = -1;

    for(int i = 0; i<QueueToModify.size(); i++) //main operation
    {
        if(!QueueToModify[i].IsCompleted)
        {
            if(!QueueToModify[i].HasStarted)
            {
                QueueToModify[i].HasStarted = true;
                QueueToModify[i].ResponseTime = time - QueueToModify[i].ArrivalTime;
            }
            if(QueueToModify[i].RemainingTime <= q)
            {
                OperationStepByStep.push_back(to_string(time) + " " + to_string(QueueToModify[i].ProcessID) + " " + to_string(QueueToModify[i].RemainingTime) + "X");
                time += QueueToModify[i].RemainingTime;
                QueueToModify[i].RemainingTime = 0;
                QueueToModify[i].IsCompleted = true;
                QueueToModify[i].TimeOfCompletion = time;
                QueueToModify[i].TurnaroundTime = QueueToModify[i].TimeOfCompletion - QueueToModify[i].ArrivalTime;
                QueueToModify[i].WaitTime = QueueToModify[i].TurnaroundTime - QueueToModify[i].BurstTime;
            }
            else
            {
                OperationStepByStep.push_back(to_string(time) + " " + to_string(QueueToModify[i].ProcessID) + " " + to_string(q));
                time += q;
                QueueToModify[i].RemainingTime -= q;
            }
        }
        bool IsTheRobinDone = true;
        if(QueueToModify.size() < QueueCopyOfOriginal.size())
        {
            for(int j = QueueToModify.size(); j <QueueCopyOfOriginal.size(); j++)
            {
                if(QueueCopyOfOriginal[j].ArrivalTime <= time)
                {
                    QueueToModify.push_back(QueueCopyOfOriginal[j]);
                    if(j-i > 1)
                    {
                        BackJump = i;
                        i++;
                    }
                    break;
                }
                else
                {
                    i = BackJump;
                    BackJump = -1;
                }
            }
        }

        for(int j = 0; j<QueueToModify.size(); j++)
        {
            IsTheRobinDone *= QueueToModify[j].IsCompleted;
        }
        
        if(i==QueueToModify.size()-1)
        {
            if(IsTheRobinDone)
            {
                break;
            }
            else
            {
                i = -1;
            }
        }
    }

    std::sort(QueueToModify.begin(), QueueToModify.end(), compareByArrivalTime);
    for(int i = 0; i<QueueCopyOfOriginal.size(); i++)
    {
        for(int j = 0; j < QueueToModify.size(); j++)
        {
            if(QueueCopyOfOriginal[i].ProcessID == QueueToModify[j].ProcessID)
            {
                QueueCopyOfOriginal[i] = QueueToModify[j];
                break;
            }
        }
    }
    std::sort(QueueCopyOfOriginal.begin(), QueueCopyOfOriginal.end(), compareByProcessID);
    processCaseOutput(time, QueueCopyOfOriginal, ResultsPerCase, OperationStepByStep);
}

void getProcessDescriptions(vector<ProcessDescription> &ListOfProcesses) //https://www.geeksforgeeks.org/passing-vector-function-cpp/
{
    for(int i = 0; i < ListOfProcesses.size(); i++) //https://www.tutorialspoint.com/how-do-i-find-the-length-of-an-array-in-c-cplusplus
    {
        ProcessDescription temp;
        temp.ProcessID = i + 1;
        scanf("%d %d %d", &temp.ArrivalTime, &temp.BurstTime, &temp.PriorityValue);
        ListOfProcesses[i] = temp;
    }
}

void passProcessesToOperation(vector<ProcessDescription> &ListOfProcesses, string operation, int quantum, vector<string> &ResultsPerCase)
{
    if (operation == "FCFS")
    {
        runFCFS(ListOfProcesses, ResultsPerCase);
    }
    else if (operation == "SJF")
    {
        runSJF(ListOfProcesses, ResultsPerCase);
    }
    else if (operation == "SRTF")
    {
        runSRTF(ListOfProcesses, ResultsPerCase);
    }
    else if (operation == "P")
    {
        runP(ListOfProcesses, ResultsPerCase);
    }
    else if (operation == "RR")
    {
        runRR(ListOfProcesses, quantum, ResultsPerCase);
    }
}

void initOperation(int CaseNumber, vector<string> &ResultsPerCase)
{
    int ProcessesCount = 5;
    int Quantum = 0;
    char OperationType[5];
    scanf("%d %s", &ProcessesCount, &OperationType);
    if(std::string(OperationType) == "RR") //https://stackoverflow.com/questions/8960087/how-to-convert-a-char-array-to-a-string
    {
        scanf("%d", &Quantum);
    }
    ResultsPerCase.push_back(to_string(CaseNumber + 1) + " " + OperationType);

    std::vector<ProcessDescription> ListOfProcesses(ProcessesCount); //https:stackoverflow.com/questions/28625465/c-creating-an-array-with-a-size-entered-by-the-user
    getProcessDescriptions(ListOfProcesses);
    passProcessesToOperation(ListOfProcesses, OperationType, Quantum, ResultsPerCase);
}

void displayAllCaseResults(vector<vector<string>> AllResults)
{
    cout << endl;
    for(int i = 0; i<AllResults.size(); i++)
    {
        std::vector<string> temp(AllResults[i].size());
        temp = AllResults[i];
        for(int j = 0; j<temp.size(); j++)
        {
            cout << temp[j] << endl;
        }
    }
}

int main(void)
{
    int cases;
    cases = getNumOfTestCases();

    std::vector<std::vector<string>> AllResults(cases); //https://stackoverflow.com/questions/36497674/create-an-array-of-vectors-in-c

    for(int i = 0; i<cases; i++)
    {
        initOperation(i, AllResults[i]);
    }
    displayAllCaseResults(AllResults);
    return 0;
}