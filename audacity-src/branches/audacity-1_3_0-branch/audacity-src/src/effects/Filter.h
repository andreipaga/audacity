/**********************************************************************

  Audacity: A Digital Audio Editor

  Filter.h

  Dominic Mazzoni

**********************************************************************/

#include "Effect.h"

#ifndef __AUDACITY_EFFECT_FILTER__
#define __AUDACITY_EFFECT_FILTER__

#include <wx/dialog.h>
#include <wx/intl.h>
#include <wx/panel.h>

class wxString;
class wxBitmap;
class wxSizer;

class Envelope;
class WaveTrack;

class EffectFilter: public Effect {

public:
   
   EffectFilter();
   virtual ~EffectFilter();
   
   virtual wxString GetEffectName() {
      return wxString(_("FFT Filter..."));
   }
   
   virtual wxString GetEffectAction() {
      return wxString(_("Performing FFT Filter"));
   }
   
   virtual bool PromptUser();
   virtual bool TransferParameters( Shuttle & shuttle );
   
   virtual bool Process();

   virtual void Preview();
   
private:
   bool ProcessOne(int count, WaveTrack * track,
                   longSampleCount start, sampleCount len);

   void Filter(sampleCount len,
               float *buffer);
   
   Envelope *mEnvelope;

   int windowSize;
   float *filterFunc;
   
};

class FilterPanel: public wxPanel
{
public:
   FilterPanel( wxWindow *parent, wxWindowID id, 
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize);

   void OnMouseEvent(wxMouseEvent & event);
   void OnPaint(wxPaintEvent & event);

   Envelope *mEnvelope;

private:

   wxBitmap *mBitmap;
   wxRect mEnvRect;
   int mWidth;
   int mHeight;

   DECLARE_EVENT_TABLE()
};

// WDR: class declarations

//----------------------------------------------------------------------------
// FilterDialog
//----------------------------------------------------------------------------

// Declare window functions

class FilterDialog: public wxDialog
{
public:
   wxSizer *MakeFilterDialog( wxWindow *parent, bool call_fit = TRUE,
                              bool set_sizer = TRUE );

   // constructors and destructors
   FilterDialog( EffectFilter *effect,
                 wxWindow *parent, wxWindowID id, const wxString &title,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = wxDEFAULT_DIALOG_STYLE );
   
   // WDR: method declarations for FilterDialog
   virtual bool Validate();
   virtual bool TransferDataToWindow();
   virtual bool TransferDataFromWindow();
   
   void SetEnvelope(Envelope *env);
   
private:
   // WDR: member variable declarations for FilterDialog
   
private:
   // WDR: handler declarations for FilterDialog
   void OnClear( wxCommandEvent &event );
   void OnOk( wxCommandEvent &event );
   void OnCancel( wxCommandEvent &event );
   void OnPreview( wxCommandEvent &event );
   void OnSize( wxSizeEvent &event );

   EffectFilter *mEffect;
   
private:
   DECLARE_EVENT_TABLE()
};

#endif

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: 4c5f5a1f-fc80-4f97-893c-27799134a63c

