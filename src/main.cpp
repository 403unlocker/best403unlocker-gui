#include "main.h"

#include <wx/app.h>
#include <wx/image.h>

#include "main_frame.h"

wxIMPLEMENT_APP(Unlocker);

bool Unlocker::OnInit() {
  wxImage::AddHandler(new wxXPMHandler{});
  wxIcon icon{"./assets/icon.xpm", wxBITMAP_TYPE_XPM};

  MainFrame *mainFrame = new MainFrame();
  mainFrame->SetWindowStyle(wxDEFAULT_FRAME_STYLE ^ wxMAXIMIZE_BOX ^
                            wxRESIZE_BORDER);
  mainFrame->SetClientSize(300, 500);
  mainFrame->SetIcon(icon);
  mainFrame->Center();
  mainFrame->Show();
  return true;
}
