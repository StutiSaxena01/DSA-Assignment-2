#include <iostream>
using namespace std;
int csize=0;
template <class K, class V>
class Ordered_Map
{
    public:
    K key;
    V value;
    
    Ordered_Map<K, V> *left, *right;
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
    Ordered_Map<K, V>* balance(Ordered_Map<K, V> *root)
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
    Ordered_Map<K, V>*insert(Ordered_Map<K, V> *root, K x, V y)
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
            root->left = insert(root->left, x, y);
        }
        else if (x >= root->key)
        {
            root->right = insert(root->right, x, y);
        }
       
        root = balance(root);
        // preorder(root);
        //cout << "----------mid--------"<< endl;
        return root;
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
                root->left = child->left;
                root->right = child->right;
                free(child);
            }
            else
            {
                /*
             * if AVL has both child then find inOrder SUC 
             * and copy data of inorder successor to given AVL
             * and then delete that successor AVL. 
             */
                Ordered_Map<K, V> *ino_suc = root->right;
                while (ino_suc->left != NULL)
                    ino_suc = ino_suc->left;
                root->key = ino_suc->key;
                root->right = deletion(root->right, ino_suc->key);
            }
            csize--;
        }
    if (root == NULL)
        return root;

    root = balance(root);
    return root;
    }
    bool find(Ordered_Map<K, V> *root, K x)
    {
        if (root == NULL)
            return false;
        if (root->key == x)
            return true;
        else if (root->key > x)
            return find(root->left, x);
        else
            return find(root->right, x);

        return false;
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
    
    void deleteMap(Ordered_Map<K,V> *node)
    {
        if(node==NULL) return;
        deleteMap(node->left);
        deleteMap(node->right);
        free(node);
    }
    void clear(Ordered_Map<K,V> *root)
    {
        deleteMap(root);
    }
};
int main()
{
    int n;
    cin >> n;
    Ordered_Map<int, string> *root = NULL;
    Ordered_Map<int, string> a;
    int x;string y;
    for (int i = 1; i <= n; i++)
    {
        cin >> x >> y;
        root = a.insert(root,x, y);
    }

    cout << "\n-------------------Before----------------\n";
    a.inorder(root);
     cout <<"\n-----------Size----------\n"; 
    cout << a.size();
    cout << endl;
    a.deletion(root,14);
    cout << "\n-------------------After----------------\n";
    a.inorder(root);
    cout << endl;
    if(a.find(root,12)==1) cout <<"True";
    else cout << "0";   
    cout <<"\n-----------Size----------\n"; 
    cout << a.size();
    cout <<"\n-----------clear----------\n"; 
    a.clear(root);
    cout <<"\n-------------after clear-----\n";
    a.inorder(root);
    return 0;
}