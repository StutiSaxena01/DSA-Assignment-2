#include <iostream>
#include <sstream>
using namespace std;

template <class K, class V>
class Unordered_Map
{

public:
    K key;
    V value;
    Unordered_Map *next;
    Unordered_Map *map[101];

    Unordered_Map()
    {
        for (int i = 0; i < 101; i++)
            map[i] = NULL;
    }
    int calculatehash(K key)
    {
        int prime = 37;
        ostringstream s1;
        s1 << key;
        string s = s1.str();
        int hashvalue = 0;
        int mul = 1;
        for (int i = 0; i < s.size(); i++)
        {
            hashvalue += (s[i] * mul);
            hashvalue %= 101;
            mul *= prime;
        }
        return hashvalue;
    }
    Unordered_Map *create(K key, V value)
    {
        Unordered_Map *newnode = new Unordered_Map;
        newnode->key = key;
        newnode->value = value;
        newnode->next = NULL;
        return newnode;
    }
    void insert(K key, V value)
    {
        int index = calculatehash(key);
        Unordered_Map *temp = map[index];
        if (temp == NULL)
        {
            Unordered_Map *nnode = create(key, value);
            map[index] = nnode;
            return;
        }
        else if (temp->next != NULL)
        {
            Unordered_Map *node = temp;
            while (node->next != NULL)
            {
                if (node->key == key)
                    return;
                else
                {
                    node = node->next;
                }
            }
            if (node->key == key)
                return;
            else
            {
                Unordered_Map *nnode = create(key, value);
                node->next = nnode;
                return;
            }
        }
        else
        {
            if (temp->key == key)
                return;
            else
            {
                Unordered_Map *nnode = create(key, value);
                temp->next = nnode;
                return;
            }
        }
    }
    void erase(K key)
    {
        int index = calculatehash(key);
        Unordered_Map *node = map[index];
        if (node == NULL)
            return;
        else
        {
            Unordered_Map *node1 = node, *prev = NULL, *head;
            if (node->key == key)
            {
                head = node;
                head = head->next;
                map[index] = head;
                free(node);
            }
            while (node->next != NULL)
            {
                if (node->key != key)
                {
                    prev = node;
                    node = node->next;
                }
                else
                {
                    prev->next = node->next;
                    free(node);
                }
            }
            if (node->key == key)
            {
                prev->next = NULL;
                free(node);
            }
            else
                return;
        }
    }
    bool find(K key)
    {
        int index = calculatehash(key);
        Unordered_Map *trav = map[index];
        if (trav == NULL)
            return false;
        else if (trav->next == NULL)
        {
            if (trav->key == key)
                return true;
            else
                return false;
        }
        else
        {
            Unordered_Map *trav1 = trav;
            while (trav1 != NULL)
            {
                if (trav1->key == key)
                    return true;
                else
                {
                    trav1 = trav1->next;
                }
            }
        }
        return false;
    }

    void print_all_LL()
    {
        for (int i = 0; i < 101; i++)
        {
            cout << endl
                << i << " : ";
            Unordered_Map *print = map[i];
            while (print != NULL)
            {
                cout << " " << print->key << " " << print->value;
                print = print->next;
                cout << endl;
            }
        }
    }

    V operator[](K key)
    {
        int index = calculatehash(key);
        Unordered_Map *node = map[index];
        if (node == NULL)
            exit(0);
        Unordered_Map *node1 = map[index];
        Unordered_Map *trav1 = node1;
        while (trav1 != NULL)
        {
            if (trav1->key == key)
                return trav1->value;
            else
            {
                trav1 = trav1->next;
            }
        }
        return trav1->value;
    }
};

int main()
{
    int n, m1;
    cin >> n;
    string s;
    Unordered_Map<int, string> m;
    for (int i = 0; i < n; i++)
    {
        cin >> m1 >> s;
        m.insert(m1, s);
    }
    m.print_all_LL();
    cout << endl;
    if (m.find(12) == 0)
        cout << "False";
    else
        cout << "True";
    m.erase(12);
    m.print_all_LL();
    cout << "---------------------";
    cout << m[14];
    return 0;
}