#include "ECEditor.h"
#include "ECConcreteObserver.h"
#include <cctype>
#include <iostream>


TextInsertCmd::TextInsertCmd(EditorDocument* docIn, int posIn, char keyIn, int lineIn):doc(docIn), pos(posIn), key(keyIn), line(lineIn){}
void TextInsertCmd::Execute()
{
    doc->InsertChar(key, pos);
}

void TextInsertCmd::UnExecute()
{ 
}

TextDeleteCmd::TextDeleteCmd(EditorDocument* docIn, int posIn, int lineIn):doc(docIn), pos(posIn), line(lineIn){}

void TextDeleteCmd::Execute()
{
    std::string currStr = doc->GetMsg()[line];
    char charToBeDeleted;
    if (pos > 0)
    {
        charToBeDeleted = currStr[pos-1];
    }
    else if (pos == 0 && line > 0)
    {
        charToBeDeleted = '\0';
    }
    deletedChars.push_back(charToBeDeleted);
    doc->DeleteChar(pos, line);
}

void TextDeleteCmd::UnExecute(){ }



EditorController::EditorController(EditorDocument* editorIn, ECTextViewImp* viewIn):editorDoc(editorIn), view(viewIn), editMode(false)
{
    view->Attach(this);
    ModeObserver *currMode = new ModeObserver(view, this);
    RegKeyObserver * key = new RegKeyObserver(view, this);
    EnterObserver * enter = new EnterObserver(view, this);
    RightKeyObserver * rightKey = new RightKeyObserver(view, this);
    LeftKeyObserver * leftKey = new LeftKeyObserver(view, this);
    UpKeyObserver * upKey = new UpKeyObserver(view, this);
    DownKeyObserver * downKey = new DownKeyObserver(view, this);
    BackSpaceObserver *backSpace = new BackSpaceObserver(view, this);
    TabObserver * tab = new TabObserver(view, this);
    UndoObserver *undo = new UndoObserver(view, this);
    RedoObserver *redo = new RedoObserver(view, this);

    this->commandModeObservers.push_back(currMode);
    this->commandModeObservers.push_back(rightKey);
    this->commandModeObservers.push_back(leftKey);
    this->commandModeObservers.push_back(upKey);
    this->commandModeObservers.push_back(downKey);
    this->commandModeObservers.push_back(undo);
    this->commandModeObservers.push_back(redo);

    this->editorModeObservers.push_back(key);
    this->editorModeObservers.push_back(enter);
    this->editorModeObservers.push_back(rightKey);
    this->editorModeObservers.push_back(leftKey);
    this->editorModeObservers.push_back(upKey);
    this->editorModeObservers.push_back(downKey);
    this->editorModeObservers.push_back(backSpace);
    this->editorModeObservers.push_back(tab);


}
void EditorController::Update()
{   
    bool prevEditMode = GetEditMode();
    this->commandModeObservers[0]->Update();
    bool curEditMode = GetEditMode();
    if (curEditMode == false)
    {
        for (auto it = commandModeObservers.begin()+1; it < commandModeObservers.end(); it++)
        {   
            (*it)->Update();
        }
    }
    else if (curEditMode == true)
    {
        for(auto x : editorModeObservers)
        {
            if (prevEditMode == false)
            {
                break;
            }
            x->Update();
        }
    }
}

EditorController::~EditorController()
{
    for(auto x : editorModeObservers)
    {
        delete x;
    }
}


void EditorController::InsertText(char key)
{   
    pos = view->GetCursorX();
    int currLine = view->GetCursorY();
    TextInsertCmd * insertCmd = new TextInsertCmd(editorDoc, pos, key, currLine);
    commandHist.ExecuteCmd(insertCmd);
    if (pos >= view->GetColNumInView()-1)
    {
        view->SetCursorX(0);
        view->SetCursorY(currLine+1);
    }
    else
    {
        view->SetCursorX(pos+1);
    }
}

