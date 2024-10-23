#include "main_frame.h"

#include <wx/wx.h>

#include <thread>
#include <vector>

#include "config.h"
#include "downloads.h"

MainFrame::MainFrame() : wxFrame{nullptr, wxID_ANY, "Unlocker 403"} {
  CreateWidgets();
  ConfigureLayout();
  CreateEventBinds();
}

void MainFrame::CreateWidgets() {
  dnsResult = std::vector<DnsResult>{};
  fetchThread = nullptr;
  panel = new wxPanel{this, wxID_ANY};
  scrolledWindow = new wxScrolledWindow{panel, wxID_ANY};
  testBtn = new wxButton{panel, wxID_ANY, "Speed Test"};
  copyBtn = new wxButton{panel, wxID_ANY, "Copy Best DNS"};
  gauge = new wxGauge{panel, wxID_ANY, 0};
#ifdef _WIN32
  testBtn->SetSizeHints(wxSize{-1, 30});
  copyBtn->SetSizeHints(wxSize{-1, 30});
#endif
  gauge->Hide();
  copyBtn->Disable();
}

void MainFrame::ConfigureLayout() {
  outerSizer = new wxBoxSizer{wxVERTICAL};
  innerSizer = new wxBoxSizer{wxVERTICAL};

  outerSizer->Add(innerSizer,
                  wxSizerFlags{}.Expand().Proportion(1).Border(wxALL, 12));
  innerSizer->Add(scrolledWindow, wxSizerFlags{}.Expand().Proportion(1));
  innerSizer->AddSpacer(4);
  innerSizer->Add(gauge, wxSizerFlags{}.Expand());
  innerSizer->AddSpacer(6);
  innerSizer->Add(testBtn, wxSizerFlags{}.Expand());
  innerSizer->AddSpacer(4);
  innerSizer->Add(copyBtn, wxSizerFlags{}.Expand());

  panel->SetSizer(outerSizer);

  scrolledSizer = new wxBoxSizer{wxVERTICAL};
  scrolledWindow->SetSizer(scrolledSizer);
  scrolledWindow->SetScrollRate(5, 5);
}

void MainFrame::CreateEventBinds() {
  Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClose, this);
  //Bind(wxEVT_SHOW, &MainFrame::OnShow, this);
  testBtn->Bind(wxEVT_BUTTON, &MainFrame::OnTestBtnClick, this);
}

void MainFrame::OnWindowClose(wxCloseEvent &event) {
  if (fetchThread != nullptr && fetchThread->joinable()) {
    fetchThread->join();
    delete fetchThread;
    fetchThread = nullptr;
  }
  event.Skip();
}

void MainFrame::OnShow(wxShowEvent &event) { TriggerDnsFetch(); }

void MainFrame::OnTestBtnClick(wxCommandEvent &event) { TriggerDnsFetch(); }

void MainFrame::TriggerDnsFetch() {
  if (fetchThread != nullptr) return;

  gauge->Show();
  copyBtn->Disable();
  testBtn->Disable();
  innerSizer->Layout();
  fetchThread = new std::thread{&MainFrame::FetchDnsResult, this};
}

void MainFrame::FetchDnsResult() {
  dnsResult.clear();
  std::vector<std::string> dnsList = GetDNSConfig();

  CallAfter([this, dnsList]() {
    gauge->SetRange(dnsList.size());
    gauge->SetValue(0);
  });

  for (std::string dnsItem : dnsList) {
    dnsResult.push_back(DownloadTest(dnsItem));

    CallAfter([this]() {
      int value = gauge->GetValue();
      gauge->SetValue(value + 1);
    });
  }

  CallAfter([this]() {
    gauge->Hide();
    scrolledSizer->Clear(true);

    for (DnsResult result : dnsResult) {
      wxBoxSizer *sizer = new wxBoxSizer{wxHORIZONTAL};
      wxStaticText *dns =
          new wxStaticText{scrolledWindow, wxID_ANY, result.dns};
      wxStaticText *downloaded = new wxStaticText{
          scrolledWindow, wxID_ANY, std::to_string(result.downloaded) + " KB"};

      sizer->Add(dns);
      sizer->AddStretchSpacer();
      sizer->Add(downloaded);
      scrolledSizer->Add(sizer, wxSizerFlags{}.Expand());
      scrolledSizer->AddSpacer(8);
    }

    copyBtn->Enable();
    testBtn->Enable();
    innerSizer->Layout();
    scrolledSizer->Layout();

    if (fetchThread != nullptr && fetchThread->joinable()) {
      fetchThread->join();
      delete fetchThread;
      fetchThread = nullptr;
    }
  });
}
