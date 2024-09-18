#include "main.hpp"
#include "main_frame.hpp"
#include <wx/app.h>

wxIMPLEMENT_APP(Unlocker);

bool Unlocker::OnInit() {
   MainFrame *mainFrame = new MainFrame();
   mainFrame->SetWindowStyle(wxDEFAULT_FRAME_STYLE ^ wxMAXIMIZE_BOX ^ wxRESIZE_BORDER);
   mainFrame->SetClientSize(300, 500);
   mainFrame->Center();
   mainFrame->Show();
   return true;
}
