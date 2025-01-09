/*
** EPITECH PROJECT, 2025
** leVraiRtype
** File description:
** genModule
*/

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

void help() {
    std::cout << "./newModule moduleName" << std::endl;
    std::cout << "\tmoduleName: the name of the module to be created." << std::endl;
}

int addToRootCmake(const std::string &moduleName) {
    std::ofstream fichier("CMakeLists.txt", std::ios::app);

    if (fichier) {
        fichier << "add_subdirectory(" + moduleName + ")" << std::endl;
        std::cout << "Modules CmakeLists modified successfuly!" << std::endl;
        return 0;
    } else {
        std::cerr << "Error while openeing modules CMakeLists.txt" << std::endl;
        return 1;
    }
}

int genCmake(std::string moduleName) {
    std::ofstream cmake("CMakeLists.txt");

    if (!cmake.is_open()) {
        std::cout << "Failed to generate modules CmakeLists.";
        return 1;
    }
    moduleName = "module" + moduleName;
    cmake << "cmake_minimum_required(VERSION 3.26)" << std::endl << std::endl;
    cmake << "project(" + moduleName + " VERSION 1.0)" << std::endl << std::endl;
    cmake << "set(SRC" << std::endl << "\t" << (moduleName.substr(6)) << ".cpp" << std::endl << ")" << std::endl << std::endl;
    cmake << "find_package(asio REQUIRED CONFIG)" << std::endl << std::endl;
    cmake << "add_library(" << moduleName << " SHARED " << "${SRC})" << std::endl << std::endl;
    cmake << "target_include_directories(" << moduleName << " PUBLIC ${GLOBAL_INCLUDE_DIRS})" << std::endl << std::endl;
    cmake << "add_custom_command(" << std::endl
        << "\tTARGET " << moduleName << " POST_BUILD" << std::endl
        << "\tCOMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:" << moduleName
        << "> ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin" << std::endl
        << ")" << std::endl << std::endl;
    cmake << "target_link_libraries(" << moduleName << " PRIVATE asio)" << std::endl << std::endl; 
    return 0;
}

void addEpitechHeader(std::ofstream &file, const std::string &moduleName) {
    file << "/*" << std::endl << "** EPITECH PROJECT, 2025" << std::endl
        << "** RTYPE" << std::endl << "** FILE description:" << std::endl << "** "
        << "Module " << moduleName << std::endl << "*/" << std::endl << std::endl;
}

int genCpp(const std::string &moduleName) {
    std::ofstream file(moduleName + ".cpp");

    if (!file.is_open()) {
        std::cout << "Failed to generate " + moduleName + ".cpp.";
        return 1;
    }
    addEpitechHeader(file, moduleName);
    file << "#include \"" << moduleName << ".hpp\"" << std::endl << std::endl;
    //TO DO: Add declspec for windows compilation
    file << "extern \"C\" zef::Imodule *entryPoint() {" << std::endl
        << "\treturn new " << moduleName << ";" << std::endl << "}" << std::endl;

    return 0;
}

int genHpp(const std::string &moduleName) {
    std::ofstream file(moduleName + ".hpp");

    if (!file.is_open()) {
        std::cout << "Failed to generate " + moduleName + ".hpp.";
        return 1;
    }
    addEpitechHeader(file, moduleName);
    file << "#include <iostream>" << std::endl << std::endl;
    file << "#include \"AModule.hpp\"" << std::endl << "#include \"Engine.hpp\"" << std::endl << std::endl;
    
    file << "class ExampleComp1 {" << std::endl << "\tpublic:" << std::endl;
    file << "\t\tExampleComp1(int a, float b) : _a(a), _b {}" << std::endl << std::endl;
    file << "\t\tint _a;" << std::endl << "\t\tfloat _b;" << std::endl << "};" << std::endl << std::endl;

    file << "class ExampleComp2 {" << std::endl << "\tpublic:" << std::endl;
    file << "\t\tExampleComp2(float a, char b) : _a(a), _b {}" << std::endl << std::endl;
    file << "\t\float _a;" << std::endl << "\t\tchar _b;" << std::endl << "};" << std::endl << std::endl;

    file 

    file << "class " << moduleName << " : public zef::AModule<" << std::endl
        << "\tzef::Component<ExampleComp1, int, float>, //Name of component 1 and there attributes types in the same order than the constructor" << std::endl
        << "\tzef::Component<ExampleComp2, float, char>, //Name of component 2 and there attributes types in the same order than the constructor" << std::endl
        << "> {" << std::endl << "public:" << std::endl << "\t\t" << moduleName << "() : AMdoule {}"
        << "\t\t~" << moduleName << "() = default;" << std::endl << std::endl;
}

int generateModule(const std::string &moduleName) {
    std::filesystem::path dir = moduleName;
    try {
        if (std::filesystem::create_directory(dir)) {
            std::cout << "Directory " + moduleName + " created successfully!" << std::endl;
        } else {
            std::cout << "Failed to create directory. It might already exist." << std::endl;
            return 1;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    if (addToRootCmake(moduleName)) return 1;
    std::filesystem::current_path(std::filesystem::current_path().string() + "/" + moduleName);
    if (genCmake(moduleName)) return 1;
    if (genCpp(moduleName)) return 1;
    if (genHpp(moduleName)) return 1;

    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        help();
        return 1;
    }
    std::string ar2(argv[1]);
    if (argc == 2 && (ar2 == "-h" || ar2 == "-help"
    || ar2 == "h" || ar2 == "help")) {
        help();
        return 0;
    }

    std::filesystem::current_path(std::filesystem::current_path().string() + "/../engine/modules");
    return generateModule(ar2);

}
