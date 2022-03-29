#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct process_struct {
        int arrivalTime;
        int burstTime;
        int ct, wt, tat, rt, startTime;
        int burstTimeRemaning;

};


int main() {

        int processQuantity, index;
        queue<int> processQueue;
        bool visited[100] = {false}, is_first_process = true;
        int current_time = 0;
        int completed = 0, timeQuantum, total_idle_time = 0;
        float sumTurnAroundTime = 0, sumWaitTime = 0, sumResponseTime = 0;
        process_struct process[100];

        cin >> processQuantity >> timeQuantum;

        for (int i = 0; i < processQuantity; i++) {
                cin >> process[i].arrivalTime >> process[i].burstTime;
                process[i].burstTimeRemaning = process[i].burstTime;
        }

        processQueue.push(0);
        visited[0] = true;

        while (completed != processQuantity) {
                index = processQueue.front();
                processQueue.pop();

                if (process[index].burstTimeRemaning == process[index].burstTime) {
                        process[index].startTime = max(current_time, process[index].arrivalTime);
                        total_idle_time += (is_first_process == true) ? 0 : process[index].startTime - current_time;
                        current_time = process[index].startTime;
                        is_first_process = false;

                }

                if (process[index].burstTimeRemaning - timeQuantum > 0) {
                        process[index].burstTimeRemaning -= timeQuantum;
                        current_time += timeQuantum;

                } else {
                        current_time += process[index].burstTimeRemaning;
                        process[index].burstTimeRemaning = 0;
                        completed++;

                        process[index].ct = current_time;
                        process[index].tat = process[index].ct - process[index].arrivalTime;
                        process[index].wt = process[index].tat - process[index].burstTime;
                        process[index].rt = process[index].startTime - process[index].arrivalTime;

                        sumTurnAroundTime += process[index].tat;
                        sumWaitTime += process[index].wt;
                        sumResponseTime += process[index].rt;

                }

                // check which new Processes needs to be pushed to Ready Queue from Input list
                for (int i = 1; i < processQuantity; i++) {
                        if (process[i].burstTimeRemaning > 0 && process[i].arrivalTime <= current_time && visited[i] == false) {
                                processQueue.push(i);
                                visited[i] = true;

                        }
                }

                // check if Process on CPU needs to be pushed to Ready Queue
                if (process[index].burstTimeRemaning > 0) {
                        processQueue.push(index);

                }

                // if queue is empty, just add one process from list, whose remaining burst time > 0
                if (processQueue.empty()) {
                        for (int i = 1; i < processQuantity; i++) {
                                if (process[i].burstTimeRemaning > 0) {
                                        processQueue.push(i);
                                        visited[i] = true;
                                        break;
                                }
                        }
                }
        }


        // Output
        float averageTurnAroundTime, averageWaiteTime, averageResponseTime;
        averageTurnAroundTime = (float)sumTurnAroundTime / processQuantity;
        averageWaiteTime = (float)sumWaitTime / processQuantity;
        averageResponseTime = (float)sumResponseTime / processQuantity;

        printf("RR %.1f %.1f %.1f\n", averageTurnAroundTime, averageResponseTime, averageWaiteTime);
        
        return 0;
}