#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
using namespace std;

// ======================= TEMPLATE STACK =======================
template <typename T>
class Stack {
private:
    T* data;
    int topIndex;
    int capacity;
public:
    Stack(int size = 200) {
        capacity = size;
        data = new T[capacity];
        topIndex = -1;
    }

    ~Stack() { delete[] data; }

    bool isEmpty() const { return topIndex == -1; }

    void push(const T& val) {
        data[++topIndex] = val;
    }

    void pop() {
        if (!isEmpty()) topIndex--;
    }

    T top() const {
        return data[topIndex];
    }
};

// ======================= CLASS BieuThuc =======================
class BieuThuc {
private:
    string infix, postfix, prefix;

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    int uuTien(char c) {
        if (c == '+' || c == '-') return 1;
        if (c == '*' || c == '/') return 2;
        if (c == '^') return 3;
        return 0;
    }

    bool isNumber(const string& s) {
        return isdigit(s[0]) || ((s[0] == '+' || s[0] == '-') && s.size() > 1 && isdigit(s[1]));
        // l� s? 1, -1, +1
    }

public:
    bool check() {
        Stack<char> s;
        int last = 1;  
        // 0 = s?, 1 = to�n t?, 2 = '(', 3 = ')'

        for (int i = 0; i < infix.size(); i++) {
            char c = infix[i];
            if (isspace(c)) continue;

            // (
            if (c == '(') {
                s.push(c);
                last = 2;
            }

            // ()
            else if (c == ')') {
                if (s.isEmpty() || s.top() != '(') return false;
                s.pop();
                if (last == 1 || last == 2) return false;  // kh�ng c� g? trong ngo?c
                last = 3;
            }

            // 6 6
            else if (isdigit(c) || c == '.') {
                if (last == 3 || last == 0) return false; // kh�ng th? c� 2 s? li?n
                while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) i++;
                i--; 
                last = 0;
            }

            // 4 +
            else if (isOperator(c)) {
                // Tr�?ng h?p d?u �m/d��ng �?ng �?u ho?c sau '(' ? l� ph?n c?a s?
                if ((c == '+' || c == '-') && (i == 0 || last == 1 || last == 2)) {
                    // n?u sau �� kh�ng c� s? th? sai
                    int j = i + 1;
                    while (j < infix.size() && isspace(infix[j])) j++;
                    if (j >= infix.size() || (!isdigit(infix[j]) && infix[j] != '.')) return false;
                    continue;
                }

                if (last == 1 || last == 2 || i == 0) return false;
                last = 1;
            }

            // k� t? l?
            else {
                return false;
            
            }
        }

        if (!s.isEmpty()) return false;        // c?n ngo?c ch�a ��ng
        if (last == 1 || last == 2) return false; // k?t th�c b?ng to�n t? ho?c '('

