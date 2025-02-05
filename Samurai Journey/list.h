#pragma once
#include "Entity.h"
#include <cstddef> // Para nullptr

namespace List {

    template <typename T>
    class List {
    private:
        // Classe Node privada
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        };

        Node* head; // Início da lista
        Node* tail; // Fim da lista
        size_t size; // Tamanho da lista

    public:
        // Classe Iterator aninhada
        class Iterator {
        private:
            Node* current;

        public:
            explicit Iterator(Node* node = nullptr) : current(node) {}

            T& operator*() const { return current->data; }

            Iterator& operator++() {
                current = current->next;
                return *this;
            }

            Iterator operator++(int) {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            Iterator& operator--() {
                current = current->prev;
                return *this;
            }

            Iterator operator--(int) {
                Iterator temp = *this;
                --(*this);
                return temp;
            }

            bool operator==(const Iterator& other) const { return current == other.current; }
            bool operator!=(const Iterator& other) const { return current != other.current; }
        };

        // Construtor
        List() : head(nullptr), tail(nullptr), size(0) {}

        // Destrutor
        ~List() { clear(); }

        // Adiciona ao final da lista
        void push_back(const T& value) {
            Node* newNode = new Node(value);
            if (tail) {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            else {
                head = tail = newNode;
            }
            size++;
        }

        // Remove um elemento da lista
        void remove(const T& value) {
            Node* current = head;
            while (current && current->data != value) {
                current = current->next;
            }

            if (current) {
                if (current == head) {
                    head = head->next;
                    if (head) head->prev = nullptr;
                }
                else if (current == tail) {
                    tail = tail->prev;
                    if (tail) tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                size--;
            }
        }

        // Limpa a lista
        void clear() {
            Node* current = head;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            head = tail = nullptr;
            size = 0;
        }
        


        // Retorna o tamanho da lista
        size_t getSize() const { return size; }

        // Iteradores
        Iterator begin() { return Iterator(head); }
        Iterator end() { return Iterator(nullptr); }

        Iterator rbegin() { return Iterator(tail); }
        Iterator rend() { return Iterator(nullptr); }
    };
}