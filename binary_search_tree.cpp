#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Cấu trúc node của cây nhị phân tìm kiếm
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Hàm chèn node vào BST - O(log n) trung bình, O(n) xấu nhất
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Duyệt cây theo thứ tự (In-order traversal) - O(n)
void inorderTraversal(Node* root, vector<int>& result) {
    if (root == nullptr) return;

    inorderTraversal(root->left, result);
    result.push_back(root->data);
    inorderTraversal(root->right, result);
}

// Hàm sắp xếp sử dụng BST
// Độ phức tạp: O(n log n) trung bình, O(n²) xấu nhất
vector<int> bstSort(vector<int>& arr) {
    Node* root = nullptr;

    // Chèn tất cả phần tử vào BST - O(n log n)
    for (int value : arr) {
        root = insert(root, value);
    }

    // Duyệt cây theo thứ tự để lấy mảng đã sắp xếp - O(n)
    vector<int> sortedArray;
    inorderTraversal(root, sortedArray);

    return sortedArray;
}

// Hàm giải phóng bộ nhớ
void deleteTree(Node* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Hàm tìm kiếm trong BST - O(log n) trung bình
Node* search(Node* root, int value) {
    if (root == nullptr || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    }

    return search(root->right, value);
}

// Hàm tìm node có giá trị nhỏ nhất - O(log n)
Node* findMin(Node* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Hàm xóa node - O(log n) trung bình
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Trường hợp 1: Node không có con hoặc có 1 con
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Trường hợp 2: Node có 2 con
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Hàm in cây theo dạng cây
void printTree(Node* root, int space = 0, int indent = 4) {
    if (root == nullptr) return;

    space += indent;
    printTree(root->right, space);

    cout << endl;
    for (int i = indent; i < space; i++) {
        cout << " ";
    }
    cout << root->data << endl;

    printTree(root->left, space);
}

int main() {
    cout << "=== CHƯƠNG TRÌNH SẮP XẾP VÀ QUẢN LÝ CÂY NHỊ PHÂN TÌM KIẾM ===" << endl;
    cout << "Độ phức tạp: Insert/Search/Delete O(log n), Duyệt cây O(n)" << endl << endl;

    // Ví dụ 1: Sắp xếp mảng bằng BST
    vector<int> arr = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 65};

    cout << "Mảng ban đầu: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    vector<int> sortedArr = bstSort(arr);

    cout << "Mảng đã sắp xếp: ";
    for (int val : sortedArr) {
        cout << val << " ";
    }
    cout << endl << endl;

    // Ví dụ 2: Thao tác với BST
    Node* root = nullptr;
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};

    cout << "Xây dựng cây BST với các giá trị: ";
    for (int val : values) {
        cout << val << " ";
        root = insert(root, val);
    }
    cout << endl << endl;

    cout << "Cấu trúc cây (xoay 90 độ):" << endl;
    printTree(root);
    cout << endl;

    // Tìm kiếm
    int searchValue = 40;
    Node* found = search(root, searchValue);
    cout << "Tìm kiếm giá trị " << searchValue << ": ";
    cout << (found ? "Tìm thấy!" : "Không tìm thấy!") << endl;

    searchValue = 100;
    found = search(root, searchValue);
    cout << "Tìm kiếm giá trị " << searchValue << ": ";
    cout << (found ? "Tìm thấy!" : "Không tìm thấy!") << endl << endl;

    // Duyệt cây
    vector<int> traversal;
    inorderTraversal(root, traversal);
    cout << "Duyệt cây theo thứ tự (In-order): ";
    for (int val : traversal) {
        cout << val << " ";
    }
    cout << endl << endl;

    // Xóa node
    int deleteValue = 30;
    cout << "Xóa node có giá trị " << deleteValue << endl;
    root = deleteNode(root, deleteValue);

    cout << "Cây sau khi xóa:" << endl;
    printTree(root);
    cout << endl;

    traversal.clear();
    inorderTraversal(root, traversal);
    cout << "Duyệt cây sau khi xóa: ";
    for (int val : traversal) {
        cout << val << " ";
    }
    cout << endl << endl;

    // Giải phóng bộ nhớ
    deleteTree(root);

    cout << "=== PHÂN TÍCH ĐỘ PHỨC TẠP ===" << endl;
    cout << "Insert (Chèn):     O(log n) trung bình, O(n) xấu nhất" << endl;
    cout << "Search (Tìm kiếm): O(log n) trung bình, O(n) xấu nhất" << endl;
    cout << "Delete (Xóa):      O(log n) trung bình, O(n) xấu nhất" << endl;
    cout << "Traversal (Duyệt): O(n)" << endl;
    cout << "BST Sort:          O(n log n) trung bình, O(n²) xấu nhất" << endl;

    return 0;
}
