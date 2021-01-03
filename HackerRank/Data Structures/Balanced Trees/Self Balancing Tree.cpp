
int nodeHt(node *root)
{
    if (root)
    {
        return 1 + max(nodeHt(root->left), nodeHt(root->right));
    }

    return -1;
}

void updateHt(node *root)
{
    if (root)
    {
        root->ht = 1 + max(nodeHt(root->left), nodeHt(root->right));
    }
}

node *rotateRight(node *root)
{
    node *tempRoot = root->left;
    node *tempLeft = tempRoot->right;

    tempRoot->right = root;
    root->left = tempLeft;

    updateHt(tempRoot);
    updateHt(root);

    return tempRoot;
}

node *rotateLeft(node *root)
{
    node *tempRoot = root->right;
    node *tempRight = tempRoot->left;

    tempRoot->left = root;
    root->right = tempRight;

    updateHt(tempRoot);
    updateHt(root);

    return tempRoot;
}

node *insert(node *root, int val)
{
    if (!root)
    {
        root = new node;

        root->ht = 0;
        root->val = val;
        root->left = root->right = NULL;

        return root;
    }

    if (val > root->val)
    {
        root->right = insert(root->right, val);
    }
    else if (val < root->val)
    {
        root->left = insert(root->left, val);
    }

    updateHt(root);

    int balanceFactor = nodeHt(root->left) - nodeHt(root->right);

    if (balanceFactor < -1 && val > root->right->val)
    {
        root = rotateLeft(root);
    }

    if (balanceFactor > 1 && val < root->left->val)
    {
        root = rotateRight(root);
    }

    if (balanceFactor < -1 && val < root->right->val)
    {
        root->right = rotateRight(root->right);
        root = rotateLeft(root);
    }

    if (balanceFactor > 1 && val > root->left->val)
    {
        root->left = rotateLeft(root->left);
        root = rotateRight(root);
    }

    return root;
}