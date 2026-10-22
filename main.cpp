#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

// ARVORE AVL

struct NodeAVL {
    int key;
    int height;
    NodeAVL* left;
    NodeAVL* right;

    NodeAVL(int val) : key(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    NodeAVL* root;
    long long rotationCount;

    int getHeight(NodeAVL* n) {
        return n ? n->height : 0;
    }

    int getBalance(NodeAVL* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    void updateHeight(NodeAVL* n) {
        if (n) {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        }
    }

    NodeAVL* rotateRight(NodeAVL* y) {
        rotationCount++;
        NodeAVL* x = y->left;
        NodeAVL* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    NodeAVL* rotateLeft(NodeAVL* x) {
        rotationCount++;
        NodeAVL* y = x->right;
        NodeAVL* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    NodeAVL* insertNode(NodeAVL* node, int key) {
        if (!node) return new NodeAVL(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else {
            cout << " [Aviso] Elemento " << key << " ja existe na AVL. Ignorado.\n";
            return node;
        }

        updateHeight(node);
        int balance = getBalance(node);

        // Caso Esquerda-Esquerda
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Caso Direita-Direita
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Caso Esquerda-Direita
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Caso Direita-Esquerda
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    NodeAVL* getMinValueNode(NodeAVL* node) {
        NodeAVL* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    NodeAVL* deleteNode(NodeAVL* root, int key, bool& found) {
        if (!root) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key, found);
        else if (key > root->key)
            root->right = deleteNode(root->right, key, found);
        else {
            found = true;
            if (!root->left || !root->right) {
                NodeAVL* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                NodeAVL* temp = getMinValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key, found);
            }
        }

        if (!root) return root;

        updateHeight(root);
        int balance = getBalance(root);

        // Balanceamento pos-remocao
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inOrderHelper(NodeAVL* root) {
        if (!root) return;
        inOrderHelper(root->left);
        cout << root->key << " ";
        inOrderHelper(root->right);
    }

    void printTreeHelper(NodeAVL* root, string indent, bool last) {
        if (root) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            cout << "[" << root->key << "] (h=" << root->height << ")\n";
            printTreeHelper(root->left, indent, false);
            printTreeHelper(root->right, indent, true);
        }
    }

    bool searchHelper(NodeAVL* root, int key) {
        if (!root) return false;
        if (root->key == key) return true;
        if (key < root->key) return searchHelper(root->left, key);
        return searchHelper(root->right, key);
    }

public:
    AVLTree() : root(nullptr), rotationCount(0) {}

    void insert(int key) { root = insertNode(root, key); }
    
    void remove(int key) {
        bool found = false;
        root = deleteNode(root, key, found);
        if (!found) cout << " [Aviso] Elemento " << key << " nao encontrado na AVL.\n";
    }

    bool search(int key) { return searchHelper(root, key); }

    void inOrder() {
        inOrderHelper(root);
        cout << "\n";
    }

    void printTree() {
        if (!root) cout << "Arvore AVL Vazia.\n";
        else printTreeHelper(root, "", true);
    }

    int getHeight() { return getHeight(root); }
    long long getRotations() { return rotationCount; }
};

// ARVORE RUBRO-NEGRA

enum Color { RED, BLACK };

struct NodeRB {
    int key;
    Color color;
    NodeRB *left, *right, *parent;

    NodeRB(int val) : key(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    NodeRB* root;
    NodeRB* TNULL;
    long long rotationCount;

    void initializeNULLNode(NodeRB* node, NodeRB* parent) {
        node->key = 0;
        node->color = BLACK;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
    }

    void leftRotate(NodeRB* x) {
        rotationCount++;
        NodeRB* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodeRB* x) {
        rotationCount++;
        NodeRB* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(NodeRB* k) {
        NodeRB* u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = BLACK;
    }

    void rbTransplant(NodeRB* u, NodeRB* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    NodeRB* minimum(NodeRB* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    void fixDelete(NodeRB* x) {
        NodeRB* s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void printTreeHelper(NodeRB* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            string sColor = (root->color == RED) ? "VERMELHO" : "PRETO";
            cout << "[" << root->key << "] (" << sColor << ")\n";
            printTreeHelper(root->left, indent, false);
            printTreeHelper(root->right, indent, true);
        }
    }

    void inOrderHelper(NodeRB* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->key << " ";
            inOrderHelper(node->right);
        }
    }

    int calculateHeight(NodeRB* node) {
        if (node == TNULL) return 0;
        return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
    }

public:
    RedBlackTree() : rotationCount(0) {
        TNULL = new NodeRB(0);
        TNULL->color = BLACK;
        root = TNULL;
    }

    void insert(int key) {
        NodeRB* node = new NodeRB(key);
        node->parent = nullptr;
        node->key = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        NodeRB* y = nullptr;
        NodeRB* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            } else if (node->key > x->key) {
                x = x->right;
            } else {
                cout << " [Aviso] Elemento " << key << " ja existe na Rubro-Negra. Ignorado.\n";
                delete node;
                return;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->key < y->key) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) return;

        fixInsert(node);
    }

    void remove(int key) {
        NodeRB* z = TNULL;
        NodeRB* x;
        NodeRB* y;
        NodeRB* node = this->root;

        while (node != TNULL) {
            if (node->key == key) z = node;
            if (node->key <= key) node = node->right;
            else node = node->left;
        }

        if (z == TNULL) {
            cout << " [Aviso] Elemento " << key << " nao encontrado na Rubro-Negra.\n";
            return;
        }

        y = z;
        Color yOriginalColor = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }

    bool search(int key) {
        NodeRB* curr = root;
        while (curr != TNULL) {
            if (key == curr->key) return true;
            if (key < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    void inOrder() {
        inOrderHelper(root);
        cout << "\n";
    }

    void printTree() {
        if (root == TNULL) cout << "Arvore Rubro-Negra Vazia.\n";
        else printTreeHelper(this->root, "", true);
    }

    int getHeight() { return calculateHeight(root); }
    long long getRotations() { return rotationCount; }
};

// MENU E TESTES

int main() {
    int option;
    cout << "=================================================\n";
    cout << "  AMAZON ENGINEERING CHALLENGE - LOGISTICS SYSTEM\n";
    cout << "=================================================\n";
    cout << "Selecione a estrutura de dados inicial:\n";
    cout << "1. Arvore AVL\n";
    cout << "2. Arvore Rubro-Negra\n";
    cout << "Escolha: ";
    cin >> option;

    if (option == 1) {
        AVLTree avl;
        int choice, val;
        do {
            cout << "\n--- MENU AVL ---\n";
            cout << "1. Inserir Pacote\n2. Remover Pacote\n3. Buscar Pacote\n4. Em-Ordem\n5. Imprimir Arvore\n6. Altura e Rotacoes\n0. Sair\nOpcao: ";
            cin >> choice;
            switch (choice) {
                case 1: cout << "ID: "; cin >> val; avl.insert(val); break;
                case 2: cout << "ID: "; cin >> val; avl.remove(val); break;
                case 3: cout << "ID: "; cin >> val; cout << (avl.search(val) ? "Encontrado!\n" : "Nao encontrado!\n"); break;
                case 4: avl.inOrder(); break;
                case 5: avl.printTree(); break;
                case 6: cout << "Altura: " << avl.getHeight() << " | Rotacoes: " << avl.getRotations() << "\n"; break;
            }
        } while (choice != 0);
    } else {
        RedBlackTree rb;
        int choice, val;
        do {
            cout << "\n--- MENU RUBRO-NEGRA ---\n";
            cout << "1. Inserir Pacote\n2. Remover Pacote\n3. Buscar Pacote\n4. Em-Ordem\n5. Imprimir Arvore\n6. Altura e Rotacoes\n0. Sair\nOpcao: ";
            cin >> choice;
            switch (choice) {
                case 1: cout << "ID: "; cin >> val; rb.insert(val); break;
                case 2: cout << "ID: "; cin >> val; rb.remove(val); break;
                case 3: cout << "ID: "; cin >> val; cout << (rb.search(val) ? "Encontrado!\n" : "Nao encontrado!\n"); break;
                case 4: rb.inOrder(); break;
                case 5: rb.printTree(); break;
                case 6: cout << "Altura: " << rb.getHeight() << " | Rotacoes: " << rb.getRotations() << "\n"; break;
            }
        } while (choice != 0);
    }

    return 0;
}