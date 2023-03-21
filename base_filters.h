#pragma once

class BaseFilter {
public:
    virtual void Apply() = 0;
};

class BlurFilter : public BaseFilter {
public:
    void Apply() override;
};

class CropFilter : public BaseFilter {
public:
    void Apply() override;
};