#include <iostream>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::endl;

// Estrutura do Nó
typedef struct Node {
    Node* ptrNext;
    Node* ptrPrev;
    int iData;
} Node;

// Protótipo de funções - questão 1
Node* newNode(int);
Node* newList(int[], Node**, int);
void showList(Node*);
void advanceList(Node**);
void reverseList(Node**);
void removeNodeById(Node**, int);
void clearList(Node**);
Node* mergePlaylists(Node*, Node*);

// Protótipo de funções - questão 2
bool hasLoop(Node*);

// Protótipo de funções - questão 3
Node* ouroBoros(int, int);

int main() {
    // Array de dados para criar a lista 1
    int array1[] = {1, 2, 3, 4, 5};
    Node* head1 = nullptr;
    newList(array1, &head1, 5);

    // Array de dados para criar a lista 2
    int array2[] = {6, 7, 8};
    Node* head2 = nullptr;
    newList(array2, &head2, 3);

    // Mostrar listas originais
    cout << "Lista 1: ";
    showList(head1);
    cout << "Lista 2: ";
    showList(head2);
    cout << "===============================" << endl;

    // Avançar na lista 1 e mostrar
    advanceList(&head1);
    cout << "Avançando na Lista 1:" << endl;
    showList(head1);
    cout << "===============================" << endl;

    // Retroceder na lista 2 e mostrar
    reverseList(&head2);
    cout << "Retrocedendo na Lista 2:" << endl;
    showList(head2);
    cout << "===============================" << endl;

    // Remover nó com ID 3 da lista 1 e mostrar atualização
    removeNodeById(&head1, 3);
    cout << "Removendo o nó com ID 3 da Lista 1:" << endl;
    showList(head1);
    cout << "===============================" << endl;

    // Juntar as duas listas e mostrar a lista combinada
    Node* mergedList = mergePlaylists(head1, head2);
    cout << "Lista combinada das Playlists:" << endl;
    showList(mergedList);
    cout << "===============================" << endl;

    // Verifica se há loop na lista 1
    bool hasLoopInList1 = hasLoop(head1);
    if (hasLoopInList1) {
        cout << "Lista 1 possui um loop." << endl;
    } else {
        cout << "Lista 1 não possui um loop." << endl;
    }
    cout << "===============================" << endl;

    // Teste ouroboros

    Node* head3 =  ouroBoros(224, 3);
    showList(head3);

    Node* head4 =  ouroBoros(12, 3);
    showList(head4);

    Node* head5 =  ouroBoros(320, 3);
    showList(head5);

    cout << "===============================" << endl;

    // Liberar memória das listas
    clearList(&head1);
    clearList(&head2);
    clearList(&head3);
    clearList(&head4);
    clearList(&head5);
    clearList(&mergedList);
    cout << "Listas liberadas." << endl;
    showList(head1);

    cout << "===============================" << endl;

    return 0;
}

// Questão 1:

// Função para criar um novo nó com um valor específico
Node* newNode(int iValue) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->iData = iValue;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;

    return temp;
}

// Função para criar uma nova lista duplamente encadeada a partir de um array de inteiros
Node* newList(int iArray[], Node** head, int iSize) {
    // Cria o primeiro nó da lista
    Node* node = newNode(iArray[0]);
    (*head) = node;
    Node* current = (*head);

    // Percorre o array para criar os nós subsequentes
    for(int c = 1; c < iSize; c++) {
        node = newNode(iArray[c]);
        current->ptrNext = node;
        node->ptrPrev = current;
        current = node;
    }

    // Fecha o ciclo da lista
    current->ptrNext = (*head);
    (*head)->ptrPrev = current;

    return *head;
}

// Função para mostrar os dados da lista
void showList(Node* head) {
    if (head == nullptr) {
        cout << "Lista vazia." << endl;
        return;
    }

    Node* current = head;
    cout << "Lista: ";
    do {
        cout << current->iData << " ";
        current = current->ptrNext;
    } while (current != head);
    cout << endl;
}

// Função para avançar na lista circular
void advanceList(Node** head) {
    if ((*head) == nullptr) return;
    (*head) = (*head)->ptrNext;
}

// Função para retroceder na lista circular
void reverseList(Node** head) {
    if ((*head) == nullptr) return;
    (*head) = (*head)->ptrPrev;
}

