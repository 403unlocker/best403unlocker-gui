#ifndef BEST403UNLOCKER_SRC_MAINFRAME_HPP
#define BEST403UNLOCKER_SRC_MAINFRAME_HPP

#include "downloads.hpp"
#include <thread>
#include <vector>
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
   MainFrame();

  private:
   void CreateWidgets();
   void CreateEventBinds();
   void ConfigureLayout();

   void OnTestBtnClick(wxCommandEvent &event);

   void FetchDnsResult();

   wxPanel *panel;
   wxButton *testBtn;
   wxButton *copyBtn;
   wxScrolledWindow *scrolledWindow;
   wxBoxSizer *outerSizer;
   wxBoxSizer *innerSizer;
   wxBoxSizer *scrolledSizer;
   wxGauge *gauge;
   std::vector<DnsResult> dnsResult;
   std::thread *fetchThread;
};

#endif