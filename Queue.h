#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include <string>
#include <vector>

#include "Node.h"

/**
 * @brief Classe que implementa um iterador para a classe Queue
 *
 */
template <typename Type>
class iterator_queue {
   private:
    Node<int>* m_ptr;  // ponteiro para o no atual
   public:
    /**
     * @brief Construtor da classe iterator_queue
     *
     * @param ptr
     */
    iterator_queue(Node<Type>* ptr) { m_ptr = ptr; }

    /**
     * @brief Sobrecarga do operador de pré-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     *
     * @return iterator& retorna uma referencia para o iterador
     */
    iterator_queue& operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }

    /**
     * @brief Sobrecarga do operador de pós-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     *
     * @return iterator retorna o iterador antes de ser incrementado
     */
    iterator_queue operator++(int) {
        iterator_queue temp = *this;
        m_ptr = m_ptr->next;
        return temp;
    }

    /**
     * @brief Sobrecarga do operador de indireção.
     * Retorna o valor armazenado no Node apontado pelo iterador.
     *
     * @return Type& retorna uma referencia para o dado armazenado no Node
     */
    Type& operator*() { return m_ptr->data; }

    /**
     * @brief Sobrecarga do operador de igualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para o mesmo nó
     * @return false caso contrário
     */
    bool operator==(const iterator_queue& other) {
        return m_ptr == other.m_ptr;
    }

    /**
     * @brief Sobrecarga do operador de desigualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para nós diferentes
     * @return false caso contrário
     */
    bool operator!=(const iterator_queue& other) {
        return m_ptr != other.m_ptr;
    }
};

template <typename Type>
class Queue {
   private:
    Node<Type>* m_head;  // ponteiro para o no sentinela
    Node<Type>* m_tail;  // ponteiro para o ultimo nó da fila
    unsigned m_size{};   // quantidade de elementos na fila

   public:
    /**
     * @brief Construtor da classe Queue. Cria uma fila vazia.
     *
     */
    Queue() {
        m_head = new Node<Type>(Type(), nullptr);
        m_tail = m_head;
        m_size = 0;
    }

    /**
     * @brief Construtor de cópia da classe Queue
     *
     * @param lst - fila a ser copiada
     */
    Queue(const Queue& lst) {
        m_head = new Node<Type>(Type(), nullptr);
        Node<Type>* aux = lst.m_head;
        while (aux != nullptr) {
            push(aux->data);
            aux = aux->next;
        }
        m_size = lst.m_size;
    }

    /**
     * @brief Destrutor da classe Queue.
     * Libera toda a memoria alocada, ate mesmo o nó sentinela
     *
     */
    ~Queue() { delete m_head; }

    /**
     * @brief Funçãi que verifica se uma lista está vazia.
     *
     * @return true se a lista está vazia,
     * @return false caso contrário
     */
    bool empty() const { return m_head->next == nullptr; }

    /**
     * @brief Função que retorna o número de elementos na fila
     *
     * @return unsigned int
     */
    unsigned int size() const { return m_size; }

    /**
     * @brief Função que remove todos os elementos da lista: size() == 0
     *
     */
    void clear() { delete m_head; }

    /**
     * @brief Função que insere um elemento na fila. O elemento é inserido no
     * final da fila.
     *
     * @param val - valor a ser inserido
     */
    void push(const int& val) {
        Node<Type>* aux = new Node<Type>(val, nullptr);
        if (m_size > 0) {
            m_tail->next = aux;
            m_tail = aux;
        } else {
            m_tail = m_head = aux;
        }
        m_size++;
    }

    /**
     * @brief Função que retorna uma referencia para o primeiro elemento da fila
     *
     * @return int&
     */
    int& front() {
        if (m_size == 0) throw std::runtime_error("empty queue");
        return m_head->data;
    }

    /**
     * @brief Função que retorna uma referencia para o primeiro elemento da fila
     *
     * @return const int&
     */
    const int& front() const {
        if (m_size == 0) throw std::runtime_error("empty queue");
        return m_head->data;
    }

    /**
     * @brief Função que remove o primeiro elemento da fila
     *
     */
    void pop() {
        Node<Type>* aux = m_head;
        void pop() {
            if (m_size == 0) throw std::runtime_error(" empty queue ");
            Node<Type>* aux = m_head;
            m_head = aux->next;
            aux->next = nullptr;
            delete aux;
            m_size--;
        }

        /**
         * @brief Função que retorna uma referencia para o último elemento da
         * fila
         *
         * @return int&
         */
        int& back() {
            if (m_size == 0) throw std::runtime_error("empty queue");
            return m_tail->data;
        }

        /**
         * @brief Função que retorna uma referencia para o último elemento da
         * fila
         *
         * @return const int&
         */
        const int& back() const {
            if (m_size == 0) throw std::runtime_error("empty queue");
            return m_tail->data;
        }

        /**
         * @brief Função que retorna um iterador que aponta para o primeiro
         * elemento da fila
         *
         * @return iterator_queue<Type>
         */
        iterator_queue<Type> begin() { return iterator_queue<Type>(m_head); }

        /**
         * @brief Função que retorna um iterador que aponta para o primeiro bit
         * após o último elemento da fila
         *
         * @return iterator_queue<Type>
         */
        iterator_queue<Type> end() {
            return iterator_queue<Type>(m_tail->next);
        }
    };

#endif