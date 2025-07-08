#pragma once
class Application
{
public:
    Application();
    ~Application();

    void run();

private:
    void initImGui();
    void loadAssets();
    void loadStates();
};