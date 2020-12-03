#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node();
        virtual ~Node();

        Node* newNode(int key);

    private:
        int data;
        Node *left, *right;

};

#endif // NODE_H