void EditorController::HandleEnter()
{
    pos = view->GetCursorX();
    int line = view->GetCursorY();
    std::vector<std::string > msg = editorDoc->GetMsg();
    if (msg.empty())
    {
        this->InsertText('\0');
        editorDoc->SetMsg(0, line, "");
    }
    else if (msg[line].empty())
    {
        editorDoc->SetMsg(0, line, "");
        editorDoc->DisplayFileElementAtEnter();
        this->InsertText('\0');
    }
    else if (msg[line].size() > 0 && msg[line].size() == pos)
    {
        editorDoc->SetMsg(0, line, "");
        editorDoc->DisplayFileElementAtEnter();
        this->InsertText('\0');
    }
    else if (msg[line].size() > 0 && msg[line].size() > pos)
    {
        editorDoc->SetMsg(pos, line, msg[line]);
        editorDoc->DisplayFileElementAtEnter();
        this->InsertText('\0');
    }
    // if (msg.size() > view->GetRowNumInView())
    // {
    //     editorDoc->DisplayFileElementAtEnter();
    // }
    if (msg.size() < view->GetColNumInView())
    {
        view->SetCursorX(0);
        view->SetCursorY(line+1);
    }
}

void EditorController::HandleTab()
{
    this->InsertText(' ');
}

void EditorController::HandleRightKey(int keyPos, int line)
{
    std::vector<std::string > msg = editorDoc->GetMsg();
    string currentLine = msg[line];
    if (keyPos >= 0 && keyPos < currentLine.size())
    {
        view->SetCursorX(keyPos+1);
    }
    else if (keyPos == currentLine.size()){}
}

void EditorController::HandleLeftKey(int keyPos, int line)
{
    std::vector<std::string > msg = editorDoc->GetMsg();
    string currentLine = msg[line];
    if (keyPos == 0){}
    else if (keyPos > 0 && keyPos <= currentLine.size()){
        view->SetCursorX(keyPos-1);
    }
}
void EditorController::HandleUpKey(int keyPos, int line)
{
    std::vector<std::string > msg = editorDoc->GetMsg();
    int numLine = msg.size();
    if (line == 0){}
    else if (line > 0 && line <= numLine)
    {
        if (msg[line-1].size() >= keyPos)
        {
            view->SetCursorY(line-1);
        }
        else if (msg[line-1].size() < keyPos)
        {
            view->SetCursorY(line-1);
            view->SetCursorX(msg[line-1].size());
        }
    }
}

void EditorController::HandleDownKey(int keyPos, int line)
{
    std::vector<std::string > msg = editorDoc->GetMsg();
    int numLine = msg.size();
    if (line >= 0 && line < numLine-1)
    {
        if (msg[line+1].size() >= keyPos)
        {
            view->SetCursorY(line+1);
        }
        else if (msg[line+1].size() < keyPos)
        {
            view->SetCursorY(line+1);
            view->SetCursorX(msg[line+1].size());
        }
    }
    if (line == numLine){}
}


void EditorController::DeleteText(int keyPos, int line){
    TextDeleteCmd* deleteCmd = new TextDeleteCmd(editorDoc, keyPos, line);
    commandHist.ExecuteCmd(deleteCmd);
}

void EditorController::HandleUndo()
{
    if (editorDoc->GetFileName() != "")
    {
        editorDoc->Undo();
    }
    // editorDoc->Undo();

}

void EditorController::HandleRedo()
{
    if (editorDoc->GetFileName() != "")
    {
        editorDoc->Redo();
    }
}

EditorDocument::EditorDocument(ECTextViewImp *viewIn, const std::string& fName):view(viewIn), docCtrl(this, viewIn), noLine(0), fileName(fName), myFile(fileName, std::ios::in | std::ios::out), lastLineCurrDisplayed(-1){
    if (myFile.is_open())
    {
        this->ReadFileElement(myFile);
        this->DisplayFileElement(view->GetRowNumInView(), view->GetColNumInView());
    }
}

