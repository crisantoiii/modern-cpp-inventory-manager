#pragma once

#include <memory>
#include <vector>

class ICommandx;

class UndoManager
{
public:

    void Execute(
        std::unique_ptr<ICommandx> command);

    bool CanUndo() const;

    bool CanRedo() const;

    void Undo();

    void Redo();

private:

    std::vector<std::unique_ptr<ICommandx>> m_undoStack;

    std::vector<std::unique_ptr<ICommandx>> m_redoStack;
};