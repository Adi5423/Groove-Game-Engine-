#include "Engine.hpp"
#include "core/FileWriter.hpp" // Add this line

int main() {
    // Example usage
    Groove::Core::FileWriter::EnsureFilePath("Logs/sandbox_log.txt");
    Groove::Core::FileWriter::AppendText("Logs/sandbox_log.txt", "Sandbox started.\n");

    Engine::Init();
    Engine::Run();
    Engine::Shutdown();

    Groove::Core::FileWriter::AppendText("Logs/sandbox_log.txt", "Sandbox shutdown.\n");
    return 0;
}