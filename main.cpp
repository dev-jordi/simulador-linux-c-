#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>
#include <sstream>

class Node {
public:
    std::string name;
    bool isFile;
    std::string content;
    std::vector<std::shared_ptr<Node>> children;

    Node(const std::string& name, bool isFile = false) : name(name), isFile(isFile) {}

    std::shared_ptr<Node> findChild(const std::string& name) {
        for (auto& child : children) {
            if (child->name == name) return child;
        }
        return nullptr;
    }
};

class FileSystem {
private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> current;

    void saveNode(std::ofstream& file, const std::shared_ptr<Node>& node, int depth) {
        file << std::string(depth, '-') << (node->isFile ? "F " : "D ") << node->name << "\n";
        if (node->isFile) file << node->content << "\n";
        for (auto& child : node->children) {
            saveNode(file, child, depth + 1);
        }
    }

    std::shared_ptr<Node> loadNode(std::ifstream& file, int depth) {
        std::string line;
        std::getline(file, line);
        if (line.empty()) return nullptr;

        int currentDepth = line.find_first_not_of('-');
        if (currentDepth != depth) return nullptr;

        bool isFile = (line[currentDepth] == 'F');
        std::string name = line.substr(currentDepth + 2);

        auto node = std::make_shared<Node>(name, isFile);
        if (isFile) {
            std::getline(file, node->content);
        } else {
            while (true) {
                auto child = loadNode(file, depth + 1);
                if (!child) break;
                node->children.push_back(child);
            }
        }
        return node;
    }

public:
    FileSystem() {
        root = std::make_shared<Node>("root");
        current = root;
    }

    void createFile(const std::string& name, const std::string& content) {
        if (current->findChild(name)) {
            std::cout << "Arquivo já existe!\n";
            return;
        }
        auto file = std::make_shared<Node>(name, true);
        file->content = content;
        current->children.push_back(file);
    }

    void createFolder(const std::string& name) {
        if (current->findChild(name)) {
            std::cout << "Pasta já existe!\n";
            return;
        }
        current->children.push_back(std::make_shared<Node>(name));
    }

    void listContents() const {
        for (auto& child : current->children) {
            std::cout << (child->isFile ? "[F] " : "[D] ") << child->name << "\n";
        }
    }

    void changeDirectory(const std::string& name) {
        if (name == "..") {
            if (current != root) current = root; // Voltar ao root para simplificar
        } else {
            auto next = current->findChild(name);
            if (!next || next->isFile) {
                std::cout << "Diretório não encontrado!\n";
            } else {
                current = next;
            }
        }
    }

    void remove(const std::string& name) {
        auto it = std::remove_if(current->children.begin(), current->children.end(),
            [&](const std::shared_ptr<Node>& child) { return child->name == name; });
        if (it != current->children.end()) {
            current->children.erase(it, current->children.end());
            std::cout << "Removido com sucesso!\n";
        } else {
            std::cout << "Arquivo ou pasta não encontrado!\n";
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Erro ao salvar!\n";
            return;
        }
        saveNode(file, root, 0);
        std::cout << "Sistema salvo em " << filename << "\n";
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Erro ao carregar!\n";
            return;
        }
        root = loadNode(file, 0);
        current = root;
        std::cout << "Sistema carregado de " << filename << "\n";
    }
};

int main()
{
    FileSystem fs;
    std::string input;

    std::cout << "=== Shell do Sistema de Arquivos Virtual ===\n";
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string cmd;
        iss >> cmd;

        if (cmd == "touch")
        {
            std::string name, content;
            iss >> name;
            std::cout << "Conteúdo: ";
            std::getline(std::cin, content);
            fs.createFile(name, content);
        }
        else if (cmd == "mkdir")
        {
            std::string name;
            iss >> name;
            fs.createFolder(name);
        }
        else if (cmd == "ls")
        {
            fs.listContents();
        }
        else if (cmd == "cd")
        {
            std::string name;
            iss >> name;
            fs.changeDirectory(name);
        }
        else if (cmd == "rm")
        {
            std::string name;
            iss >> name;
            fs.remove(name);
        }
        else if (cmd == "save")
        {
            fs.saveToFile("filesystem.dat");
        }
        else if (cmd == "load")
        {
            fs.loadFromFile("filesystem.dat");
        }
        else if (cmd == "exit" || cmd == "quit")
        {
            std::cout << "Tchau!\n";
            break;
        }
        else if (cmd.empty())
        {
            continue; // ignore empty lines
        }
        else
        {
            std::cout << "Comando desconhecido: " << cmd << "\n";
        }
    }

    return 0;
}
