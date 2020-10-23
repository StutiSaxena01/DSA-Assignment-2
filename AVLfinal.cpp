#include <iostream>
using namespace std;

int c = 0, size = 0, i = -1;
template <class D>
struct Less
{
    bool operator()(D &lhs, D &rhs)
    {
        return lhs < rhs;
    }
};
template <class D>
struct Equal
{
    bool operator()(D &lhs, D &rhs)
    {
        return lhs == rhs;
    }
};
template <class D>
struct Greater
{
    bool operator()(D &lhs, D &rhs)
    {
        return lhs > rhs;
    }
};
template <class D, class Compare1 = Less<D>, class Compare2 = Equal<D>, class Compare3 = Greater<D>>
class AVL
{
public:
    D arr[100];
    D data;
    AVL<D> *right, *left;
    Compare1 isless;
    Compare2 isequal;
    Compare3 isgreat;
    int count;
    AVL()
    {
    }

    AVL(D n)
    {
        data = n;
        left = right = NULL;
        count = 1;
    }

    AVL<D> *root = NULL;

    int height(AVL<D> *root)
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

    AVL<D> *ll_rotation(AVL<D> *root)
    {
        AVL<D> *temp;
        temp = root->left;
        root->left = temp->right;
        temp->right = root;
        return temp;
    }

    AVL<D> *rr_rotation(AVL<D> *root)
    {
        AVL<D> *temp;
        temp = root->right;
        root->right = temp->left;
        temp->left = root;
        return temp;
    }

    AVL<D> *rl_rotation(AVL<D> *root)
    {
        AVL<D> *temp;
        temp = root->right;
        root->right = ll_rotation(temp);
        return rr_rotation(root);
    }

    AVL<D> *lr_rotation(AVL<D> *root)
    {
        AVL<D> *temp;
        temp = root->left;
        root->left = rr_rotation(temp);
        return ll_rotation(root);
    }

    int diff(AVL<D> *root)
    {
        int lh = height(root->left);
        int rh = height(root->right);
        int dif = lh - rh;
        return dif;
    }

    AVL<D> *balance(AVL<D> *root)
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

    AVL<D> *insert(AVL<D> *root, D x)
    {
        if (root == NULL)
        {
            root = new AVL<D>(x);
            return root;
        }
        if (isequal(x, root->data))
        {
            (root->count)++;
            return root;
        }
        else if (isless(x, root->data))
        {
            root->left = insert(root->left, x);
        }
        else if (!isless(x, root->data) && !isequal(x, root->data))
        {
            root->right = insert(root->right, x);
        }
        root = balance(root);
        size++;
        //cout << "----------mid--------"<< endl;
        return root;
    }

