#pragma once

class ICommandx
{
public:

    virtual ~ICommandx() = default;

    virtual void Execute() = 0;

    virtual void Undo() = 0;
};