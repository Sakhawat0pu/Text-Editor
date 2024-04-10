#ifndef EC_EDITOR_H
#define EC_EDITOR_H

#include "ECObserver.h"
#include "ECTextViewImp.h"
#include <vector>
#include "ECCommand.h"
#include <fstream>

class EditorDocument;

class TextInsertCmd : public ECCommand
{
public:
    TextInsertCmd(EditorDocument* docIn, int posIn, char keyIn, int lineIn);
    virtual ~TextInsertCmd(){}
    virtual void Execute();
    virtual void UnExecute();
private:
    EditorDocument* doc;
    int pos;
    char key;
    int line;
};

class TextDeleteCmd : public ECCommand
{
public:
    TextDeleteCmd(EditorDocument* doc, int posIn, int lineIn);
    virtual ~TextDeleteCmd(){}
    virtual void Execute();
    virtual void UnExecute();
private:
    EditorDocument* doc;
    int pos;
    int line;
    std::vector<char> deletedChars;
};

class EditorController : public ECObserver
{
public:
    EditorController(EditorDocument* editorIn, ECTextViewImp* viewIn);
    virtual ~EditorController();
    virtual void Update();
    virtual void InsertText(char key);
    virtual void SetEditMode(bool val){editMode = val;}
    virtual bool GetEditMode(){return editMode;}
    virtual void HandleEnter();
    virtual void HandleTab();
    virtual void HandleRightKey(int keyPos, int line);
    virtual void HandleLeftKey(int keyPos, int line);
    virtual void HandleUpKey(int keyPos, int line);
    virtual void HandleDownKey(int keyPos, int line);
    virtual void DeleteText(int keyPos, int line);
    virtual void HandleUndo();
    virtual void HandleRedo();
private:
    EditorDocument* editorDoc;
    ECTextViewImp* view;
    ECCommandHistory commandHist;
    std::vector<ECObserver *> editorModeObservers;
    std::vector<ECObserver *> commandModeObservers;
    int pos;
    bool editMode;
};

class EditorDocument
{
public:
    EditorDocument(ECTextViewImp *viewIn, const std::string& fName);
    virtual ~EditorDocument();
    virtual void InsertChar(char key, int pos);
    virtual void DeleteChar(int keyPos, int line);
    virtual std::vector<std::string> GetMsg();
    virtual void SetMsg(int index, int line, std::string message);
    virtual void SetEntireMsg(std::vector<std::string> message);
    virtual void ReadFileElement(std::fstream& fileName);
    virtual void DisplayFileElement(int numRow, int numCol);
    virtual bool isFileOpen(){return myFile.is_open();}
    virtual std::vector<std::string> GetFileElement(){return fileElements;}
    virtual std::string GetFileName(){return fileName;}
    virtual void DisplayNextFileElement();
    virtual void DisplayFileElementAtEnter();
    virtual void SaveFile();
    virtual void KeywordColoring();
    virtual void Undo();
    virtual void Redo();

private:
    ECTextViewImp* view;
    EditorController docCtrl;
    std::vector<std::string> msg;
    std::vector<std::string> msgToRedo;
    int noLine;
    std::string fileName;
    std::fstream myFile;
    std::vector<std::string> fileElements;
    int lastLineCurrDisplayed;
};



#endif 