    AVL<D> *deletion(AVL<D> *root, D x)
    {
        if (root == NULL)
            return root;
        if (isgreat(x, root->data))
            root->right = deletion(root->right, x);
        else if (isless(x, root->data))
            root->left = deletion(root->left, x);
        else if (isequal(x, root->data))
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

    int countoccurence(AVL<D> *root, D x)
    {
        if (root == NULL)
            return 0;
        if (isequal(root->data, x))
            return root->count;
        else if (isgreat(root->data, x))
            return countoccurence(root->left, x);
        else
            return countoccurence(root->right, x);

        return 0;
    }

    bool search(AVL<D> *root, D x)
    {
        if (root == NULL)
            return false;
        if (isequal(root->data, x))
            return true;
        else if (isgreat(root->data, x))
            return search(root->left, x);
        else
            return search(root->right, x);

        return false;
    }

    void preorder(AVL<D> *root)
    {
        if (root == NULL)
            return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void inorder1(AVL<D> *root)
    {
        if (root == NULL)
            return;

        inorder1(root->left);
        int c = root->count;
        for (int j = 0; j < c; j++)
        {
            //cout << root->data << " ";
            arr[++i] = root->data;
            //cout << "i :" << i << "  "<<arr[i];
        }
        inorder1(root->right);
    }

    void inorder(AVL<D> *root)
    {
        if (root == NULL)
            return;

        inorder(root->left);
        int c = root->count;
        for (int j = 0; j < c; j++)
            cout << root->data << " ";
        inorder(root->right);
    }

    void lowerbound(AVL<D> *root, D x)
    {
        if (root == NULL)
            return;
        if (isgreat(root->data, x) || isequal(root->data, x))
        {
            lb = root;
            lowerbound(root->left, x);
        }
        else
        {
            lowerbound(root->right, x);
        }
    }

    AVL<D> *lower_bound(AVL<D> *root, D x)
    {
        lb = NULL;
        lowerbound(root, x);
        return lb;
    }

    void upperbound(AVL<D> *root, D x)
    {
        if (root == NULL)
            return;
        if (isgreat(root->data, x))
        {
            ub = root;
            upperbound(root->left, x);
        }
        else
        {
            upperbound(root->right, x);
        }
    }

    AVL<D> *upper_bound(AVL<D> *root, D x)
    {
        ub = NULL;
        upperbound(root, x);
        return ub;
    }

    D klargest(int k)
    {
        //cout << size;
        if (k <= size)
        {
            i = -1;
            inorder1(root);
            return arr[i - k + 1];
        }
        else
        {
            exit(0);
        }
        return 0;
    }

    int range(AVL<D> *root, D start, D end)
    {
        if (root == NULL)
            return 0;
        if (isless(start, root->data))
        {
            range(root->left, start, end);
        }
        if (!isgreat(start, root->data) && !isless(end, root->data))
            c += root->count;

        if (isgreat(end, root->data))
            range(root->right, start, end);

        return c;
    }

    AVL<D> *inpred(AVL<D> *root)
    {
        AVL<D> *ino_pred = root->left;
        while (ino_pred->right != NULL)
            ino_pred = ino_pred->right;
        return ino_pred;
    }
    AVL<D> *insucc(AVL<D> *root)
    {
        AVL<D> *ino_suc = root->right;
        while (ino_suc->left != NULL)
            ino_suc = ino_suc->left;
        return ino_suc;
    }

    D closestvalue(AVL<D> *root, D x)
    {
        if (isequal(root->data, x))
            return x;
        else if (isless(x, root->data))
        {
            if (isgreat(x, inpred(root)->data))
            {
                D pre = inpred(root)->data;
                D diffp = x - pre;
                D diffr = root->data - x;
                if (isless(diffp, diffr))
                {
                    return pre;
                }
                else if (isgreat(diffp, diffr))
                {
                    return root->data;
                }
                else
                {
                    return min(pre, root->data);
                }
            }
            else
            {
                return closestvalue(root->left, x);
            }
        }
        if (isgreat(x, root->data))
        {
            if (isless(x, insucc(root)->data))
            {
                D succ = insucc(root)->data;
                D diffs = succ - x;
                D diffr = x - root->data;
                if (isgreat(diffs, diffr))
                {
                    return root->data;
                }
                else if (isless(diffs, diffr))
                {
                    return succ;
                }
                else
                {
                    return min(succ, root->data);
                }
            }
            else
            {
                return closestvalue(root->right, x);
            }
        }
        return 0;
    }

private:
    AVL<D> *ub, *lb;
};

int main()
{
    int n;
    cin >> n;
    AVL<int> a;
    for (int i = 0; i < n; i++)
    {
        int q;
        cin >> q;
        int x, y;
        switch (q)
        {
        case 1:
            cin >> x;
            a.root = a.insert(a.root, x);
            a.inorder(a.root);
            break;

        case 2:
            cin >> y;
            a.root = a.deletion(a.root, y);
            a.inorder(a.root);
            break;

        case 3:
            cin >> x;
            cout << a.search(a.root, x);
            break;

        case 4:
            cin >> y;
            cout << a.countoccurence(a.root, y);
            break;

        case 5:
            cin >> y;
            cout << a.lower_bound(a.root, y)->data;
            break;

        case 6:
            cin >> y;
            cout << a.upper_bound(a.root, y)->data;
            break;

        case 7:
            cin >> x;
            cout << a.closestvalue(a.root, x);
            break;

        case 8:
            cin >> x;
            cout << a.klargest(x);
            break;

        case 9:
            cin >> x >> y;
            cout << a.range(a.root, x, y);
            break;

        default:
            break;
        }
    }
    return 0;
}