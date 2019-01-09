#include "graph.h"
#include "QDebug"
#include "QHash"

Graph::Graph()
{
        root = nullptr;
}

void Graph::_insert(Node *&root, QString word, QString meaning)
{
        if (word.length() == 0)
                return;
        if (root == nullptr) {
                root = getNode(word[0], word.length() == 1 ? meaning : "",
                               nullptr, nullptr);
                _insert(root->child, word.remove(0, 1), meaning);
        } else if (root->data == word[0])
                _insert(root->child, word.remove(0, 1), meaning);
        else
                _insert(root->right, word, meaning);
}
void Graph::_remove(Node *root, QString word)
{
        _NList nodes = _findPath(root, word);
        if (nodes.isEmpty())
                return;
        while (!nodes.isEmpty()) {
                if (nodes.last()->child == nullptr &&
                    nodes.last()->right == nullptr) {
                        Node *tmp = nodes.last();
                        nodes.removeLast();
                        if (nodes.last()->child == tmp)
                                nodes.last()->child = nullptr;
                        else if (nodes.last()->right == tmp)
                                nodes.last()->right = nullptr;
                        delete tmp;
                        continue;
                }
                break;
        }
}
_NList Graph::_findPath(Node *root, QString word)
{
        _NList nodes, empty;
        while (root != nullptr) {
                nodes.append(root);
                if (root->data == word[0]) {
                        word = word.remove(0, 1);
                        root = root->child;
                        continue;
                } else if (root->data != word[0]) {
                        root = root->right;
                        continue;
                }
        }

        if (word.length() == 0)
                return nodes;

        return empty;
}
void Graph::_search(Node *root, QString word, QString &result, QString tmp)
{
        if (root != nullptr) {
                _search(root->right, word, result, tmp);
                tmp.append(root->data);
                if ((root->meaning != "") && tmp == word)
                        result = root->meaning;
                _search(root->child, word, result, tmp);
        }
}
void Graph::_listAll(Node *root, _List &result, QString word)
{
        if (root == nullptr)
                return;
        _listAll(root->right, result, word);
        word.append(root->data);
        if (root->meaning != "")
                result.insert(word, root->meaning);
        _listAll(root->child, result, word);
}
void Graph::insert(QString word, QString meaning)
{
        _insert(root, word, meaning);
}
Node *Graph::getNode(QChar data, QString meaning, Node *child, Node *right)
{
        Node *p = new Node;
        p->data = data;
        p->meaning = meaning;
        p->child = child;
        p->right = right;
        return p;
}
_List Graph::listAll()
{
        _List result;
        _listAll(root, result);
        return result;
}
QString Graph::search(QString word)
{
        QString result;
        _search(root, word, result);
        return result;
}
void Graph::printPath(QString word)
{
        _NList nodes = _findPath(root, word);
        foreach(Node * n, nodes) qDebug() << n->data;
}
void Graph::remove(QString word)
{
        _remove(root, word);
}
