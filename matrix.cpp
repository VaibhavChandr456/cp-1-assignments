#include <iostream>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    int **data;
    static int objectCount;

public:
    Matrix() {
        rows = 0;
        cols = 0;
        data = NULL;
        objectCount++;
    }

    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data = new int *[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
        objectCount++;
    }

    Matrix(const Matrix &other) {
        rows = other.rows;
        cols = other.cols;
        data = new int *[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        objectCount++;
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        objectCount--;
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    static int getObjectCount() {
        return objectCount;
    }

    void setElement(int i, int j, int value) {
        data[i][j] = value;
    }

    void input() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Element [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    Matrix add(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Addition not possible.\n";
            return Matrix();
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix multiply(const Matrix &other) const {
        if (cols != other.rows) {
            cout << "Multiplication not possible.\n";
            return Matrix();
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }
};

int Matrix::objectCount = 0;

int main() {
    int r1, c1, r2, c2;

    cout << "First matrix rows and columns: ";
    cin >> r1 >> c1;
    while (r1 < 1 || c1 < 1) {
        cout << "Rows and columns must be at least 1. Re-enter: ";
        cin >> r1 >> c1;
    }
    Matrix a(r1, c1);
    a.input();

    cout << "\nSecond matrix rows and columns: ";
    cin >> r2 >> c2;
    while (r2 < 1 || c2 < 1) {
        cout << "Rows and columns must be at least 1. Re-enter: ";
        cin >> r2 >> c2;
    }
    Matrix b(r2, c2);
    b.input();

    cout << "\nFirst Matrix:\n";
    a.display();
    cout << "\nSecond Matrix:\n";
    b.display();

    if (a.getRows() == b.getRows() && a.getCols() == b.getCols()) {
        Matrix sum = a.add(b);
        cout << "\nSum:\n";
        sum.display();
    } else {
        cout << "\nAddition is not possible.\n";
    }

    if (a.getCols() == b.getRows()) {
        Matrix product = a.multiply(b);
        cout << "\nProduct:\n";
        product.display();
    } else {
        cout << "\nMultiplication is not possible.\n";
    }

    Matrix t = a.transpose();
    cout << "\nTranspose of First Matrix:\n";
    t.display();

    Matrix copy(a);
    copy.setElement(0, 0, 999);
    cout << "\nOriginal First Matrix:\n";
    a.display();
    cout << "\nCopied Matrix (element [0][0] changed to 999):\n";
    copy.display();

    cout << "\nMatrix objects currently existing: " << Matrix::getObjectCount() << "\n";

    return 0;
}
