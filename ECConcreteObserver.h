#ifndef EC_CONCRETE_OBSERVER_H
#define EC_CONCRETE_OBSERVER_H

#include "ECObserver.h"
#include "ECEditor.h"
#include "ECTextViewImp.h"

class RegKeyObserver : public ECObserver
{
public:
    RegKeyObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~RegKeyObserver(){}
    void Update();
    
private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};


class EnterObserver : public ECObserver
{
public:
    EnterObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~EnterObserver(){}
    void Update();

private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class TabObserver : public ECObserver
{
public:
    TabObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~TabObserver(){}
    void Update();

private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class RightKeyObserver : public ECObserver
{
public:
    RightKeyObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~RightKeyObserver(){}
    void Update();

private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class LeftKeyObserver : public ECObserver
{
public:
    LeftKeyObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~LeftKeyObserver(){}
    void Update();

private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};


class UpKeyObserver : public ECObserver
{
public:
    UpKeyObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~UpKeyObserver(){}
    void Update();

private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class DownKeyObserver : public ECObserver
{
public:
    DownKeyObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~DownKeyObserver(){}
    void Update();

private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class BackSpaceObserver : public ECObserver
{
public:
    BackSpaceObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~BackSpaceObserver(){}
    void Update();

private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class ModeObserver : public ECObserver
{
public:
    ModeObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~ModeObserver(){}
    void Update();
private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class UndoObserver : public ECObserver
{
public:
    UndoObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~UndoObserver(){}
    void Update();
private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

class RedoObserver : public ECObserver
{
public:
    RedoObserver(ECTextViewImp* vi, EditorController *ctrl);
    virtual ~RedoObserver(){}
    void Update();
private:
    ECTextViewImp *view;
    EditorController *editorCtrl;
};

#endif 
