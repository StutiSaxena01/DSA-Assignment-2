#include <iostream>
using namespace std;
int c = 0;
template <class D>
class AVL
{
public:
    D data;
    AVL<D> *right, *left;
    int count;
    int rc;
    AVL()
    {

    }
    AVL(D n)
    {
        data = n;
        left = right = NULL;
        count = 1;
        rc = 0;
    }
    AVL<D> *insert(AVL<D> *root, D value);
    AVL<D> *deletion(AVL<D> *root, D value);
    AVL<D> *balance(AVL<D> *root);
    int diff(AVL<D> *root);
    int height(AVL<D> *root);
    AVL<D> *ll_rotation(AVL<D> *root);
    AVL<D> *rl_rotation(AVL<D> *root);
    AVL<D> *lr_rotation(AVL<D> *root);
    AVL<D> *rr_rotation(AVL<D> *root);
    bool search(AVL<D> *root, D x);
    void inorder(AVL<D> *root);
    void preorder(AVL<D> *root);
    int countoccurence(AVL<D> *root, D x);
    void lowerbound(AVL<D> *root, D x);
    AVL<D> *lower_bound(AVL<D> *root, D x);
    void upperbound(AVL<D> *root, D x);
    AVL<D> *upper_bound(AVL<D> *root, D x);
    AVL<D> *klargest(AVL<D> *root, int k);
    int range(AVL<D> *root, D s, D e);
    AVL<D> *inpred(AVL<D>* root,D x);
    AVL<D> * insucc(AVL<D>* root, D x);
    D  closestvalue(AVL<D>* root, D x);

private:
    AVL<D> *ub, *lb;
};
template <typename D>
int AVL<D>::height(AVL<D> *root)
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
template <typename D>
AVL<D> *AVL<D>::lr_rotation(AVL<D> *root)
{
    AVL<D> *temp;
    temp = root->left;
    root->left = rr_rotation(temp);
    return ll_rotation(root);
}
template <typename D>
AVL<D> *AVL<D>::rr_rotation(AVL<D> *root)
{
    AVL<D> *temp;
    temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}
template <typename D>
AVL<D> *AVL<D>::rl_rotation(AVL<D> *root)
{
    AVL<D> *temp;
    temp = root->right;
    root->right = ll_rotation(temp);
    return rr_rotation(root);
}