EditorDocument::~EditorDocument()
{
    if (this->isFileOpen())
    {
        // this->SaveFile();
        this->myFile.close();
    }
    this->SaveFile();
    msg.clear();
}
void EditorDocument::InsertChar(char key, int pos)
{
    int line = view->GetCursorY();

    if (noLine == 0 && msg.empty())
    {
        this->msg.push_back("");
    }
    noLine = line;

    if (this->msg.size() == noLine)
    {
        this->msg.push_back("");
    }

    if (key == '\0')
    {
        // this->msg[noLine] = this->msg[noLine].insert(pos, 1, '');
    }
    else
    {
        this->msg[noLine] = this->msg[noLine].insert(pos, 1, key);
    }
    
    view->InitRows();
    for (auto x: msg)
    {
        view->AddRow(x);
    }
    this->KeywordColoring();
}
void EditorDocument::DeleteChar(int keyPos, int line)
{
    std::vector<std::string > message = this->GetMsg();
    std::string currentLine = message[line];
    if(keyPos > 0)
    {
        message[line] = currentLine.erase(keyPos-1, 1);
        view->SetCursorX(keyPos-1);
    }
    else if (keyPos == 0 && line > 0)
    {
        std::string prevLine = message[line-1];

        if (currentLine.size() == 0)
        {
            currentLine = "";
        }
        std::string newLine = prevLine + currentLine;
        if (prevLine.empty())
        {
            message[line-1] = currentLine;
        }
        else
        {
            message[line-1] = newLine;
        }

        message.erase(message.begin()+line);
        view->SetCursorX(prevLine.size());
        view->SetCursorY(line-1);
    }
    this->SetEntireMsg(message);
    this->DisplayNextFileElement();
    std::vector<std::string >  updatedMsg = this->GetMsg();
    view->InitRows();
    for (auto x: updatedMsg)
    {
        view->AddRow(x);
    }
}

void EditorDocument::Undo()
{
    // std::vector<std::string > message = this->GetMsg();
    // std::string currentLine = message[line];
    // message[line] = currentLine.erase(keyPos, 1);
    // if (keyPos == 0 && line > 0)
    // {
    //     message.erase(message.begin()+line);
    //     view->SetCursorX(message[line-1].size());
    //     view->SetCursorY(line-1);
    // }
    // if (keyPos > 0)
    // {
    //     view->SetCursorX(keyPos-1);
    // }
    // view->SetCursorX(0);
    // view->SetCursorY(0);
    // this->SetEntireMsg(message);
    // std::vector<std::string >  updatedMsg = this->GetMsg();
    // view->InitRows();
    // for (auto x: updatedMsg)
    // {
    //     view->AddRow(x);
    // }
    unsigned int line;
    int xCursorPos = 0;
    int yCursorPos = 0;

    if (this->fileElements.size() > 0)
    {
        for(line = 0; line < this->msg.size(); ++line)
        {
            if (this->msg[line] != this->fileElements[line])
            {
                if (this->msg[line].find(this->fileElements[line]) != std::string::npos)
                {
                    xCursorPos = this->fileElements[line].size();
                    yCursorPos = line;
                }
                else
                {
                    xCursorPos = this->fileElements[line-1].size();
                    yCursorPos = line-1;
                }
                break;
            }
        }

        this->lastLineCurrDisplayed = -1;
        this->msgToRedo = this->msg;
        this->msg.clear();
        int maxLine = view->GetRowNumInView();
        if (this->fileElements.size() <= maxLine)
        {
            for(auto x : this->fileElements)
            {
                this->msg.push_back(x);
                this->lastLineCurrDisplayed++;
            }
        }
        else
        {
            for(int i = 0; i < maxLine; i++)
            {
                this->msg.push_back(this->fileElements[i]);
            }
            this->lastLineCurrDisplayed = maxLine - 1;
        }
    }
    else
    {
        this->msgToRedo = this->msg;
        this->msg.clear();
    }
    
    std::vector<std::string >  updatedMsg = this->GetMsg();
    view->InitRows();
    for (auto x: updatedMsg)
    {
        view->AddRow(x);
    }
    view->SetCursorX(xCursorPos);
    view->SetCursorY(yCursorPos);
}

void EditorDocument::Redo()
{
    if (!this->msgToRedo.empty())
    {
        int line;
        int maxLine = this->msgToRedo.size();
        int xCursorPos = 0;
        int yCursorPos = 0;
        for (line = 0; line < maxLine; line++)
        {
            if (this->msgToRedo[line] != this->msg[line])
            {
                xCursorPos = this->msgToRedo[line].size();
                yCursorPos = line;
                break;
            }
        }
        this->msg.clear();
        this->lastLineCurrDisplayed = -1;
        for(auto x : this->msgToRedo)
        {
            this->msg.push_back(x);
            this->lastLineCurrDisplayed += 1;
        }
        std::vector<std::string >  updatedMsg = this->GetMsg();
        view->InitRows();
        for (auto x: updatedMsg)
        {
            view->AddRow(x);
        }
        view->SetCursorX(xCursorPos);
        view->SetCursorY(yCursorPos);
        this->msgToRedo.clear();
    }
}

