class CommandProcessor {
public:
    void execute(const std::string& command) {
        if (command == "clear") {
            consoleLog.clear();
        }
        else {
            consoleLog.addLog("Unknown command: " + command);
        }
    }
};

CommandProcessor commandProcessor;

void renderScriptingConsole() {
    static char inputBuf[256] = "";

    ImGui::Begin("Scripting Console");

    if (ImGui::InputText("Input", inputBuf, IM_ARRAYSIZE(inputBuf), ImGuiInputTextFlags_EnterReturnsTrue)) {
        commandProcessor.execute(inputBuf);
        inputBuf[0] = '\0';
    }

    ImGui::End();
}