#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string url;
    Node* prev;
    Node* next;
    
    Node(string _url) : url(_url), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
private:
    Node* current;

public:
    BrowserHistory(string homepage) {
        current = new Node(homepage);
    }
    
    void visit(string url) {
        Node* new_page = new Node(url);
        current->next = new_page;
        new_page->prev = current;
        current = new_page;
    }
    
    string back(int steps) {
        while (current->prev != nullptr && steps-- > 0) {
            current = current->prev;
        }
        return current->url;
    }
    
    string forward(int steps) {
        while (current->next != nullptr && steps-- > 0) {
            current = current->next;
        }
        return current->url;
    }
};

int main() {
    BrowserHistory browser("leetcode.com");
    browser.visit("google.com");
    browser.visit("facebook.com");
    browser.visit("youtube.com");
    cout << browser.back(1) << endl;     // return "facebook.com"
    cout << browser.back(1) << endl;     // return "google.com"
    cout << browser.forward(1) << endl;  // return "facebook.com"
    browser.visit("linkedin.com");
    cout << browser.forward(2) << endl;  // return "linkedin.com" because you cannot move forward any steps.
    cout << browser.back(2) << endl;     // return "google.com"
    cout << browser.back(7) << endl;     // return "leetcode.com"
    return 0;
}
