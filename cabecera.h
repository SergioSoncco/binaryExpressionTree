#include <string>

class Node{
  private:
    std::string info{""};
  public:
    Node* sonLeft{nullptr};
    Node* sonRight{nullptr};
    std::string getInfo();
    void setInfo(std::string info);
    bool isOperator();
};

class Multiplication{
  public:
    double calculateMult(double a, double b);
};

class Sum{
  public:
    double calculateSum(double a, double b);
};

class Core{
  private:
    Node head;
    Node last;
  public:
    void construct(std::vector<Node> exp);
    double calculate(double res, Node* node);
    void inorder(Node* node);
};

class Interface{
 public:
   void process(std::string exp, Core tree);
};
