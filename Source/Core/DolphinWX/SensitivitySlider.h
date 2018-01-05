#pragma once

#include <wx/dialog.h>
#include <wx/textctrl.h>

class SensitivitySlider : public wxDialog
{
public:
  SensitivitySlider(wxWindow* parent, wxWindowID id = wxID_ANY,
    const wxString& title = _("Sensitivity Slider"), const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

  void OnOK(wxCommandEvent&);

private:
  wxTextCtrl* m_text_entry;
};
