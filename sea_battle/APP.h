#pragma once

class APP {
private:
    bool _exit_requested;

    void print() const;

public:
    APP();

    int run();
};