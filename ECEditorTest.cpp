// Test code for editor
#include "ECTextViewImp.h"
#include "ECObserver.h"
#include "ECEditor.h"
#include <iostream>

using namespace  std;

int myCounter = 0;

// class EscapeObserver : public ECObserver
// {
// public:
//     EscapeObserver(ECTextViewImp *window)
//     {
//         wndTest = window;
//         wndTest->Attach(this);
//     }
//     virtual ~EscapeObserver(){wndTest->Detach(this);}

//     virtual void Update()
//     {
//         if (wndTest->GetPressedKey() == ESC)
//         {
//             wndTest->InitRows();
//             wndTest->ClearColor();
//             wndTest->AddRow("Sakhawat Hossain");
//             wndTest->SetColor(0,0,7, TEXT_COLOR_MAGENTA);
//             wndTest->SetColor(0,9,15, TEXT_COLOR_GREEN);
//             // wndTest->AddStatusRow("Editor", "For demo only", true);
//             wndTest->Show();
//         }
//     }

// private:
//     ECTextViewImp *wndTest;

// };

int main(int argc, char *argv[])
{
    //
    std::string fileName = "";
    ECTextViewImp wndTest;
    // wndTest.AddRow("CSE 3150");
    // wndTest.SetColor(0, 0, 0, TEXT_COLOR_RED);
    // wndTest.SetColor(0, 1, 1, TEXT_COLOR_GREEN);
    // wndTest.SetColor(0, 2, 2, TEXT_COLOR_BLUE);
    // wndTest.SetColor(0, 4, 4, TEXT_COLOR_RED);
    // wndTest.SetColor(0, 5, 5, TEXT_COLOR_GREEN);
    // wndTest.SetColor(0, 6, 6, TEXT_COLOR_BLUE);
    // wndTest.SetColor(0, 7, 7, TEXT_COLOR_MAGENTA);
    // wndTest.AddRow("This is a very simple demo of the ECTextViewImp functionalities.");
    // wndTest.SetColor(1, 10, 13, TEXT_COLOR_GREEN);
    // wndTest.AddRow("Press ctrl-q to quit");
    // wndTest.SetColor(2, 0, 1, TEXT_COLOR_GREEN);
    // wndTest.SetColor(2, 0, 1, TEXT_COLOR_DEF);

    // // add a status bar
    wndTest.AddStatusRow("Editor", "For demo only", true);
    // EditorDocument doc(&wndTest);

    if (argc > 1)
    {
        fileName = argv[1];
    }

    EditorDocument* doc = new EditorDocument(&wndTest, fileName);


    // EscapeObserver observe(&wndTest);
    wndTest.Show();    
    delete doc;
    return 0;
}

