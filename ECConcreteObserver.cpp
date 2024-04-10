#include "ECConcreteObserver.h"
#include "ECEditor.h"
#include "ECTextViewImp.h"

RegKeyObserver::RegKeyObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl) {}
void RegKeyObserver::Update()
{
    int pressedKey = view->GetPressedKey();
    if (pressedKey != ENTER && pressedKey != ARROW_DOWN && pressedKey != ARROW_UP && pressedKey != ARROW_RIGHT && pressedKey != ARROW_LEFT && pressedKey != BACKSPACE && pressedKey != ESC && pressedKey != CTRL_A && pressedKey != CTRL_Z && pressedKey != CTRL_Y && pressedKey != TAB)
    {
        char keyPressed = static_cast<char> (pressedKey);
        editorCtrl->InsertText(keyPressed);
    }
}


EnterObserver::EnterObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}
void EnterObserver::Update()
{
    if (view->GetPressedKey() == ENTER)
    {
        editorCtrl->HandleEnter();
    }
}

TabObserver::TabObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}
void TabObserver::Update()
{
    if (view->GetPressedKey() == TAB)
    {
        for (int i = 0; i < 4; i++)
        {
        editorCtrl->HandleTab();
        }
    }
}




RightKeyObserver::RightKeyObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}
void RightKeyObserver::Update()
{
    if (view->GetPressedKey() == ARROW_RIGHT)
    {
        int xCord = view->GetCursorX();
        int yCord = view->GetCursorY();
        editorCtrl->HandleRightKey(xCord, yCord);
    }
}


LeftKeyObserver::LeftKeyObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}
void LeftKeyObserver::Update()
{
    if (view->GetPressedKey() == ARROW_LEFT)
    {
        int xCord = view->GetCursorX();
        int yCord = view->GetCursorY();
        editorCtrl->HandleLeftKey(xCord, yCord);
    }
}




UpKeyObserver::UpKeyObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi),editorCtrl(ctrl){}
void UpKeyObserver::Update()
{
    if (view->GetPressedKey() == ARROW_UP)
    {
        int xCord = view->GetCursorX();
        int yCord = view->GetCursorY();
        editorCtrl->HandleUpKey(xCord, yCord);
    }
}


DownKeyObserver::DownKeyObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi),editorCtrl(ctrl){}
void DownKeyObserver::Update()
{
    if (view->GetPressedKey() == ARROW_DOWN)
    {
        int xCord = view->GetCursorX();
        int yCord = view->GetCursorY();
        editorCtrl->HandleDownKey(xCord, yCord);
    }
}


BackSpaceObserver::BackSpaceObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}
void BackSpaceObserver::Update()
{
    if (view->GetPressedKey() == BACKSPACE)
    {
        int xCord = view->GetCursorX();
        int yCord = view->GetCursorY();
        // editorCtrl->HandleBackSpace(xCord, yCord);
        editorCtrl->DeleteText(xCord, yCord);
    }
}

ModeObserver::ModeObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}

void ModeObserver::Update()
{
    if (view->GetPressedKey() == 'i')
    {
        editorCtrl->SetEditMode(true);
    }
    else if (view->GetPressedKey() == ESC || view->GetPressedKey() == CTRL_A)
    {
        editorCtrl->SetEditMode(false);
    }
}

UndoObserver::UndoObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}

void UndoObserver::Update()
{
    if (view->GetPressedKey() == CTRL_Z)
    {
        editorCtrl->HandleUndo();
    }
}

RedoObserver::RedoObserver(ECTextViewImp* vi, EditorController *ctrl):view(vi), editorCtrl(ctrl){}

void RedoObserver::Update()
{
    if (view->GetPressedKey() == CTRL_Y)
    {
        editorCtrl->HandleRedo();
    }
}