        return true;
    }


    bool nhap() {
        cout << "Nhap bieu thuc trung to: ";
        getline(cin, infix);
        if(!check()){
            cout<<"Bieu thuc sai";
            return false;
        }
        return true;
    }

    bool kiemTraNgoac() {
        Stack<char> s;
        for (char c : infix) {
            if (c == '(') s.push(c);
            else if (c == ')') {
                if (s.isEmpty()) return false;
                s.pop();
            }
        }
        return s.isEmpty();
    }

    // =================== CHUY?N TRUNG T? ? H?U T? ===================
    void toPostfix() {
        postfix = "";
        Stack<char> s;
        int last = 1; 
        // 0: s? 
        // 1: to�n t? 
        // 2: '(' 
        // 3: ')'

        for (int i = 0; i < infix.size(); i++) {
            char c = infix[i];

            // 1. D?u c�ch
            if (isspace(c)) continue;

            // 2. x? l? s? �m ho?c d��ng �?ng �?u / sau to�n t? / sau '(' 
            if ((c == '+' || c == '-') && (i == 0 || last == 1 || last == 2)) {
                string num;
                num += c;
                i++;
                while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
                    num += infix[i];
                    i++;
                }
                postfix += num + " ";
                i--;
                last = 0;
            }
            // 3. x? l? s? b?nh th�?ng 
            else if (isdigit(c) || c == '.') {
                string num;
                while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
                    num += infix[i];
                    i++;
                }
                postfix += num + " ";
                i--;
                last = 0;
            }
            // 4. ngo?c m? 
            else if (c == '(') {
                s.push(c);
                last = 2;
            }
            // 5. ngo?c ��ng 
            else if (c == ')') {
                while (!s.isEmpty() && s.top() != '(') {
                    postfix += s.top();
                    postfix += ' ';
                    s.pop();
                }
                if (!s.isEmpty()) s.pop(); // b? '('
                last = 3;
            }
            // 6. to�n t? 
            else if (isOperator(c)) {
                while (!s.isEmpty() &&  ((uuTien(s.top()) > uuTien(c)) || (uuTien(s.top()) == uuTien(c) && c != '^'))) {
                    postfix += s.top();
                    postfix += ' ';
                    s.pop();
                }
                s.push(c);
                last = 1;
            }
        }

        while (!s.isEmpty()) {
            postfix += s.top();
            postfix += ' ';
            s.pop();
        }

        // cout << "Bieu thuc hau to: " << postfix << endl;
    }
    string getpos(){return postfix;}

    // ===== TRUNG T? ? TI?N T? =====
    void toPrefix() {
        string rev = "";
        for (int i = infix.size() - 1; i >= 0; i--) {
            if (infix[i] == '(') rev += ')';
            else if (infix[i] == ')') rev += '(';
            else rev += infix[i];
        }

        string tmp = infix;
        infix = rev;
        toPostfix();

        // �?o th? t? c�c token thay v? �?o chu?i
        stringstream ss(postfix);
        string token;
        Stack<string> tokens;
        while (ss >> token) tokens.push(token);

        prefix = "";
        while (!tokens.isEmpty()) {
            prefix += tokens.top() + " ";
            tokens.pop();
        }

        infix = tmp;
    }

    string getpre(){return prefix;}

    // =================== T�NH GI� TR? H?U T? ===================
    void tinhGiaTriHauTo() {
        if (postfix.empty()) {
            cout << "Chua co bieu thuc hau to! Hay chon muc 3 truoc.\n";
            return;
        }

        Stack<double> s;
        stringstream ss(postfix);
        string c;

        while (ss >> c) {
            if (isNumber(c)) {
                s.push(stod(c));
            } else if (isOperator(c[0])) {
                double b = s.top(); s.pop();
                double a = s.top(); s.pop();

                double kq = 0;
                switch (c[0]) {
                    case '+': kq = a + b; break;
                    case '-': kq = a - b; break;
                    case '*': kq = a * b; break;
                    case '/': kq = a / b; break;
                    case '^': kq = pow(a, b); break;
                }
                s.push(kq);
            }
        }

        cout << "Gia tri bieu thuc: " << s.top() << endl;
    }
};

// ======================= MAIN MENU =======================
int main() {
    BieuThuc bt;
    int chon;

    do {
        cout << "\n=== CHUONG TRINH XU LY BIEU THUC ===\n";
        cout << "1. Nhap bieu thuc trung to\n";
        cout << "2. Kiem tra dau ngoac\n";
        cout << "3. Chuyen sang hau to\n";
        cout << "4. Chuyen sang tien to\n";
        cout << "5. Tinh gia tri bieu thuc\n";
        cout << "6. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();

        switch (chon) {
            case 1: if(!bt.nhap()) return 0; break;
            case 2: cout << (bt.kiemTraNgoac() ? "Hop le\n" : "Khong hop le\n"); break;
            case 3: bt.toPostfix(); cout << "Bieu thuc hau to: " << bt.getpos() << endl; break;
            case 4: bt.toPrefix(); cout << "Bieu thuc tien to: " << bt.getpre() << endl; break;
            case 5: bt.tinhGiaTriHauTo(); break;
            case 6: cout << "Thoat chuong trinh.\n"; return 0;
            default: cout << "Lua chon khong hop le.\n";
        }
    } while (chon != 6);

    return 0;
}

