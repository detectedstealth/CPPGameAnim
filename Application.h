// Copyright Bruce Wade, 2024

#pragma once

class Application
{
private:
    Application(const Application&);
    Application& operator=(const Application&);
    
public:
    Application() = default;
    virtual ~Application() = default;
    virtual void Initialize() {}
    virtual void Update(float inDeltaTime) {}
    virtual void Render(float inAspectRatio) {}
    virtual void Shutdown() {}
};
