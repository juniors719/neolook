#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H
#include <string>
#include <vector>

#include "Node.h"

/**
 * @brief
 *
 */
template <typename Type>
class iterator {
   private:
    Node<Type>* m_ptr;  // ponteiro para o Node atual

   public:
    /**
     * @brief Construtor da classe iterator
     *
     * @param ptr ponteiro para o Node atual
     */
    iterator(Node<Type>* ptr = nullptr) { m_ptr = ptr; }

    /**
     * @brief Sobrecarga do operador de desreferenciação
     *
     * @return Type& referencia para o dado armazenado no Node atual
     */
    Type& operator*() { return m_ptr->data; }

    /**
     * @brief Sobrecarga do operador de pré-incremento
     *
     * @return iterator& - referência para o próprio objeto
     */
    iterator& operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }

    /**
     * @brief Sobrecarga do operador de pós-incremento
     *
     * @return iterator - cópia do objeto antes de ser incrementado
     */
    iterator operator++(int) {
        iterator temp = *this;
        m_ptr = m_ptr->next;
        return temp;
    }

    /**
     * @brief Sobrecarga do operador de igualdade. Compara dois iterators, e
     * verifica se eles apontam para o mesmo Node.
     *
     * @param other objeto a ser comparado
     * @return true se os objetos forem iguais,
     * @return false caso contrário
     */
    bool operator==(const iterator& other) const {
        return m_ptr == other.m_ptr;
    }

    /**
     * @brief Sobrecarga do operador de diferença. Compara dois iterators, e
     * verifica se eles apontam para Nodes diferentes.
     *
     * @param other objeto a ser comparado
     * @return true se os objetos forem diferentes,
     * @return false caso contrário
     */
    bool operator!=(const iterator& other) const {
        return m_ptr != other.m_ptr;
    }
};

/**
 * @brief Classe que implementa a logica de uma lista duplamente encadeada
 *
 * @tparam Type
 */
template <typename Type>
class OrderedList {
   private:
    Node<Type>* m_head;  // ponteiro para o no sentinela
    Node<Type>* m_tail;  // ponteiro para o ultimo no da lista
    unsigned m_size{};

   public:
    /**
     * @brief Construtor da classe OrderedList
     *
     */
    OrderedList() {
        m_head = new Node<Type>();  // cria o no sentinela
        m_tail = m_head;            // inicializa o ponteiro para o ultimo no
    }

    /**
     * @brief Construtor de cópia da classe OrderedList
     *
     * @param lst lista a ser copiada
     */
    OrderedList(const OrderedList& lst) {
        m_head = new Node<Type>();  // cria o no sentinela
        m_tail = m_head;            // inicializa o ponteiro para o ultimo no
        Node<Type>* aux = lst.m_head->next;
        while (aux != nullptr) {
            insert(aux->data);
            aux = aux->next;
        }
    }

    /**
     * @brief Destrutor da classe OrderedList
     *
     */
    ~OrderedList() {
        Node<Type>* aux = m_head;
        while (aux != nullptr) {
            Node<Type>* aux2 = aux;
            aux = aux->next;
            delete aux2;
        }
    }

    /**
     * @brief Função que verifica se a lista está vazia
     *
     * @return true se a lista estiver vazia,
     * @return false caso contrário
     */
    bool isEmpyt() const { return m_size == 0; }

    /**
     * @brief Função que retorna o tamanho atual da lista
     *
     * @return int tamanho da lista
     */
    int size() const { return m_size; }

    /**
     * @brief Função que deleta todos os elementos da lista, deixando-a vazia.
     * Ao final da execução, os ponteiros m_head e m_tail devem apontar para si
     * mesmos. Complexidade: O(n)
     *
     *
     */
    void clear() {
        Node<Type>* aux = m_head->next;
        while (aux != nullptr) {
            Node<Type>* aux2 = aux;
            aux = aux->next;
            delete aux2;
        }
        m_head->next = nullptr;
        m_tail = m_head;
        m_size = 0;
    }

    /**
     * @brief Função que insere um elemento na lista, mantendo a ordem crescente
     *
     * @param val
     */
    void insert(const Type& val) {
        Node<Type>* aux = m_head->next;  // auxiliar para percorrer a lista
        Node<Type>* aux2 = m_head;       // auxiliar para guardar o anterior
        while (aux != nullptr && aux->data < val) {  // procura a posicao
            aux2 = aux;
            aux = aux->next;
        }
        Node<Type>* novo = new Node<Type>(val, aux, aux2);  // cria o novo nó
        aux2->next = novo;
        if (aux != nullptr) {
            aux->prev = novo;
        } else {
            m_tail = novo;
        }
        m_size++;
    }

    /* // construtor: cria lista vazia
    OrderedList();

    // construtor de copia
    OrderedList(const OrderedList& lst);

    // retorna true se e somente se a lista esta vazia
    bool empty() const;

    // retorna o numero de elementos na lista
    int size() const;

    // deixa a lista vazia: size() == 0
    void clear();

    // destrutor: libera toda a memoria alocada, ate mesmo o no sentinela
    ~OrderedList();

    // Imprime a lista no terminal
    void print() const;

    // --------------------------------------------------------- //
    // ----------- funcoes adicionais - parte 1 ---------------- //
    // --------------------------------------------------------- //

    // insere um elemento no inicio da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void push_front(const int& val);

    // retorna uma referencia para o primeiro elemento na lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    int& front();
    const int& front() const;

    // deleta o primeiro elemento da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void pop_front();

    // retorna uma referencia para o ultimo elemento na lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    int& back();
    const int& back() const;

    // insere um elemento no final da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void push_back(const int& val);

    // deleta o ultimo elemento da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void pop_back(); */
};

#endif