#include <iostream>
using namespace std;
int csize = 0;
template <class K, class V>
class Ordered_Map
{
public:
    K key;
    V value;

    Ordered_Map<K, V> *left, *right,*root=NULL;
    Ordered_Map()
    {
    }
    Ordered_Map(K x, V y)
    {
        key = x;
        value = y;
        left = right = NULL;
    }
    int height(Ordered_Map<K, V> *root)
    {
        int h = 0;
        if (root != NULL)
        {
            int lh = height(root->left);
            int rh = height(root->right);
            int maxh = max(lh, rh);
            h = maxh + 1;
        }
        return h;
    }
    Ordered_Map<K, V> *lr_rotation(Ordered_Map<K, V> *root)
    {
        Ordered_Map<K, V> *temp;
        temp = root->left;
        root->left = rr_rotation(temp);
        return ll_rotation(root);
    }
    Ordered_Map<K, V> *rr_rotation(Ordered_Map<K, V> *root)
    {
        Ordered_Map<K, V> *temp;
        temp = root->right;
        root->right = temp->left;
        temp->left = root;
        return temp;
    }
    Ordered_Map<K, V> *rl_rotation(Ordered_Map<K, V> *root)
    {
        Ordered_Map<K, V> *temp;
        temp = root->right;
        root->right = ll_rotation(temp);
        return rr_rotation(root);
    }
    Ordered_Map<K, V> *ll_rotation(Ordered_Map<K, V> *root)
    {
        Ordered_Map<K, V> *temp;
        temp = root->left;
        root->left = temp->right;
        temp->right = root;
        return temp;
    }
    int diff(Ordered_Map<K, V> *root)
    {
        int lh = height(root->left);
        int rh = height(root->right);
        int dif = lh - rh;
        return dif;
    }
    Ordered_Map<K, V> *balance(Ordered_Map<K, V> *root)
    {
        int hdiff = diff(root);
        if (hdiff > 1)
        {
            if (diff(root->left) > 0)
                root = ll_rotation(root);
            else
                root = lr_rotation(root);
        }
        else if (hdiff < -1)
        {
            if (diff(root->right) > 0)
                root = rl_rotation(root);
            else
                root = rr_rotation(root);
        }
        return root;
    }
    Ordered_Map<K, V> *toinsert(Ordered_Map<K, V> *root, K x, V y)
    {
        if (root == NULL)
        {
            root = new Ordered_Map<K, V>(x, y);
            csize++;
            return root;
        }
        if (x == root->key)
        {
            root->value = y;
            return root;
        }
        else if (x < root->key)
        {
            root->left = toinsert(root->left, x, y);
        }
        else if (x >= root->key)
        {
            root->right = toinsert(root->right, x, y);
        }

        root = balance(root);
        // preorder(root);
        //cout << "----------mid--------"<< endl;
        return root;
    }
    void insert(K x,V y)
    {
        root=toinsert(root,x,y);
    }
    Ordered_Map<K, V> *deletion(Ordered_Map<K, V> *root, K x)
    {
        if (root == NULL)
            return root;
        if (x > root->key)
            root->right = deletion(root->right, x);
        else if (x < root->key)
            root->left = deletion(root->left, x);
        else if (x == root->key)
        {
            if (root->left == NULL && root->right == NULL)
            {
                Ordered_Map<K, V> *tmp = root;
                root = NULL;
                free(tmp);
            }
            else if (root->left == NULL || root->right == NULL)
            {
                Ordered_Map<K, V> *child;
                if (root->left != NULL)
                    child = root->left;
                else
                    child = root->right;

                root->key = child->key;
                root->value=child->value;
                root->left = child->left;
                root->right = child->right;
                free(child);
            }
            else
            {
                Ordered_Map<K, V> *ino_suc = root->right;
                while (ino_suc->left != NULL)
                    ino_suc = ino_suc->left;
                root->key = ino_suc->key;
                root->value=ino_suc->value;
                root->right = deletion(root->right, ino_suc->key);
            }
            csize--;
        }
        if (root == NULL)
            return root;

        root = balance(root);
        return root;
    }
    void erase(K x)
    {
        root=deletion(root,x);
    }
    bool tofind(Ordered_Map<K, V> *root, K x)
    {
        if (root == NULL)
            return false;
        if (root->key == x)
            return true;
        else if (root->key > x)
            return tofind(root->left, x);
        else
            return tofind(root->right, x);

        return false;
    }
    bool find(K x)
    {
        return tofind(root,x);
    }
    Ordered_Map<K,V> *search(Ordered_Map<K, V> *root, K x)
    {
        if (root == NULL)
            return root;
        if (root->key == x)
            return root;
        else if (root->key > x)
            return search(root->left, x);
        
            return search(root->right, x);
    }
    void inorder(Ordered_Map<K, V> *root)
    {
        if (root == NULL)
            return;
        inorder(root->left);
        cout << root->key << " " << root->value << endl;
        inorder(root->right);
    }
    int size()
    {
        return csize;
    }
    Ordered_Map<K, V> * toclear(Ordered_Map<K, V> *root)
    {
        if (root == NULL)
            return root;    
        csize = 0;
        toclear(root->right);
        toclear(root->left);

        root->left = NULL;
        free(root->left);

        root->right = NULL;
        free(root->right);

        root = NULL;
        free(root);
        return root;
    }
    void clear()
    {
        root=toclear(root);
    }
    V &operator [](K key)
    {
        Ordered_Map* m=search(root,key);
        if(m)
        return m->value;
        else
        {
            V value=V{};
            root=toinsert(root,key,value);      
        }

        Ordered_Map* m1=search(root,key);
        return m1->value;
    }
};
int main()
{
    int n,c;
    cin >> n;
    //Ordered_Map<int, string> *root = NULL;
    Ordered_Map<string, char> a;
    char v;
    int q;
    string k;
    for (int i = 1; i <= n; i++)
    {
        cin >> q;
        switch(q)
        {
            case 1: 
            cin >> k >> v;
            a.insert(k,v);
            a.inorder(a.root);
            break;

            case 2:
            cin >> k;
            a.erase(k);
            a.inorder(a.root);
            break;

            case 3:
            cin >> k;
            if(a.find(k)==1) 
            cout << "True"<< endl;
            else
                cout <<"False";
            break;

            case 4:
            cin >> c;
            switch(c)
            {
            case 1:
            cin >> k;
            cout << a[k] << endl;
            break;
            case 2:
            cin >> k;
            cin >> v;
            a[k]=v;
            cout << a[k] << endl;
            break;
            }
            break;

            case 5:
            cout << a.size()<< endl;
            break;

            case 6:
            a.clear();
            break;

            default:
            break;
        }
    }
    return 0;
}