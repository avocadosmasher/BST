#include <iostream>

using namespace std;

class BST;
class BstNode {
friend class BST;
private:
    int key; // key값.
    BstNode* LeftChild; // 왼쪽 자식을 가르킴.
    BstNode* RightChild; // 오른쪽 자식을 가르킴.
};

class BST {
private:
    BstNode* root; // root node를 가르킴.
public:
    BstNode* Search(const int& x);  // 검색멤버함수.
    bool Insert(const int& x);      // 삽입멤버함수.
    bool Delete(const int& x);      // 삭제멤버함수.
    void Inorder();                 // 중위우선순회 Driver.
    void Inorder(BstNode* CurrenNode); // 중위우선순회 실제 작동 코드부분.
    BST() { // 초기화 root는 초기에 NULL값을 가진다.
        root = NULL;
    }
};

BstNode* BST::Search(const int& x) // 검색
{
    for (BstNode* t = root; t;) // 현재 가르키는 노드가 NULL이 아닐때까지 반복.
    {
        // key값이 검색하는 값이랑 일치
        if (x == t->key) return t;
        // key값이 현재 확인하는 노드가 아니라 왼쪽자식으로 갈지 오른쪽 자식으로 갈지 확인.
        if (x < t->key) t = t->LeftChild;
        else t = t->RightChild;
    }
    // 만약 여기에 도달한다면 일치하는 값이 없다는 뜻. return 0를 통해 NULL값을 반환해주자.
    return 0;
}

bool BST::Insert(const int& x) // 삽입
{
    BstNode* c = root; BstNode* p = 0; // c는 자식이 될 노드, p는 부모노드를 가르킬 예정.
    while (c) { // 삽입하려는 값이 이미 존재하는지 확인하고 존재하면 삽입을 부정.
        p = c;
        if (x == c->key) return false;
        if (x < c->key) c = c->LeftChild;
        else c = c->RightChild;
    }
    // 여기까지 도달시 현재 입력하려는 값은 새로 입력되는 값.
    // 그러니 입력을 진행해준다.
    // 현재 c는 입력될 위치를 가르키고, p는 그 부모이다.
    c = new BstNode;
    c->LeftChild = c->RightChild = 0; c->key = x; // 일단 좌측, 우측 노드는 NULL값을 가르키고, key는 입력값으로. 
    if (!root) root = c; // 만약 root가 NULL이었다면 root를 갱신.
    else if (x < p->key) p->LeftChild = c; // c가 p의 왼쪽자식인지 확인.
    else p->RightChild = c; // 왼쪽자식이 아니라면 오른쪽 자식으로. 
    return true;
}

