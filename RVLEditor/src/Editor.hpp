#pragma once

#include "EditorState.hpp"

class Editor : public Rvl::App
{
public:
    Editor();
    ~Editor();

private:
    void Start() override;
    void Update() override;
    void Tick() override;

};

