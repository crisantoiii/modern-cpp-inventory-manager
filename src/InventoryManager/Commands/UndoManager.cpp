#include "pch.h"

#include "UndoManager.h"

#include "ICommand.h"

void UndoManager::Execute(
    std::unique_ptr<ICommandx> command)
{
    command->Execute();

    m_redoStack.clear();

    m_undoStack.push_back(
        std::move(command));
}

bool UndoManager::CanUndo() const
{
    return !m_undoStack.empty();
}

bool UndoManager::CanRedo() const
{
    return !m_redoStack.empty();
}

void UndoManager::Undo()
{
}

void UndoManager::Redo()
{
}