std::vector<std::string> EditorDocument::GetMsg()
{
    return msg;
}

void EditorDocument::SetMsg(int index, int line, std::string message)
{
    int pos = view->GetCursorX();
    if (this->msg[line].size() == 0 && this->msg.size()-1 == line)
    {
        this->msg.push_back(message);
    }
    else if (this->msg[line].size() == 0 && this->msg.size()-1 > line)
    {
        this->msg.insert(this->msg.begin()+line+1, "");
    }
    else if (this->msg[line].size() > 0 && this->msg.size()-1 == line && this->msg[line].size() == pos)
    {
        this->msg.push_back(message);
    }
    else if (this->msg[line].size() > 0 && this->msg.size()-1 > line && this->msg[line].size() == pos)
    {
        this->msg.insert(this->msg.begin()+(line+1), "");
    }
    else if (this->msg[line].size() > 0 && this->msg.size()-1 == line && this->msg[line].size() > pos)
    {
        std::string firstHalf = message.substr(0, index);
        std::string secondHalf = message.substr(index);
        this->msg[line] = firstHalf;
        this->msg.push_back(secondHalf);
    }
    else if (this->msg[line].size() > 0 && this->msg.size()-1 > line && this->msg[line].size() > pos)
    {
        std::string firstHalf = message.substr(0, index);
        std::string secondHalf = message.substr(index);
        this->msg[line] = firstHalf;
        this->msg.insert(this->msg.begin()+line+1, secondHalf);
    }
}

void EditorDocument::SetEntireMsg(std::vector<std::string> message)
{
    this->msg = message;
}

void EditorDocument::ReadFileElement(std::fstream& fileName)
{
    if (fileName.is_open())
    {
        std::string line;
        while(std::getline(fileName, line))
        {
            fileElements.push_back(line);
        }
    }
}

void EditorDocument::DisplayFileElement(int numRow, int numCol)
{
    if(this->fileElements.size() > numRow)
    {
        for (int i = 0; i < numRow; i++)
        {
            this->msg.push_back(fileElements[i]);
        }
        lastLineCurrDisplayed = numRow-1;
    }
    else
    {
        for(auto x: fileElements)
        {
            this->msg.push_back(x);
            lastLineCurrDisplayed +=1;
        }
    }
    view->InitRows();
    for (auto x: this->msg)
    {
        view->AddRow(x);
    }
    this->KeywordColoring();
    view->Refresh();
    view->SetCursorX(0);
    view->SetCursorY(0);
}

void EditorDocument::DisplayNextFileElement()
{
    if (this->isFileOpen() && this->fileElements.size() > view->GetRowNumInView())
    {
        if (this->msg.size() < view->GetRowNumInView())
        {
            this->msg.push_back(this->fileElements[++lastLineCurrDisplayed]);
        }
    }
}

void EditorDocument::DisplayFileElementAtEnter()
{
    if (this->msg.size() > view->GetRowNumInView())
    {
        int maxLine = view->GetRowNumInView();
        int currLine = view->GetCursorY();
        this->msg.pop_back();
        if (currLine < maxLine-1)
        {
            --lastLineCurrDisplayed;
        }
    }
}


void EditorDocument::SaveFile()
{
    for (int i = this->msg.size(); i < fileElements.size(); ++i)
    {
        this->msg.push_back(this->fileElements[i]);
    }

    std::ofstream newFile(this->fileName);
    if (newFile.is_open())
    {
        std::vector<std::string> message = this->GetMsg();
        for (auto x: message)
        {
            newFile << x << endl;
        }
    }
    newFile.close();
}

void EditorDocument::KeywordColoring()
{
    std::string keyword = "keyword";
    if (this->fileName == "keywords.txt" && this->isFileOpen())
    {
        view->ClearColor();
        for (unsigned int i = 0; i < this->msg.size(); ++i)
        {
            std::string line = this->msg[i];
            size_t keyPos = line.find(keyword);
            if (keyPos != std::string::npos)
            {
                int endPos = keyPos + keyword.size() - 1;
                view->SetColor(i, keyPos, endPos, TEXT_COLOR_BLUE);
            }
        }
    }
}


