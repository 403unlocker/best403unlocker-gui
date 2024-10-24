#ifndef BEST403UNLOCKER_MAIN_FRAME_H_
#define BEST403UNLOCKER_MAIN_FRAME_H_

#include <wx/wx.h>

#include <thread>
#include <vector>

#include "downloads.h"

class MainFrame : public wxFrame {
 public:
  MainFrame();

 private:
  void CreateWidgets();
  void ConfigureLayout();
  void CreateEventBinds();

  void OnWindowClose(wxCloseEvent &event);
  void OnShow(wxShowEvent &event);
  void OnTestBtnClick(wxCommandEvent &event);
  void OnCopyBtnClick(wxCommandEvent &event);

  void TriggerDnsFetch();
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