template <typename D>
AVL<D> *AVL<D>::ll_rotation(AVL<D> *root)
{
    AVL<D> *temp;
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    temp->rc++;
    return temp;
}
template <typename D>
int AVL<D>::diff(AVL<D> *root)
{
    int lh = height(root->left);
    int rh = height(root->right);
    int dif = lh - rh;
    return dif;
}
template <typename D>
AVL<D> *AVL<D>::balance(AVL<D> *root)
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
template <typename D>
AVL<D> *AVL<D>::insert(AVL<D> *root, D x)
{
    if (root == NULL)
    {
        root = new AVL<D>(x);
        return root;
    }
    if (x == root->data)
    {
        (root->count)++;
        return root;
    }
    else if (x < root->data)
    {
        root->left = insert(root->left, x);
    }
    else if (x >= root->data)
    {
        root->right = insert(root->right, x);
        root->rc++;
    }
    root = balance(root);
    // preorder(root);
    //cout << "----------mid--------"<< endl;
    return root;
}
template <typename D>
AVL<D> *AVL<D>::deletion(AVL<D> *root, D x)
{
    if (root == NULL)
        return root;
    if (x > root->data)
        root->right = deletion(root->right, x);
    else if (x < root->data)
        root->left = deletion(root->left, x);
    else if (x == root->data)
    {
        if (root->count == 1)
        {
            if (root->left == NULL && root->right == NULL)
            {
                AVL<D> *tmp = root;
                root = NULL;
                free(tmp);
            }
            else if (root->left == NULL || root->right == NULL)
            {
                AVL<D> *child;
                if (root->left != NULL)
                    child = root->left;
                else
                    child = root->right;

                root->data = child->data;
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
                AVL<D> *ino_suc = root->right;
                while (ino_suc->left != NULL)
                    ino_suc = ino_suc->left;
                root->data = ino_suc->data;
                root->right = deletion(root->right, ino_suc->data);
            }
        }
        else
        {
            root->count--;
        }
    }
    if (root == NULL)
        return root;

    root = balance(root);
    return root;
}
template <typename D>
int AVL<D>::countoccurence(AVL<D> *root, D x)
{
    if (root == NULL)
        return 0;
    if (root->data == x)
        return root->count;
    else if (root->data > x)
        return countoccurence(root->left, x);
    else
        return countoccurence(root->right, x);

    return 0;
}
template <typename D>
bool AVL<D>::search(AVL<D> *root, D x)
{
    if (root == NULL)
        return false;
    if (root->data == x)
        return true;
    else if (root->data > x)
        return search(root->left, x);
    else
        return search(root->right, x);

    return false;
}
template <typename D>
void AVL<D>::preorder(AVL<D> *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
template <typename D>
void AVL<D>::inorder(AVL<D> *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
template <typename D>
void AVL<D>::lowerbound(AVL<D> *root, D x)
{
    if (root == NULL)
        return;
    if (root->data >= x)
    {
        lb = root;
        lowerbound(root->left, x);
    }
    else
    {
        lowerbound(root->right, x);
    }
}

template <typename D>
AVL<D> *AVL<D>::lower_bound(AVL<D> *root, D x)
{
    lb = NULL;
    lowerbound(root, x);
    return lb;
}
template <typename D>
void AVL<D>::upperbound(AVL<D> *root, D x)
{
    if (root == NULL)
        return;
    if (root->data > x)
    {
        lb = root;
        upperbound(root->left, x);
    }
    else
    {
        upperbound(root->right, x);
    }
}

template <typename D>
AVL<D> *AVL<D>::upper_bound(AVL<D> *root, D x)
{
    lb = NULL;
    upperbound(root, x);
    return lb;
}
template <typename D>
AVL<D>* AVL<D>::inpred(AVL<D>* root, D x)
{
    AVL<D> *ino_pred = root->left;
    while (ino_pred->right != NULL)
        ino_pred = ino_pred->right;
    return ino_pred;
}
template <typename D>
AVL<D>* AVL<D>::insucc(AVL<D>* root, D x)
{
    AVL<D> *ino_suc = root->right;
    while (ino_suc->left != NULL)
        ino_suc = ino_suc->left;
    return ino_suc;
}
template <typename D>
D AVL<D>::closestvalue(AVL<D>* root, D x)
{
    D temp=insucc(root,x)->data;
    D temp1=inpred(root,x)->data;
    //cout << temp <<" "<< temp1 << endl;
    if (temp-x > x-temp1)
    return temp1;
    else if(x-temp1 > temp-x)
        return temp;
    else
    {
        if(temp1>temp) return temp;
        else
        {
            return temp1;
        }
    }
    return 0;  
}
template <typename D>
AVL<D> *AVL<D>::klargest(AVL<D> *root, int k)
{
    if (root == NULL)
        return NULL;

    int count = root->rc + 1;
    if (count == k)
        return root;

    if (count > k)
        return klargest(root->right, k);

    // else search in right subtree
    return klargest(root->left, k - count);
}
template <typename D>
int AVL<D>::range(AVL<D> *root, D start, D end)
{
    if (root == NULL)
        return 0;
    if (start < root->data)
    {
        range(root->left, start, end);
    }
    if (start <= root->data && end >= root->data)
        c += root->count;

    if (end > root->data)
        range(root->right, start, end);

    return c;
}
int main()
{
    int n;
    cin >> n;
    AVL<float> *root = NULL;
    AVL<float> a;
    float y;
    for (int i = 1; i <= n; i++)
    {
        cin >> y;
        root = a.insert(root, y);
    }

    cout << "\n-------------------Before----------------\n";
    a.inorder(root);
    cout << endl;
    a.preorder(root);
    root = a.insert(root,6);
    cout << "\n-------------------After----------------\n";
    a.inorder(root);
    cout << endl;
    a.preorder(root);
    cout << "\n-------------------Search----------------\n";
    cout << a.search(root, 2) << endl;
    cout << "-------------------count occurence----------------\n";
    cout << a.countoccurence(root,2) << endl;
    cout << "-------------------lowerbound----------------\n";
    float x1;
    cin >> x1;
    cout <<a.lower_bound(root,x1)->data;
    cout << "\n-------------------upperbound----------------\n";
    cout<< a.upper_bound(root, x1)->data;
    root = a.deletion(root, 0);
    cout << "\n-----------------------After deletion\n";
    a.preorder(root);
    cout << "\n-------------------count occurence----------------\n";
    cout << a.countoccurence(root,2) << endl;
    cout << "\n-------------------numbers in given range----------------\n";
    int start, end;
    cin >> start >> end;
    cout << a.range(root, start, end);
    cout <<"\n---------------------Closest Value----------------\n";
    cout << a.closestvalue(root,5);
    return 0;
}

