#pragma once

namespace List {

    template <class T>
    class List {
    private:
        class Node {
        private:
            T* data;               // Armazena o valor diretamente
            Node* next;            // Ponteiro para o pr�ximo n�
            Node* prev;            // Ponteiro para o n� anterior
        public:
            Node() : data(nullptr), next(nullptr), prev(nullptr) {}
            ~Node() { data = nullptr; next = nullptr; prev = nullptr; }

            void setData(T* d) { data = d; }
            void setNext(Node* n) { next = n; }
            void setPrev(Node* p) { prev = p; }

            T* getData() const { return data; }
            Node* getNext() { return next; }
            Node* getPrev() { return prev; }
        };

        Node* head;  // In�cio da lista
        Node* tail;  // Fim da lista
        int size;    // Tamanho da lista

    public:
        // Classe iteradora
        class iterator {
        private:
            Node* current;  // Ponteiro para o n� atual
        public:
            explicit iterator(Node* node = nullptr) : current(node) {}

            T* operator*() const {
                return current->getData();
            }

            iterator& operator++() {
                current = current->getNext();
                return *this;
            }

            iterator& operator--() {
                current = current->getPrev();
                return *this;
            }

            bool operator==(const iterator& other) const {
                return current == other.current;
            }

            bool operator!=(const iterator& other) const {
                return current != other.current;
            }
        };

        // Construtor
        List() : head(nullptr), tail(nullptr), size(0) {}

        // Destrutor
        ~List() {
            clear();
        }

        void push_back(T* data) {
            Node* aux = new Node();
            aux->setData(data);
            if (head == nullptr) {
                head = tail = aux;
            }
            else {
                tail->setNext(aux);
                aux->setPrev(tail);
                tail = aux;
            }
            size++;
        }

        void remove(T* data) {
            Node* aux = head;
            while (aux != nullptr && aux->getData() != data) {
                aux = aux->getNext();
            }
            if (aux != nullptr) {
                if (aux == head) {
                    head = aux->getNext();
                    if (head != nullptr) {
                        head->setPrev(nullptr);
                    }
                }
                else if (aux == tail) {
                    tail = aux->getPrev();
                    if (tail != nullptr) {
                        tail->setNext(nullptr);
                    }
                }
                else {
                    aux->getPrev()->setNext(aux->getNext());
                    aux->getNext()->setPrev(aux->getPrev());
                }
                delete aux;
                size--;
            }
        }

        void clear() {
            Node* current = head;
            while (current != nullptr) {
                Node* next = current->getNext();
                if (current->getData()) {
                    delete current->getData(); // Deleta o dado do n�
                }
                delete current;
                current = next;
            }
            head = tail = nullptr;
            size = 0;
        }

        int getSize() const {
            return size;
        }

        iterator begin() {
            return iterator(head);
        }

        iterator end() {
            return iterator(nullptr);
        }
    };
}
