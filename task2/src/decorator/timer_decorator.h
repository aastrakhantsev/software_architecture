#pragma once
#include "../command/command.h"
#include <chrono>
#include <iostream>

class TimerDecorator : public Command {
private:
    Command* wrapped_command;
public:
    TimerDecorator(Command* cmd) : wrapped_command(cmd) {}

    void execute() override {
        auto start = std::chrono::high_resolution_clock::now();
        wrapped_command->execute();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "[TimerDecorator] Execution time: " << elapsed.count() << " seconds\n";
    }
};
