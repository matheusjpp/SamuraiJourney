#include <iostream>
#include <stdexcept>

template <class T>
class List {
private:
    // Classe interna Node com membros privados
    class Node {
    private:
        T data;           // Armazena o valor diretamente
        Node* next;       // Ponteiro para o próximo nó
        Node* prev;       // Ponteiro para o nó anterior

    public:
        explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

        T& getData() { return data; }
        const T& getData() const { return data; }

        void setData(const T& value) { data = value; }

        Node* getNext() const { return next; }
        void setNext(Node* node) { next = node; }

        Node* getPrev() const { return prev; }
        void setPrev(Node* node) { prev = node; }

        friend class List; // Permite que List acesse os membros privados
        friend class iterator; // Permite que iterator acesse os membros privados
    };

    Node* head;  // Início da lista
    Node* tail;  // Fim da lista
    int size;    // Tamanho da lista

public:
    // Classe iteradora
    class iterator {
    private:
        Node* current;  // Ponteiro para o nó atual
    public:
        explicit iterator(Node* node = nullptr) : current(node) {}

        // Operador de desreferenciação
        T& operator*() const {
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

        // Acesso ao nó atual
        Node* getNode() const {
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
        Node* newNode = new Node(value);
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
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->getNext();
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
    T getData(iterator it) const {
        if (it.getNode()) {
            return it.getNode()->getData();
        }
        throw std::out_of_range("Iterator inválido");
    }

    void setData(iterator it, const T& value) {
        if (it.getNode()) {
            it.getNode()->setData(value);
        }
        else {
            throw std::out_of_range("Iterator inválido");
        }
    }

    // Retorna um iterador para o início da lista
    iterator begin() {
        return iterator(head);
    }

    // Retorna um iterador para o final da lista (nullptr)
    iterator end() {
        return iterator(nullptr);
    }
};
