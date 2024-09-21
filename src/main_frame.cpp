#include "main_frame.hpp"
#include "downloads.hpp"
#include <thread>
#include <vector>
#include <wx/wx.h>

MainFrame::MainFrame() : wxFrame{nullptr, wxID_ANY, "Unlocker 403"} {
   CreateWidgets();
   ConfigureLayout();
   CreateEventBinds();
}

void MainFrame::CreateWidgets() {
   dnsResult = std::vector<DnsResult>{};
   panel = new wxPanel{this, wxID_ANY};
   scrolledWindow = new wxScrolledWindow{panel, wxID_ANY};
   testBtn = new wxButton{panel, wxID_ANY, "Speed Test"};
   copyBtn = new wxButton{panel, wxID_ANY, "Copy Best DNS"};
   gauge = new wxGauge{panel, wxID_ANY, 0};
#ifdef _WIN32
   testBtn->SetSizeHints(wxSize{-1, 30});
   copyBtn->SetSizeHints(wxSize{-1, 30});
#endif
}

void MainFrame::ConfigureLayout() {
   outerSizer = new wxBoxSizer{wxVERTICAL};
   innerSizer = new wxBoxSizer{wxVERTICAL};

   outerSizer->Add(innerSizer, wxSizerFlags{}.Expand().Proportion(1).Border(wxALL, 12));
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

   copyBtn->Hide();
   testBtn->Enable(false);
   std::thread fetchThread{&MainFrame::FetchDnsResult, this};
   fetchThread.detach();
}


void MainFrame::CreateEventBinds() {
   testBtn->Bind(wxEVT_BUTTON, &MainFrame::OnTestBtnClick, this);
}

void MainFrame::OnTestBtnClick(wxCommandEvent &event) {
   gauge->Show();
   testBtn->Enable(false);
   innerSizer->Layout();
   std::thread fetchThread{&MainFrame::FetchDnsResult, this};
   fetchThread.detach();
}

void MainFrame::FetchDnsResult() {
   dnsResult.clear();
   std::vector<std::string> dnsList{"178.22.122.100", "78.157.42.100", "78.157.42.101"};

   CallAfter([this, dnsList]() {
      gauge->SetRange(dnsList.size());
      gauge->SetValue(1);
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
         wxStaticText *dns = new wxStaticText{scrolledWindow, wxID_ANY, result.dns};
         wxStaticText *downloaded =
             new wxStaticText{scrolledWindow, wxID_ANY, std::to_string(result.downloaded) + " KB"};

         sizer->Add(dns);
         sizer->AddStretchSpacer();
         sizer->Add(downloaded);
         scrolledSizer->Add(sizer, wxSizerFlags{}.Expand());
         scrolledSizer->AddSpacer(8);
      }

      copyBtn->Show();
      testBtn->Enable();
      innerSizer->Layout();
      scrolledSizer->Layout();
   });
}
