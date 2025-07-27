#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

// Representa um nó de diretório ou arquivo
class Node {
public:
    std::string name;
    bool isFile;
    std::string content;
    std::vector<std::shared_ptr<Node>> children;

    Node(const std::string& name, bool isFile = false);

    std::shared_ptr<Node> findChild(const std::string& name);
};

// Sistema de arquivos virtual com diretórios e arquivos em árvore
class FileSystem {
private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> current;

    void saveNode(std::ofstream& file, const std::shared_ptr<Node>& node, int depth);
    std::shared_ptr<Node> loadNode(std::ifstream& file, int depth);

public:
    FileSystem();

    void createFile(const std::string& name, const std::string& content);
    void createFolder(const std::string& name);
    void listContents() const;
    void changeDirectory(const std::string& name);
    void remove(const std::string& name);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    std::shared_ptr<Node> getCurrent() const;  // útil para testes
};

#endif // FILESYSTEM_HPP
