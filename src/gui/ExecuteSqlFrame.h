/*
  The contents of this file are subject to the Initial Developer's Public
  License Version 1.0 (the "License"); you may not use this file except in
  compliance with the License. You may obtain a copy of the License here:
  http://www.flamerobin.org/license.html.

  Software distributed under the License is distributed on an "AS IS"
  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
  License for the specific language governing rights and limitations under
  the License.

  The Original Code is FlameRobin (TM).

  The Initial Developer of the Original Code is Milan Babuskov.

  Portions created by the original developer
  are Copyright (C) 2004 Milan Babuskov.

  All Rights Reserved.

  Contributor(s): Nando Dessena
*/

// -*- C++ -*- generated by wxGlade 0.2.2 on Fri Jun 04 12:31:56 2004

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/stc/stc.h>

#ifndef EXECUTESQLFRAME_H
#define EXECUTESQLFRAME_H

#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/dnd.h>

#include "ibpp.h"
#include "metadata/database.h"
#include "observer.h"
#include "myDataGrid.h"
#include "BaseFrame.h"

class ExecuteSqlFrame: public BaseFrame, public YxObserver {
public:
	void setDatabase(YDatabase *db);

    // begin wxGlade: ExecuteSqlFrame::ids
    enum {
        ID_button_new = 101,
        ID_button_load = 102,
        ID_button_save = 103,
        ID_button_execute = 104,
        ID_button_commit = 105,
        ID_button_rollback = 106,
		ID_button_toggle = 107,
		ID_button_wrap = 108,
        ID_grid_data = 200,
		ID_stc_sql = 201
    };
    // end wxGlade

	void executeAllStatements(bool autoExecute = false);
	void setSql(wxString sql);

    ExecuteSqlFrame(wxWindow* parent, int id, wxString title, const wxPoint& pos=wxDefaultPosition,
		const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

private:
	std::vector<std::string> executedStatementsM;

	typedef enum { ttNormal, ttSql, ttError } TextType;
	void log(wxString s, TextType type = ttNormal);		// write messages to textbox
	void SplitScreen();
	YDatabase *databaseM;

	bool execute(std::string sql);
	bool inTransactionM;
	IBPP::Transaction transactionM;
	IBPP::Statement statementM;
	void InTransaction(bool started);		// changes controls (enable/disable)
	void commitTransaction();

	void setupEditor();		// Setup the Scintilla editor
	void OnSqlEditUpdateUI(wxStyledTextEvent &event);

	void OnSqlEditCharAdded(wxStyledTextEvent &event);		// autocomplete stuff
	wxString keywordsM;		// text used for autocomplete
	void setKeywords();

	// events
	void OnClose(wxCloseEvent& event);
    void OnKeyDown(wxKeyEvent &event);
    void OnButtonNewClick(wxCommandEvent &event);
    void OnButtonLoadClick(wxCommandEvent &event);
    void OnButtonSaveClick(wxCommandEvent &event);
    void OnButtonExecuteClick(wxCommandEvent &event);
    void OnButtonCommitClick(wxCommandEvent &event);
    void OnButtonRollbackClick(wxCommandEvent &event);
    void OnButtonToggleClick(wxCommandEvent &event);
    void OnButtonWrapClick(wxCommandEvent &event);

    // begin wxGlade: ExecuteSqlFrame::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
	void removeObservedObject(YxSubject *object);
	void update();
	bool closeWhenTransactionDoneM;

    wxPanel* panel_contents;

    wxBitmapButton* button_new;
    wxBitmapButton* button_load;
    wxBitmapButton* button_save;
    wxButton* button_execute;
    wxButton* button_commit;
    wxButton* button_rollback;
    wxButton* button_toggle;
    wxButton* button_wrap;

    wxSplitterWindow* splitter_window_1;
    wxPanel* panel_splitter_top;
    wxPanel* panel_splitter_bottom;
    wxStyledTextCtrl* styled_text_ctrl_sql;
    wxNotebook* notebook_1;
    wxPanel* notebook_pane_1;
    wxPanel* notebook_pane_2;
    myDataGrid* grid_data;
	wxStyledTextCtrl* styled_text_ctrl_stats;

    wxStatusBar* statusbar_1;

	virtual const std::string getName() const;
	virtual void doReadConfigSettings(const std::string& prefix);
	virtual void doWriteConfigSettings(const std::string& prefix) const;
	virtual const wxRect getDefaultRect() const;

    DECLARE_EVENT_TABLE()
};

class DnDText : public wxTextDropTarget
{
public:
    DnDText(wxStyledTextCtrl *owner, YDatabase *db) { ownerM = owner; databaseM = db; }
    virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& text);

private:
    wxStyledTextCtrl *ownerM;
	YDatabase *databaseM;
};

#endif // EXECUTESQLFRAME_H
