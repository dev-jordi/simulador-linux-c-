#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FileSystem.hpp"

TEST_SUITE("FileSystem") {

    TEST_CASE("Criação de arquivos e pastas") {
        FileSystem fs;

        fs.createFolder("docs");
        fs.createFile("readme.txt", "Olá mundo");

        auto current = fs.getCurrent();

        CHECK(current->findChild("docs") != nullptr);
        CHECK(current->findChild("readme.txt") != nullptr);
        CHECK(current->findChild("readme.txt")->content == "Olá mundo");
    }

    TEST_CASE("Mudança de diretório") {
        FileSystem fs;
        fs.createFolder("code");
        fs.changeDirectory("code");
        fs.createFile("main.cpp", "int main() { return 0; }");

        auto current = fs.getCurrent();

        CHECK(current->name == "code");
        CHECK(current->findChild("main.cpp") != nullptr);
        CHECK(current->findChild("main.cpp")->content == "int main() { return 0; }");
    }

    TEST_CASE("Remoção de arquivos") {
        FileSystem fs;
        fs.createFile("delete.me", "testando");
        fs.remove("delete.me");

        CHECK(fs.getCurrent()->findChild("delete.me") == nullptr);
    }

    TEST_CASE("Salvar e carregar estrutura do sistema de arquivos") {
        FileSystem fs;
        fs.createFolder("projects");
        fs.createFile("notes.txt", "anotações");

        fs.saveToFile("fs.txt");

        FileSystem fs2;
        fs2.loadFromFile("fs.txt");

        auto current = fs2.getCurrent();
        CHECK(current->findChild("projects") != nullptr);
        CHECK(current->findChild("notes.txt") != nullptr);
        CHECK(current->findChild("notes.txt")->content == "anotações");
    }

}
