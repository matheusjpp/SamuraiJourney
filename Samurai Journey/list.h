#include <iostream>
#include <stdexcept>

namespace Lists {

template <class T>
class List {
private:
    // Classe interna Node como template
    template <class U>
    class Node {
    private:
        U data;           // Armazena o valor diretamente
        Node* next;       // Ponteiro para o próximo nó
        Node* prev;       // Ponteiro para o nó anterior

    public:
        explicit Node(const U& value) : data(value), next(nullptr), prev(nullptr) {}

        U& getData() { return data; }
        const U& getData() const { return data; }

        void setData(const U& value) { data = value; }

        Node* getNext() const { return next; }
        void setNext(Node* node) { next = node; }

        Node* getPrev() const { return prev; }
        void setPrev(Node* node) { prev = node; }

        friend class List; // Permite que List acesse os membros privados
    };

    // Ponteiros para o início e fim da lista
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    // Classe iteradora como template
    template <class U>
    class iterator {
    private:
        Node<U>* current;  // Ponteiro para o nó atual
    public:
        explicit iterator(Node<U>* node = nullptr) : current(node) {}

        // Operador de desreferenciação
        U& operator*() const {
            return current->getData();
        }

        // Operador de incremento prefixado
        iterator& operator++() {
            current = current->getNext();
            return *this;
        }

        // Operador de decremento prefixado
        iterator& operator--() {
            current = current->getPrev();
            return *this;
        }

        // Operador de igualdade
        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        // Operador de desigualdade
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

        Node<U>* getNode() const {
            return current;
        }
    };

    // Construtor
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Destrutor
    ~List() {
        clear();
    }

    // Adiciona um elemento ao final da lista
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        size++;
    }

    // Limpa todos os elementos da lista
    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->getNext();
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    // Retorna o tamanho da lista
    int getSize() const {
        return size;
    }

    // Métodos de acesso/modificação de dados no nó
    T getData(iterator<T> it) const {
        if (it.getNode()) {
            return it.getNode()->getData();
        }
        throw std::out_of_range("Iterator inválido");
    }

    void setData(iterator<T> it, const T& value) {
        if (it.getNode()) {
            it.getNode()->setData(value);
        }
        else {
            throw std::out_of_range("Iterator inválido");
        }
    }

    // Retorna um iterador para o início da lista
    iterator<T> begin() {
        return iterator<T>(head);
    }

    // Retorna um iterador para o final da lista (nullptr)
    iterator<T> end() {
        return iterator<T>(nullptr);
    }
};

}