// Função para remover um nó da lista por ID
void removeNodeById(Node** head, int id) {
    if (*head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    Node* current = (*head);

    // Caso especial: remover se for o primeiro e único nó na lista
    if ((*head)->iData == id && (*head)->ptrNext == (*head)) {
        free(*head);
        (*head) = nullptr;
        return;
    }

    // Caso especial: remover se for o primeiro nó, mas não único
    if ((*head)->iData == id) {
        (*head) = (*head)->ptrNext;
        (*head)->ptrPrev = current->ptrPrev;
        current->ptrPrev->ptrNext = (*head);
        free(current);
        return;
    }

    current = current->ptrNext;

    // Percorre a lista para encontrar o nó com o ID especificado
    while(current != (*head) && current->iData != id){
        current = current->ptrNext;
    }

    // Remove o nó caso o tenha encontrado
    if(current->iData == id){
        current->ptrPrev->ptrNext = current->ptrNext;
        current->ptrNext->ptrPrev = current->ptrPrev;
        free(current);
        return;
    }

    // Se o nó com o ID especificado não for encontrado
    cout << "Nó não encontrado" << endl;
}

// Função para liberar toda a memória da lista
void clearList(Node** head) {
    while((*head) != nullptr){
        removeNodeById(head, (*head)->iData);
    }
}

// Função para juntar duas playlists em uma nova lista circular
Node* mergePlaylists(Node* head1, Node* head2) {
    if (head1 == nullptr) {
        return head2;
    }
    if (head2 == nullptr) {
        return head1;
    }

    int size1 = 0, size2 = 0;
    Node* current1 = head1->ptrNext;
    Node* current2 = head2->ptrNext;

    // Contar o tamanho da primeira lista
    do {
        size1++;
        current1 = current1->ptrNext;
    }while (current1 != head1);

    // Contar o tamanho da segunda lista
    do {
        size2++;
        current2 = current2->ptrNext;
    }while (current2 != head2);

    // Criar um array para armazenar os elementos das duas listas
    int iArray[size1 + size2];
    int index = 0;

    current1 = head1;
    current2 = head2;

    // força o loop funcionar pelo menos duas vezes
    int c = 0;

    // Percorre as duas listas adicionando as musicas alternadamente
    while((current1 != head1 && current2 != head2) || c < 2){
        if(index % 2 == 0){
            iArray[index] = current1->iData;
            current1 = current1->ptrNext;
        } else{
            iArray[index] = current2->iData;
            current2 = current2->ptrNext;
        }
        index++;
        c++;
    }

    // Adiciona as músicas restantes da lista 1
    if(current1 != head1){
        while(current1 != head1){
            iArray[index] = current1->iData;
            current1 = current1->ptrNext;
            index++;
        }
    }

    // Adiciona as músicas restantes da lista 2
    if(current2 != head2){
        while(current2 != head2){
            iArray[index] = current2->iData;
            current2 = current2->ptrNext;
            index++;
        }
    }

    // Cria uma nova lista circular com os elementos do vetor
    Node* list = nullptr;
    list = newList(iArray, &list, index);
    
    return list;
}

// Questão 2:

// Função para verificar se há um loop na lista encadeada
bool hasLoop(Node* head) {
    if (head == nullptr) {
        return false;
    }

    // Cria um ponteiro rápido e um lento
    Node* ptrSlow = head;
    Node* ptrFast = head->ptrNext;

    // Ou os dois ponteiro irão se encontrar, ou o rápido chegará ao fim da lista
    while (ptrFast != nullptr && ptrFast != ptrSlow) {
        ptrFast = ptrFast->ptrNext;
        ptrSlow = ptrSlow->ptrNext;
        
        if (ptrFast != nullptr) {
            ptrFast = ptrFast->ptrNext;
        }
    }

    // Retorna se há ou não loop
    return ptrFast == ptrSlow;
}

// Questão 3:

// Função para simular o processo do Ouroboros e criar a lista circular
Node* ouroBoros(int iValue, int iSize) {
    int iArray[iSize];
    iArray[0] = iValue;
    int a, b;

    // Loop para construir o array de valores do Ouroboros
    for (int c = 1; c < iSize; ++c) {
        int potencia2 = 0;
        
        // Divide o número por 2 até que não seja mais divisível
        int tempValue = iArray[0];
        while (tempValue % 2 == 0) {
            tempValue = tempValue / 2;
            potencia2++;
        }

        // Encontra o "a" e "b"
        a = potencia2 + 1;
        b = ((iArray[0] / pow(2, potencia2)) - 1) / 2;

        // Escreve o vetor com os nós do ouroboros
        iArray[0] = a;
        iArray[c] = b;
    }

    // Cria a lista circular diretamente com o array de valores
    Node* ouroBoros = nullptr;
    ouroBoros = newList(iArray, &ouroBoros, iSize);

    return ouroBoros;
}