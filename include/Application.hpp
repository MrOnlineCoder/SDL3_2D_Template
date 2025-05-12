#ifndef APPLICATION_HPP
#define APPLICATION_HPP

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

#endif