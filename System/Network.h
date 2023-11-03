#ifndef NETWORK_H
#define NETWORK_H

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class Network {
   private:
    Process process{};     // processo que está sendo executado no disco
    Queue<Process> queue;  // fila de processos do disco
    PriorityQueuePair<Process> pq;  // fila de processos do disco
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;      // indica se o disco está ocupado
    int time;       // tempo de execução do processo atual

   public:
    Network(bool politica) : politica(politica) {
        queue = Queue<Process>();
        pq = PriorityQueuePair<Process>();
        busy = false;
        std::cout << "\tRede criada" << std::endl;
    }

    ~Network() { std::cout << "Rede destruida" << std::endl; }

    // // getters e setters

    // /**
    //  * @brief Retorna o processo que está sendo executado no disco
    //  *
    //  * @return Process*
    //  */
    // Process& getProcess() { return process; }

    /**
     * @brief Seta um processo para ser executado no disco. Se o disco já
     * estiver ocupado, o processo é adicionado na fila de processos do
     disco.
     *
     * @param p Processo a ser executado no disco
     */
    void setProcess(Process& p) {
        if (!busy) {
            process = p;
            busy = true;
            time = 0;
            std::cout << "\t\tProcesso " << process.getInstant()
                      << " inserido na Rede" << std::endl;
        } else {
            if (politica) {
                pq.push(p.getNetwork(), p);
                std::cout << "\t\tProcesso " << process.getInstant()
                          << " carregado no Rede" << std::endl;
            } else {
                queue.push(p);
                std::cout << "\t\tProcesso " << process.getInstant()
                          << " carregado no Rede" << std::endl;
            }
        }
    }

    // void setTime() { time++; }

    // int getTime() { return time; }

    // void setBusy(bool b) { busy = b; }

    // /**
    //  * @brief Função que imprime o estado atual do disco
    //  *
    //  */
    // void print() {
    //     std::cout << "Disco: " << std::endl;
    //     std::cout << "\tEm execução: ";
    //     if (busy)
    //         process.print();
    //     else
    //         std::cout << "Nenhum processo em execução" << std::endl;

    //     std::cout << "\tFila: " << std::endl;
    //     if (politica) {
    //         if (pq.empty())
    //             std::cout << "\t\tFila vazia" << std::endl;
    //         else
    //             for (auto& p : pq) {
    //                 p.print();
    //             }
    //     } else {
    //         if (queue.empty())
    //             std::cout << "\t\tFila vazia" << std::endl;
    //         else
    //             for (auto& p : queue) {
    //                 p.print();
    //             }
    //     }
    // }

    // bool isConcluded() {
    //     if (!busy && queue.empty() && pq.empty()) return true;
    // }

    Process* execute() {
        if (busy) {
            if (time == process.getDisk()) {
                std::cout << "\t\tProcesso " << process.getInstant()
                          << " concluido na Disco" << std::endl;
                busy = false;
                return &process;
            } else {
                time++;
            }
        } else {
            if (politica) {
                if (!pq.empty()) {
                    process = pq.top();
                    pq.pop();
                    busy = true;
                    time = 0;
                    std::cout << "\t\tProcesso " << process.getInstant()
                              << " inserido na fila do Disco" << std::endl;
                }
            } else {
                if (!queue.empty()) {
                    process = queue.front();
                    queue.pop();
                    busy = true;
                    time = 0;
                    std::cout << "\t\tProcesso " << process.getInstant()
                              << " inserido na fila do Disco" << std::endl;
                }
            }
        }
        return nullptr;
    }
};

#endif  // DISK_H