bool BST::Delete(const int& x) // 삭제.
{
    BstNode* target = root; BstNode* target_p = 0; // target은 삭제할 노드를 가르키게 될 예정, target_p는 target의 부모노드를 가르킬것임.
    while (target) {
        if (x == target->key) break;
        target_p = target;
        if (x < target->key) target = target->LeftChild;
        else target = target->RightChild;
    }
    // 현재 target에는 삭제하려는 노드 target_p에는 삭제하려는 노드의 부모 노드가 저장되어있다.
    if (target) {
        // 여기서 3가지 Case로 나뉜다. 3가지 케이스 다 root노드의 삭제에 대해서는 root의 갱신이 필요하다.
        if (target->LeftChild == 0 && target->RightChild == 0)
        {
            // 1. 삭제하려는 노드가 Leaf 노드 즉, 자식이 없는 노드일때.
            if(target_p) // target_p가 NULL이 아니라면 삭제하려는 Leaf 노드는 root노드가 아님을 의미.
            {
                if (target_p->LeftChild == target) { // target이 target_p의 왼쪽 자식인지 확인.
                    target_p->LeftChild = 0; // 삭제할것이니 target_p으 LeftChild를 NULL로 바꿈.
                }
                else { // 오른쪽 자식이었을 경우.
                    target_p->RightChild = 0; // target_p의 RightChild를 NULL로
                }
            }
            else root = 0; // 만약 target_p가 NULL이라면 삭제하려는 Leaf노드가 root 노드였다는 의미.

            delete target;
            return true;
        }
        else if (target->LeftChild != 0 && target->RightChild != 0) {
            // 2. 삭제하려는 노드가 두 자식을 갖는 비단말노드일 경우.
            // 오른쪽 자식중에 제일 작은 노드를 고를것임.
            BstNode* p = target->RightChild, * q = target; // p는 target의 오른쪽 노드 중 제일 작은 노드, q는 그 부모노드를 가르킬 예정.
            while (p->LeftChild != (BstNode*)0) { // 제일 작은 노드를 찾는다.
                q = p;
                p = p->LeftChild;
            }
            if (q == target) { // q가 target이라면 target의 바로 오른쪽 노드였던 p가 제일 작은 오른쪽 자식이었음.
                p->LeftChild = q->LeftChild;
            }
            else { // 제일 작은 노드가 따로 있었음.
                q->LeftChild = p->RightChild; 
                p->RightChild = target->RightChild;
                p->LeftChild = target->LeftChild;
            }
            if (target == root) root = p; // 삭제하려는 노드가 root 노드였다면 root의 갱신.
            else { // 만약 삭제하는 노드가 root노드가 아니었다면 부모노드를 재 연결.
                if (target_p->RightChild == target) {// 우측노드였었음.
                    target_p->RightChild = p;
                }
                else { // 좌측노드였었음.
                    target_p->LeftChild = p;
                }
            }
            delete target;
            return true;
        }
        else {
            // 3. 삭제하려는 노드가 하나의 자식을 갖는 비단말노드일 경우.
            if (target->LeftChild == 0) { // 오른쪽 자식이 있는 경우

                if (target_p) // 삭제하려는 노드가 root노드가 아닐경우.
                {
                    if (target_p->RightChild == target) { // 삭제하려는 노드가 오른쪽 자식이었을 경우.
                        target_p->RightChild = target->RightChild;
                    }
                    else { // 삭제하려는 노드가 왼쪽 자식이었을 경우.
                        target_p->LeftChild = target->RightChild;
                    }
                }
                else { // 삭제하려는 노드가 root 노드였을 경우.
                    root = target->RightChild;
                }
            }
            else { // 왼쪽 자식이 있는 경우.

                if (target_p) // 삭제하려는 노드가 root노드가 아닐경우.
                {
                    if (target_p->RightChild == target) { // 삭제하려는 노드가 오른쪽 자식이었을 경우.
                        target_p->RightChild = target->LeftChild;
                    }
                    else { // 삭제하려는 노드가 왼쪽 자식이었을 경우.
                        target_p->LeftChild = target->LeftChild;
                    }
                }
                else { // 삭제하려는 노드가 root 노드.
                    root = target->LeftChild;
                }
            }

            delete target;

            return true;
        }
    }
    return false; // 삭제하려는 노드가 존재하지 않아서 target이 NULL의 값을 가졌다면 return false.
}

void BST::Inorder()
{
    Inorder(root);
    cout << "\n";
}

void BST::Inorder(BstNode* CurrentNode)
{
    if (CurrentNode) {
        Inorder(CurrentNode->LeftChild);
        cout << CurrentNode->key << " ";
        Inorder(CurrentNode->RightChild);
    }
}

int main()
{
    BST test;

    int input;
    while (1)
    {
        cout << "1. 삽입, 2. 삭제, 3.탐색, 4.중위우선순회, 5.종료." << "\n";
        cin >> input;

        switch (input) {
        case 1:
            cin >> input;
            test.Insert(input) ? cout << "삽입 성공.\n" : cout << "이미 존재하는 값입니다.\n";
            break;
        case 2:
            cin >> input;
            test.Delete(input) ? cout << "삭제완료. \n" : cout << "삭제하려는 값이 존재하지 않습니다. \n";
            break;
        case 3:
            cin >> input;
            test.Search(input) ? cout << "성공\n" : cout << "검색하려는 값이 존재하지 않습니다.\n";
            break;
        case 4:
            test.Inorder();
            break;
        case 5:
            return 0;
        }
    }
}
