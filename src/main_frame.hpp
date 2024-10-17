#ifndef BEST403UNLOCKER_SRC_MAINFRAME_HPP
#define BEST403UNLOCKER_SRC_MAINFRAME_HPP

#include <wx/wx.h>

#include <thread>
#include <vector>

#include "downloads.hpp"

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