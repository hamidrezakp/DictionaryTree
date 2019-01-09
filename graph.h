#ifndef GRAPH_H
#define GRAPH_H
#include "QtCore"

struct Node {
    QChar data;
    QString meaning;
    Node *child, *right;
};
typedef QHash<QString, QString> _List;
typedef QList<Node*> _NList;

class Graph {
    Node *root;
    void _listAll(Node *root, _List &result, QString word="");
    void _search(Node *root, QString word, QString &result, QString tmp="");
    Node* getNode(QChar data, QString meaning, Node *child = nullptr, Node *right = nullptr);
    void _insert(Node *&root, QString word, QString meaning);
    _NList _findPath(Node *root, QString word);
    void _remove(Node *root, QString word);

public:
    Graph();
    void insert(QString word, QString meaning);
    _List listAll();
    QString search(QString word);
    void printPath(QString word);
    void remove(QString word);
};

#endif // GRAPH_H
