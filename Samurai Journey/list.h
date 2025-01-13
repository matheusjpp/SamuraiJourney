#include <iostream>
#pragma once

namespace List {

    template <class T>

    class List {
    private:
        Node* head;  // In�cio da lista
        Node* tail;  // Fim da lista
        int size;    // Tamanho da lista
        // Classe interna Node
    public:
        template <class T1>
        class Node {
        private:
            T1* data;           // Armazena o valor diretamente
            Node<T1>* next;       // Ponteiro para o pr�ximo n�
            Node<T1>* prev;       // Ponteiro para o n� anterior
        public:
            Node() : data(nullptr), next(nullptr), prev(nullptr) {}
            ~Node{ data = nullptr; next = nullptr; prev = nullptr; }

                void setData(T1* d) {
                data = d;
            }

            void setNext(Node<T1>* n) {
                next = n;
            }

            void setPrev(Node<T1>* p) {
                prev = p;
            }
            T1* getData() const { return data; }
            Node<T1>* getPrev{ return prev; }
            Node<T1>* getNext{ return next; }
        };

        // Classe iteradora
        class iterator {
        private:
            Node<T>* current;  // Ponteiro para o n� atual
        public:
            explicit iterator(Node* node = nullptr) : current(node) {}

            // Operador de desreferencia��o
            T& operator*() const {
                return current->data;
            }

            // Operador de incremento prefixado
            iterator& operator++() {
                current = current->next;
                return *this;
            }

            // Operador de decremento prefixado
            iterator& operator--() {
                current = current->prev;
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

            // Acesso ao n� atual (para m�todos como getData ou setData)
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
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            size++;
        }

        // Limpa todos os elementos da lista
        void clear() {
            Node<T1>* current = head;
            while (current != nullptr) {
                Node<T1>* next = current->next;
                if (current->getData()) {
                    delete current->getData;//deleta o dado do n�
                }
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

        // M�todos de acesso/modifica��o de dados no n�
        T getData(iterator it) const {
            if (it.getNode()) {
                return it.getNode()->data;
            }
            throw std::out_of_range("Iterator inv�lido");
        }

        void setData(iterator it, const T& value) {
            if (it.getNode()) {
                it.getNode()->data = value;
            }
            else {
                throw std::out_of_range("Iterator inv�lido");
            }
        }

        // Retorna um iterador para o in�cio da lista
        iterator begin() {
            return iterator(head);
        }

        // Retorna um iterador para o final da lista (nullptr)
        iterator end() {
            return iterator(nullptr);
        }
    };
}