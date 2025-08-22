#pragma once

#include <iostream>
#include "Node.h"

//#ifdef _DEBUG
//#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//// allocations to be of _CLIENT_BLOCK type
//#else
//#define new new
//#endif

// 노드 제거 함수.
template<typename T>
void SafeDelete(T*& target)
{
    if (target)
    {
        delete target;
        target = nullptr;
    }
}

template<typename T>
class LinkedList
{
public:
    LinkedList()
        : first(new Node<T>()), last(new Node<T>()), count(0)
    {
        // 시작 노드 서로 연결.
        first->next = last;
        last->previous = first;
    }

    ~LinkedList()
    {
        // 노드 전부 제거.
        Clear();

        // 기본 노드 삭제.
        SafeDelete(first);
        SafeDelete(last);
    }

    // 노드 전체 삭제 함수.
    void Clear()
    {
        // 시작 노드 저장.
        Node<T>* current = first->next;

        // 끝까지 반복하면서 삭제.
        while (current != nullptr && current != last)
        {
            // 다음 노드 임시 저장.
            Node<T>* next = current->next;

            // 현재 노드 제거.
            SafeDelete(current);

            // 다음 노드로 이동.
            current = next;
        }

        // 정리.
        count = 0;

        first->next = last;
        last->previous = first;
    }

    // 마지막 위치에 노드 추가하는 함수.
    void PushLast(const T& newData)
    {
        // 새 노드 생성.
        Node<T>* newNode = new Node<T>();
        newNode->data = newData;

        // newNode:5.
        // [f]<-[1]<-[2]<-[3] <-[5] <-[l]

        // 원래의 마지막 노드 임시 저장.
        // 이전 노드 관련 포인터 정리.
        Node<T>* previous = last->previous;
        previous->next = newNode;
        newNode->previous = previous;

        // 새로운 노드 관련 포인터 정리.
        newNode->next = last;
        last->previous = newNode;

        ++count;
    }

    // 첫번째 위치에 노드 추가하는 함수
    void PushFirst(const T& newData)
    {
        // 추가할 노드 생성
        Node<T>* newNode = new Node<T>();
        newNode->data = newData;

        // [f]->next <- newNode
        // [f]->newNode->[f->next]
        // [f]<-newNode
        Node<T>* next = first->next;
        newNode->next = next;
        first->next = newNode;
        newNode->previous = first;
        next->privious = newNode;

        ++count;
    }

    // 삭제 함수.
    void Delete(const T& deleteData)
    {
        // 비어 있는 상태.
        if (first->next == nullptr)
        {
            std::cout << "리스트가 비어 있어 노드를 삭제할 수 없습니다.\n";
            return;
        }

        // 검색 시작.
        Node<T>* deleteNode = first->next;

        // 종료조건 #2.
        while (deleteNode && deleteNode != last)
        {
            // 삭제할 노드를 찾은 경우.
            // 종료 조건 #1.
            if (deleteNode->data == deleteData)
            {
                break;
            }

            // 못찾았으면 다음 노드를 이어서 검색 진행.
            deleteNode = deleteNode->next;
        }

        // 삭제.
        // 찾았는지 확인.
        if (!deleteNode || deleteNode == last)
        {
            std::cout << "삭제할 노드를 찾지 못했습니다.\n";
            return;
        }

        // 삭제 진행.
        // 2번을 지운다고 가정.
        // ..[0]->[1]->[2]->[3]->[l]->nullptr.
        // ..[0]->[1]->[3]->[l]->nullptr.

        // 앞뒤의 포인터 정리.
        deleteNode->previous->next = deleteNode->next;
        deleteNode->next->previous = deleteNode->previous;

        // 노드 삭제.
        SafeDelete(deleteNode);

        // 저장 수 감소 처리.
        --count;
    }

    // 출력.
    void Print()
    {
        // 시작 노드부터.
        Node<T>* current = first->next;

        while (current && current != last)
        {
            std::cout << "데이터: " << current->data << "\n";
            current = current->next;
        }
    }

private:
    // 처음과 마지막을 가리키는 노드.
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;

    // 리스트에 저장된 요소 수.
    int count = 0;
};