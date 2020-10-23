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
        int prime=37;
        ostringstream s1;
        s1 << key;
        string s = s1.str();
        int len=s.size();
        int hashvalue = 0;
        int mul = 1;
        for (int i = 1; i < len; i++)
        {
            hashvalue = ((hashvalue*prime)+s[i])%101;
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

    void print()
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
    Unordered_Map<int, string> m;
    int n,c;
    cin >> n;
    int key;
    string value;

    for(int i=0;i<n;i++)
    {
        cin >> c;
        switch(c)
        {
            case 1:  
                cin >> key >> value;
                m.insert(key,value);
                break;

            case 2:
                cin >> key;
                m.erase(key);
                break;
            
            case 3:
                cin >> key;
                if(m.find(key)==0)
                cout << "False";
                else
                cout << "True";
                break;

            case 4:
                cin >> key;
                cout << m[key] << endl;
                break;

            case 5:
                m.print();
                break;

            default: break;
        }
    }
    return 0;
}